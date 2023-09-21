#include<bits/stdc++.h>
using namespace std;

const int MAX_BOOKS = 10;
const int MAX_USERS = 10;

struct Books {
    int id{};
    string name{};
    int total_quantity{};
    int total_borrowed{};

    vector<string> borrowed_books;
};
Books books[MAX_BOOKS + 1];
bool cmp_books_by_id(Books x, Books y) {
    return x.id < y.id;
}
bool cmp_books_by_name(Books x, Books y) {
    return x.name < y.name;
}

struct Users {
    int national_id{};
    string name{};
    vector<int> borrowed_books_ids;

};
Users users[MAX_USERS + 1];

int menu() {
    int choice = -1;
    while (choice == -1) {
        cout << "\nLibrary Menu:\n";
        cout << "1) add_book\n";
        cout << "2) search_books_by_prefix\n";
        cout << "3) print_who_borrowed_book_by_name\n";
        cout << "4) print_library_by_id\n";
        cout << "5) print_library_by_name\n";
        cout << "6) add_user\n";
        cout << "7) user_borrow_book\n";
        cout << "8) user_return_book\n";
        cout << "9) print_users\n";
        cout << "10) Exit\n";
        cin >> choice;

        if (!(1 <= choice && choice <= 10)) {
            cout << "Invalid choice. Try again\n";
            choice = -1;
        }
    }
    return choice;
}

bool add_book() {
    int pos{ 1 };
    while (books[pos].id != 0) {
        if (pos == 10) {
            cout << "Maximum books reached [10].\n"
                << "YOU CAN'T ADD MORE!\n";
            return false;
        }
        pos++;
    }
    cout << "Enter books id & name & total quantity: ";
    cin >> books[pos].id >> books[pos].name >> books[pos].total_quantity;
    return true;
}

bool add_user() {
    int pos{ 1 };
    while (users[pos].national_id != 0) {
        if (pos == 10) {
            cout << "Maximum users reached [10].\n"
                << "YOU CAN'T ADD MORE!\n";
            return false;
        }
        pos++;
    }
    cout << "Enter user name & national id: ";
    cin >> users[pos].name >> users[pos].national_id;
    return true;
}

int check_user_name_validity(string _user) {
    for (int i = 1; i <= MAX_USERS; i++) {
        if (users[i].national_id != 0) {
            if (users[i].name == _user) {
                return i;
            }
        }
    }
    return false;
}

int check_book_validity(string _book_name) {
    for (int i = 1; i <= MAX_BOOKS; ++i) {
        if (books[i].id != 0) {
            if (books[i].name == _book_name) {
                return i;
            }
        }
    }
    return false;
}

bool user_borrow_book() {
    cout << "Enter user name and book name : ";
    string _user, _book_name;
    cin >> _user >> _book_name;
    int userIdx = check_user_name_validity(_user);
    int bookIdx = check_book_validity(_book_name);

    if (!(bookIdx && userIdx)) {
        cout << "Invalid user name or book not found.. please try again.\n";
        return false;
    }
    if (books[bookIdx].total_quantity == 0) {
        cout << "Book name : " << _book_name << " has 0 quantities left..\n";
        return false;
    }

    books[bookIdx].total_quantity--; books[bookIdx].total_borrowed++;
    books[bookIdx].borrowed_books.push_back(_user);

    users[userIdx].borrowed_books_ids.push_back(books[bookIdx].id);
    return true;
}
bool user_return_book() {
    cout << "Enter user name and book name : ";
    string _user, _book_name;
    cin >> _user >> _book_name;
    int userIdx = check_user_name_validity(_user);
    int bookIdx = check_book_validity(_book_name);

    if (!(bookIdx && userIdx)) {
        cout << "Invalid user name or book not found.. please try again.\n";
        return false;
    }
    books[bookIdx].total_quantity++; books[bookIdx].total_borrowed--;

    books[bookIdx].borrowed_books.erase(find(books[bookIdx].borrowed_books.begin(), books[bookIdx].borrowed_books.end(), _user));

    users[userIdx].borrowed_books_ids.erase(find(users[userIdx].borrowed_books_ids.begin(), users[userIdx].borrowed_books_ids.end(), books[bookIdx].id));
    return true;
}

bool search_books_by_prefix() {
    cout << "Enter book name prefix: ";
    string _book_name;
    cin >> _book_name;
    int cnt{ 0 };
    for (int i = 1; i <= MAX_BOOKS; ++i) {
        if (books[i].id != 0) {
            bool exist = true;
            for (int j = 0; j < _book_name.length(); j++) {
                if (_book_name[j] != books[i].name[j]) {
                    exist = false;
                }
            }
            if (exist) {
                cout << books[i].name << endl;
                cnt++;
            }
        }
    }
    if (!cnt) cout << "No books with such prefix..\n";
    return true;
}

bool print_who_borrowed_book_by_name() {
    cout << "Enter book name: ";
    string _book_name;
    cin >> _book_name;
    int bookIdx = check_book_validity(_book_name);
    if (bookIdx) {
        for (auto it = books[bookIdx].borrowed_books.begin(); it != books[bookIdx].borrowed_books.end(); it++) {

            cout << *it << endl;
        }
    }
    else {
        cout << "Book not found .. try again..\n";
        return false;
    }
    return true;
}

void print_library_by_id() {
    sort(books, books + MAX_BOOKS + 1, cmp_books_by_id);
    for (auto book : books) {
        if (book.id != 0) {
            cout << "Id = " << book.id << " name = " << book.name
                << " total_quantity = " << book.total_quantity
                << " total_borrowed = " << book.total_borrowed << endl;
        }
    }
}
void print_library_by_name() {
    sort(books, books + MAX_BOOKS + 1, cmp_books_by_name);
    for (auto book : books) {
        if (book.id != 0) {
            cout << "Id = " << book.id << " name = " << book.name
                << " total_quantity = " << book.total_quantity
                << " total_borrowed = " << book.total_borrowed << endl;
        }
    }
}
void print_users() {
    for (auto user : users) {
        if (user.national_id != 0) {
            cout << "user: " << user.name
                << " national_id: " << user.national_id
                << " borrowed_books_ids: ";
            for (auto it = user.borrowed_books_ids.begin(); it != user.borrowed_books_ids.end(); it++)
                cout << *it << " ";
            cout << '\n';
        }
    }
}

void system() {
    while (true) {
        int choice = menu();
        if (choice == 1)
            add_book();
        else if (choice == 2)
            search_books_by_prefix();
        else if (choice == 3)
            print_who_borrowed_book_by_name();
        else if (choice == 4)
            print_library_by_id();
        else if (choice == 5)
            print_library_by_name();
        else if (choice == 6)
            add_user();
        else if (choice == 7)
            user_borrow_book();
        else if (choice == 8)
            user_return_book();
        else if (choice == 9)
            print_users();
        else if (choice == 10)
            break;
    }
}

int main() {
    system();
    return 0;
}
