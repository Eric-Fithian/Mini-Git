#include <iostream>
#include "../code_1/miniGit.hpp"
#include <filesystem>
using namespace std;

/*
 * Purpose; displays a menu with options
 */

void testHash() {
    string a[] = {"a", "b"};
    int n = 2;

    // 7 is count of buckets in hash table
    HashTable ht(5);

    // insert the keys into the hash table.
    // SILVER TODO : Complete insertItem() function
    for (int i = 0; i < n; i++)
    {
    ht.insertItem(a[i],1);
    }

    cout << "Contents of the hash table are" << endl;
    // SILVER TODO : Complete printTable() function
    ht.printTable();

    cout << endl;

    string searchFor = "a";
    // SILVER TODO : Complete searchItem() function
    if (ht.searchItem(searchFor))
    {
    cout << searchFor << " found in the hash table" << endl;
    }
    else
    {
    cout << searchFor << " not found in the hash table" << endl;
    }
    cout << "------------------------------------" << endl;
}

void displayMenu()
{
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. init " << endl;
    cout << " 2. add " << endl;
    cout << " 3. rm " << endl;
    cout << " 4. commit " << endl;
    cout << " 5. checkout" << endl;
    cout << " 6. search" << endl;
    cout << " 7. print current structure" << endl;
    cout << " 8. quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "Select a numerical option:" << endl;
}

void runApp() {
    MiniGit git;

    string input;
    displayMenu();
    getline(cin, input);

    while (1) {
        if (input == "1") {
            git.init(5);
        }
        else if (input == "2"){
            git.add();
            git.printSLL();
        }
        else if (input == "3"){
            git.rm();
            git.printSLL();
        }
        else if (input == "4"){
            int id =  git.commit();
            cout << "Commit ID: " << id << endl;
            git.printDLL();
        }
        else if (input == "5"){
            git.checkout();
            git.printDLL();
        }
        else if (input == "6") {
            git.search();
        }
        else if (input == "7") {
            git.printDLL();
            git.printSearchTable();
        }
        else if (input == "8"){
            cout << "Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid input!" << endl;
        }
        displayMenu();
        getline(cin, input);
    }
}

int main(int argc, char* argv[]) {
    
    //testHash();
    //testMiniGit();
    runApp();
    return 0;
}

