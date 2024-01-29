#include <iostream>
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
        this->right=nullptr;
        this->left=nullptr;
        this->colour=BLACK;

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
    Node<T, E> *NIL=new Node<T,E>();

public:
    RBT()
    {
        this->rootRBT = nullptr;
        //cout<<NIL->colour<<endl;
        this->size = 0;
    }
    Node<T, E> *LeftRotation(Node<T, E> *node)
    {
        Node<T, E> *Node_Er_Left = node->left;
        Node<T, E> *Node_Er_Right = node->right;
        Node<T, E> *Node_Er_Right_Er_Left = Node_Er_Right->left;
        Node_Er_Right->left = node;
        node->right = Node_Er_Right_Er_Left;
        node->parent = Node_Er_Right;
        if (Node_Er_Right_Er_Left != nullptr)
        {
            Node_Er_Right_Er_Left->parent = node;
        }
        return Node_Er_Right;
    }
    Node<T, E> *RightRotation(Node<T, E> *node)
    {
        Node<T, E> *Node_Er_Left = node->left;
        Node<T, E> *Node_Er_Right = node->right;
        Node<T, E> *Node_Er_Left_Er_Right = Node_Er_Left->right;
        Node_Er_Left->right = node;
        node->left = Node_Er_Left_Er_Right;
        node->parent = Node_Er_Left;
        if (Node_Er_Left_Er_Right != nullptr)
        {
            Node_Er_Left_Er_Right->parent = node;
        }
        return Node_Er_Left;
    }
    Node<T, E> *INSERTHELPER(E value, T key, Node<T, E> *root)
    {

        if (root == nullptr)
        {
            return new Node<T, E>(key, value);
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
                    cout << "(key<root->key) RED CONFLICT DETECTED" << endl;
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
                cout << "(key>root->key) RED CONFLICT DETECTED" << endl;
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
            cout << "LeftLeftCase" << endl;
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
                cout << "RED CONFLICT: root->parent->right == root " << endl;
                if (root->parent->left == nullptr || root->parent->left->colour == BLACK)
                {
                    if (root->left != nullptr && root->left->colour == RED)
                    {
                        RightLeftCase = true;
                    }
                    else if (root->right != nullptr && root->right->colour == RED)
                    {
                        cout << "LeftLeftCase" << endl;
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
                if (root->parent->right == nullptr || root->parent->right->colour == BLACK)
                {
                    if (root->left != nullptr && root->left->colour == RED)
                    {
                        RightRightCase = true;
                    }
                    else if (root->right != nullptr && root->right->colour == RED)
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

    void insert(T key, E value)
    {
        if (this->rootRBT == nullptr)
        {
            this->rootRBT = new Node<T, E>(key, value);
            this->rootRBT->colour = BLACK;
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
    }
    int Size()
    {
        return this->size;
    }
    bool Empty()
    {
        return this->size == 0;
    }

    void printTree(Node<T, E> *root)
    {
        if (root == nullptr)
        {
            return;
        }

        cout << root->key << "_" << root->colour;

        if (root->left != nullptr || root->right != nullptr)
        {
            cout << "(";
            printTree(root->left);
            cout << ",";
            printTree(root->right);
            cout << ")";
        }
    }

    bool FindHelper(Node<T, E> *root, T key)
    {
        if (root == nullptr)
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
        if (root == nullptr)
        {
            return nullptr;
        }
        else if (root->key == key)
        {
            return root;
        }

        else if (root->key < key)
        {
            SearchNode(root->right, key);
        }
        else if (root->key > key)
        {
            SearchNode(root->left, key);
        }
    }
    Node<T, E> *Search(T key)
    {
        return SearchNode(this->rootRBT, key);
    }

    void Find_Replace(Node<T, E> *root, T key, E value)
    {
        if (root == nullptr)
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
        while (root->left != nullptr)
        {
            successor = successor->left;
        }
        return successor;
    }
    Node<T, E> *Replace(Node<T, E> *root)
    {
        if (root->left != nullptr && root->right != nullptr)
        {
            return InorderSuccessor(root->right);
        }
        else if (root->left == nullptr && root->right == nullptr)
        {
            return nullptr;
        }
        else if (root->left == nullptr && root->right != nullptr)
        {
            return root->right;
        }
        else if (root->left != nullptr && root->right == nullptr)
        {
            return root->left;
        }
    }
    void transplant(Node<T, E> *u, Node<T, E> *v)
    {
        if (u->parent == nullptr)
        {
            this->rootRBT = v;
        }
        else if (u == u->parent->left)
        {
            
            u->parent->left = v;
            cout<<"transplant u=u->parent->left"<<endl;
        }
        else
        {
            u->parent->right = v;
        }
       if (v != nullptr)
    {
        v->parent = u->parent;
    }
        cout<<"v->parent = u->parent"<<endl;
    }
    void Erase(T key)
    {
        Node<T, E> *Z = Search(key);
        //cout<<Z->value<<endl;
        Node<T, E> *X;
        if (Z == nullptr)
        {
            return;
        }
        Node<T, E> *Y = Z;
        int Y_Original_Color = Y->colour;
        if (Z->left == nullptr)
        {
            cout<<"Erase left NULL"<<endl;
            X = Z->right;
            transplant(Z, Z->right);
        }
        else if (Z->right == nullptr)
        {
            cout<<"Erase right NULL"<<endl;
            X = Z->left;
            transplant(Z, Z->left);
        }
        else
        {
            cout<<"No child NULL"<<endl;
            Y = InorderSuccessor(Z->right);
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
        }
        delete Z;
        if (Y_Original_Color == BLACK)
        {
            cout<<"Y_Original_Color == BLACK"<<endl;
            FixRbt(X);
        }
    }
    bool check(Node<T,E> * X)
    {
        if(X==nullptr)
        {
            return true;
        }
        else if(X != rootRBT && (X->colour == BLACK||X==nullptr))
        {
            return true;
        }
        return false;
    }
    void FixRbt(Node<T, E> *X)
    {
        Node<T, E> *W;
        cout<<"Outside while loop FixRBT"<<endl;
        while (check(X))
        {
            cout << "Fix_RBt" << endl;
            if (X->parent->left == X)
            {
                W = X->parent->right;
                if (W->colour == RED)
                {
                    W->colour = BLACK;
                    X->parent->colour = RED;
                    LeftRotation(X->parent);
                    W = X->parent->right;
                }
                if (W->left->colour == BLACK && W->right->colour == BLACK)
                {
                    W->colour = RED;
                    X = X->parent;
                }
                else
                {
                    if (W->right->colour == BLACK)
                    {
                        W->left->colour = BLACK;
                        W->colour = RED;
                        RightRotation(W);
                        W = X->parent->right;
                    }
                    W->colour = X->parent->colour;
                    X->parent->colour = BLACK;
                    W->right->colour = BLACK;
                    LeftRotation(X);
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
                    RightRotation(X->parent);
                    W = X->parent->left;
                }
                if ((W->right->colour == BLACK || W->right == nullptr) && (W->left->colour == BLACK || W->left == nullptr))
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
                        LeftRotation(W);
                        W = X->parent->left;
                    }
                    W->colour = X->parent->colour;
                    X->parent->colour = BLACK;
                    W->left->colour = BLACK;
                    RightRotation(X);
                    X = this->rootRBT;
                }
            }
        }
        if (X == rootRBT && X->colour == RED)
        {
            X->colour = BLACK;
        }
    }
    void DeleteNode(Node<T, E> *node_to_be_deleted)
    {
        Node<T, E> *node_to_be_replaced = Replace(node_to_be_deleted);
        if (node_to_be_replaced == nullptr)
        {
            if (node_to_be_deleted == this->rootRBT)
            {
                delete node_to_be_deleted;
                return;
            }
            else if (node_to_be_deleted->colour == RED)
            {
                delete node_to_be_deleted;
                return;
            }
            else if (node_to_be_deleted->colour == BLACK)
            {
                if (node_to_be_deleted->sibling()->colour == BLACK || node_to_be_deleted->sibling() == nullptr)
                {
                    if ((node_to_be_deleted->sibling()->LeftChild()->colour == BLACK || node_to_be_deleted->sibling()->LeftChild() == nullptr) && (node_to_be_deleted->sibling()->RightChild()->colour == BLACK || node_to_be_deleted->sibling()->RightChild() == nullptr))
                    {
                        if (node_to_be_deleted->parent->colour == RED)
                        {
                            node_to_be_deleted->parent->colour = BLACK;
                            node_to_be_deleted->sibling()->colour == RED;
                            delete node_to_be_deleted;
                            return;
                        }
                        else if (node_to_be_deleted->parent->colour == BLACK)
                        {
                            fixDoubleBlack(node_to_be_deleted);
                        }
                    }
                }
            }
        }
        if (node_to_be_replaced->colour == RED)
        {
            node_to_be_deleted->value = node_to_be_replaced->value;
            Delete(node_to_be_replaced);
        }
    }
    bool bothChildBlack(Node<T, E> *root)
    {
        if ((root->sibling()->LeftChild()->colour == BLACK ||
             root->sibling()->LeftChild() == nullptr) &&
            (root->sibling()->RightChild()->colour == BLACK ||
             root->sibling()->RightChild() == nullptr))
        {
            return true;
        }
        return false;
    }
    void fixDoubleBlack(Node<T, E> *root)
    {
        if (root == this->rootRBT)
        {
            return;
        }
        if (root->sibling() == nullptr)
        {
            fixDoubleBlack(root);
        }
        else
        {
            if (root->sibling()->colour == BLACK)
            {
                if (bothChildBlack(root->sibling()))
                {
                    root->sibling() = BLACK;
                    if (root->parent->colour == BLACK)
                    {
                        fixDoubleBlack(root->parent);
                    }
                    else
                    {
                        root->parent->colour = BLACK;
                    }
                }
            }
        }
    }

    void Delete(T key)
    {
        if (this->rootRBT == nullptr)
        {
            return;
        }
        Node<T, E> *node_to_be_deleted = Search(rootRBT, key);
        Node<T, E> *u;
        if (node_to_be_deleted == nullptr)
        {
            return;
        }
    }
    void Find(T key)
    {
        // if(this->rootRBT==nullptr)
        // {
        //     cout<<"unsuccessful"<<endl;
        // }

        if (FindHelper(this->rootRBT, key))
        {
            cout << "successful" << endl;
        }
        else
        {
            cout << "unsuccessful" << endl;
        }
    }
    void inorderTraversal(Node<T, E> *root)
    {
        if (root == nullptr)
        {
            return;
        }
        inorderTraversal(root->left);
        cout << root->key << "->" << root->value << endl;
        inorderTraversal(root->right);
    }
    void Iteration()
    {
        inorderTraversal(this->rootRBT);
    }

    void Print()
    {
        printTree(this->rootRBT);
    }
};
int main()
{
    int n;
    RBT<int, string> R;
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    cout << "hi" << endl;
    R.Find(200);

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int key;
        string value;

        cin >> key >> value;
        R.insert(key, value);
        R.Print();
        cout << endl;
        // R.insert(temp);
    }
    cout << "Dreams are messages from the deep." << endl;
    cout << R.Size() << endl;
    if (R.Empty())
    {
        cout << "yes" << endl;
    }
    else
    {
        cout << "no" << endl;
    }
    // R.Print();
    R.Find(200);
    R.Iteration();
    int data;
    // cin >> data;
    R.Erase(12);
    R.Print();

    // fclose(stdin);
    // fclose(stdout);

    return 0;
}