# OJ2

## Vector 操作练习

### 解题思路

这题按照题意使用 `std::vector` 对每一个操作进行模拟即可。假设某次操作时，`std::vector` 的大小为 $n$，可能操作失败的地方有：

- 在插入时，需要判断插入的位置是否合法，应位于 $[0, n]$ 中。这里需要注意的是，**可以在所有元素的末尾插入**，此时对应的下标为 $n$。
- 在删除时，需要判断删除的位置是否合法，应位于 $[0, n)$ 中。
- 在访问时，需要判断访问的位置是否合法，应位于 $[0, n)$ 中。
- 在 `pop_back` 时，需要判断 `std::vector` 是否为空。

### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int a[10];
    for (int i = 0; i < 10; i++) {
        cin >> a[i];
    }

    vector<int> vec = vector<int>(a, a + 10);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int operation_id;
        cin >> operation_id;
        if (operation_id == 1) {
            int value;
            cin >> value;
            vec.push_back(value);
        } else if (operation_id == 2) {
            if (!vec.empty())
                vec.pop_back();
        } else if (operation_id == 3) {
            int position, value;
            cin >> position >> value;
            if (position >= 0 && position <= vec.size()) {
                vec.insert(vec.begin() + position, value);
            }
        } else if (operation_id == 4) {
            int position;
            cin >> position;
            if (position >= 0 && position < vec.size()) {
                vec.erase(vec.begin() + position);
            }
        } else if (operation_id == 5) {
            cout << vec.size() << endl;
        } else if (operation_id == 6) {
            for (auto it = vec.begin(); it != vec.end(); it++) {
                cout << *it << " ";
            }
            cout << endl;
        } else if (operation_id == 7) {
            for (auto it = vec.rbegin(); it != vec.rend(); it++) {
                cout << *it << " ";
            }
            cout << endl;
        } else if (operation_id == 8) {
            int position;
            cin >> position;
            if (position >= 0 && position < vec.size()) {
                cout << vec[position] << endl;
            } else {
                cout << "Invalid position" << endl;
            }
        }
    }
    return 0;
}
```

## 图书管理系统

### 解题思路

这题需要实现一个图书管理系统，其中有两个类，一个是 `Library` 类，一个是 `BookBorrower` 类。

- 在借书的时候，需要将 `book` 从 `library` 中移除，并且加入到 `borrower` 的借书列表中。
  - 需要判断的是，`borrower` 是否已经借过这本书；
  - 还需要判断的是，`library` 中是否存在这本书。
- 在还书的时候，需要将 `book` 从 `borrower` 的借书列表中移除，并且加入到 `library` 中。
  - 需要判断的是，`borrower` 是否借过这本书；
  - 还需要判断的是，`library` 中是否已经有这本书。

### 代码实现

先开始我的代码一直是 20 分，肉眼检查了好久，一直是 20 分。后来，我尝试用 `std::set` 写了一个不用指针的解答，通过了此题。

但我一直很纳闷；最后，我在本地通过生成随机数据对二者进行对拍，才发现是因为输出时**需要按照书本编号升序输出**。我在代码中用 `std::sort` 进行了排序，最后通过了此题。

同时，我也使用了宏定义的方式，来控制是否输出调试信息，这极大程度上方便了我本地调试。最终我提交的代码如下：

```cpp
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
```

## 反馈与建议

1. 希望以后能够允许使用 Markdown 进行排版，这样看起来会更加清晰。
2. 希望能够在题目中增加更多细节上的描述，例如第二题，我没意识到输出时需要按照书本编号升序输出（题目中似乎也没有提到）。
