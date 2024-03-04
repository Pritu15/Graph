#include <iostream>
#include "2105109_Node.h"
#include "2105109_HashFunction.h"
#include <math.h>
#include <random>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

class CustomProbing
{
  

public:
  vector<Node *> HashTable;
    long long Tablesize, collisionCounter=0, ProbeCounter=0, HashFunctionCnt, size,noOfElements=0;
    const long long C1 = 37, C2 = 41;
    CustomProbing(long long n, long long HashFunctionCnt)
    {
        this->Tablesize = nearestPrime(n);
        this->HashFunctionCnt = HashFunctionCnt;
        InitializeTable();
    }
    void InitializeTable()
    {
        this->HashTable.resize(Tablesize, nullptr);
    }
    double checkLoadFactor()
    {
        return noOfElements/Tablesize;
    }

    void insert(string key, long long value)
    {
          if(noOfElements>=Tablesize)
        {
            return;
        }
        if (Find(key) != -1)
        {
            return;
        }
        long long i = 0;
        long long h = customProbing(key, i);
        long long Previous;
        long long Offset = 0;
        while (HashTable[h] != nullptr && i < Tablesize)
        {
            Previous = h;
            h = (customProbing(key, ++i)) % Tablesize;
            // if (h == Previous)
            // {
            //     Offset++;
            //     i = 0;
            // }
            //collisionCounter++;
        }
        if(i>0)
        {
            collisionCounter++;

        }
        if (HashTable[h] == nullptr)
        {
            HashTable[h] = new Node(key, value);
            size++;
            noOfElements++;
        }
    }

    long long Find(string key)
    {
        long long i = 0;
        long long h = customProbing(key, i);
        long long Previous;
        long long Offset = 0;
        while (HashTable[h] != nullptr && i < Tablesize)
        {
            //Previous = h;
            if (HashTable[h]->getKey() == key&& HashTable[h]->getDeleted()==false)
            {
                //ProbeCounter++;
                return HashTable[h]->getValue();
            }
            h = ( customProbing(key, ++i)) % Tablesize;
            // if (h == Previous)
            // {
            //     Offset++;
            //     i = 0;
            // }
            // else
            // {
                //ProbeCounter++;
            //}
        }
        return -1;
    }
    long long search(string key)
    {
        long long i = 0;
        long long h = customProbing(key, i);
        long long Previous;
        long long Offset = 0;
        while (HashTable[h] != nullptr && i < Tablesize)
        {
            //Previous = h;
            if (HashTable[h]->getKey() == key&& HashTable[h]->getDeleted()==false)
            {
                ProbeCounter++;
                return HashTable[h]->getValue();
            }
            h = (customProbing(key, ++i)) % Tablesize;
            // if (h == Previous)
            // {
            //     Offset++;
            //     i = 0;
            // }
            // else
            // {
                ProbeCounter++;
                if (i == Tablesize)
        {
            break;
        }
            // }
        }
        return -1;
    }
    void print()
    {
        cout << "Hash Table Contents:" << endl;
        for (long long i = 0; i < Tablesize; ++i)
        {
            cout << "Bucket " << i << ": ";
            if (HashTable[i] == nullptr|| HashTable[i]->getDeleted()==true)
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

    void remove(string key)
    {
        long long i = 0;
        long long h = customProbing(key, i);
        long long Previous;
        long long Offset = 0;
        while (HashTable[h] != nullptr && i < Tablesize)
        {
            Previous = h;
            if (HashTable[h]->getKey() == key&& HashTable[h]->getDeleted()==false)
            {
                ProbeCounter++;
                HashTable[h]->SetDeleted(true);
                //delete HashTable[h];    // Deallocate memory
                //HashTable[h] = nullptr; // Set to null pointer
                size--;
                noOfElements--;
                return;
            }
            h = (customProbing(key, ++i)) % Tablesize;
            // if (h == Previous)
            // {
            //     Offset++;
            //     i = 0;
            // }
            // else
            // {
                ProbeCounter++;
            // }
        }
    }
    void ReHashing(long long choice)
    {
        long long oldTableSize = Tablesize, OldCollisionCounter = collisionCounter;
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
        noOfElements=0;
        // cout<<"Printing after Initialization**"<<endl;
        // printInternal(HashTable);
        // cout<<"OKay Printed"<<endl;
        // insertCnt = 0;
        long long i;
        for (long long j = 0; j < oldTable.size(); j++)
        {
            Node *temp = oldTable[j];
            if(temp!=nullptr)
            {
                if(temp->getDeleted()==false)
                {
                insert(temp->getKey(),temp->getValue());
                }
            }
        }
        ProbeCounter=0;
    }

    long long customProbing(string key, long long i)
    {
        // customHash(k, i) = (Hash(k) + C1 × i × auxHash(k) + C2 × i2) % N

        if (HashFunctionCnt == 1)
        {
            return (myHash1(key) + (C1 * i * (auxHash(key) % Tablesize)) + (C2 * i * i)) % Tablesize;
        }
        else{
            return (myHash2(key) + (C1 * i * (auxHash(key) % Tablesize)) + (C2 * i * i)) % Tablesize;

        }
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
};