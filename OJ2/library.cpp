#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class Book {
public:
    Book(int id) : id_(id) {}
    int getId() const { return id_; }
private:
    int id_;
};


class BookBorrower;

class Library {
public:
    void addBook(int idx) {
        books_.push_back(std::make_shared<Book>(Book(idx)));
    }
    
    void printBooks() const {
        for (const auto& book : books_) {
            std::cout << book->getId() << " ";
        }
      std::cout<<std::endl;
    }

    bool borrowBook(int id, BookBorrower& borrower);
    bool returnBook(int id, BookBorrower& borrower);

    void printDebug() const {
        for (auto it = books_.begin(); it != books_.end(); ++it) {
            std::cout << (*it)->getId() << ": " << it->use_count() << std::endl;
        }
    }
    
    ~Library() {
        books_.clear();
    }

private:
    std::vector<std::shared_ptr<Book>> books_;
};

class BookBorrower {
public:

    bool borrowBook(std::shared_ptr<Book> book) {
        borrowedBooks.push_back(book);
        return true;
    }

    bool returnBook(int id) {
        for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
            if ((*it)->getId() == id) {
                borrowedBooks.erase(it);
                return true;
            }
        }
        return false;
    }

    void printDebug() const {
        for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
            std::cout << (*it)->getId() << ": " << it->use_count() << std::endl;
        }
    }

private:
    std::vector<std::shared_ptr<Book>> borrowedBooks;
};

bool Library::borrowBook(int id, BookBorrower& borrower) {
    for (auto it = books_.begin(); it != books_.end(); ++it) {
        if ((*it)->getId() == id) {
            if (borrower.borrowBook(*it)) {
                books_.erase(it);
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

bool Library::returnBook(int id, BookBorrower& borrower) {
    if (borrower.returnBook(id)) {
        books_.push_back(std::make_shared<Book>(Book(id)));
        std::sort(books_.begin(), books_.end(),
            [](const std::shared_ptr<Book>& a, const std::shared_ptr<Book>& b) {
                return a->getId() < b->getId();
            }
        );
        return true;
    } else {
        return false;
    }
}


int main() {
    Library library;
    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        library.addBook(i);
    }

    int m;
    std::cin >> m;

    BookBorrower borrower;

    for (int i = 0; i < m; ++i) {
        int op, x;
        std::cin >> op;
        if (op == 1) {
            std::cin >> x;
            std::cout << (library.borrowBook(x, borrower) ? 1 : 0) << std::endl;
        } else if (op == 2) {
            std::cin >> x;
            std::cout << (library.returnBook(x, borrower) ? 1 : 0) << std::endl;
        } else if (op == 3) {
            library.printBooks();
        }
#ifdef LEVERIMMY_LOCAL_DEBUG
        puts("------Borrower------");
        borrower.printDebug();
        puts("------Library------");
        library.printDebug();
        puts("-------------------");
#endif
    }

    return 0;
}
