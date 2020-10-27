/**
 *  @brief:code of assignment2
 *  @file:Library.cpp
 *  @author:Simon_Chen
 */

#include "Library.h"
#include <iostream>

//--------------------------------------------------
// Class Library

Library::Library(): borrowers_cnt(0), catalogue(Catalogue()) {
    int cnt;
    cin >> cnt;
    for (int i = 0; i < cnt; i++) add_book();
    loan_books_cnt = catalogue.get_free_num();
}

Library::~Library() = default;

void Library::show_books_detail() const {
    // Total number of books on loan: 6
    // Total number of books in catalogue: 3
    cout << "Total number of books on loan: " << catalogue.get_loan_num()
         << "\nTotal number of books in catalogue: " << catalogue.get_free_num() << '\n';
    catalogue.show_detail();
}

void Library::show_borrowers_detail() const {
    // Total number of borrowers: 3
    cout << "Total number of borrowers: " << borrowers_cnt << '\n';
    int cnt = 0;
    for (auto borrower : borrowers) {
        cout << "Borrower " << cnt++ << "\n===========\n";
        borrower.show_detail();
    }
}

void Library::add_book() {
    catalogue.add_book();
}

void Library::loan_book(string book_name) {
    catalogue.loan_book(book_name);
}

void Library::add_borrower() {
    borrowers_cnt++;
    borrowers.push_back(split(getline(), ';'));
    for (auto& book : borrowers.back().get_loan_books()) loan_book(book);
}

//--------------------------------------------------
// Class Borrower

Borrower::Borrower(const vector<string>& vec):
      borrower_id(str2int(vec[0])),
      first_name(split(vec[1], ' ')[0]),
      last_name(split(vec[1], ' ')[1]),
      number_of_books_on_loan(str2int(vec[2])) {
    // borrower_id;first_name last_name;number_of_books_on_loan;book_ids
    if (vec[0].length() != 5) throw invalid_argument("the borrower's ID must consists of 5 digits");
    if (number_of_books_on_loan > 5) throw invalid_argument("too many books for loan");
    for (int i = 0; i < number_of_books_on_loan; i++) books_on_loan.push_back(vec[3 + i]);
}

Borrower::~Borrower() = default;

void Borrower::show_detail() const {
    // Borrower ID: 12345
    // Name: Joe Bloggs
    // Number of loaned books: 3
    // IDs of books on loan: N123 A251 Z001
    cout << "Borrower ID: " << borrower_id << "\nName: " << first_name << ' ' << last_name
         << "\nNumber of loaned books: " << number_of_books_on_loan << "\nIDs of books on loan: ";
    for (int i = 0; i < (int)books_on_loan.size(); i++)
        cout << books_on_loan[i] << " \n"[i + 1 == (int)books_on_loan.size()];
}

vector<string> Borrower::get_loan_books() const {
    return books_on_loan;
}

//--------------------------------------------------
// Class Catalogue

Catalogue::Catalogue(): book_records_cnt(0) {}

Catalogue::~Catalogue() = default;

void Catalogue::show_detail() const {
    int cnt = 0;
    for (auto book_record : book_records) {
        cout << "Book Record " << cnt++ << "\n=============\n";
        book_record.show_detail();
    }
}

void Catalogue::add_book() {
    book_records_cnt++;
    book_records.push_back(BookRecord(split(getline(), ';')));
}

void Catalogue::loan_book(string book_name) {
    for (auto& book : book_records)
        if (book.get_book_id() == book_name) {
            book.loan_one();
            return;
        }
}

int Catalogue::get_loan_num() const {
    int ans = 0;
    for (auto& book : book_records) ans += book.get_number() - book.get_number_can_loan();
    return ans;
}

int Catalogue::get_free_num() const {
    int ans = 0;
    for (auto& book : book_records) ans += book.get_number_can_loan();
    return ans;
}

//--------------------------------------------------
// Class BookRecord

BookRecord::BookRecord(const vector<string>& vec):
      book_id(vec[0]),
      book_title(vec[1]),
      first_name(split(vec[2], ' ')[0]),
      last_name(split(vec[2], ' ')[1]),
      year_published(str2int(vec[3])),
      number_of_copies(str2int(vec[4])),
      number_of_copies_available(number_of_copies) {
    // book_id;book_title;first_name last_name;year_published;number_of_copies
    if (book_id[0] < 'A' || book_id[0] > 'Z') throw invalid_argument("book ID must starts with an uppercase letter");
    if (vec[3].length() != 4 || (vec[3][0] != '1' && vec[3][0] != '2'))
        throw invalid_argument("the year of publication has 4 digits and "
                               "starts with a 1 or a 2. ");
}

BookRecord::~BookRecord() = default;

string BookRecord::get_book_id() const {
    return book_id;
}

void BookRecord::show_detail() const {
    // Book ID: A251
    // Title: UML Modelling and Design
    // Author: Barry Arthurs
    // Year published: 2005
    // Total number of copies: 1
    // Number available for loan: 0
    cout << "Book ID: " << book_id << "\nTitle: " << book_title << "\nAuthor: " << first_name << ' ' << last_name
         << "\nYear published: " << year_published << "\nTotal number of copies: " << number_of_copies
         << "\nNumber available for loan: " << number_of_copies_available << '\n';
}

int BookRecord::get_number() const {
    return number_of_copies;
}

int BookRecord::get_number_can_loan() const {
    return number_of_copies_available;
}

void BookRecord::loan_one() {
    if (number_of_copies_available)
        number_of_copies_available--;
    else
        throw invalid_argument("not book for loan");
}

void BookRecord::return_one() {
    if (number_of_copies_available < number_of_copies)
        number_of_copies++;
    else
        throw invalid_argument("didn't loan a book");
}

//--------------------------------------------------
// Others

string getline() {
    string ans;
    while (cin.peek() == '\n') cin.ignore();
    while (cin.peek() != '\n') ans.push_back(cin.get());
    return ans;
}

vector<string> split(string str, char ch) {
    vector<string> ans {""};
    for (auto& p : str)
        if (p != ch)
            ans.back().push_back(p);
        else
            ans.push_back("");
    return ans;
}

int str2int(string str) {
    int ans = 0;
    for (auto& p : str) {
        ans *= 10;
        ans += p - '0';
    }
    return ans;
}