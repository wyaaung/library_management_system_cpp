#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "magazine.h"
#include "novel.h"
#include "comic.h"

class Library {
  private:
    std::vector<std::unique_ptr<Document>> _docs;

  public:
    Library();
    ~Library();

    void print();

    bool dump_csv(const std::string_view filename);

    std::unique_ptr<Document> search_document(const std::string_view title);

    bool add_document(document_type type, const std::string_view title, const std::string_view author, int issue, int quantity);
    bool delete_document(const std::string_view title);

    bool add_document(std::unique_ptr<Document> document);
    int add_document(Document* document);

    int count_document_of_type(document_type type);

    bool borrow_document(const std::string_view title);
    bool return_document(const std::string_view title);
};
