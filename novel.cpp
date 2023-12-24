#include "novel.h"

Novel::Novel(const std::string_view title, const std::string_view author, int quantity)
  : _author(author), Document(title, quantity) {
}

Novel::~Novel() {}

document_type Novel::get_document_type() { return DOC_NOVEL; }

void Novel::print(){
    std::cout << "Novel, title: " << _title <<
            ", author: " << _author << 
            ", quantity: " << _quantity << "\n";
}

void Novel::update_author(const std::string_view new_author){
    _author = new_author;
}

const std::string_view Novel::get_author() const{
    return _author;
}