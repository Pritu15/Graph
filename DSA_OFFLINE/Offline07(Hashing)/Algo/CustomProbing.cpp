#include <iostream>
#include "Node.h"
#include "HashFunction.h"
#include <math.h>
#include <random>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

class DoubleHash
{
    vector<Node *> HashTable;
    long long Tablesize, collisionCounter, ProbeCounter, HashFunctionCnt, size;
    const long long C1 = 37, C2 = 41;

public:
    DoubleHash(long long n, long long HashFunctionCnt)
    {
        this->Tablesize = nearestPrime(n);
        this->HashFunctionCnt = HashFunctionCnt;
        InitializeTable();
    }
    void InitializeTable()
{
    this->HashTable.resize(Tablesize, nullptr); // Initialize with nullptr
}

void insert(string key, long long value)
{
    if (Find(key) != -1)
    {
        return;
    }
    long long i = 0;
    long long h = doubleHash(key, i);
    long long Previous;
    long long Offset = 0;
    while (HashTable[h] != nullptr && i < Tablesize) // Check for null pointer
    {
        Previous = h;
        h = (Offset + doubleHash(key, ++i)) % Tablesize;
        if (h == Previous)
        {
            Offset++;
            i = 0;
        }
        collisionCounter++;
    }
    if (HashTable[h] == nullptr)
    {
        HashTable[h] = new Node(key, value);
        size++;
    }
}

long long Find(string key)
{
    long long i = 0;
    long long h = doubleHash(key, i);
    long long Previous;
    long long Offset = 0;
    while (HashTable[h] != nullptr && i < Tablesize)
    {
        Previous = h;
        if (HashTable[h]->getKey() == key)
        {
            ProbeCounter++;
            return HashTable[h]->getValue();
        }
        h = (Offset + doubleHash(key, ++i)) % Tablesize;
        if (h == Previous)
        {
            Offset++;
            i = 0;
        }
        else
        {
            ProbeCounter++;
        }
    }
    return -1;
}

void remove(string key)
{
    long long i = 0;
    long long h = doubleHash(key, i);
    long long Previous;
    long long Offset = 0;
    while (HashTable[h] != nullptr && i < Tablesize)
    {
        Previous = h;
        if (HashTable[h]->getKey() == key)
        {
            ProbeCounter++;
            delete HashTable[h]; // Deallocate memory
            HashTable[h] = nullptr; // Set to null pointer
            size--;
            return;
        }
        h = (Offset + doubleHash(key, ++i)) % Tablesize;
        if (h == Previous)
        {
            Offset++;
            i = 0;
        }
        else
        {
            ProbeCounter++;
        }
    }
}


    // void InitializeTable()
    // {
    //     this->HashTable.resize(Tablesize);
    //     for (long long i = 0; i <= Tablesize; i++)
    //     {
    //         HashTable[i] = nullptr;
    //     }
    // }

    // void insert(string key,long long value)
    // {
    //     if(Find(key)!=-1)
    //     {
    //         return;
    //     }
    //     long long i = 0;
    //     long long h = doubleHash(key, i);
    //     long long Previous;
    //     long long Offset = 0;
    //     while (HashTable[h]->getKey() != "")
    //     {
    //         Previous = h;
    //         // if (HashTable[h]->getKey() == key)
    //         // {
    //         //     ProbeCounter++;
    //         //     //return HashTable[h]->getValue();
    //         // }
    //         h = (Offset + doubleHash(key, ++i) )% Tablesize;
    //         if (h == Previous)
    //         {
    //             Offset++;
    //             i = 0;
    //         }
    //         collisionCounter++;

    //     }
    //     //return -1;
    //     HashTable[h]=new Node(key,value);
    //     size++;
    // }
    
    // long long Find(string key)
    // {
    //     long long i = 0;
    //     long long h = doubleHash(key, i);
    //     long long Previous;
    //     long long Offset = 0;
    //     // if(HashTable[h]==nullptr)
    //     // {
    //     //     return -1;
    //     // }
    //     while (HashTable[h]->getKey() != "" && i < Tablesize)
    //     {
    //         Previous = h;
    //         if (HashTable[h]->getKey() == key)
    //         {
    //             ProbeCounter++;
    //             return HashTable[h]->getValue();
    //         }
    //         h = (Offset + doubleHash(key, ++i) )% Tablesize;
    //         if (h == Previous)
    //         {
    //             Offset++;
    //             i = 0;
    //         }
    //         else
    //         {
    //             ProbeCounter++;
    //         }
    //     }
    //     return -1;
    // }
    long long doubleHash(string key, long long i)
    {
        // customHash(k, i) = (Hash(k) + C1 × i × auxHash(k) + C2 × i2) % N

        if (HashFunctionCnt == 1)
        {
            return (myHash1(key) + (C1*i * (auxHash(key) % Tablesize))+(C2*i*i)) % Tablesize;
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
    // void remove(string key)
    // {
        
    //     long long i = 0;
    //     long long h = doubleHash(key, i);
    //     long long Previous;
    //     long long Offset = 0;
    //     while (HashTable[h]->getKey() != "" && i < Tablesize)
    //     {
    //         Previous = h;
    //         if (HashTable[h]->getKey() == key)
    //         {
    //             ProbeCounter++;
    //             HashTable[h]=new Node();
    //             size--;
    //             return;
    //             //return HashTable[h]->getValue();
    //         }
    //         h = (Offset + doubleHash(key, ++i) )% Tablesize;
    //         if (h == Previous)
    //         {
    //             Offset++;
    //             i = 0;
    //         }
    //         else
    //         {
    //             ProbeCounter++;
    //         }
    //     }
    //     //return -1;

    // }
};

int main()
{
    DoubleHash H(5,1);
    H.insert("Pritu",109);
    H.insert("Pritu",109);
    H.insert("Pritu",109);
    H.insert("Pritu",109);
    H.insert("Pritu",109);
    H.insert("Pritu",109);
    H.insert("Pritu",109);
    H.insert("Pritu",109);
    H.insert("Pritu",109);
    H.insert("Pritu",109);
    H.insert("Pritu",109);
    H.insert("Pritu",109);
    H.insert("Pritu",109);
    H.insert("Pritu",109);
    H.insert("Pritu",109);
    H.insert("Pritu",109);
    H.insert("Pritu",109);
    H.insert("Pritu",109);
    H.insert("Pritu",109);
    H.insert("Pritu",109);
    H.insert("Pritu",109);

    cout<<"HIIII"<<endl;

    return 0;
}