/*
Beginning with an empty binary search tree, Construct binary search tree by inserting
the values in the order given. After constructing a binary tree -
i. Insert new node
ii. Find number of nodes in longest path from root
iii. Minimum data value found in the tree
iv. Change a tree so that the roles of the left and right pointers are swapped at every node
v. Search a value
*/

#include <iostream>

using namespace std;

class BinaryTreeNode
{

public:
    int data;
    BinaryTreeNode *left;
    BinaryTreeNode *right;

    BinaryTreeNode(int data)
    {
        this->data = data;
        left = NULL;
        right = NULL;
    }
};

class BST
{

private:
    BinaryTreeNode *root;
    BinaryTreeNode *insert(BinaryTreeNode *node, int value);
    int longestPathNodeCount(BinaryTreeNode *node);
    int minimumData(BinaryTreeNode *node);
    void swappingPointers(BinaryTreeNode *node);
    bool search(BinaryTreeNode *root, int value);
    void display(BinaryTreeNode *root);
    BinaryTreeNode *deleteNode(BinaryTreeNode *node, int value);
    void preOrderTraversal(BinaryTreeNode *node);
    void inOrderTraversal(BinaryTreeNode *node);
    void postOrderTraversal(BinaryTreeNode *node);

public:
    BST();
    void insert(int value);
    int longestPathNodeCount();
    int minimumData();
    void swappingPointers();
    bool search(int value);
    void display();
    void deleteNode(int value);
    ~BST();
};

BST ::BST()
{
    root = NULL;
}

BinaryTreeNode *BST ::insert(BinaryTreeNode *node, int value)
{
    if (node == NULL)
    {
        BinaryTreeNode *newNode = new BinaryTreeNode(value);
        return newNode;
    }
    if (node->data > value)
    {
        node->left = insert(node->left, value);
    }
    else
    {
        node->right = insert(node->right, value);
    }
    return node;
}

void BST ::insert(int value)
{
    root = insert(root, value);
}

int BST ::longestPathNodeCount(BinaryTreeNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    int leftHeight = longestPathNodeCount(node->left);
    int rightHeight = longestPathNodeCount(node->right);
    return max(leftHeight, rightHeight) + 1;
}

int BST ::longestPathNodeCount()
{
    return longestPathNodeCount(root);
}

int BST ::minimumData(BinaryTreeNode *node)
{
    if (node == NULL)
    {
        cout << "Tree is Empty." << endl;
        return -1;
    }

    BinaryTreeNode *current = node;

    while (current->left != NULL)
    {
        current = current->left;
    }
    return current->data;
}

int BST ::minimumData()
{
    return minimumData(root);
}

void BST ::swappingPointers(BinaryTreeNode *node)
{
    if (node == NULL)
    {
        return;
    }
    swappingPointers(node->left);
    swappingPointers(node->right);
    swap(node->left, node->right);
}

void BST ::swappingPointers()
{
    swappingPointers(root);
}

bool BST ::search(BinaryTreeNode *node, int value)
{
    if (node == NULL)
    {
        return false;
    }
    if (node->data == value)
    {
        return true;
    }
    if (node->data > value)
    {
        return search(node->left, value);
    }
    else
    {
        return search(node->right, value);
    }
}

bool BST ::search(int value)
{
    return search(root, value);
}

void BST ::preOrderTraversal(BinaryTreeNode *node)
{
    if (node == NULL)
    {
        return;
    }
    cout << node->data << " ";
    preOrderTraversal(node->left);
    preOrderTraversal(node->right);
}

void BST ::inOrderTraversal(BinaryTreeNode *node)
{
    if (node == NULL)
    {
        return;
    }
    inOrderTraversal(node->left);
    cout << node->data << " ";
    inOrderTraversal(node->right);
}

void BST ::postOrderTraversal(BinaryTreeNode *node)
{
    if (node == NULL)
    {
        return;
    }
    postOrderTraversal(node->left);
    postOrderTraversal(node->right);
    cout << node->data << " ";
}

void BST ::display(BinaryTreeNode *node)
{
    cout << "Inorder Traversal: ";
    inOrderTraversal(node);
    cout << endl;

    cout << "Preorder Traversal: ";
    preOrderTraversal(node);
    cout << endl;

    cout << "Postorder Traversal: ";
    postOrderTraversal(node);
    cout << endl;
}
void BST ::display()
{
    display(root);
}

BinaryTreeNode *BST ::deleteNode(BinaryTreeNode *node, int value)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (node->data > value)
    {
        node->left = deleteNode(node->left, value);
    }
    else if (node->data < value)
    {
        node->right = deleteNode(node->right, value);
    }
    else
    {
        if (node->left == NULL && node->right == NULL)
        {
            delete node;
            return NULL;
        }
        else if (node->left == NULL)
        {
            BinaryTreeNode *temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == NULL)
        {
            BinaryTreeNode *temp = node->left;
            delete node;
            return temp;
        }
        else
        {
            BinaryTreeNode *minNode = node->right;
            while (minNode->left != NULL)
            {
                minNode = minNode->left;
            }
            int rightMinData = minNode->data;
            node->data = rightMinData;
            node->right = deleteNode(node->right, rightMinData);
            return node;
        }
    }
    return node;
}
void BST ::deleteNode(int value)
{
    root = deleteNode(root, value);
}

BST::~BST() {}

int main()
{
    BST bst;

    int choice;
    bool flag = true;
    while (flag)
    {
        cout << "-----------Binary Search Tree Operations----------------------" << endl;
        cout << "1. Insert Node\n";
        cout << "2. Display Traversals\n";
        cout << "3. Find number of nodes in longest path from root \n";
        cout << "4. Find Minimum Value\n";
        cout << "5. Search Value\n";
        cout << "6. Swap Left and Right pointer\n";
        cout << "7. Delete Node\n";
        cout << "8. Exit Program\n";

        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice)
        {

        case 1:
        {
            int value;
            cout << "Enter value to insert:" << endl;
            cin >> value;
            bst.insert(value);
            break;
        }

        case 2:
        {
            bst.display();
            break;
        }
        case 3:
        {
            int height = bst.longestPathNodeCount();
            cout << "number of nodes in longest path from root:" << height << endl;
            break;
        }

        case 4:
        {
            int minvalue = bst.minimumData();
            cout << "Minimum value in tree:" << minvalue << endl;
            break;
        }

        case 5:
        {
            int value;
            cout << "Enter the value to be search:" << endl;
            cin >> value;
            bool result = bst.search(value);
            if (result)
            {
                cout << "value found" << endl;
            }
            else
            {
                cout << "value not found" << endl;
            }
            break;
        }
        case 6:
        {
            bst.swappingPointers();
            cout << "Pointers swapped successfully." << endl;
            bst.display();
            break;
        }
        case 7:
        {
            int value;
            cout << "Enter the value to delete:";
            cin >> value;
            bool result = bst.search(value);
            if (!result)
            {
                cout << "value not found in tree." << endl;
                break;
            }
            bst.deleteNode(value);
            cout << "Node deleted successfully." << endl;
            break;
        }
        case 8:
        {
            flag = false;
            break;
        }
        default:
        {
            cout << "Invalid Choice." << endl;
        }
        }
    }
    return 0;
}
/* The overall time and space complexity of the program depends on the operations performed and the size of the binary search tree. Let's analyze the time and space complexity of each function and the program as a whole:

1. `BinaryTreeNode` constructor: This function initializes a binary tree node with a given value. It has a time complexity of O(1) and a space complexity of O(1).

2. `BST` constructor: This function initializes an empty binary search tree. It has a time complexity of O(1) and a space complexity of O(1).

3. `BST::insert`: This function inserts a node with a given value into the binary search tree. The time complexity depends on the height of the tree and is O(log N) in the average case for a balanced tree. In the worst case, when the tree is skewed, the time complexity is O(N) where N is the number of nodes in the tree. The space complexity is O(log N) in the average case due to the recursive nature of the function. In the worst case, it can be O(N) when the tree is skewed.

4. `BST::longestPathNodeCount`: This function calculates the number of nodes in the longest path from the root to a leaf node. It recursively traverses the tree and computes the height of the tree. The time complexity is O(N) since it visits each node once. The space complexity is O(log N) in the average case due to the recursive calls. In the worst case, it can be O(N) when the tree is skewed.

5. `BST::minimumData`: This function finds the minimum value in the binary search tree. It traverses the left subtree until it reaches the leftmost leaf node. The time complexity is O(log N) in the average case for a balanced tree. In the worst case, when the tree is skewed, the time complexity is O(N) where N is the number of nodes in the tree. The space complexity is O(1) since it doesn't use any additional memory.

6. `BST::swappingPointers`: This function swaps the left and right pointers of each node in the tree. It recursively traverses the tree and swaps the pointers. The time complexity is O(N) since it visits each node once. The space complexity is O(log N) in the average case due to the recursive calls. In the worst case, it can be O(N) when the tree is skewed.

7. `BST::search`: This function searches for a given value in the binary search tree. It recursively traverses the tree and compares the value with each node. The time complexity is O(log N) in the average case for a balanced tree. In the worst case, when the tree is skewed, the time complexity is O(N) where N is the number of nodes in the tree. The space complexity is O(log N) in the average case due to the recursive calls. In the worst case, it can be O(N) when the tree is skewed.

8. `BST::preOrderTraversal`: This function performs a pre-order traversal of the binary search tree. It recursively visits each node and prints its value. The time complexity is O(N) since it visits each node once. The space complexity is O(log N) in the average case due to the recursive calls. In the worst case, it can be O(N) when the tree is skewed.

9. `BST::inOrderTraversal`: This function performs an in-order traversal of the binary search tree. It recursively visits each node and prints its value. The time complexity is O(N) since it visits each node once. The space complexity is O(log N) in the average case due to the recursive calls. In the

 worst case, it can be O(N) when the tree is skewed.

10. `BST::postOrderTraversal`: This function performs a post-order traversal of the binary search tree. It recursively visits each node and prints its value. The time complexity is O(N) since it visits each node once. The space complexity is O(log N) in the average case due to the recursive calls. In the worst case, it can be O(N) when the tree is skewed.

11. `BST::display`: This function displays the in-order, pre-order, and post-order traversals of the binary search tree by calling the respective traversal functions. The time and space complexity depend on the traversal functions used.

12. `BST::deleteNode`: This function deletes a node with a given value from the binary search tree. The time complexity depends on the height of the tree and is O(log N) in the average case for a balanced tree. In the worst case, when the tree is skewed, the time complexity is O(N) where N is the number of nodes in the tree. The space complexity is O(log N) in the average case due to the recursive nature of the function. In the worst case, it can be O(N) when the tree is skewed.

13. `BST` destructor: This function deallocates the memory allocated for the binary search tree. It has a time complexity of O(N) and a space complexity of O(1).

Overall, the time complexity of the program depends on the operations performed and the structure of the binary search tree. In the average case, the time complexity is O(log N) for most operations. However, in the worst case, when the tree is heavily skewed, the time complexity can be O(N) for insertions, deletions, and searches.

The space complexity of the program is determined by the maximum number of recursive function calls on the call stack, which depends on the height of the tree. In the average case for a balanced tree, the space complexity is O(log N). In the worst case, it can be O(N) when the tree is skewed.

Oral Questions:
1. What is a binary search tree (BST), and what are its properties?
2. Explain the process of inserting a node into a binary search tree.
3. How can you find the minimum value in a binary search tree?
4. Describe the process of swapping the left and right pointers of each node in a binary search tree.
5. How does searching for a value in a binary search tree work?
6. What is the difference between pre-order, in-order, and post-order traversals of a binary search tree?
7. How can you delete a node from a binary search tree?
8. Explain the time and space complexity of the overall program and each function.
9. What is the worst-case time complexity for inserting, searching, and deleting nodes in a binary search tree?
10. What is the space complexity of the program, and when does it occur?

Answers:
1. A binary search tree is a type of binary tree in which the values in the left subtree of a node are less than the node's value, and the values in the right subtree are greater than the node's value. It allows for efficient searching, insertion, and deletion operations.
2. To insert a node into a binary search tree, compare the value of the node to be inserted with the current node. If the value is smaller, go to the left subtree; if it is larger, go to the right subtree. Repeat this process until an empty spot is found, and insert the new node there.
3. The minimum value in a binary search tree can be found by traversing the left subtree until reaching the leftmost leaf node.
4. Swapping

 the left and right pointers of each node in a binary search tree involves traversing the entire tree and swapping the pointers for each node. This can be done recursively or iteratively.
5. Searching for a value in a binary search tree starts at the root node. If the value is equal to the current node's value, the search is successful. If the value is less than the current node's value, the search continues in the left subtree. If the value is greater, the search continues in the right subtree. The process is repeated until the value is found or a leaf node is reached.
6. Pre-order traversal visits the current node first, followed by the left subtree and then the right subtree. In-order traversal visits the left subtree first, then the current node, and finally the right subtree. Post-order traversal visits the left subtree, then the right subtree, and finally the current node.
7. To delete a node from a binary search tree, there are three cases to consider: a node with no children, a node with one child, and a node with two children. The node is replaced with its predecessor or successor in the latter case. The tree is then adjusted to maintain the binary search tree properties.
8. The overall time complexity of the program depends on the operations performed and the structure of the binary search tree. The worst-case time complexity for inserting, searching, and deleting nodes is O(N) when the tree is heavily skewed. The space complexity is O(log N) in the average case and O(N) in the worst case.
9. The worst-case time complexity for inserting, searching, and deleting nodes in a binary search tree is O(N) when the tree is heavily skewed.
10. The space complexity of the program is O(log N) in the average case due to the recursive nature of the functions and O(N) in the worst case when the tree is skewed. */
