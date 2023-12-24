#include "document.h"

Document::Document(const std::string_view title, int quantity) : _title(title), _quantity(quantity) {}

Document::~Document() {}

// Copy Constructor
Document::Document(const Document& document) : _title(document._title), _quantity(document._quantity) {}

Document& Document::operator=(const Document& document) {
  if (this != &document) {
    _title = document._title;
    _quantity = document._quantity;
  }
  return *this;
}

// Move Constructor
Document::Document(Document&& document) noexcept
  : _title(std::move(document._title)), _quantity(document._quantity) {
  document._quantity = 0;
}

Document& Document::operator=(Document&& document) noexcept {
  if (this != &document) {
    _title = std::move(document._title);
    _quantity = document._quantity;
    document._quantity = 0;
  }
  return *this;
}

void Document::update_title(const std::string_view new_title) {
  _title = new_title;
}

void Document::update_quantity(int new_quantity) {
  _quantity = new_quantity;
}

const std::string_view Document::get_title() const {
  return _title;
}

int Document::get_quantity() const {
  return _quantity;
}

bool Document::borrow_document() {
  if (_quantity > 0) {
    update_quantity(_quantity - 1);
    return true;
  }
  return false;
}

void Document::return_document() {
  update_quantity(get_quantity() + 1);
}
