#include "document.h"

class Novel : public Document {
  private:
    std::string _author;      // author of a novel

  public:
    /* Constructor and Destructor */
    Novel(const std::string_view title, const std::string_view author, int quantity);
    ~Novel();

    document_type get_document_type() override;
    void print() override;

    /* getters and setters */
    void update_author(const std::string_view new_author);
    const std::string_view get_author() const;
};
