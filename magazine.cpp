#include "magazine.h"

Magazine::Magazine(const std::string_view title, int issue, int quantity)
  : _issue(issue), Document(title, quantity) {
}

Magazine::~Magazine() {}

document_type Magazine::get_document_type() { return DOC_MAGAZINE; }

void Magazine::print(){
    std::cout << "Magazine, title: " << get_title() <<
            ", issue: " << _issue << 
            ", quantity: " << _quantity << "\n";
}

void Magazine::update_issue(int new_issue) {
  _issue = new_issue;
}

int Magazine::get_issue() const {
  return _issue;
}
