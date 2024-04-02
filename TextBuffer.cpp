#include "TextBuffer.hpp"

  //EFFECTS: Creates a new editor with an empty text buffer, with the
  //         current position at row 1 and column 0.
  TextBuffer::TextBuffer(): row(1), column(0), index(0) {
    cursor = data.begin();
  }

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor one position forward and updates the
  //          row and column, unless the cursor is already at the end
  //          of the buffer, in which case this does nothing. Returns
  //          true if the position changed, or false if it did not
  //          (i.e. if the cursor was already at the end of the
  //          buffer).
  bool TextBuffer::forward() {
    if(!is_at_end()){
        if(*cursor == '\n'){
            row++;
            column = 0;
        }
        else{
            column++;
        }
        cursor++;
        index++;
        return true;
    }
    return false;
  }

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor one position backward and updates the
  //          row and column, unless the cursor is already at the
  //          start of the buffer, in which case this does nothing.
  //          Returns true if the position changed, or false if it did
  //          not (i.e. if the cursor was already at the start of the
  //          buffer).
  //HINT: Implement and use the private compute_column() member
  //      function to compute the column when moving left from the
  //      beginning of a line to the end of the previous one.
  bool TextBuffer::backward() {
    if (cursor != data.begin()) {
        if (column == 0) {
            row--;
            cursor--;
            index--;
            column = compute_column();
        } else {
            cursor--;
            index--;
            column--;
        }
        return true;
    }
    return false;
  }

  //

  //MODIFIES: *this
  //EFFECTS:  Inserts a character in the buffer at the cursor and
  //          updates the current row and column.
  void TextBuffer::insert(char c) { 
  cursor = data.insert(cursor, c);
    index++;
    if (c == '\n') {
      row++;
      cursor++;
      index++;
      column = 0;
    } else {
        column++;
        cursor++;
        index++;
    }
  }

  //MODIFIES: *this
  //EFFECTS:  Deletes the character from the buffer that is at cursor.
  //          Does nothing if the cursor is at the end of the buffer.
  //          Returns true if a character was removed, or false if not
  //          (i.e. if the cursor was at the end of the buffer).
  bool TextBuffer::remove() {
    if (!is_at_end()) {
        cursor = data.erase(cursor);
        return true;
    }
    return false;
  }

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the start of the current row (column
  //          0).
  void TextBuffer::move_to_row_start() {
    while (column != 0){ 
        backward(); 
    }
  }

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the end of the current row (the
  //          newline character that ends the row, or the end of the
  //          buffer if the row is the last one in the buffer).
  void TextBuffer::move_to_row_end() {
    while (cursor != data.end() && *cursor != '\n') {
        ++cursor;
        ++index;
        ++column;
    }
  }


  //REQUIRES: new_column >= 0
  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the given column in the current row,
  //          or to the end of the row if the row does not have that
  //          many columns.

  void TextBuffer::move_to_column(int new_column) {
    if (new_column >= 0) {
        while (column > new_column && cursor != data.begin()) {
            --cursor;
            --index;
            --column;
        }
        while (column < new_column && cursor != data.end() && *cursor != '\n') {
            ++cursor;
            ++index;
            ++column;
        }
    }
  }


  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the previous row, retaining the
  //          current column if possible. If the previous row is
  //          shorter than the current column, moves to the end of the
  //          previous row (the newline character that ends the row).
  //          Does nothing if the cursor is already in the first row.
  //          Returns true if the position changed, or false if it did
  //          not (i.e. if the cursor was already in the first row).
  bool TextBuffer::up() {
	if(row > 1){
		const int current_column = column;
		move_to_row_start();
		backward();
		move_to_column(current_column);
		return true;
	}
	return false;
  }

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the next row, retaining the current
  //          column if possible. If the next row is shorter than the
  //          current column, moves to the end of the next row (the
  //          newline character that ends the row, or the end of the
  //          buffer if it is the last row). Does nothing if the
  //          cursor is already in the last row.
  //          Returns true if the position changed, or false if it did
  //          not (i.e. if the cursor was already in the last row).
  bool TextBuffer::down() {
    int original = column;
    move_to_row_end();
    if(cursor != data.end()){ 
        forward();
        move_to_column(original);
    }
    return false;
  }

  //EFFECTS:  Returns whether the cursor is at the end of the buffer.
  bool TextBuffer::is_at_end() const {
    if(cursor == data.end()){
        return true;
    }
    return false;
  }

  //REQUIRES: the cursor is not at the end of the buffer
  //EFFECTS:  Returns the character at the current cursor
  char TextBuffer::data_at_cursor() const {
    if (cursor != data.end()) {
        return *cursor;
    }
    return '\0';
  }

  int TextBuffer::get_row() const {
    return row;
  }

  //EFFECTS:  Returns the column of the character at the current
  //          cursor.
  int TextBuffer::get_column() const {
    return column;
  }

  //EFFECTS:  Returns the index of the character at the current cursor
  //          with respect to the entire contents. If the cursor is at
  //          the end of the buffer, returns size() as the index.
  //HINT: Traversing a list is really slow. Instead, use the index
  //      private member variable to keep track of the index and
  //      update it as necessary.
  int TextBuffer::get_index() const {
    if(cursor == data.end()){ 
        return data.size(); 
    }
    return index;
  }

  //EFFECTS:  Returns the number of characters in the buffer.
  int TextBuffer::size() const {
    return data.size();
  }

  //EFFECTS:  Returns the contents of the text buffer as a string.
  //HINT: Implement this using the string constructor that takes a
  //      begin and end iterator:
  //        return std::string(data.begin(), data.end());
  std::string TextBuffer::stringify() const {
    return std::string(data.begin(), data.end());
  }

  //EFFECTS: Computes the column of the cursor within the current
  //         row.
  //NOTE: This does not assume that the "column" member variable has
  //      a correct value (i.e. the second INVARIANT can be broken).
  int TextBuffer::compute_column() const {
     int col = 0;
    Iterator it = cursor;
    while (it != data.begin() && *(--it) != '\n') {
        ++col;
    }
    return col;
  }