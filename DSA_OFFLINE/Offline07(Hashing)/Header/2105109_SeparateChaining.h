#include <iostream>
#include "2105109_Node.h"
#include "2105109_HashFunction.h"
#include <math.h>
#include <random>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;
// template <typename T, typename E>

// template <typename T, typename E>
class SeparateChaining
{
public:
    long long Tablesize, InitialTableSize, collisionCounter = 0, ProbeCounter, HashFunctionCnt, size, noOfElements = 0;
    vector<list<Node *>> theLists;
    long long insertCnt = 0, deletecnt = 0;
    int maxChainLength;
    int abd = 1;
    vector<string> allKeys;
    // Node **HashTable;
    vector<Node *> HashTable;
    SeparateChaining(long long n, long long hashFunction)
    {
        this->Tablesize = nearestPrime(n);
        this->InitialTableSize = Tablesize;
        this->HashFunctionCnt = hashFunction;
        InitializeTable();
        // this->HashTable = new Node *[Tablesize + 1];
    }
    SeparateChaining(long long n, long long hashFunction, long long maxChainLength)
    {
        this->Tablesize = nearestPrime(n);
        this->HashFunctionCnt = hashFunction;
        this->maxChainLength = maxChainLength;
        this->ProbeCounter = 0;
        InitializeTable();
        // cout<<Tablesize<<" "<<HashFunctionCnt<<" "<<maxChainLength<<endl;
        //  this->HashTable = new Node *[Tablesize + 1];
    }
    void InitializeTable()
    {
        this->HashTable.resize(Tablesize);
        for (int i = 0; i < Tablesize; i++)
        {
            HashTable[i] = nullptr;
        }
    }
    long long checkChainLength()
    {
        int len = INT16_MIN;
        for (int i = 0; i < HashTable.size(); i++)
        {
            Node *temp = HashTable[i];
            int templen = 0;
            while (temp != nullptr)
            {
                templen++;
                temp = temp->getNext();
            }
            if (templen > len)
            {
                len = templen;
            }
        }
        return len;
    }
    /*
    Also, after every 100 deletions from your table, check whether the maximum chain length has fallen below 0.8×C.
    If so, rehash to a new table with approximately half the size. But do not rehash if the new table size would fall
    below the initial size, N.

    */

    void Delete(string key)
    {
        long long i;
        // cout << deletecnt << " :Deleting" << endl;
        if (deletecnt % 100 == 0 && deletecnt != 0)
        {
            // cout << "deletecnt 100 Rehashing" << endl;
            if ((0.8 * checkChainLength()) < maxChainLength)
            {
                if (nearestPrime(0.5 * Tablesize) > InitialTableSize)
                {
                    // cout << "Rehashing" << endl;
                    ReHashing(2);
                }
            }
        }
        if (HashFunctionCnt == 1)
        {
            // i = HashFunction1(key);
            i = myHash1(key);
        }
        else
        {
            i = myHash2(key);
        }
        if (HashTable[i] == nullptr)
        {
            // cout << "Not Exist" << endl;
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
                deletecnt++;
                noOfElements--;
                // cout << "Got the value" << endl;
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
                    noOfElements--;
                    deletecnt++;
                    // cout << "Loop e paichi value" << endl;
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
            i = myHash1(key);
        }
        else
        {
            i = myHash2(key);
        }
        if (HashTable[i] == nullptr)
        {
            return -1;
        }
        else
        {
            Node *temp = HashTable[i];
            // ProbeCounter++;
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
                // ProbeCounter++;
            }
        }
    }
    long long find(string key)
    {

        long long i;
        if (HashFunctionCnt == 1)
        {
            i = myHash1(key);
        }
        else
        {
            i = myHash2(key);
        }
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
    void insert(string key, long long value)
    {
        long long i;
        // cout<<"Aschi insert e"<<endl;
        if (Search(key) != -1)
        {
            return;
        }
        // cout<<insertCnt<<" :insert"<<endl;
        if (insertCnt % 100 == 0 && insertCnt != 0)
        {
            // cout << "Atleast Here!!" << endl;
            if (maxChainLength < checkChainLength())
            {
                // cout << "Aal is well: " << checkChainLength() << endl;

                ReHashing(1);
            }
        }

        if (HashFunctionCnt == 1)
        {
            // i = HashFunction1(key);
            i = myHash1(key);
        }
        else
        {
            i = myHash2(key);
        }
        if (HashTable[i] == nullptr)
        {
            HashTable[i] = new Node(key, value);
        }
        else
        {
            collisionCounter++;
            Node *t = HashTable[i];
            Node *newNode = new Node(key, value);
            newNode->setNxt(t);
            HashTable[i] = newNode;
            // while (temp->getNext() != nullptr)
            // {
            //     temp = temp->getNext();
            // }
            // temp->setNxt(new Node(key, value));
        }
        size++;
        insertCnt++;
        noOfElements++;
        allKeys.push_back(key);
        // cout << abd++ << " Here I am!!!" << endl;
        //  cout<<"Aal is well"<<endl;
    }
    void ReHashing(long long choice)
    {
        long long oldTableSize = Tablesize, OldCollisionCounter = collisionCounter;
        cout << "Before Rehasing:" << endl;
        cout<<"__________________"<<endl;
        int searchSize=0.1*allKeys.size();
        for (int i = 0; i <searchSize; i++)
        {
            // cout<<"Vai Please"<<endl;
            long long t1 = rand() % allKeys.size();
            find(allKeys[t1]);
        }
        cout<<"average probecount: "<<((ProbeCounter*1.0)/searchSize)<<endl;
        cout<<"load factor: "<<(noOfElements*1.0)/Tablesize<<endl;
        cout<<"maximum chainlength: "<<checkChainLength()<<endl;
        ProbeCounter=0;
        if (choice == 1)
        {
            Tablesize = nearestPrime(Tablesize * 2);
            // cout << "Tablesize: " << Tablesize << endl;
        }
        else
        {
            Tablesize = nearestPrime(Tablesize / 2);
        }
        vector<Node *> oldTable = HashTable;
        // cout<<"Printing Old Table****"<<endl;
        // printInternal(oldTable);
        // cout<<"Done****"<<endl;
        InitializeTable();
        // cout<<"Printing after Initialization**"<<endl;
        // printInternal(HashTable);
        // cout<<"OKay Printed"<<endl;
        // insertCnt = 0;
        long long i;
        for (long long j = 0; j < oldTable.size(); j++)
        {
            Node *temp = oldTable[j];
            while (temp != nullptr)
            {
                if (HashFunctionCnt == 1)
                {
                    // i = HashFunction1(key);
                    i = myHash1(temp->getKey());
                }
                else
                {
                    // cout<<"hash function 2"<<endl;
                    i = myHash2(temp->getKey());
                }
                // cout << "(" << temp->getKey() << ", " << temp->getValue() << ") : "<<i<<endl;
                if (HashTable[i] == nullptr)
                {
                    HashTable[i] = new Node(temp->getKey(), temp->getValue());
                }
                else
                {
                    // collisionCounter++;
                    Node *t = HashTable[i];
                    Node *newNode = new Node(t->getKey(), t->getValue());
                    newNode->setNxt(t);
                    HashTable[i] = newNode;
                }
                // insert(temp->getKey(), temp->getValue());
                temp = temp->getNext();
            }
        }
         cout << "After Rehasing:" << endl;
        cout<<"__________________"<<endl;
         searchSize=0.1*allKeys.size();
        for (int i = 0; i <searchSize; i++)
        {
            // cout<<"Vai Please"<<endl;
            long long t1 = rand() % allKeys.size();
            find(allKeys[t1]);
        }
        cout<<"average probecount: "<<((ProbeCounter*1.0)/searchSize)<<endl;
        cout<<"load factor: "<<(noOfElements*1.0)/Tablesize<<endl;
        cout<<"maximum chain length: "<<checkChainLength()<<endl;
        ProbeCounter=0;
    }

    // collisions = oldCollisions;
    // delete[] oldTable;
    // HashTable.resize(Tablesize + 1);
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
    int myHash2(string x)
    {
        int hashVal = HashFunction2(x);
        // hashVal %= theLists.size();
        hashVal %= Tablesize;
        if (hashVal < 0)
        {
            hashVal += Tablesize;
        }
        return hashVal;
    }
    void print()
    {
        cout << "Hash Table Contents:" << endl;
        for (long long i = 0; i < Tablesize; ++i)
        {
            cout << "Bucket " << i << ": ";
            if (HashTable[i] == nullptr)
            {
                cout << "Empty";
            }
            else
            {
                Node *temp = HashTable[i];
                while (temp != nullptr)
                {
                    cout << "(" << temp->getKey() << ", " << temp->getValue() << ") ";
                    temp = temp->getNext();
                }
            }
            cout << endl;
        }
    }
    void printInternal(vector<Node *> &HashTable)
    {
        cout << "Hash Table Contents:" << endl;
        for (long long i = 0; i < HashTable.size(); ++i)
        {
            cout << "Bucket " << i << ": ";
            if (HashTable[i] == nullptr)
            {
                cout << "Empty";
            }
            else
            {
                Node *temp = HashTable[i];
                while (temp != nullptr)
                {
                    cout << "(" << temp->getKey() << ", " << temp->getValue() << ") ";
                    temp = temp->getNext();
                }
            }
            cout << endl;
        }
    }

    // bool insert(string key,long long value)
    // {

    // }
};