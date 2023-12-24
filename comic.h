#include "document.h"

class Comic : public Document {
  private:
    std::string _author;  // author of a comic
    int _issue;           // issue number of a comic

  public:
    /* Constructor and Destructor */
    Comic(const std::string_view title, const std::string_view author, int issue, int quantity);
    ~Comic();

    document_type get_document_type() override;
    void print() override;

    /* getters, setters */
    void update_author(const std::string_view new_author);
    void update_issue(int new_issue);
    const std::string_view get_author() const;
    int get_issue() const;
};
