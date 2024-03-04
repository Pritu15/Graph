#include<iostream>
using namespace std;
class Node
{
    string key;
    long long value;
    Node *nxt;

public:
    Node(string key="", long long value=-1,Node* next=nullptr)
    {
        this->key = key;
        this->value = value;
        this->nxt = next;
    }
    void SetKey(string key)
    {
        this->key = key;
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