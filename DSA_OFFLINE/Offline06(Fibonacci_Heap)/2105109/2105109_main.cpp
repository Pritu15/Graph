#include <iostream>
#include <math.h>
using namespace std;

template <typename T, typename E>
class Node
{

public:
    T key;
    E value;
    int degree;
    bool mark;
    Node<T, E> *Parent;
    Node<T, E> *Child;
    Node<T, E> *left;
    Node<T, E> *right;
    Node(T key, E value)
    {
        this->key = key;
        this->value = value;
        this->degree = 0;
        this->mark = false;
        this->Parent = nullptr;
        this->Child = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }
};

template <typename T, typename E>
class FibonacciHeap
{

public:
    Node<T, E> *max;
    Node<T, E> *rootList;
    int noOfTrees;
    int noOfNodes;

    FibonacciHeap()
    {
        this->max = nullptr;
        this->rootList = nullptr;
        this->noOfTrees = 0;
        this->noOfNodes = 0;
    }
    int getN()
    {
        return noOfTrees;
    }
    Node<T, E> *getmax()
    {
        return max;
    }
    void setmax(Node<T, E> *x)
    {
        this->max = x;
    }
    int getNoOfTrees()
    {
        return this->noOfTrees;
    }
};
template <typename T, typename E>
class PriorityQueue
{
    int size;
    Node<T, E> *valueKey[100000];

public:
    FibonacciHeap<T, E> *make_Heap()
    {
        this->size = 0;
        return new FibonacciHeap<T, E>();
    }
    void insert(FibonacciHeap<T, E> *H, T key, E value)
    {
        Node<T, E> *node = new Node<T, E>(key, value);
        node->left = node;
        node->right = node;
        // cout<<"In Insert"<<endl;
        mergeWithRootList(H, node);

        if ((H->max == nullptr) || node->key > H->max->key)
        {
            H->max = node;
        }
        H->noOfNodes += 1;
    }
    FibonacciHeap<T, E> *meld(FibonacciHeap<T, E> *H1, FibonacciHeap<T, E> *H2)
    {
        FibonacciHeap<T, E> *H = make_Heap();
        if (H1->max == nullptr && H2->max == nullptr)
        {
            return H;
        }

        if (H1->max != nullptr && H2->max != nullptr)
        {
            H->max = H1->max->key > H2->max->key ? H1->max : H2->max;
        }
        else if (H1->max != nullptr)
        {
            H->max = H1->max;
        }
        else
        {
            H->max = H2->max;
        }

        if (H1->rootList != nullptr && H2->rootList != nullptr)
        {
            H->rootList = H1->rootList;
            Node<T, E> *H1End = H1->rootList->left;
            Node<T, E> *H2End = H2->rootList->left;

            H1End->right = H2->rootList;
            H2->rootList->left = H1End;

            H2End->right = H->rootList;
            H->rootList->left = H2End;
        }
        else if (H1->rootList != nullptr)
        {
            H->rootList = H1->rootList;
            as
        }
        else
        {
            H->rootList = H2->rootList;
        }

        H->noOfTrees = H1->noOfTrees + H2->noOfTrees;
        return H;
    }

    void Extract_max(FibonacciHeap<T, E> *H)
    {
        // Print(H);
        Node<T, E> *z = H->max;
        // cout<<"Z key "<<z->key<<endl;
        if (z != nullptr)
        {
            if (z->Child != nullptr)
            {
                Node<T, E> *temp;
                temp = z->Child;
                for (int i = 0; i < z->degree; i++)
                {
                    if (temp == z)
                    {
                        break;
                    }
                    Node<T, E> *store = temp->right;
                    mergeWithRootList(H, temp);
                    temp->Parent = nullptr;
                    temp = store;
                }
            }
            removeFromRootList(H, z);
            if (z == z->right)
            {
                H->max = nullptr;
                H->rootList = nullptr;
            }
            else
            {
                H->max = z->right;
                // cout<<H->max->key<<endl;
                this->CONSOLIDATE(H);
                // cout<<"Consolidated"<<endl;
            }
        }
        // H->noOfTrees--;
        H->noOfNodes -= 1;
    }

    void removeFromRootList(FibonacciHeap<T, E> *H, Node<T, E> *node)
    {
        if (node == H->rootList)
        {
            H->rootList = node->right;
        }
        node->left->right = node->right;
        node->right->left = node->left;
        H->noOfTrees--;
        // cout<<"removeFromRootList"<<endl;
        // Print(H);
        // cout<<"Hi"<<endl;
    }

    void CONSOLIDATE(FibonacciHeap<T, E> *H)
    {
        // cout << "Consolidate" << endl;
        int d;
        float f = (log(H->noOfTrees)) / (log(2));
        int D = f + 10;
        // cout <<"D: "<< D << endl;
        Node<T, E> *A[D];
        Node<T, E> *w = H->rootList;
        Node<T, E> *x;
        Node<T, E> *y;
        // int d;
        int noOfTrees = H->noOfTrees;
        for (int i = 0; i < D; i++)
        {
            A[i] = nullptr;
        }
        for (int i = 0; i < noOfTrees; i++)
        {
            // cout<<"Oh God  Please"<<endl;
            x = w;
            // cout<<"w:"<<w->key<<endl;
            w = w->right;
            // cout<<"w->right:"<<w->key<<endl;
            // cout << "x " << x->key << "->" << x->value << endl;
            d = x->degree;
            // cout<<"x->degree:"<<d<<endl;
            while (A[d] != nullptr)
            {
                y = A[d];
                // cout << "A[" << d << "]" << A[d]->key << endl;
                if (x->key < y->key)
                {
                    Node<T, E> *temp = x;
                    x = y;
                    y = temp;
                }
                // cout << "Before Heap Link" << endl;
                // cout << x->key << "->" << x->value << endl;
                // cout << y->key << "->" << y->value << endl;
                // cout << "After Heap Link" << endl;
                HEAP_LINK(H, y, x);
                A[d] = nullptr;
                // x->degree += 1;
                d++;
            }
            // cout << "W " << x->key << "->" << x->value << endl;
            // w = w->right;
            A[d] = x;
        }
        for (int i = 0; i < D; i++)
        {
            if (A[i] != nullptr)
            {
                if (A[i]->key > H->max->key)
                {
                    H->max = A[i];
                }
            }
        }
    }
    void HEAP_LINK(FibonacciHeap<T, E> *H, Node<T, E> *y, Node<T, E> *x)
    {
        removeFromRootList(H, y);
        y->left = y->right = y;
        mergeWithChildList(x, y);
        x->degree++;
        y->Parent = x;
        y->mark = false;
    }
    void mergeWithChildList(Node<T, E> *x, Node<T, E> *y)
    {
        if (x->Child == nullptr)
        {
            x->Child = y;
        }
        else
        {
            y->right = x->Child->right;
            y->left = x->Child;
            x->Child->right->left = y;
            x->Child->right = y;
        }
    }
    Node<T, E> *Search(Node<T, E> *root, E value)
    {
        if (root == nullptr || root->mark)
        {
            return nullptr;
        }

        Node<T, E> *x = root;
        x->mark = true;
        Node<T, E> *requirednode = nullptr;

        if (root->value == value)
        {
            requirednode = root;
            x->mark = false;
            return requirednode;
        }

        if (requirednode == nullptr && root->Child != nullptr)
        {
            requirednode = Search(root->Child, value);
        }

        if (requirednode == nullptr && !((root->right)->mark))
        {
            requirednode = Search(root->right, value);
        }

        x->mark = false;
        return requirednode;
    }
    void Increase_key(FibonacciHeap<T, E> *H, E value, T newKey)
    {
        // Node<T, E> *x = Search(H->rootList, value);
        Node<T, E> *x = valueKey[value];
        // cout<<x->key<<endl;
        if (x == nullptr || (newKey < x->key))
        {
            cout << value << " not found" << endl;
            return;
        }
        Node<T, E> *y = x->Parent;
        // cout << x->key << endl;
        //  cout<<y->key<<endl;
        x->key = newKey;
        if (y != nullptr && x->key > y->key)
        {
            // cout << x->key << endl;
            // cout << y->mark << endl;
            CUT(H, x, y);
            CASCADING_CUT(H, y);
        }
        if (x->key > H->max->key)
        {
            H->max = x;
        }
        H->noOfNodes -= 1;
    }
    void CUT(FibonacciHeap<T, E> *H, Node<T, E> *x, Node<T, E> *y)
    {
        removeFromChildList(y, x);
        y->degree--;
        mergeWithRootList(H, x);
        x->Parent = nullptr;
        x->mark = false;
        // Print(H);
    }
    void mergeWithRootList(FibonacciHeap<T, E> *H, Node<T, E> *node)
    {
        if (H->rootList == nullptr)
        {
            H->rootList = node;
        }
        else
        {

            node->right = H->rootList;
            node->left = H->rootList->left;
            H->rootList->left->right = node;
            H->rootList->left = node;
        }
        valueKey[node->value] = node;
        H->noOfTrees += 1;
    }
    void CASCADING_CUT(FibonacciHeap<T, E> *H, Node<T, E> *x)
    {
        Node<T, E> *temp = x->Parent;
        if (temp != nullptr)
        {
            if (!(x->mark))
            {
                x->mark = true;
                // cout << "Marked" << endl;
            }
            else
            {
                // cout << "Marked" << endl;
                CUT(H, x, temp);
                CASCADING_CUT(H, temp);
            }
        }
    }
    void removeFromChildList(Node<T, E> *parent, Node<T, E> *node)
    {
        if (node == node->right)
        {
            parent->Child = nullptr;
        }
        node->left->right = node->right;
        node->right->left = node->left;
        // if (parent->Child == parent->Child->right)
        // {
        //     parent->Child = nullptr;

        // }
        if (parent->Child == node)
        {
            parent->Child = node->right;
            // node->right->Parent = parent;
            // node->left->right = node->right;
            // node->right->left = node->left;
        }
    }

    bool isEmpty(FibonacciHeap<T, E> *H)
    {
        if (H->rootList == nullptr)
        {
            return true;
        }
        return false;
    }
    T find_max(FibonacciHeap<T, E> *H)
    {
        if (H->max == nullptr)
        {
            return;
        }
        return H->max->key;
    }
    void PrintRootList(FibonacciHeap<T, E> *H)
    {
        // cout << "RootList Print Started" << endl;
        Node<T, E> *temp = H->rootList;
        for (int i = 0; i < H->noOfTrees; i++)
        {
            // cout << temp->key << endl;
            temp = temp->right;
        }
        // cout << "RootList Print Done" << endl;
    }
    void RecursivePrint(Node<T, E> *node, int degree)
    {
        if (node == nullptr)
        {
            return;
        }
        Node<T, E> *temp = node;
        // cout << "(" << node->key << "," << node->value << ")-> ";
        for (int i = 0; i < degree; i++)
        {
            cout << "(" << temp->key << "," << temp->value << ") ";
            temp = temp->right;
        }
        cout << endl;
        temp = node;
        for (int i = 0; i < degree; i++)
        {
            // cout<<"("<<node->key<<","<<node->value<<") ";
            //
            if (temp->Child != nullptr)
            {
                cout << "      (" << temp->key << "," << temp->value << ")-> ";
            }

            RecursivePrint(temp->Child, temp->degree);
            temp = temp->right;
        }
        return;
    }
    void Delete(FibonacciHeap<T, E> *H, E value)
    {
        Increase_key(H, value, INT16_MAX);
        Extract_max(H);
    }

    void Print(FibonacciHeap<T, E> *H)
    {
        // cout<<H->max->key<<
        Node<T, E> *temp;
        temp = H->rootList;
        // cout << H->rootList->key << endl;
        for (int i = 1; i <= H->noOfTrees; i++)
        {
            cout << "Tree " << i << ":";
            cout << "(" << temp->key << "," << temp->value << ")-> ";
            // if(temp->Child!=nullptr)
            // {
            //     cout<<"Child"<<temp->Child->key<<endl;
            // }

            RecursivePrint(temp->Child, temp->degree);
            temp = temp->right;
            cout << endl;
            // valueKey[10];
        }
    }
    void test()
    {

        FibonacciHeap<int, int> *H1 = make_Heap();
        FibonacciHeap<int, int> *H2 = make_Heap();
        int n;
        // cin >> n;

        for (int i = 1; i <= 10; i++)
        {
            // int key, value;
            //  cin >> key >> value;
            insert(H1, i, i);
        }
        // for (int i = 21; i <= 40; i++)
        // {
        //     Q.insert(H2, i, i);
        // }
        Print(H1);
        // Q.PrintRootList(H1);
        cout << "1.First Extract_max" << endl;
        Extract_max(H1);
        Print(H1);
        cout << "2.Extract Max without Child" << endl;
        // Q.Increase_key(H1,8,20);
        Extract_max(H1);
        Print(H1);
        cout << "3.Extracting which have 3 children" << endl;
        Extract_max(H1);
        Print(H1);
        cout << "4.Increase Key 6 to 10" << endl;
        Increase_key(H1, 6, 10);
        Print(H1);
        cout << "5.Extracting Max()" << endl;
        Extract_max(H1);
        Print(H1);
        cout << "6.Increasing 3 to 8" << endl;
        Increase_key(H1, 3, 8);
        Print(H1);
        cout << "7.Inserting 9 to 12" << endl;
        for (int i = 9; i <= 12; i++)
        {
            insert(H1, i, i);
        }
        Print(H1);
        cout << "8.Extracting Max" << endl;
        Extract_max(H1);
        Print(H1);
        cout << "9.increasing 5 to 12" << endl;
        Increase_key(H1, 5, 12);
        Print(H1);
        cout << "10.increasing 4 to 13" << endl;
        Increase_key(H1, 4, 13);
        Print(H1);

        cout << "11.Taking input for another Heap(2)" << endl;
        for (int i = 20; i <= 31; i++)
        {
            insert(H2, i, i);
        }
        Print(H2);
        cout << "12.Extract Max H2" << endl;
        Extract_max(H2);
        Print(H2);
        cout << "13.Melding with H1" << endl;
        FibonacciHeap<int, int> *H3 = meld(H1, H2);
        Print(H3);
        cout << "14.Deleting 7 from heap3" << endl;
        Delete(H3, 7);
        Print(H3);
        cout << "15.Deleting 27 from heap3" << endl;
        Delete(H3, 27);
        Print(H3);
        // cout<<H3->max->key<<endl;
        //
        // cout << H3->max->key << endl;

        // cout << "I Am Commanded To Say Nothing, To See Nothing." << endl;
    }
};

int main()
{
    PriorityQueue<int, int> Q;
    // Q.test();
    FibonacciHeap<int, int> *H1 = Q.make_Heap();
    for (int i = 1000; i <= 3000; i++)
    {
        Q.insert(H1, i, 2 * i);
        if (i % 100 == 0)
        {
            Q.Extract_max(H1);
        }
    }
    Q.Print(H1);
    FibonacciHeap<int, int> *H2 = Q.make_Heap();
    for (int i = 4000; i <= 7000; i++)
    {
        Q.insert(H2, i, 2 * i);
        if (i % 100 == 0)
        {
            Q.Extract_max(H2);
        }
    }
    Q.Print(H2);
    FibonacciHeap<int, int> *H = Q.meld(H1, H2);
    Q.Print(H);

    // H=make_Heap();
    // cout<<H->getN()<<endl;

    // Q.Print(H1);
    // Q.Print(H1);
    // Q.Print(H1);
    // cout<<"Max"<<H1->max->key<<endl;
    // cout<<"rootList"<<H1->rootList->key<<endl;
    // cout<<"Give up EveryThing and die"<<endl;
    /*
    cout << "Second Extract_max" << endl;
    Q.Extract_max(H1);
    // cout<<"Dreams are messages from deep"<<endl;
    Q.Print(H1);
    // Q.PrintRootList(H1);
    cout << "Third Extract_max" << endl;
    Q.Extract_max(H1);
    // cout<<"Dreams are messages from deep"<<endl;
    Q.Print(H1);
    cout << "Fourth Extract_max" << endl;
    Q.Extract_max(H1);
    // cout<<"Dreams are messages from deep"<<endl;
    Q.Print(H1);
    cout << "Fifth Extract_max" << endl;
    Q.Extract_max(H1);
    Q.Print(H1);
    cout << "Sixth" << endl;
    Q.Extract_max(H1);
    Q.Print(H1);
    cout << "7Th" << endl;
    Q.Extract_max(H1);
    Q.Print(H1);
    cout << "8 th" << endl;
    Q.Extract_max(H1);
    Q.Print(H1);
    cout << "9 th" << endl;
    Q.Extract_max(H1);
    Q.Print(H1);
    cout << "10 th" << endl;
    Q.Extract_max(H1);
    Q.Print(H1);
    cout << "HWLLLL" << endl;
    cout << "11 er" << endl;
    Q.Extract_max(H1);
    Q.Print(H1);
    cout << "12 er" << endl;
    Q.Extract_max(H1);
    Q.Print(H1);
    cout<<"13 er node count: "<<H1->noOfNodes-1<<endl;
    Q.Extract_max(H1);
    Q.Print(H1);
    // cout<<"Dreams are messages from deep"<<endl;
    // Q.Print(H1);
    // Q.Increase_key(H1, 30, 300);
    // cout<<Q.Search(H1->rootList,30)->key<<endl;
    cout << "************Increase Key**********" << endl;
    Q.Increase_key(H1, 4, 4000);
    Q.Print(H1);
    Q.Increase_key(H1,1005,5000);
    Q.Increase_key(H1,976,5675);
    Q.Increase_key(H1,968,10000);

    // cout << Q.Search(H1->rootList, 50)->key << endl;
    // Q.Decrease_key(H1, 50, 1);
    // Q.Print(H1);
     //Q.Delete(H1,22);
    // Q.Print(H1);
    //   Q.Display(H1);

    Q.Print(H1);
    cout << "Give up EveryThing and die" << endl;
    cout << H1->max->key << endl;
    // cin >> n;
    FibonacciHeap<int,int>* H=Q.meld(H1,H2);
    Q.Extract_max(H);
    Q.Print(H);
    cout<<"Why this Kolaveri D::"<<endl;
    Q.Delete(H,26);
    cout<<"Printing after calling Delete"<<endl;
    Q.Print(H);





    // for (int i = 0; i < n; i++)
    // {
    //     int key, value;
    //     cin >> key >> value;
    //     Q.insert(H2, key, value);
    // }
    // // Q.Display(H2);
    // FibonacciHeap<int, int> *H = Q.meld(H1, H2);
    // Q.Display(H);
    //  Q.insert(H,1,10);
    // cout << H1->getNoOfTrees() << endl;
    // cout << H1->getmax()->value << endl;
    cout<<"I Am Commanded To Say Nothing, To See Nothing."<<endl;
    */
    return 0;
}