#pragma once

#include<iostream>
#include<vector>
#include<fstream>
#include "hash.hpp"

using namespace std;


enum GITOP {init, add, rm, commit, checkout, status};

struct FileNode {
    string name;
    int version;
    FileNode* next;
};

struct BranchNode {
    int commitID;
    string commitMessage;
    BranchNode* next;
    BranchNode* previous;
    FileNode* fileHead;   
};

//*** You can add helper functions if you desire ***//
class MiniGit {
private:    
    BranchNode* commitHead = nullptr;
    int commits = -1;
    HashTable* ht = nullptr;
    
   

public:
    MiniGit();
    ~MiniGit();

    void deleteDLL(BranchNode * cur);
    void deleteSLL(BranchNode * cur);

    void init(int hashtablesize);
    void add();
    void copyFileToMiniGit(string fileName, int version);
    void rm();
    void search();
    int commit();
    void checkout();
    FileNode* deepCopySLL(FileNode * head);
    void hashCommitMSG(string msg);
    void printSearchTable();
    void printDLL();
    void printSLL();
    void printSLL(BranchNode * main);
};