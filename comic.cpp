#include "comic.h"

Comic::Comic(const std::string_view title, const std::string_view author, int issue, int quantity)
  : _author(author), _issue(issue), Document(title, quantity) {
}

Comic::~Comic() {}

document_type Comic::get_document_type() { return DOC_COMIC; }

void Comic::print(){
    std::cout << "Comic, title: " << _title << 
            ", author: " << _author << 
            ", issue: " << _issue << 
            ", quantity: " << _quantity << "\n";
}

void Comic::update_author(const std::string_view new_author) {
  _author = new_author;
}

void Comic::update_issue(int new_issue) {
  _issue = new_issue;
}

const std::string_view Comic::get_author() const {
  return _author;
}

int Comic::get_issue() const {
  return _issue;
}
