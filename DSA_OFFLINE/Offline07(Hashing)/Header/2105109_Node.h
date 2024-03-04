#ifndef NODE_H
#define NODE_H

#include<iostream>
using namespace std;
class Node
{
    string key;
    long long value;
    Node *nxt;
    bool deleted;

public:
    Node(string key="", long long value=-1,Node* next=nullptr)
    {
        this->key = key;
        this->value = value;
        this->nxt = next;
        this->deleted=false;
    }
    void SetKey(string key)
    {
        this->key = key;
    }
    void SetDeleted(bool flag)
    {
        this->deleted=flag;
    }
    bool getDeleted()
    {
        return this->deleted;
    }
    string getKey()
    {
        return this->key;
    }
    void setValue(long long value)
    {
        this->value = value;
    }
    long long getValue()
    {
        return this->value;
    }
    void setNxt(Node *nxt)
    {
        this->nxt = nxt;
    }
    Node *getNext()
    {
        return this->nxt;
    }
};
#endif // NODE_H