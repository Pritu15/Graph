#include "./color-console-master/include/color.hpp"
#include <iostream>
#include <vector>
#define RED 1
#define BLACK 2
using namespace std;

template <typename T, typename E>
class Node
{

public:
    T key;
    E value;
    Node<T, E> *right = nullptr;
    Node<T, E> *left = nullptr;
    Node<T, E> *parent = nullptr;
    int colour = RED;
    Node()
    {
        //  this->key = key;
        // this->value = value;
        this->right = nullptr;
        this->left = nullptr;
        this->colour = BLACK;
    }
    Node(T key, E value)
    {
        this->key = key;
        this->value = value;
    }
    void PrintNode()
    {
        cout << key << " " << colour << endl;
    }
    Node<T, E> *sibling()
    {
        if (this->parent == nullptr)
        {
            return nullptr;
        }

        else if (this == this->parent->left)
        {
            return this->parent->right;
        }
        else if (this == this->parent->right)
        {
            return this->parent->left;
        }
    }
    bool isLeftChild()
    {
        if (this == this->parent->left)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    Node<T, E> *LeftChild()
    {
        if (this->left == nullptr)
        {
            return nullptr;
        }
        else
        {
            return this->left;
        }
    }
    Node<T, E> *RightChild()
    {
        if (this->right == nullptr)
        {
            return nullptr;
        }
        else
        {
            return this->right;
        }
    }
};

template <typename T, typename E>
class RBT
{
    Node<T, E> *rootRBT;
    int size;
    bool RedConflictFlag = false;
    bool RightLeftCase = false;
    bool RightRightCase = false;
    bool LeftRightCase = false;
    bool LeftLeftCase = false;
    Node<T, E> *NIL = new Node<T, E>();
    void printTree(Node<T, E> *root)
    {
        if (root == NIL)
        {
            return;
        }
        if (root->colour == RED)
        {
            cout << dye::red(root->key) << dye::red("_") << dye::red(root->value);
        }
        else
        {
            cout << root->key << "_" << root->value;
        }

        if (root->left != NIL || root->right != NIL)
        {
            cout << "(";
            printTree(root->left);
            cout << ",";
            printTree(root->right);
            cout << ")";
        }
    }

    Node<T, E> *LeftRotation(Node<T, E> *node)
    {
        //Node<T, E> *Node_Er_Left = node->left;
        Node<T, E> *Node_Er_Right = node->right;
        Node<T, E> *Node_Er_Right_Er_Left = Node_Er_Right->left;
        Node_Er_Right->left = node;
        node->right = Node_Er_Right_Er_Left;
        node->parent = Node_Er_Right;
        Node_Er_Right->parent = node->parent;
        if (Node_Er_Right_Er_Left != NIL)
        {
            Node_Er_Right_Er_Left->parent = node;
        }
        return Node_Er_Right;
    }
    void LeftRotationForDelete(Node<T, E> *X)
    {
        Node<T, E> *Y = X->right;
        X->right = Y->left;
        if (Y->left != NIL)
        {
            Y->left->parent = X;
        }
        Y->parent = X->parent;
        if (X->parent == NIL)
        {
            this->rootRBT = Y;
        }
        else if (X == X->parent->left)
        {
            X->parent->left = Y;
        }
        else
        {
            X->parent->right = Y;
        }
        Y->left = X;
        X->parent = Y;
    }
    void RightRotationForDelete(Node<T, E> *X)
    {
        Node<T, E> *Y = X->left;
        X->left = Y->right;
        if (Y->right != NIL)
        {
            Y->right->parent = X;
        }
        Y->parent = X->parent;
        if (X->parent == NIL)
        {
            this->rootRBT = Y;
        }
        else if (X == X->parent->right)
        {
            X->parent->right = Y;
        }
        else
        {
            X->parent->left = Y;
        }
        Y->right = X;
        X->parent = Y;
    }
    Node<T, E> *RightRotation(Node<T, E> *node)
    {
        Node<T, E> *Node_Er_Left = node->left;
        Node<T, E> *Node_Er_Right = node->right;
        Node<T, E> *Node_Er_Left_Er_Right = Node_Er_Left->right;
        Node_Er_Left->right = node;
        node->left = Node_Er_Left_Er_Right;
        node->parent = Node_Er_Left;
        if (Node_Er_Left_Er_Right != NIL)
        {
            Node_Er_Left_Er_Right->parent = node;
        }
        return Node_Er_Left;
    }
    Node<T, E> *INSERTHELPER(E value, T key, Node<T, E> *root)
    {

        if (root == NIL)
        {
            Node<T, E> *temp = new Node<T, E>(key, value);
            temp->right = NIL;
            temp->left = NIL;
            temp->parent = NIL;
            temp->colour = RED;
            return temp;
            // root->colour = BLACK;
        }

        else if (key < root->key)
        {
            root->left = INSERTHELPER(value, key, root->left);
            root->left->parent = root;
            if (root != this->rootRBT)
            {
                if (root->colour == RED && root->left->colour == RED)
                {
                    // cout << "(key<root->key) RED CONFLICT DETECTED" << endl;
                    RedConflictFlag = true;
                }
            }
        }
        else
        {
            root->right = INSERTHELPER(value, key, root->right);
            root->right->parent = root;
            if (root->colour == RED && root->right->colour == RED)
            {
                // cout << "(key>root->key) RED CONFLICT DETECTED" << endl;
                RedConflictFlag = true;
            }
        }
        if (LeftRightCase)
        {
            root->left = LeftRotation(root->left);
            root->left->parent = root;
            root = RightRotation(root);
            root->colour = BLACK;
            // root->left=BLACK;
            root->right->colour = RED;
            LeftRightCase = false;
        }
        else if (RightLeftCase)
        {
            root->right = RightRotation(root->right);
            root->right->parent = root;
            root = LeftRotation(root);
            root->colour = BLACK;
            root->left->colour = RED,
            RightLeftCase = false;
        }
        else if (LeftLeftCase)
        {
            // cout << "LeftLeftCase" << endl;
            root = LeftRotation(root);
            root->colour = BLACK;
            root->left->colour = RED;
            LeftLeftCase = false;
        }
        else if (RightRightCase)
        {
            root = RightRotation(root);
            root->colour = BLACK;
            root->right->colour = RED;
            RightRightCase = false;
        }
        if (RedConflictFlag)
        {
            if (root->parent->right == root)
            {
                // cout << "RED CONFLICT: root->parent->right == root " << endl;
                if (root->parent->left == NIL || root->parent->left->colour == BLACK)
                {
                    if (root->left != NIL && root->left->colour == RED)
                    {
                        RightLeftCase = true;
                    }
                    else if (root->right != NIL && root->right->colour == RED)
                    {
                        // cout << "LeftLeftCase" << endl;
                        LeftLeftCase = true;
                    }
                }
                else
                {
                    root->colour = BLACK;
                    root->parent->left->colour = BLACK;
                    if (root->parent != this->rootRBT)
                    {
                        root->parent->colour = RED;
                    }
                }
            }
            else if (root->parent->left == root)
            {
                if (root->parent->right == NIL || root->parent->right->colour == BLACK)
                {
                    if (root->left != NIL && root->left->colour == RED)
                    {
                        RightRightCase = true;
                    }
                    else if (root->right != NIL && root->right->colour == RED)
                    {
                        LeftRightCase = true;
                    }
                }
                else
                {
                    root->colour = BLACK;
                    root->parent->right->colour = BLACK;
                    if (root->parent != this->rootRBT)
                    {
                        root->parent->colour = RED;
                    }
                }
            }
            RedConflictFlag = false;
        }
        return root;
    }

    bool FindHelper(Node<T, E> *root, T key)
    {
        if (root == NIL)
        {
            return false;
        }
        else if (root->key == key)
        {
            return true;
        }

        else if (root->key < key)
        {
            return FindHelper(root->right, key);
        }
        else if (root->key > key)
        {
            return FindHelper(root->left, key);
        }
    }
    Node<T, E> *SearchNode(Node<T, E> *root, T key)
    {
        if (root == NIL)
        {
            return NIL;
        }
        else if (root->key == key)
        {
            return root;
        }

        else if (root->key < key)
        {
            return SearchNode(root->right, key);
        }
        else if (root->key > key)
        {
            return SearchNode(root->left, key);
        }
    }
    Node<T, E> *Search(T key)
    {
        return SearchNode(this->rootRBT, key);
    }

    void Find_Replace(Node<T, E> *root, T key, E value)
    {
        if (root == NIL)
        {
            return;
        }
        else if (root->key == key)
        {
            root->value = value;
        }

        else if (root->key < key)
        {
            Find_Replace(root->right, key, value);
        }
        else if (root->key > key)
        {
            Find_Replace(root->left, key, value);
        }
    }
    Node<T, E> *InorderSuccessor(Node<T, E> *root)
    {
        Node<T, E> *successor = root;
        while (successor->left != NIL)
        {
            successor = successor->left;
        }
        return successor;
    }
    void transplant(Node<T, E> *u, Node<T, E> *v)
    {
        if (u->parent == NIL)
        {
            this->rootRBT = v;
        }
        else if (u == u->parent->left)
        {

            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
        //    if (v != nullptr)
        // {
        v->parent = u->parent;
        // }
        // cout << "v->parent = u->parent" << endl;
    }
    void FixRbt(Node<T, E> *X)
    {
        // Print();
        Node<T, E> *W;
        // cout << "Outside while loop FixRBT" << endl;
        while (X != rootRBT && X->colour == BLACK)
        {
            // cout << "Fix_RBt" << endl;
            if (X->parent->left == X)
            {
                // cout << "X->parent->left == X" << endl;
                W = X->parent->right;
                if (W->colour == RED)
                {
                    W->colour = BLACK;
                    X->parent->colour = RED;
                    // Print();
                    LeftRotationForDelete(X->parent);
                    W = X->parent->right;
                    // Print();
                }
                if (W->left->colour == BLACK && W->right->colour == BLACK)
                {
                    W->colour = RED;
                    X = X->parent;
                }

                else
                {
                    //     // if (W->right->colour == BLACK)
                    // {

                    // }
                    if (W->right->colour == BLACK)
                    {
                        W->left->colour = BLACK;
                        W->colour = RED;
                        RightRotationForDelete(W);
                        W = X->parent->right;
                    }
                    W->colour = X->parent->colour;
                    X->parent->colour = BLACK;
                    W->right->colour = BLACK;
                    // cout<<"Before LeftRotation"<<endl;
                    // Print();
                    LeftRotationForDelete(X->parent);
                    // cout<<"After RightRotation"<<endl;
                    // Print();
                    X = this->rootRBT;
                }
            }
            else
            {
                W = X->parent->left;
                if (W->colour == RED)
                {
                    W->colour = BLACK;
                    X->parent->colour = RED;
                    RightRotationForDelete(X->parent);
                    W = X->parent->left;
                }
                if (W->right->colour == BLACK && W->left->colour == BLACK)
                {
                    W->colour = RED;
                    X = X->parent;
                }

                else
                {
                    if (W->left->colour == BLACK)
                    {
                        W->right->colour = BLACK;
                        W->colour = RED;
                        LeftRotationForDelete(W);
                        W = X->parent->left;
                    }

                    W->colour = X->parent->colour;
                    X->parent->colour = BLACK;
                    W->left->colour = BLACK;
                    RightRotationForDelete(X->parent);
                    X = this->rootRBT;
                }
            }
        }
        // if (X == rootRBT && X->colour == RED)
        // {
        X->colour = BLACK;
        // }
    }

public:
    RBT()
    {
        this->rootRBT = NIL;
        // cout<<NIL->colour<<endl;
        this->size = 0;
    }

    void insert(T key, E value)
    {
        if (this->rootRBT == NIL)
        {
            this->rootRBT = new Node<T, E>(key, value);
            this->rootRBT->colour = BLACK;
            this->rootRBT->right = NIL;
            this->rootRBT->left = NIL;
            this->rootRBT->parent = NIL;
            this->size++;
        }
        else if (FindHelper(this->rootRBT, key))
        {
            Find_Replace(rootRBT, key, value);
        }
        else
        {
            this->rootRBT = INSERTHELPER(value, key, rootRBT);
            this->size++;
        }
        Print();
    }
    int Size()
    {
        return this->size;
    }
    bool Empty()
    {
        return this->size == 0;
    }
    void clearHelper(Node<T, E> *root)
    {
         if (root == NIL)
        {
            return;
        }
        clearHelper(root->left);
        clearHelper(root->right);
        this->size--;
        delete root;
        
    }
    void clear()
    {
        if(this->rootRBT==NIL)
        {
            cout<<"unsuccessful"<<endl;
            return;
        }
        clearHelper(this->rootRBT);
        this->rootRBT=NIL;
        cout<<"successful"<<endl;
    }

    void Erase(T key)
    {
        Node<T, E> *Z = Search(key);
        // cout << Z->value << endl;
        Node<T, E> *X;
        if (Z == NIL)
        {
            cout<<key<<" not found"<<endl;
            return;
        }
        Node<T, E> *Y = Z;
        int Y_Original_Color = Y->colour;
        if (Z->left == NIL)
        {
            // cout << "Erase left NULL" << endl;
            X = Z->right;
            transplant(Z, Z->right);
        }
        else if (Z->right == NIL)
        {
            // cout << "Erase right NULL" << endl;
            X = Z->left;
            transplant(Z, Z->left);
        }
        else
        {
            // cout << "No child NULL" << endl;
            Y = InorderSuccessor(Z->right);
            //cout << Y->value << endl;
            Y_Original_Color = Y->colour;
            X = Y->right;
            if (Y->parent == Z)
            {
                X->parent = Y;
            }
            else
            {
                transplant(Y, Y->right);
                Y->right = Z->right;
                Y->right->parent = Y;
            }

            transplant(Z, Y);
            Y->left = Z->left;
            Y->left->parent = Y;
            Y->colour = Z->colour;
            //Print();
        }
         delete Z;
        // cout<<"Before Delete"<<endl;
        //  Print();
        if (Y_Original_Color == BLACK)
        {
            // cout << "Y_Original_Color == BLACK" << endl;
            // cout<<X->key<<endl;
            FixRbt(X);
        }
        this->size--;
        // Print();
    }

    void Find(T key)
    {

        if (FindHelper(this->rootRBT, key))
        {
            cout << key << " found" << endl;
        }
        else
        {
            cout << key << " not found" << endl;
        }
    }
    void inorderTraversal(Node<T, E> *root)
    {
        if (root == NIL)
        {
            return;
        }
        inorderTraversal(root->left);
        cout << root->key << "=>" << root->value << endl;
        inorderTraversal(root->right);
    }
    void Iteration()
    {
        inorderTraversal(this->rootRBT);
    }

    void Print()
    {
        printTree(this->rootRBT);
        cout << endl;
    }
};
template <typename T, typename E>
class Map
{
    RBT<T, E> R;

public:
    void insert(T key, E value)
    {
        R.insert(key, value);
    }
    void Erase(T key)
    {
        R.Erase(key);
        R.Print();
    }
    void Find(T key)
    {
        R.Find(key);
    }
    void Empty()
    {
        if (R.Empty())
        {
            cout << "yes" << endl;
        }
        else
        {
            cout << "no" << endl;
        }
    }
    void size()
    {
        cout << R.Size() << endl;
    }
    void Iteration()
    {
        R.Iteration();
    }
    void clear()
    {
        // for (auto v : keystore)
        // {
        //     R.Erase(v);
        // }
        R.clear();
    }
};
// int main()
// {
//     int n;
//     RBT<int, string> R;
//     //R.FixRbt();
//     // freopen("input.txt", "r", stdin);
//     // freopen("output.txt", "w", stdout);
//     cout << "hi" << endl;
//     R.Find(200);

//     cin >> n;
//     for (int i = 0; i < n; i++)
//     {
//         int key;
//         string value;

//         cin >> key >> value;
//         R.insert(key, value);
//         R.Print();
//         cout << endl;
//         // R.insert(temp);
//     }
//     cout << "Dreams are messages from the deep." << endl;
//     cout << R.Size() << endl;
//     if (R.Empty())
//     {
//         cout << "yes" << endl;
//     }
//     else
//     {
//         cout << "no" << endl;
//     }
//     // R.Print();
//     R.Find(200);
//     R.Iteration();
//     int data;
//     // cin >> data;
//     R.Erase(40);
//     R.Erase(78);
//     R.Print();

//     // fclose(stdin);
//     // fclose(stdout);

//     return 0;
// }