//!  @file:Library.h

#pragma once
#include <string>
#include <vector>
using namespace std;

// Details regarding the data and functionality of the classes required by the
// program are as follow. It is fine to write other supporting functions or to
// add additional data fields if you want to.

class Borrower {
  private:
    // 1. An ID field.
    int borrower_id;

    // 2. A first name field.
    string first_name;

    // 3. A last name field.
    string last_name;

    // 4. A number of books loaned by the borrower field.
    int number_of_books_on_loan;

    // 5. An array of the book IDs currently loaned by the borrower.
    vector<string> books_on_loan;

  public:
    // 6. An appropriate constructor and destructor.
    Borrower(const vector<string>&);
    ~Borrower();

    // 7. A function that displays the data.
    void show_detail() const;

    // NOTE: In the function that enters a borrower's record, the function
    // should check that the borrower's ID consists of 5 digits. Otherwise an
    // error message should be displayed and the program should terminate.

    vector<string> get_loan_books() const;
};

class BookRecord {
  private:
    // 1. A book ID field.
    string book_id;

    // 2. A book title field.
    string book_title;

    // 3. An author's first name field.
    string first_name;

    // 4. An author's last name field.
    string last_name;

    // 5. A year of publication field.
    int year_published;

    // 6. A total number of book copies field.
    int number_of_copies;

    // 7. A number of copies still available for loan field.
    int number_of_copies_available;

  public:
    // 8. An appropriate constructor and destructor.
    BookRecord(const vector<string>&);
    ~BookRecord();

    // 9. A function that returns the book's ID.
    string get_book_id() const;

    // 10. A function that displays the data.
    void show_detail() const;

    // NOTE : In the function that enters a book record, the function should
    // check that the book ID starts with an uppercase letter, and that the year
    // of publication has 4 digits and starts with a 1 or a 2. Otherwise an
    // error message should be displayed and the program should terminate.

    int get_number() const;
    int get_number_can_loan() const;
    void loan_one();
    void return_one();
};

class Catalogue {
  private:
    // 1. A total number of book records field.
    int book_records_cnt;

    // 2. An array of BookRecords
    vector<BookRecord> book_records;

  public:
    // 3. An appropriate constructor and destructor.
    Catalogue();
    ~Catalogue();

    // 4. A function that displays the total number of books in the catalogue
    // and the individual book records.
    void show_detail() const;

    void add_book();
    void loan_book(string);
    int get_loan_num() const;
    int get_free_num() const;
};

class Library {
  private:
    // 1. A total number of books on loan field.
    int loan_books_cnt;

    // 2. A total number of borrowers field.
    int borrowers_cnt;

    // 3. A Catalogue object (described below). This should be populated during
    // initialization by the constructor.
    Catalogue catalogue;

    // 4. An array of Borrower objects (described below). This should be
    // populated during initialization by the constructor.
    vector<Borrower> borrowers;

  public:
    // 5. A constructor that accepts the input data.
    Library();

    // 6. An appropriate destructor.
    ~Library();

    // 7. A function that displays the total number of books on loan, the total
    // number of book records and displays the individual book records.
    void show_books_detail() const;

    // 8. A function that displays the total number of borrowers and the
    // individual borrower records.
    void show_borrowers_detail() const;

    void add_book();
    void loan_book(string);
    void add_borrower();
};

// NOTE: The program should update the total number of books on loan and the
// individual book numbers available for loan, based on the borrowers data.

string getline();

vector<string> split(string str, char ch);

int str2int(string str);