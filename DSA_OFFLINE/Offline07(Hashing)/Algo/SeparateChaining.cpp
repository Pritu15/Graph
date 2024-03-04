#include <iostream>
#include "Node.h"
#include "HashFunction.h"
#include <math.h>
#include <random>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;
// template <typename T, typename E>

// template <typename T, typename E>
class OpenChainingHash
{
public:
    long long Tablesize, collisionCounter, ProbeCounter, HashFunctionCnt, size;
    vector<list<Node *>> theLists;
    // Node **HashTable;
    vector<Node *> HashTable;
    OpenChainingHash(long long n, long long hashFunction)
    {
        this->Tablesize = nearestPrime(n);
        this->HashFunctionCnt = hashFunction;
        InitializeTable();
        // this->HashTable = new Node *[Tablesize + 1];
    }
    void InitializeTable()
    {
        this->HashTable.resize(Tablesize);
        for (long long i = 0; i <= Tablesize; i++)
        {
            HashTable[i] = nullptr;
        }
    }
    void insert(string key, long long value)
    {
        long long i;
        if (HashFunctionCnt == 1)
        {
            // i = HashFunction1(key);
            i = myHash1(key);
        }
        // else{
        //     i=;
        // }
        if (HashTable[i] == nullptr)
        {
            HashTable[i] = new Node(key, value);
        }
        else
        {
            collisionCounter++;
            Node *temp = HashTable[i];
            while (temp->getNext() != nullptr)
            {
                temp = temp->getNext();
            }
            temp->setNxt(new Node(key, value));
        }
        size++;
    }
    void remove(string key)
    {
        long long i;
        if (HashFunctionCnt == 1)
        {
            // i = HashFunction1(key);
            i = myHash1(key);
        }
        // else{
        //     i=;
        // }
        if (HashTable[i] == nullptr)
        {
            return;
        }
        else
        {
            Node *temp = HashTable[i];
            if (temp->getKey() == key)
            {
                HashTable[i] = temp->getNext();
                delete temp;
                size--;
                return;
            }
            while (temp->getNext() != nullptr)
            {
                if (temp->getNext()->getKey() == key)
                {
                    Node *temp2 = temp->getNext();
                    temp->setNxt(temp2->getNext());
                    delete temp2;
                    size--;
                    return;
                }
                temp = temp->getNext();
            }
        }
    }
    // bool insert(string key, long long value)
    // {
    //     list<Node *> &whichList = theLists[myHash(key)];
    //     if (find(whichList.begin(), whichList.end(), key) != whichList.end())
    //     {
    //         return false;
    //     }
    // }
    long long Search(string key)
    {

        long long i;
        if (HashFunctionCnt == 1)
        {
            i = HashFunction1(key);
        }
        // else{
        //     i=;
        // }
        if (HashTable[i] == nullptr)
        {
            return -1;
        }
        else
        {
            Node *temp = HashTable[i];
            ProbeCounter++;
            while (true)
            {
                if (temp->getKey() == key)
                {
                    return temp->getValue();
                }
                if (temp->getNext() == nullptr)
                {
                    return -1;
                }
                temp = temp->getNext();
                ProbeCounter++;
            }
        }
    }
    void ReHashing(long long choice)
    {
        long long oldTableSize = Tablesize, OldCollisionCounter = collisionCounter;
        if (choice == 1)
        {
            Tablesize = nearestPrime(Tablesize * 2);
        }
        else
        {
            Tablesize = nearestPrime(Tablesize / 2);
        }
        vector<Node *> oldTable = HashTable;
        InitializeTable();
        for (long long i = 0; i < oldTableSize; i++)
        {
            Node *temp = oldTable[i];
            while (temp != nullptr)
            {
                insert(temp->getKey(), temp->getValue());
                temp = temp->getNext();
            }
        }
        oldTable.clear();
    }

    // collisions = oldCollisions;
    // delete[] oldTable;

    // HashTable.resize(Tablesize + 1);
    // }
    string generateRandomWord(long long length)
    {
        static const string allCharacters = "abcdefghijklmnopqrstuvwxyz";
        long long allCharacters_size = 26;
        string word;

        for (long long i = 0; i < length; i++)
        {
            long long index = rand() % allCharacters_size;
            word += allCharacters[index];
        }

        return word;
    }
    int myHash1(string x)
    {
        int hashVal = HashFunction1(x);
        // hashVal %= theLists.size();
        hashVal %= Tablesize;
        if (hashVal < 0)
        {
            hashVal += Tablesize;
        }
        return hashVal;
    }
    // bool insert(string key,long long value)
    // {

    // }
};

int main()
{
    // OpenChainingHash H;
    cout << HashFunction1("ab") << endl;
    // while (true)
    // cout << H.generateRandomWord(5) << endl;

    return 0;
}