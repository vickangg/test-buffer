#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 Project 4
 */

#include <__config>
#include <iostream>
#include <iterator> //std::bidirectional_iterator_tag
#include <cassert>  //assert


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //EFFECTS:  returns true if the list is empty
  bool empty() const {
    if(first == nullptr){
      return true;
    }
    return false;
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow. Instead, keep track of the size
  //         with a private member variable. That's how std::list does it.
  int size() const{
    return num_size;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front(){
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back(){
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum){
    Node *first_push = new Node;
    first_push->datum = datum;
    num_size++;
    if (empty()){
      first = first_push;
      last = first_push;
      first_push->prev = nullptr;
      first_push->next = nullptr;
    } else {
      first->prev = first_push;
      first_push->next = first;
      first = first_push;
      first_push->prev = nullptr;
    }
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum){
    Node *last_push = new Node;
    last_push->datum = datum;
    num_size++;
    if(empty()){
      first = last_push;
      last = last_push;
      last_push->prev = nullptr;
      last_push->next = nullptr;
    }
    else{
      last->next = last_push;
      last_push->prev = last;
      last = last_push;
      last_push->next = nullptr;
    }
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front(){
    Node* first_pop = first;
    if (first == last){
      delete first_pop;
      num_size--;
      first = nullptr;
      last = nullptr;
    }
    else{
      first = first->next;
      first->prev = nullptr;
      delete first_pop;
      num_size--;
    }
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back(){
    Node* last_pop = last;
    if(first == last){
      delete last_pop;
      num_size--;
      first = nullptr;
      last = nullptr;
    }
    else{
      last = last->prev;
      last->next = nullptr;
      delete last_pop;
      num_size--;
    }
   
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear(){
    int numIterations = num_size;
    for (int i = 0; i < numIterations; i++){
      pop_front();
    }
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you should omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists.

  List(): num_size(0), first(nullptr), last(nullptr) {}
  ~List(){
    clear();
  }


private:
  int num_size;
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other){
    Node *copy = other.first;
    while (copy->next != nullptr){
      push_back(copy->datum);
      copy = copy->next;
    }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
public:
  ////////////////////////////////////////
  class Iterator {
  public:
    //OVERVIEW: Iterator interface to List

    // Add a default constructor here. The default constructor must set both
    // pointer members to null pointers.

    Iterator() : list_ptr(nullptr), node_ptr(nullptr) {}

    // Add custom implementations of the destructor, copy constructor, and
    // overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you should omit them. A user
    // of the class must be able to copy, assign, and destroy Iterators.

    Iterator& operator=(const Iterator& other) {
      list_ptr = other.list_ptr;
      node_ptr = other.node_ptr;
      return *this;
    }

    ~Iterator() {}    

    // Your iterator should implement the following public operators:
    // *, ++ (both prefix and postfix), == and !=.
    // Equality comparisons must satisfy the following rules:
    // - two default-constructed iterators must compare equal
    // - a default-constructed iterator must compare unequal to an
    //   iterator obtained from a list, even if it is the end iterator
    // - two iterators to the same location in the same list must
    //   compare equal
    // - two iterators to different locations in the same list must
    //   compare unequal
    // - comparing iterators obtained from different lists results in
    //   undefined behavior
    //   - Your implementation can handle this however you like, but
    //     don't assume any particular behavior in your test cases --
    //     comparing iterators from different lists essentially
    //     violates the REQURES clause.
    // Note: comparing both the list and node pointers should be
    // sufficient to meet these requirements.



    // Type aliases required to work with STL algorithms. Do not modify these.
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is either dereferenceable or an end Iterator
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a reference to this Iterator
    Iterator& operator--() { // prefix -- (e.g. --it)
      assert(list_ptr);
      if (node_ptr) {
        node_ptr = node_ptr->prev;
      } else { // decrementing an end Iterator moves it to the last element
        node_ptr = list_ptr->last;
      }
      return *this;
    }

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is either dereferenceable or an end Iterator
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a copy of the original Iterator
    Iterator operator--(int /*dummy*/) { // postfix -- (e.g. it--)
      Iterator copy = *this;
      operator--();
      return copy;
    }

    // REQUIRES: Iterator is dereferenceable
    // EFFECTS: returns the underlying element by pointer
    // NOTE: T must be a class type to use the syntax it->. If T has a
    //       member variable f, then it->f accesses f on the
    //       underlying T element.
    T* operator->() const {
      return &operator*();
    }

    T& operator*() const {
      assert(node_ptr != nullptr);
      return node_ptr->datum;
    }

    Iterator& operator++() { // prefix ++
      assert(node_ptr != nullptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    Iterator operator++(int /*dummy*/) { // postfix ++
      Iterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const Iterator& other) const {
      return node_ptr == other.node_ptr && list_ptr == other.list_ptr;
    }

    bool operator!=(const Iterator& other) const {
      return !(*this == other);
    }

  private:
    const List *list_ptr; //pointer to the List associated with this Iterator
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here


    // add any friend declarations here

    friend class List;


    // construct an Iterator at a specific position in the given List
    //Iterator(const List *lp, Node *np);

    Iterator(const List *lp, Node *np) : list_ptr(lp), node_ptr(np) {}

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const{
    return Iterator(this, first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const{
    return Iterator(this, nullptr);
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container.
  //         Returns An iterator pointing to the element that followed the
  //         element erased by the function call
  Iterator erase(Iterator i){
  Node *temp = i.node_ptr;
  Iterator single = Iterator(this, temp->next);

  if (temp == first) {
    pop_front();
  } else if (temp == last) {
    pop_back();
  } else {
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    delete temp;
    num_size--;
  }

  return single;

}

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: Inserts datum before the element at the specified position.
  //         Returns an iterator to the the newly inserted element.
  Iterator insert(Iterator i, const T &datum){
    if (i == begin()) {
        push_front(datum);
        return begin();
    }
    else if (i == end()) {
        push_back(datum);
        return Iterator(this, last);
    }
    else {
        Node* element = new Node;  
        element->datum = datum;    
        Node* temp = i.node_ptr;
        element->next = temp;
        element->prev = temp->prev;
        
        if (temp->prev) {
            temp->prev->next = element;
        }
        temp->prev = element;
        
        num_size++;
        return Iterator(this, element);
    }
}

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.