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

public:
    RBT()
    {
        this->rootRBT = nullptr;
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
        return y;
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

        cout << root->key << "_" << root->value;

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

    // fclose(stdin);
    // fclose(stdout);

    return 0;
}