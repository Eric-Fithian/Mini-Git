// CPP program to implement hashing with chaining
#include<iostream>
#include "hash.hpp"


using namespace std;

HashNode* HashTable::createNode(string key, HashNode* next, int cNum)
{
    HashNode* nw = new HashNode;
    nw->key = key;
    nw->next = next;
    nw->commitNums.push_back(cNum);
    return nw;
}

HashTable::HashTable(int bsize)
{
    this->tableSize = bsize;
    table = new HashNode * [bsize];
    for (int i=0; i<tableSize; i++) {
        table[i] = nullptr;
    }

}

//function to calculate hash function
unsigned int HashTable::hashFunction(string s)
{
    int sum = 0;
    int index = 0;
    for (string::size_type i = 0; i < s.length(); i++) {
        sum += s[i];
    }
    index = sum % tableSize;
    return index;
}

// TODO Complete this function
//function to search
HashNode* HashTable::searchItem(string key)
{
    int index = hashFunction(key);

    HashNode *head = table[index];
    while (head != nullptr && head->key != key)
    {
        head = head->next;
    }
    return head;  
}

//TODO Complete this function
//function to insert
bool HashTable::insertItem(string key, int cNum)
{
    HashNode * n = searchItem(key);
    if (n == nullptr)
    {
        // TODO :
        // Use the hash function on the key to get the index/slot,
        int index = hashFunction(key);
        // create a new node with the key and insert it at the head of this slot's list
        HashNode *head = table[index];
        table[index] = createNode(key, head, cNum);
        return true;
    }
    else
    {
        n->commitNums.push_back(cNum);
        return true;
    }
    return false;
}


// function to display hash table //
/* assume the table size is 5. For each bucket it will show the 
** the string key and the commit number (separated by comma) within parenthesis
** e.g. the key is science and commit numbers are 1 and 4. The key science
** is hashed to position 0. So the print format will be-

0|| science(1,4,)
1|| 
2|| 
3|| 
4|| difficult(3,)-->fun(2,)-->computer(0,)

*/
void HashTable::printTable()
{
    for (int i=0; i < tableSize; i++) {
        HashNode * head = table[i];
        cout << i << "|| ";
        if (head != nullptr) {
            cout << head->key << "(";
            for (int i: head->commitNums) {
                cout << i << ",";
            }
            cout << ")";
            head = head->next;
            while (head != nullptr) {
                cout << "-->" << head->key << "(";
                for (int i: head->commitNums) {
                    cout << i << ",";
                }
                cout << ")";
                head = head->next;
            }
        }
        cout << endl;
        
    }
}
