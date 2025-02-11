#include<iostream>
#include<cstdlib>
#include<fstream>
using namespace std;

class temp{
    string id, name, author, search;
    fstream file;
public:
    void addBook();
    void showAll();
    void extractBook();
};

int main(){
    char choice;
    temp book;
    cout << "------------------------------------\n";
    cout << "1 - Show All Books\n";
    cout << "2 - Extract Books\n";
    cout << "3 - Add Books (ADMIN)\n";
    cout << "4 - Exit\n";
    cout << "------------------------------------\n";
    cout << "Enter Your Choice: ";
    cin >> choice;
    cin.ignore();  // To ignore the leftover newline character from the choice input
    
    switch(choice){
        case '1':
            book.showAll();
            break;
        case '2':
            book.extractBook();
            break;
        case '3':
            book.addBook();
            break;
        case '4':
            exit(0);
        default:
            cout << "Invalid Choice...!\n";
    }
    return 0;
}

void temp::addBook(){
    cout << "Enter Book Id: ";
    getline(cin, id);
    cout << "Enter Book Name: ";
    getline(cin, name);
    cout << "Enter Book Author Name: ";
    getline(cin, author);

    file.open("BookData.txt", ios::out | ios::app);
    if (!file) {
        cout << "Error opening file!\n";
        return;
    }
    file << id << "*" << name << "*" << author << endl;
    file.close();
}

void temp::showAll(){
    file.open("BookData.txt", ios::in);
    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    cout << "\n\n";
    cout << "\t\t Book Id \t\t\t Book Name \t\t\t Book Author\n";

    while (getline(file, id, '*')) {
        getline(file, name, '*');
        getline(file, author);

        cout << "\t\t " << id << " \t\t\t " << name << " \t\t\t " << author << endl;
    }

    file.close();
}

void temp::extractBook(){
    cout << "Enter Book Id to Extract: ";
    getline(cin, search);
    bool found = false;

    file.open("BookData.txt", ios::in);
    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    fstream tempFile;
    tempFile.open("TempBookData.txt", ios::out);
    
    while (getline(file, id, '*')) {
        getline(file, name, '*');
        getline(file, author);
        
        if (id != search) {
            tempFile << id << "*" << name << "*" << author << endl;
        } else {
            found = true;
        }
    }
    
    file.close();
    tempFile.close();

    remove("BookData.txt");
    rename("TempBookData.txt", "BookData.txt");

    if (found) {
        cout << "Book with ID " << search << " has been removed.\n";
    } else {
        cout << "Book with ID " << search << " not found.\n";
    }
}
