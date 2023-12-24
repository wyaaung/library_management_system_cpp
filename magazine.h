#include "document.h"

class Magazine : public Document {
  private:
    int _issue;   // issue number of a magazine

  public:
    /* Constructor and Destructor */
    Magazine(const std::string_view title, int issue, int quantity);
    ~Magazine();

    document_type get_document_type() override;
    void print() override;

    void update_issue(int new_issue);
    int get_issue() const;
};
