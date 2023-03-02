#include <iostream>
#include "../code_1/miniGit.hpp"
#include <filesystem>
using namespace std;

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
