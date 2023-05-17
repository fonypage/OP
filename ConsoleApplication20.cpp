#include <iostream>
using namespace std;

struct Tree {
    Tree* left;
    Tree* right;
    int info;
};
void Add_node(Tree* root, int data)
{
    if (data < root->info)
        if (root->left == NULL)
        {
            Tree* r;
            r = new Tree;
            r->info = data;
            r->left = NULL;
            r->right = NULL;
            root->left = r;
        }
        else Add_node(root->left, data);
    else
        if (root->right == NULL)
        {
            Tree* r;
            r = new Tree;
            r->info = data;
            r->left = NULL;
            r->right = NULL;
            root->right = r;
        }
        else Add_node(root->right, data);
}
void print_LNR(Tree* root) {
    if (root != NULL)
    {
        print_LNR(root->left);
        cout << root->info << " ";
        print_LNR(root->right);
    }
}
void ADD(int arr[], int n) {
    Tree* root = NULL;
    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0) {
            if (root == NULL) {
                root = new Tree;
                root->info = arr[i];
                root->left = NULL;
                root->right = NULL;
            }
            else {
                Add_node(root, arr[i]);
            }
        }
    }
    cout << "\nПолученное дерево: ";
    print_LNR(root);
    delete root;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Условие задачи:\nДан массив.Исключить из него все отрицательные элементы с помощью дерева и вывести дерево в порядке возрастания\n\n";
    int n;
    cout << "Введите размер массива: ";
    cin >> n;
    int* arr = new int[n];
    cout << "\nВведите элементы массива: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    ADD(arr, n);
    delete[] arr;
    return 0;
}