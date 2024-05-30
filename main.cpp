#include <iostream>
#include <string>
#include <conio.h>
using namespace std;


struct Leaf{
    string FIO;
    int key;
};

struct Tree{
    Tree* left, *right;
    Leaf leaf;
};

struct QueueNode {
    Tree* node;
    int level;
    QueueNode* next;
    QueueNode(Tree* n, int l) : node(n), level(l), next(NULL) {}
};

struct Queue {
    QueueNode* front;
    QueueNode* rear;

    Queue() : front(NULL), rear(NULL) {}

    void push(Tree* node, int level) {
        QueueNode* t = new QueueNode(node, level);
        if (rear) {
            rear->next = t;
        } else {
            front = t;
        }
        rear = t;
    }

    void pop() {
        if (front) {
            QueueNode* k = front;
            front = front->next;
            if (!front) {
                rear = nullptr;
            }
            delete k;
        }
    }

    bool empty() {
        return front == nullptr;
    }

    std::pair<Tree*, int> frontElement() {
        if (front) {
            return {front->node, front->level};
        }
        return {nullptr, -1};
    }
};

void quickSort(Leaf a[], int l, int r) {
    if (l >= r) return;
    int i = l, j = r;
    int x =  a[(l + r) / 2].key;

    while (i <= j) {
        while (a[i].key < x) i++;
        while (a[j].key > x) j--;
        if (i <= j) {
            Leaf temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }
    quickSort(a, l, j);
    quickSort(a, i, r);
}

void Add_Leaf(Tree*, int, string);
void Find_And_View(Tree*, int);
Tree* Del(Tree*, int);
//In-order
void View_Left_Root_Right(Tree*, int);
//Pre-Order
void View_Root_Left_Right(Tree*, int);
//Post-Order
void View_Left_Right_Root(Tree*, int);
void Make_Blns(Tree**, int, int, Leaf[]);
void Create_Tree(Tree** , int, Leaf[]);
void Del_Tree(Tree*);
int Task(Tree*, int, int*&);

int main()
{
    int n;
    string FIO;
    int key;
    Leaf arr[100];
    cout << "Input a length: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Input FIO: ";
        cin >> FIO;
        cout << "Input a key: ";
        cin >> key;
        arr[i].FIO = FIO;
        arr[i].key = key;
    }

    quickSort(arr, 0, n - 1);
    Tree *tree = new Tree;
    Create_Tree(&tree, n, arr);
    char c;

    for(;;)
    {
        system("cls");
        cout << "Input\nAdd information to list - 1\nFind element by key - 2\nDelete element by key - 3\nPrint the pre-order information - 4\nPrint the post-order information - 5 \
        \nPrint the in-order information - 6\nTask - 7\nQuit - 8\n";
        cin >> c;
        switch(c)
        {
        case '1':
            cout << "Input FIO: ";
            cin >> FIO;
            cout << "Input a key: ";
            cin >> key;
            Add_Leaf(tree, key, FIO);
            break;
        case '2':
            cout << "Input a key: ";
            cin >> key;
            Find_And_View(tree, key);
            break;
        case '3':
            cout << "Input a key: ";
            cin >> key;
            tree = Del(tree, key);
            break;
        case '4':
            View_Root_Left_Right(tree, 0);
            getch();
            break;
        case '5':
            View_Left_Right_Root(tree, 0);
            getch();
            break;
        case '6':
            View_Left_Root_Right(tree, 0);
            getch();
            break;
        case '7':
        {
            int *leafCountPerLevel;
            int levels = Task(tree, 0, leafCountPerLevel);
            for (int k = 0; k <= levels; k++)
                cout << "Level: " << k << "Count: " << leafCountPerLevel[k] << endl;
            delete[] leafCountPerLevel;
            getch();
            break;
        }
        case '8':
            Del_Tree(tree);
            return 0;
        }
    }
}

Tree* Del(Tree* root, int key) {
    Tree* Del = root;
    Tree* Prev_Del = nullptr;
    Tree* R;
    Tree* Prev_R;

    while (Del != nullptr && Del->leaf.key != key) {
        Prev_Del = Del;
        if (key < Del->leaf.key)
            Del = Del->left;
        else
            Del = Del->right;
    }

    if (Del == nullptr) {
        cout << "Key not found!" << endl;
        getch();
        return root;
    }

    if (Del->right == nullptr) {
        R = Del->left;
    } else if (Del->left == nullptr) {
        R = Del->right;
    } else {
        Prev_R = Del;
        R = Del->left;
        while (R->right != nullptr) {
            Prev_R = R;
            R = R->right;
        }
        if (Prev_R != Del) {
            R->right = Del->right;
            Prev_R->right = R->left;
            R->left = Prev_R;
        }else R->right = Del->right;
    }
    if (Del == root) root = R;
    else
    if (Del->leaf.key < Prev_Del->leaf.key)
        Prev_Del->left = R;
    else
        Prev_Del->right = R;

    delete Del;
    return root;
}

void Del_Tree(Tree* root)
{
    if (root == NULL)
        return;
    Del_Tree(root->left);
    Del_Tree(root->right);
    delete root;
}

void Find_And_View(Tree* t, int key)
{
    if (t != NULL)
    {
        if (t->leaf.key == key)
        {
            cout << "Element found!\n" << t->leaf.FIO << endl;
            getch();
            return;
        }
        Find_And_View(t->left, key);
        Find_And_View(t->right, key);
    }
}

void Add_Leaf(Tree* root, int key, string FIO)
{
    Tree *prev = nullptr, *t;
    bool find = true;
    t = root;
    while (t && find)
    {
        prev = t;
        getch();
        if (key == t->leaf.key)
        {
            find = false;
            cout << "The key must me unique!";
            getch();
            break;
        }
        if (key < t->leaf.key) t = t->left;
        else t = t->right;
    }
    if (find)
    {
        Tree *p = new Tree;
        Leaf leaf;
        leaf.key = key;
        leaf.FIO = FIO;
        p->leaf=leaf;
        p->left=nullptr;
        p->right=nullptr;
        if (key < prev->leaf.key) prev->left = p;
        else prev->right = p;
    }
}

void View_Left_Root_Right(Tree* root, int level)
{
    string s;
    Tree* R = root->right;
    Tree* L = root->left;
    if (L != NULL)View_Left_Root_Right(L, level + 1);
    for(int i = 0; i < level; i++)
        s = s + "  ";
    cout << s << root->leaf.FIO << endl;
    if (R != NULL)View_Left_Root_Right(R, level + 1);
    return;
}
void View_Root_Left_Right(Tree* root, int level)
{
    string s;
    Tree* R = root->right;
    Tree* L = root->left;
    for(int i = 0; i < level; i++)
        s = s + "  ";
    cout << s << root->leaf.FIO << endl;
    if (L != NULL)View_Root_Left_Right(L, level + 1);
    if (R != NULL)View_Root_Left_Right(R, level + 1);
    return;
}

void View_Left_Right_Root(Tree* root, int level)
{
    string s;
    Tree* R = root->right;
    Tree* L = root->left;
    if (L != NULL)View_Root_Left_Right(L, level + 1);
    if (R != NULL)View_Root_Left_Right(R, level + 1);
    for(int i = 0; i < level; i++)
        s = s + "  ";
    cout << s << root->leaf.FIO << endl;
    return;
}

void Make_Blns(Tree** p, int n, int k, Leaf a[])
{
    if (n == k)
    {
        *p = NULL;
        return;
    }
    int m = (n + k) / 2;

    *p = new Tree;
    (*p)->leaf= a[m];

    Make_Blns(&(*p)->left, n, m, a);
    Make_Blns(&(*p)->right, m + 1, k, a);
}

void Create_Tree(Tree** p, int n, Leaf a[])
{
    Make_Blns(p, 0, n, a);
}

int Task(Tree* node, int level,  int*& leafCountPerLevel)
{
    if (!node)
        return 0;
    leafCountPerLevel = new int[1];
    int levels = 0;
    leafCountPerLevel[0] = 0;
    Queue q;
    q.push(node, 0);
    while(!q.empty())
    {
        auto [node, level] = q.frontElement();
        q.pop();
        if (level > levels) {
            int* newLeafCountPerLevel = new int[level + 1];
            for (int i = 0; i < level; ++i) {
                newLeafCountPerLevel[i] = leafCountPerLevel[i];
            }
            newLeafCountPerLevel[level] = 0;
            delete[] leafCountPerLevel;
            leafCountPerLevel = newLeafCountPerLevel;
            levels++;
        }
        leafCountPerLevel[level]++;
        if (node->left) q.push(node->left, level + 1);
        if (node->right) q.push(node->right, level + 1);
    }
    return levels;
}
