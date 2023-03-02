#include <iostream>
#include <sstream>
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

#include "miniGit.hpp"
#include <vector>

MiniGit::MiniGit() {
    fs::remove_all(".minigit");
    fs::create_directory(".minigit");
}

MiniGit::~MiniGit() {   
    // Any postprocessing that may be required
    deleteDLL(commitHead);
    delete ht;
    fs::remove_all(".minigit");
    cout << "Successfully deleted minigit" << endl;
}

void MiniGit::deleteDLL(BranchNode * main) {
    BranchNode * cur = main;
    if (cur == nullptr) {
        return;
    }

    //go to start of linked list
    while (cur->previous != nullptr) {
        cur = cur->previous;
    }

    while (cur != nullptr) {
        deleteSLL(cur);
        BranchNode * temp = cur;
        cur = cur->next;
        delete temp;
    }
}

void MiniGit::deleteSLL(BranchNode * cur) {
    FileNode * head = cur->fileHead;

    while (head != nullptr) {
        FileNode * temp = head;
        head = head->next;
        delete temp;
    }
}

void MiniGit::init(int hashtablesize) {
    commits = -1;
    ht = new HashTable(hashtablesize);
    BranchNode * bn = new BranchNode;
    bn->commitID = 0;
    bn->commitMessage = "";
    bn->fileHead = nullptr;
    bn->next = nullptr;
    bn->previous = nullptr;

    commitHead = bn;
}

void MiniGit::add() {
    if (commits+1 != commitHead->commitID) {
        cout << "NOT ON LATEST COMMIT" << endl;
        return;
    }

    cout << "Enter a file name: ";
    string fileName;
    getline(cin, fileName);

    //Check if the file exists.
    ifstream file;
    file.open(fileName);
    while (!file) {
        cout << "File does not exist. Please enter a valid file name: " << endl;
        getline(cin, fileName);
        file.open(fileName);
    }
    file.close();

    //Check if the file has already been added
    FileNode * fn = commitHead->fileHead;
    while(fn != nullptr) {
        if (fn->name == fileName) {
            cout << "File has already been added!" << endl;
            return;
        }
        fn = fn->next;
    }

    //Create FileNode and add it to the SLL
    FileNode * newNode = new FileNode;
    newNode->name = fileName;
    newNode->version = 0;
    newNode->next = commitHead->fileHead;
    commitHead->fileHead = newNode;

    //Copy File to .minigit
    //copyFileToMiniGit(fileName, 0);
}

void MiniGit::copyFileToMiniGit(string fileName, int version) {
    ifstream ifile(fileName);
    ofstream ofile(".minigit/" + to_string(version) + fileName);

    if (ifile && ofile) {
        string line;
        while (getline(ifile, line)) {
            ofile << line << endl;
        }
    }

    ifile.close();
    ofile.close();
}

void MiniGit::rm() {
    if (commits+1 != commitHead->commitID) {
        cout << "NOT ON LATEST COMMIT" << endl;
        return;
    }

    cout << "Enter a file name: ";
    string fileName;
    getline(cin, fileName);

    FileNode * cur = commitHead->fileHead;

    if (cur == nullptr) {
        return;
    }
    else if (cur->name == fileName) {
        commitHead->fileHead = cur->next;
        delete cur;
    }
    else {
        while (cur->next != nullptr && cur->next->name != fileName) {
            cur = cur->next;
        }
        if (cur->next != nullptr) {
            FileNode * temp = cur->next;
            cur->next = temp->next;
            delete temp;
        }
        
    }
}



void MiniGit::printSearchTable()
{
    cout << endl << "---HASH TABLE---" << endl;
    ht->printTable();
    cout << endl;
}


void MiniGit::search()
{
    cout << "Enter Key Word: ";
    string word;
    getline(cin, word);

    HashNode * n = ht->searchItem(word);
    if (n == nullptr) {
        cout << "Word not found!" << endl;
    }
    else {
        cout << "Commit ID's: ";
        for (int i : n->commitNums) {
            cout << i << ", ";
        }
        cout << endl;
    }


}



int MiniGit::commit() {
    if (commits+1 != commitHead->commitID) {
        cout << "NOT ON LATEST COMMIT" << endl;
        return -1;
    }

    string msg;
    cout << "Enter Commit Message: ";
    getline(cin, msg);

    while (msg == "") {
        cout << "Invalid Message! Try Again: ";
        getline(cin, msg);
    }    

    commitHead->commitMessage = msg;

    FileNode * cur = commitHead->fileHead;
    while (cur != nullptr) {
        string fileName = to_string(cur->version) + cur->name;

        ifstream dirfile;
        dirfile.open(".minigit/" + fileName);
        if(!dirfile) {
            //file doesn't exist
            copyFileToMiniGit(cur->name, cur->version);
        }
        else {
            ifstream mainfile(cur->name);
            
            string line1;
            string line2;

            string total1 = "";
            string total2 = "";

            while (getline(mainfile, line1)) {
                total1 += line1;
            }
            while (getline(dirfile, line2)) {
                total2 += line2;
            }

            if (total1 != total2) {
                cur->version += 1;
                copyFileToMiniGit(cur->name, cur->version);
            }
        }
        cur = cur->next;
    }


    cout << "COMMIT ID: " << commitHead->commitID << endl;
    hashCommitMSG(msg);

    BranchNode * b = new BranchNode;
    b->commitID = commitHead->commitID + 1;
    b->commitMessage = "";
    b->fileHead = deepCopySLL(commitHead->fileHead);
    b->previous = commitHead;
    b->next = nullptr;

    commitHead->next = b;

    commitHead = b;

    commits++;

    return b->commitID - 1; //should return the commitID of the commited DLL node
}

void MiniGit::checkout() {
    cout << "WARNING UNCOMMITED CHANGES WILL BE LOST" << endl;
    cout << "Enter Commit ID: ";
    string sid;
    getline(cin, sid);

    int id = stoi(sid);


    //Check if commitID is valid
    if (!(id <= commits+1 && id >= 0)) {
        cout << "Not a valid commit ID" << endl;
        return;
    }

    //Traverse Branch Node to the Desired Commit
    if(id < commitHead->commitID) {
        while (commitHead->commitID != id) {
            commitHead = commitHead->previous;
        }
    }

    else if (id > commitHead->commitID) {
        while (commitHead->commitID != id) {
            commitHead = commitHead->next;
        }
    }

    //Overwrite files from .minigit to current directory
    FileNode * cur = commitHead->fileHead;
    while (cur != nullptr) {
        ifstream gitfile(".minigit/" + to_string(cur->version) + cur->name);
        ofstream ofile(cur->name);
        string line;

        while (getline(gitfile, line)) {
            ofile << line << endl;
        }

        cur = cur->next;
    }
}

FileNode* MiniGit::deepCopySLL(FileNode * head) {
    if (head == nullptr) {
        return nullptr;
    }
    FileNode * newHead = new FileNode;
    newHead->name = head->name;
    newHead->version = head->version;
    newHead->next = nullptr;


    FileNode * newCur = newHead;
    FileNode * cur = head->next;
    while (cur != nullptr) {
        newCur->next = new FileNode;
        newCur = newCur->next;
        newCur->name = cur->name;
        newCur->version = cur->version;
        newCur->next = nullptr;

        cur = cur->next;
    }

    return newHead;
}

void MiniGit::hashCommitMSG(string msg) {
    stringstream ss(msg);
    string word;
    while (ss >> word) {
        cout << word << " ";
        ht->insertItem(word, commitHead->commitID);
    }
    cout << endl;
}

void MiniGit::printDLL() {
    BranchNode * main = commitHead;
    if (main == nullptr) {
        cout << "Not initialized" << endl;
        return;
    }
    cout << "--CURRENT-- :: "; 
    cout << "ID=" << main->commitID;
    cout << " MSG=" << main->commitMessage << " ";
    printSLL();

    cout << "------ALL COMMITS------" << endl;

    while (main->previous != nullptr) {
        main = main->previous;
    }

    while (main != nullptr && main->next != nullptr) {
        cout << "--COMMIT-- :: ";
        cout << "ID=" << main->commitID;
        cout << " MSG=" << main->commitMessage << " ";
        printSLL(main);
        cout << endl;
        main = main->next;
    }
}

void MiniGit::printSLL() {
    cout << "SLL: ";
    FileNode * cur = commitHead->fileHead;
    while (cur != nullptr) {
        cout << cur->name << "-" << cur->version << " -> ";
        cur = cur->next;
    }
    cout << endl;
}

void MiniGit::printSLL(BranchNode * head) {
    cout << "SLL: ";
    FileNode * cur = head->fileHead;
    while (cur != nullptr) {
        cout << cur->name << "-" << cur->version << " -> ";
        cur = cur->next;
    }
    cout << endl;
}
