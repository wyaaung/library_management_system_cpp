#define CATCH_CONFIG_MAIN

#include "catch.h"
#include "library.h"

#include <string>
#include <string_view>

#include <cstdio>
#include <unistd.h>
#include <fcntl.h>

#ifndef BATCH
#define BATCH 0
#endif

bool same(std::string_view s1, std::string_view s2) {
	return s1 == s2;
}

TEST_CASE("constructors and getters") {
    /* Simply instantiate some documents and check that the getters return
     * the right value for the attributes of the created objects */

    Novel n1 = Novel("Monstrous Regiment", "Terry Pratchett", 1);
    CHECK(same(n1.get_title(), "Monstrous Regiment"));
    CHECK(same(n1.get_author(), "Terry Pratchett"));
    CHECK(n1.get_quantity() == 1);

    Comic c1 = Comic("Watchmen", "Alan Moore", 1, 10);
    CHECK(same(c1.get_title(), "Watchmen"));
    CHECK(same(c1.get_author(), "Alan Moore"));
    CHECK(c1.get_quantity() == 10);
    CHECK(c1.get_issue() == 1);

    Magazine m1 = Magazine("The New Yorker", 1, 20);
    CHECK(same(m1.get_title(), "The New Yorker"));
    CHECK(m1.get_issue() == 1);
    CHECK(m1.get_quantity() == 20);
}

TEST_CASE("copy constructors") {

  /* Create copy of novel */
  Novel n1 = Novel("Monstrous Regiment", "Terry Pratchett", 1);
  Novel n1b = n1;
  CHECK(n1b.get_document_type() == DOC_NOVEL);
  CHECK(same(n1b.get_title(), n1.get_title()));
  CHECK(same(n1b.get_author(), n1.get_author()));

  /* Ensure that the copy has distinct data */
  n1b.update_title("invalid");
  n1b.update_author("invalid");
  n1b.update_quantity(5000);

  CHECK(!same(n1b.get_title(), n1.get_title()));
  CHECK(!same(n1b.get_author(), n1.get_author()));
  CHECK(n1b.get_quantity() != n1.get_quantity());


  /* Create copy of comic */
  Comic c1 = Comic("Watchmen", "Alan Moore", 1, 10);
  Comic c1b = c1;
  CHECK(c1b.get_document_type() == DOC_COMIC);
  CHECK(same(c1b.get_title(), c1.get_title()));
  CHECK(same(c1b.get_author(), c1.get_author()));
  CHECK(c1b.get_issue() == c1.get_issue());

  /* Ensure that the copy has distinct data */
  c1b.update_title("invalid");
  c1b.update_author("invalid");
  c1b.update_quantity(5000);
  c1b.update_issue(5000);

  CHECK(!same(c1b.get_title(), c1.get_title()));
  CHECK(!same(c1b.get_author(), c1.get_author()));
  CHECK(c1b.get_quantity() != c1.get_quantity());
  CHECK(c1b.get_issue() != c1.get_issue());

  
  /* Create copy of magazine */
  Magazine m1 = Magazine("The New Yorker", 1, 20);
  Magazine m1b = m1;
  CHECK(m1b.get_document_type() == DOC_MAGAZINE);
  CHECK(same(m1b.get_title(), m1.get_title()));
  CHECK(m1b.get_issue() == m1.get_issue());

  /* Ensure that the copy has distinct data */
  m1b.update_title("invalid");
  m1b.update_quantity(5000);
  m1b.update_issue(5000);

  CHECK(!same(m1b.get_title(), m1.get_title()));
  CHECK(m1b.get_quantity() != m1.get_quantity());
  CHECK(m1b.get_issue() != m1.get_issue());
}

TEST_CASE("move constructors") {

  /* Move a temporary copy of n1 */
  Novel n1 = Novel("Monstrous Regiment", "Terry Pratchett", 1);
  Novel n1b = n1;
  Novel n1c = std::move(n1b);

  CHECK(n1c.get_document_type() == DOC_NOVEL);
  CHECK(same(n1c.get_title(), n1.get_title()));
  CHECK(same(n1c.get_author(), n1.get_author()));

  /* Move a temporary copy of c1 */
  Comic c1 = Comic("Watchmen", "Alan Moore", 1, 10);
  Comic c1b = c1;
  Comic c1c = std::move(c1b);

  CHECK(c1c.get_document_type() == DOC_COMIC);
  CHECK(same(c1c.get_title(), c1.get_title()));
  CHECK(same(c1c.get_author(), c1.get_author()));

  /* Move a temporary copy of m1 */
  Magazine m1 = Magazine("The New Yorker", 1, 20);
  Magazine m1b = m1;
  Magazine m1c = std::move(m1b);

  CHECK(m1c.get_document_type() == DOC_MAGAZINE);
  CHECK(same(m1c.get_title(), m1.get_title()));
}

TEST_CASE("setters") {
    Library l;

    Magazine m1 = Magazine("The New Yorkzz", 1, 20);
    m1.update_title("The New Yorker");
    CHECK(same(m1.get_title(), "The New Yorker"));
}

TEST_CASE("library construction") {
    Library l;

    REQUIRE(l.add_document(DOC_NOVEL, "Monstrous Regiment", "Terry Pratchett", -1, 1));
    REQUIRE(l.add_document(DOC_NOVEL, "Watership Down", "Richard Adams", -1, 2));
    REQUIRE(l.add_document(DOC_COMIC, "Watchmen", "Alan Moore", 1, 10));
    REQUIRE(l.add_document(DOC_MAGAZINE, "The New Yorker", "", 1, 20));

    CHECK(l.count_document_of_type(DOC_NOVEL) == 2);
    CHECK(l.count_document_of_type(DOC_COMIC) == 1);
    CHECK(l.count_document_of_type(DOC_MAGAZINE) == 1);

}

TEST_CASE("add_document interface") {
    Library l;

    Novel *n1 = new Novel("Monstrous Regiment", "Terry Pratchett", 1);
    REQUIRE(l.add_document(n1));
    CHECK(l.count_document_of_type(DOC_NOVEL) == 1);
}

TEST_CASE("removing documents from library") {
    Library l;

    REQUIRE(l.add_document(DOC_NOVEL, "Monstrous Regiment", "Terry Pratchett", -1, 1));
    REQUIRE(l.add_document(DOC_NOVEL, "Watership Down", "Richard Adams", -1, 2));
    REQUIRE(l.add_document(DOC_COMIC, "Watchmen", "Alan Moore", 1, 10));
    REQUIRE(l.add_document(DOC_MAGAZINE, "The New Yorker", "", 1, 20));

    CHECK(l.count_document_of_type(DOC_NOVEL) == 2);
    CHECK(l.count_document_of_type(DOC_COMIC) == 1);
    CHECK(l.count_document_of_type(DOC_MAGAZINE) == 1);

    CHECK((l.delete_document("Watership Down")));
    CHECK((l.delete_document("Watchmen")));
    CHECK(!(l.delete_document("Watchmen")));

    CHECK(l.count_document_of_type(DOC_NOVEL) == 1);
    CHECK(l.count_document_of_type(DOC_COMIC) == 0);
    CHECK(l.count_document_of_type(DOC_MAGAZINE) == 1);
}

#if BATCH == 0

TEST_CASE("object-level print functions") {
    char printed_n1[128], printed_n2[128], printed_c1[128], printed_m1[128];
    char expected_n1[] = "Novel, title: Monstrous Regiment, author: Terry Pratchett, " \
                         "quantity: 1\n";
    char expected_n2[] = "Novel, title: Watership Down, author: Richard " \
                         "Adams, quantity: 2\n";
    char expected_c1[] = "Comic, title: Watchmen, author: Alan Moore, " \
                         "issue: 1, quantity: 10\n";
    char expected_m1[] = "Magazine, title: The New Yorker, issue: 1, " \
                         "quantity: 20\n";

    Novel n1 = Novel("Monstrous Regiment", "Terry Pratchett", 1);
    Novel n2 = Novel("Watership Down", "Richard Adams", 2);
    Comic c1 = Comic("Watchmen", "Alan Moore", 1, 10);
    Magazine m1 = Magazine("The New Yorker", 1, 20);

#define CHECK_STDOUT(obj) { \
    memset(printed_##obj, 0x0, 128); \
    lseek(STDOUT_FILENO, 0, SEEK_SET); \
    obj.print(); \
    lseek(STDOUT_FILENO, 0, SEEK_SET); \
    read(STDOUT_FILENO, printed_##obj, strlen(expected_##obj)); \
    printed_##obj[strlen(expected_##obj)] = '\0'; \
}

    int original_stdout = dup(STDOUT_FILENO);
#ifdef O_TMPFILE
    int tmpfd = open("/tmp/", O_RDWR | O_TMPFILE, S_IRUSR | S_IWUSR);
#else
    int tmpfd = open("/tmp/temp", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
#endif
    REQUIRE(tmpfd != -1);

    /* What I'm doing here is a bit tricky and you don't need to understand
     * all the details. Long story short I am redirecting the standard output
     * into a file in order to be able to read that file and check that what
     * is normally printed in the standard output is correct (there is no
     * easy way to read the standard output from C code */
    dup2(tmpfd, STDOUT_FILENO);
    close(tmpfd);

    CHECK_STDOUT(n1);
    CHECK_STDOUT(n2);
    CHECK_STDOUT(c1);
    CHECK_STDOUT(m1);

    dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
    CHECK(same(printed_n1, expected_n1));
    CHECK(same(printed_n2, expected_n2));
    CHECK(same(printed_c1, expected_c1));
    CHECK(same(printed_m1, expected_m1));
}

TEST_CASE("library-level print function") {
    char printed[512];
    char expected[] = "Novel, title: Monstrous Regiment, " \
        "author: Terry Pratchett, quantity: 1\n" \
        "Novel, title: Watership Down, author: Richard " \
        "Adams, quantity: 2\n" \
        "Comic, title: Watchmen, author: Alan Moore, " \
        "issue: 1, quantity: 10\n" \
        "Magazine, title: The New Yorker, issue: 1, " \
        "quantity: 20\n";

    memset(printed, 0x0, 512);

    Library l;
    REQUIRE(l.add_document(DOC_NOVEL, "Monstrous Regiment", "Terry Pratchett", -1, 1));
    REQUIRE(l.add_document(DOC_NOVEL, "Watership Down", "Richard Adams", -1, 2));
    REQUIRE(l.add_document(DOC_COMIC, "Watchmen", "Alan Moore", 1, 10));
    REQUIRE(l.add_document(DOC_MAGAZINE, "The New Yorker", "", 1, 20));

    int original_stdout = dup(STDOUT_FILENO);
#ifdef O_TMPFILE
    int tmpfd = open("/tmp/", O_RDWR | O_TMPFILE, S_IRUSR | S_IWUSR);
#else
    int tmpfd = open("/tmp/temp", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
#endif
    REQUIRE(tmpfd != -1);

    dup2(tmpfd, STDOUT_FILENO);
    close(tmpfd);

    lseek(STDOUT_FILENO, 0, SEEK_SET);
    l.print();
    lseek(STDOUT_FILENO, 0, SEEK_SET); \
    read(STDOUT_FILENO, printed, strlen(expected)); \
    printed[strlen(expected)] = '\0'; \

    dup2(original_stdout, STDOUT_FILENO);
    CHECK(same(printed, expected));
}

#endif

TEST_CASE("CSV file dump") {
    Library l;
    int buf_size = 512, fd, bytes_read;
    char content_read[buf_size];
    char expected[] = "novel,Monstrous Regiment,Terry Pratchett,,1\n"
            "novel,Watership Down,Richard Adams,,2\n"
            "comic,Watchmen,Alan Moore,1,10\n"
            "magazine,The New Yorker,,1,20\n";
    char output_file[] = "output.csv";

    REQUIRE(l.add_document(DOC_NOVEL, "Monstrous Regiment", "Terry Pratchett", -1, 1));
    REQUIRE(l.add_document(DOC_NOVEL, "Watership Down", "Richard Adams", -1, 2));
    REQUIRE(l.add_document(DOC_COMIC, "Watchmen", "Alan Moore", 1, 10));
    REQUIRE(l.add_document(DOC_MAGAZINE, "The New Yorker", "", 1, 20));

    remove(output_file); /* (ignore errors) */
    REQUIRE(l.dump_csv(output_file));

    fd = open(output_file, O_RDONLY);
    REQUIRE(fd != -1);
    bytes_read = read(fd, content_read, buf_size);
    REQUIRE(bytes_read <= buf_size);
    close(fd);

    content_read[bytes_read] = '\0';
    CHECK(same(content_read, expected));
}

TEST_CASE("borrow-return functions") {
    Library l;
    int n1_num = 1, c1_num = 10;
    char n1_title[] = "Monstrous Regiment", c1_title[] = "Watchmen";

    REQUIRE(l.add_document(DOC_NOVEL, n1_title, "Terry Pratchett", -1, n1_num));
    REQUIRE(l.add_document(DOC_COMIC, c1_title, "Alan Moore", 1, c1_num));

    for(int i = 0; i < n1_num; ++i)
        CHECK(l.borrow_document(n1_title));
    CHECK(!l.borrow_document(n1_title));
    CHECK(l.return_document(n1_title));
    CHECK(l.borrow_document(n1_title));

    for(int i = 0; i < c1_num; ++i)
        CHECK(l.borrow_document(c1_title));
    CHECK(!l.borrow_document(c1_title));
    CHECK(l.return_document(c1_title));
    CHECK(l.borrow_document(c1_title));

    CHECK(!l.borrow_document("The Neverending Story"));
    CHECK(!l.return_document("Lord of the Rings"));
}
