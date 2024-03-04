#include <iostream>
#include "2105109_Node.h"
#include "2105109_HashFunction.h"
#include <math.h>
#include <random>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

class DoubleHash
{

    // const long long c1 = 37, c2 = 41;

public:
    vector<Node *> HashTable;
    long long Tablesize, collisionCounter = 0, ProbeCounter = 0, HashFunctionCnt = 0, size = 0, noOfElements = 0;
    DoubleHash(long long n, long long HashFunctionCnt)
    {
        this->Tablesize = nearestPrime(n);
        this->HashFunctionCnt = HashFunctionCnt;
        InitializeTable();
    }
    void InitializeTable()
    {
        this->HashTable.resize(Tablesize);
        for (int i = 0; i < Tablesize; i++)
        {
            HashTable[i] = nullptr;
        }
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
        long long h = doubleHash(key, i);
        long long Previous;
        // long long Offset = 0;
        while (HashTable[h] != nullptr && i < Tablesize)
        {
            Previous = h;
            h = doubleHash(key, ++i) % Tablesize;
            // if (h == Previous)
            // {
            //     i = 0;
            // }
            
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
        long long h = doubleHash(key, i);
        long long Previous;
        long long Offset = 0;
        while (HashTable[h] != nullptr && i < Tablesize)
        {
            Previous = h;
            if (HashTable[h]->getKey() == key&& HashTable[h]->getDeleted()==false)
            {
                // ProbeCounter++;
                return HashTable[h]->getValue();
            }
            h = (doubleHash(key, ++i)) % Tablesize;
            // if (h == Previous)
            // {
            //     Offset++;
            //     i = 0;
            // }
            // else
            // {
            // ProbeCounter++;
            // }
        }
        return -1;
    }
    long long find(string key)
    {
        long long i = 0;
        long long h = doubleHash(key, i);
        long long Previous;
        //long long Offset = 0;
        while (i < Tablesize && HashTable[h] != nullptr)
        {
            //Previous = h;
            if (HashTable[h]->getKey() == key && HashTable[h]->getDeleted()==false)
            {
                ProbeCounter++;
                return HashTable[h]->getValue();
            }
            h = (doubleHash(key, ++i)) % Tablesize;
            ProbeCounter++;
             if (i == Tablesize)
        {
            break;
        }
        }
        return -1;
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

    void remove(string key)
    {
        long long i = 0;
        long long h = doubleHash(key, i);
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
            h = (doubleHash(key, ++i)) % Tablesize;
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

    long long doubleHash(string key, long long i)
    {
        // doubleHash(k, i) = (Hash(k) + i × auxHash(k)) % N

        if (HashFunctionCnt == 1)
        {
            return (myHash1(key) + (i * (auxHash(key) % Tablesize))) % Tablesize;
        }
        else
        {
            return (myHash2(key) + (i * (auxHash(key) % Tablesize))) % Tablesize;
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
                insert(temp->getKey(),temp->getValue());
            }
        }
        ProbeCounter=0;
    }
    // void remove(string key)
    // {

    //     long long i = 0;
    //     long long h = DoubleHash(key, i);
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
    //         h = (Offset + DoubleHash(key, ++i) )% Tablesize;
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
//     long long Find(const string & s){
//         int i=1;
//         int key=doubleHash(s);
//         if(HashTable[key]==nullptr){
//           return -1;
//         }
//         else if(HashTable[key]->getKey()==s){
//             return HashTable[key]->getKey();
//         }
//         else {
//            while(HashTable[key] &&HashTable[key]->getKey()!=s){
//             i++;
//             key=doubleHash(s,i);
//             if(table[key]&&table[key]->key==s){
//                 ProbeCounter+=i;
//                 return table[key];

//             }

//            }
//         }
//         searchProbe+=i;
//         return nullptr;
//     }
};