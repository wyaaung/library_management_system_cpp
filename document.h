#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <iostream>
#include <string>

/* The different types of documents stored in the library */
typedef enum {
    DOC_NOVEL,
    DOC_COMIC,
    DOC_MAGAZINE
} document_type;

class Document {
  protected:
    std::string _title;   // document title
    int _quantity;  // quantity held in the library

    /* Copying or moving abstract objects is risky, but the derived objects
    * might need them to implement their default copy/move methods, so we
    * make them protected */
    Document(const Document& document);
    Document& operator=(const Document& document);
    Document(Document&& document) noexcept;
    Document& operator=(Document&& document) noexcept;

  public:
    Document(const std::string_view title, int quantity);
    /* Virtual Destructor */
    virtual ~Document();

    /* return the document type (abstract method) */
    virtual document_type get_document_type() = 0;

    /* print the document attributes in a single line on the standard output
    * (abstract method), the format for the various document types is as
    * follows:
    * Novel, title: <title>, author: <author>, quantity: <quantity>
    * Comic, title: <title>, author: <author>, issue: <issue>, quantity: <quantity>
    * Magazine, title: <title>, issue: <issue>, quantity: <quantity>
    */
    virtual void print() = 0;

    /* Setters and Getters */
    void update_title(const std::string_view new_title);
    void update_quantity(int new_quantity);
    const std::string_view get_title() const;
    int get_quantity() const;

    /* Used when someone tries to borrow a document, should return 0 on success
    * and something else on failure */
    bool borrow_document();

    /* Used when someone returns a document */
    void return_document();
};

#endif  /* DOCUMENT_H */