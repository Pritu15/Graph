#include <iostream>
#include<vector>
#include "2105109_CustomProbing.h"
#include "2105109_DoubleHash.h"
#include "2105109_Node.h"
#include "2105109_HashFunction.h"
#include "2105109_SeparateChaining.h"
using namespace std;
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
int main()
{
    //SeparateChaining S(10000, 1, 6);
    vector<string> allKeys;
     CustomProbing S(10000,2);
    //  DoubleHash S(10000,2);
    /*
    Bucket 0: (qduxwfnfoz, 3) (xggbwkf, 2)
Bucket 1: Empty
Bucket 2: (srenzkycx, 9) (ggxrpnrvys, 5) (lfdxfircvs, 1)
Bucket 3: Empty
Bucket 4: Empty
Bucket 5: (vikeffm, 7) (hqghumeayl, 0)
Bucket 6: (mwcysyycqp, 6)
Bucket 7: Empty
Bucket 8: Empty
Bucket 9: (nimkkasv, 8)
Bucket 10: (srtkjpre, 4)
    */
//     S.insert("hqghumeayl", 0);
//     //S.print();
//     S.insert("lfdxfircvs", 1);
//     //S.print();
//     S.insert("xggbwkf", 2);
//     //S.print();
//     S.insert("qduxwfnfoz", 3);
//     //S.print();
//     S.insert("srtkjpre", 4);
//     //S.print();
//     S.insert("ggxrpnrvys", 5);
//     //S.print();
//     S.insert("mwcysyycqp", 6);
//     //S.print();
//     S.insert("vikeffm", 7);
//     //S.print();
//     S.insert("nimkkasv", 8);
//    // S.print();
//     S.insert("srenzkycx", 9);
//     S.print();
//     S.insert("srenzkycx", 10);

    // S.insert("",1);

    for (int i = 0; i < 10000; i++)
    {
        //cout<<"OOO"<<endl;
        string temp=generateRandomWord((rand() % 6) + 5);
        allKeys.push_back(temp);
        //cout<<"ORI "<<endl;
        S.insert(temp, i);
    }
    //cout << "All is Well" << endl;
    //S.print();
    for (int i = 0; i < 1000; i++)
    {
        //cout<<"Vai Please"<<endl;
        long long t1=rand()%10000;
        S.search(allKeys[t1]);
    }
    S.ReHashing(1);
    S.print();
    //S.print();
    //cout << S.HashTable.size() << endl;
   // cout << S.checkChainLength() << endl;
    cout<<"Collision counter:"<<S.collisionCounter<<endl;
    cout<<"Probe Count: "<<S.ProbeCounter*1.0/1000<<endl;
    return 0;
}