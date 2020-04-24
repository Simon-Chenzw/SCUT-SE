//!  @file:Main.cpp

#include "Library.h"
#include <iostream>

int main() {
    // You are to write a Library class that, during initialization, reads data
    // from the keyboard, and has the format below:
    // 3
    // N123;Object-Oriented Programming;Dave Smith;2009;3
    // A251;UML Modelling and Design;Barry Arthur;2005;1
    // Z001;Practical Guide to STL;John Johnson;2000;5
    // The first line indicates the number of book records to follow.
    Library library;

    // Then you should reads data from the keyboard, and has the following
    // format:
    // 3
    // 12345;Joe Bloggs;3;N123;A251;Z001
    // 20498;Ales Alexis;1;Z001
    // 19090;Mike Mike;2;N123;Z001
    // The first line indicates the number of borrower records to follow.
    int tot;
    cin >> tot;
    for (int i = 0; i < tot; i++) library.add_borrower();

    // Finally, write a main() function that displays the total number of books
    // on loan, the total number of books in the catalogue, the individual book
    // records, the total number of borrowers and the individual borrower
    // records.
    library.show_books_detail();
    library.show_borrowers_detail();
}