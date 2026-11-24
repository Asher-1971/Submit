#include <iostream>
#include <string>

using namespace std;

class LibraryBook
{
private:
    int availableCopies;

public:
    string title;
    string author;
    long ISBN;

    void setCopies(int copies)
    {
        availableCopies = copies;
    }

    int getCopies()
    {
        return availableCopies;
    }

    void displayDetails()
    {
        cout << "\nBook Details\n";
        cout << "Title: " << title << '\n';
        cout << "Author: " << author << '\n';
        cout << "ISBN: " << ISBN << '\n';
        cout << "Available copies: " << getCopies() << '\n';
    }
};

int main()
{
    LibraryBook book;
    int copies;

    cout << "Enter the book title: ";
    getline(cin, book.title);

    cout << "Enter the author: ";
    getline(cin, book.author);

    cout << "Enter the ISBN: ";
    cin >> book.ISBN;

    cout << "Enter the number of available copies: ";
    cin >> copies;
    book.setCopies(copies);

    book.displayDetails();

    return 0;
}
