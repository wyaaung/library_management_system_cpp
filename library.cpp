#include "library.h"

Library::Library() {}

Library::~Library() {}

bool Library::add_document(document_type t, const std::string_view title, const std::string_view author, int issue, int quantity) {
  std::unique_ptr<Document> d;

  switch (t) {
    case DOC_NOVEL:
      d = std::make_unique<Novel>(title, author, quantity);
      break;

    case DOC_COMIC:
      d = std::make_unique<Comic>(title, author, issue, quantity);
      break;

    case DOC_MAGAZINE:
      d = std::make_unique<Magazine>(title, issue, quantity);
      break;

    default:
      return false;
  }

  return add_document(std::move(d));
}

bool Library::add_document(std::unique_ptr<Document> d) {
  if (search_document(d->get_title()) != nullptr)
    return false;

  _docs.push_back(std::move(d));
  return true;
}

int Library::add_document(Document* d) {
    std::unique_ptr<Document> docPtr(d);
    return add_document(std::move(docPtr));
}

bool Library::delete_document(const std::string_view title) {
  // Find the document by title
  auto it = std::find_if(_docs.begin(), _docs.end(),
                         [&title](const std::unique_ptr<Document>& doc) { return doc->get_title() == title; });
  if (it != _docs.end()) {
    _docs.erase(it); // Remove the document if found
    return true; // Return true on successful deletion
  }

  return false; // Return false if the document is not found
}

int Library::count_document_of_type(document_type t) {
  // Count and return the number of documents of the specified type
  return std::count_if(_docs.begin(), _docs.end(),
                       [t](const std::unique_ptr<Document>& doc) { return doc->get_document_type() == t; });
}

std::unique_ptr<Document> Library::search_document(const std::string_view title) {
  for (std::unique_ptr<Document>& doc : _docs) {
    if (doc->get_title() == title) {
      return std::unique_ptr<Document>(doc.get());
    }
  }
  return nullptr;
}

void Library::print() {
  for (std::unique_ptr<Document>& doc : _docs)
    doc->print();
}

bool Library::borrow_document(const std::string_view title) {
  for (std::unique_ptr<Document>& doc : _docs) {
    if (doc->get_title() == title) {
      return doc -> borrow_document();
    }
  }
  return false;
}

bool Library::return_document(const std::string_view title) {
  for (std::unique_ptr < Document > & doc: _docs) {
    if (doc -> get_title() == title) {
      doc -> return_document();
      return true;
    }
  }
  return false;
}

bool Library::dump_csv(const std::string_view filename) {
    std::fstream fout;

    if (_docs.size() >= 1){
        fout.open(filename,  std::ios::out | std::ios::app);
        for (std::unique_ptr<Document> & doc: _docs){
            if (doc->get_document_type() == DOC_NOVEL){
                Novel * novel = dynamic_cast < Novel * > (doc.release());
                fout << "novel," << novel->get_title() << 
                "," << novel->get_author() << ",," << 
                novel->get_quantity() << "\n";
            }
            else if(doc->get_document_type() == DOC_COMIC){
                Comic * comic = dynamic_cast < Comic * > (doc.release());
                fout << "comic," << comic->get_title() << "," 
                << comic->get_author() << "," 
                << comic->get_issue() << "," 
                << comic->get_quantity() << "\n";
            }
            else if (doc->get_document_type() == DOC_MAGAZINE){
                Magazine * magazine = dynamic_cast < Magazine * > (doc.release());
                fout << "magazine," << magazine->get_title() << ",," 
                << magazine->get_issue() << ","
                << magazine->get_quantity() << "\n";
            }

        }
        fout.close();
        return true;
    }

    return false;
}
