#include <stdio.h>
#include <iostream>
#include <string>
#include "TextBuffer.hpp"

using namespace std;

#include "TextBuffer.hpp"

// Constructor
TextBuffer::TextBuffer() {
    cursor = data.end();
    row = 1;
    column = 0;
    index = 0;
}

// Moves the cursor one position forward
bool TextBuffer::forward() {
    if (cursor == data.end()) {
        return false;
    }
    if (data_at_cursor() == '\n') {
        row++;
        column = 0;
    } else {
        column++;
    }
    index++;
    cursor++;
    return true;
}

// Moves the cursor one position backward
bool TextBuffer::backward() {
    if (cursor == data.begin()) {
        return false;
    }
    cursor--;
    index--;
    if (*cursor == '\n') {
        row--;
        column = compute_column();
    } else {
        column--;
    }
    return true;
}

// Inserts a character at the cursor
void TextBuffer::insert(char c) {
    data.insert(cursor, c);
    if (c == '\n') {
        row++;
        column = 0;
    } else {
        column++;
    }
    index++;
}

// Removes the character at the cursor
bool TextBuffer::remove() {
    if (cursor == data.end()) {
        return false;
    }
    cursor = data.erase(cursor);
    // Update row, column, and index as needed
    // ...
    return true;
}

// Moves the cursor to the start of the current row
void TextBuffer::move_to_row_start() {
    while (column != 0){
      cursor--;
      column--;
      index--;
    }
}

// Moves the cursor to the end of the current row
void TextBuffer::move_to_row_end() {
    while (cursor != data.end() && data_at_cursor()!='\n'){
      ++cursor;
      ++column;
      ++index;
    }
}

// Moves the cursor to the specified column in the current row
void TextBuffer::move_to_column(int new_column) {
    move_to_row_start();
    while (column<=new_column && cursor != data.end() && data_at_cursor() != '\n'){
      forward();
    }
}

// Moves the cursor up to the previous row
bool TextBuffer::up() {
    int goalCol = column;
    if(row == 1){
      return false;
    }
    else{
      move_to_row_start();
      backward();
      if (column >= goalCol){
        move_to_row_end();
      }
      else{
        while (column > goalCol){
          backward();
        }
      }
      return true;
    }
    return true;  // Or false, depending on the implementation
}

// Moves the cursor down to the next row
bool TextBuffer::down() {
    int colGoal = column;
    move_to_row_end();
    if (cursor == data.end()){
      return false;
    }
    else{
      forward();
      move_to_row_end();
      if (column > colGoal){
        //cursor doesn't move
      }
      else{
        move_to_row_start();
        while (column < colGoal){
          forward();
        }
      
      }
      return true;
    }
    return true;  // Or false, depending on the implementation
}

// Checks if the cursor is at the end of the text
bool TextBuffer::is_at_end() const {
    return cursor == data.end();
}

// Returns the character at the cursor
char TextBuffer::data_at_cursor() const {
    if (cursor != data.end()) {
        return *cursor;
    }
    return '\0';  // Or another suitable default
}

// Returns the current row
int TextBuffer::get_row() const {
    return row;
}

// Returns the current column
int TextBuffer::get_column() const {
    return column;
}

// Returns the index of the current cursor position
int TextBuffer::get_index() const {
    return index;
}

// Returns the size of the text buffer
int TextBuffer::size() const {
    return static_cast<int>(data.size());
}

// Returns the contents of the text buffer as a string
std::string TextBuffer::stringify() const {
    return std::string(data.begin(), data.end());
}

// Computes the column of the cursor within the current row
int TextBuffer::compute_column() const {
    int column = 0;
    std::list<char>::iterator it = cursor;
    while (it != data.begin() && *(--it) != '\n') {
        ++column;
    }
    return column;
}