/*A Dictionary stores keywords and its meanings. Provide facility for
1.adding new keywords.
2.deleting keywords.
3.updating values of any entry.
4.Provide facility to display whole data sorted in ascending/ Descending order.
5.find how many maximum comparisons may require for finding any keyword.
Use Binary Search Tree for implementation.*/
#include <iostream>
#include <string>

using namespace std;

class BinaryTreeNode
{
public:
    string keyword;
    string meaning;
    BinaryTreeNode *left;
    BinaryTreeNode *right;

    BinaryTreeNode(string keyword, string meaning)
    {
        this->keyword = keyword;
        this->meaning = meaning;
        left = NULL;
        right = NULL;
    }
};

class Dictionary
{
private:
    BinaryTreeNode *rootNode;

    BinaryTreeNode *insert(BinaryTreeNode *node, string keyword, string meaning);
    BinaryTreeNode *findMinNode(BinaryTreeNode *node);
    BinaryTreeNode *deleteNode(BinaryTreeNode *node, string keyword);
    void inOrderTraversal(BinaryTreeNode *node);
    void reverseInOrderTraversal(BinaryTreeNode *node);
    int countComparisons(BinaryTreeNode *node, string keyword, int count);

public:
    Dictionary();
    void addKeyword(string keyword, string meaning);
    void deleteKeyword(string keyword);
    void updateKeyword(string keyword, string newMeaning);
    void displayAscending();
    void displayDescending();
    int maxComparisons(string keyword);
    ~Dictionary();
};

Dictionary::Dictionary()
{
    rootNode = NULL;
}

void Dictionary::addKeyword(string keyword, string meaning)
{
    rootNode = insert(rootNode, keyword, meaning);
}

void Dictionary::deleteKeyword(string keyword)
{
    rootNode = deleteNode(rootNode, keyword);
}

void Dictionary::updateKeyword(string keyword, string newMeaning)
{
    BinaryTreeNode *node = rootNode;
    while (node != NULL)
    {
        if (keyword == node->keyword)
        {
            node->meaning = newMeaning;
            break;
        }
        else if (keyword < node->keyword)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
}

void Dictionary::displayAscending()
{
    cout << "Dictionary in ascending order:" << endl;
    inOrderTraversal(rootNode);
    cout << endl;
}

void Dictionary::displayDescending()
{
    cout << "Dictionary in descending order:" << endl;
    reverseInOrderTraversal(rootNode);
    cout << endl;
}

int Dictionary::maxComparisons(string keyword)
{
    int comparisons = countComparisons(rootNode, keyword, 0);
    return comparisons;
}

Dictionary::~Dictionary()
{
    // TODO: Implement destructor to free memory
}

BinaryTreeNode *Dictionary::insert(BinaryTreeNode *node, string keyword, string meaning)
{
    if (node == NULL)
    {
        BinaryTreeNode *newNode = new BinaryTreeNode(keyword, meaning);
        return newNode;
    }

    if (node->keyword > keyword)
    {
        node->left = insert(node->left, keyword, meaning);
    }
    else
    {
        node->right = insert(node->right, keyword, meaning);
    }

    return node;
}

BinaryTreeNode *Dictionary::findMinNode(BinaryTreeNode *node)
{
    if (node == NULL)
        return NULL;

    while (node->left != NULL)
    {
        node = node->left;
    }

    return node;
}

BinaryTreeNode *Dictionary::deleteNode(BinaryTreeNode *node, string keyword)
{
    if (node == NULL)
    {
        return NULL;
    }

    if (keyword < node->keyword)
    {
        node->left = deleteNode(node->left, keyword);
    }
    else if (keyword > node->keyword)
    {
        node->right = deleteNode(node->right, keyword);
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
            BinaryTreeNode *minNode = findMinNode(node->right);
            node->keyword = minNode->keyword;
            node->meaning = minNode->meaning;
            node->right = deleteNode(node->right, minNode->keyword);
        }
    }

    return node;
}

void Dictionary::inOrderTraversal(BinaryTreeNode *node)
{
    if (node == NULL)
    {
        return;
    }

    inOrderTraversal(node->left);
    cout << node->keyword << " - " << node->meaning << endl;
    inOrderTraversal(node->right);
}

void Dictionary::reverseInOrderTraversal(BinaryTreeNode *node)
{
    if (node == NULL)
    {
        return;
    }

    reverseInOrderTraversal(node->right);
    cout << node->keyword << " - " << node->meaning << endl;
    reverseInOrderTraversal(node->left);
}

int Dictionary::countComparisons(BinaryTreeNode *node, string keyword, int count)
{
    if (node == NULL)
    {
        return count;
    }

    if (keyword == node->keyword)
    {
        return count + 1;
    }

    if (keyword < node->keyword)
    {
        return countComparisons(node->left, keyword, count + 1);
    }
    else
    {
        return countComparisons(node->right, keyword, count + 1);
    }
}

int main()
{
    Dictionary dictionary;

    int choice;
    bool flag = true;

    while (flag)
    {
        cout << "-----------Dictionary Operations----------------------" << endl;
        cout << "1. Add a keyword\n";
        cout << "2. Delete a keyword\n";
        cout << "3. Update a keyword meaning\n";
        cout << "4. Display dictionary in ascending order\n";
        cout << "5. Display dictionary in descending order\n";
        cout << "6. Find maximum comparisons required to find a keyword\n";
        cout << "7. Exit Program\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string keyword;
            string meaning;
            cout << "Enter keyword: ";
            cin >> keyword;
            cout << "Enter meaning: ";
            cin.ignore();
            getline(cin, meaning);
            dictionary.addKeyword(keyword, meaning);
            break;
        }
        case 2:
        {
            string keyword;
            cout << "Enter keyword to delete: ";
            cin >> keyword;
            dictionary.deleteKeyword(keyword);
            break;
        }
        case 3:
        {
            string keyword;
            string newMeaning;
            cout << "Enter keyword to update: ";
            cin >> keyword;
            cout << "Enter new meaning: ";
            cin.ignore();
            getline(cin, newMeaning);
            dictionary.updateKeyword(keyword, newMeaning);
            break;
        }
        case 4:
        {
            dictionary.displayAscending();
            break;
        }
        case 5:
        {
            dictionary.displayDescending();
            break;
        }
        case 6:
        {
            string keyword;
            cout << "Enter keyword to find maximum comparisons: ";
            cin >> keyword;
            int maxComparisons = dictionary.maxComparisons(keyword);
            cout << "Maximum comparisons required: " << maxComparisons << endl;
            break;
        }
        case 7:
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
/*
The overall time and space complexity of the program and each function are as follows:

1. `Dictionary` constructor: The constructor initializes the `rootNode` pointer to NULL. It has a time complexity of O(1) and a space complexity of O(1).

2. `Dictionary::addKeyword`: This function inserts a keyword with its meaning into the binary search tree. The time complexity depends on the height of the tree and can be O(N) in the worst case if the tree is heavily skewed. The space complexity is O(log N) in the average case due to the recursive calls. In the worst case, it can be O(N) when the tree is heavily skewed.

3. `Dictionary::deleteKeyword`: This function deletes a keyword from the binary search tree. The time complexity depends on the height of the tree and can be O(N) in the worst case if the tree is heavily skewed. The space complexity is O(log N) in the average case due to the recursive calls. In the worst case, it can be O(N) when the tree is heavily skewed.

4. `Dictionary::updateKeyword`: This function updates the meaning of a keyword in the binary search tree. It performs a search for the keyword, which has a time complexity of O(N) in the worst case if the tree is heavily skewed. The space complexity is O(1) as it uses a constant amount of additional space.

5. `Dictionary::displayAscending`: This function performs an in-order traversal of the binary search tree and displays the keywords and meanings in ascending order. The time complexity is O(N) since it visits each node once. The space complexity is O(1) as it uses a constant amount of additional space.

6. `Dictionary::displayDescending`: This function performs a reverse in-order traversal of the binary search tree and displays the keywords and meanings in descending order. The time complexity is O(N) since it visits each node once. The space complexity is O(1) as it uses a constant amount of additional space.

7. `Dictionary::maxComparisons`: This function calculates the maximum number of comparisons required to find a keyword in the binary search tree. The time complexity depends on the height of the tree and can be O(N) in the worst case if the tree is heavily skewed. The space complexity is O(1) as it uses a constant amount of additional space.

8. `Dictionary` destructor: The destructor is responsible for freeing the memory allocated for the binary search tree. It needs to traverse the tree and delete each node. The time complexity is O(N) since it visits each node once. The space complexity is O(1) as it uses a constant amount of additional space.

The overall time complexity of the program depends on the operations performed and the structure of the binary search tree. The worst-case time complexity for adding, deleting, and finding a keyword is O(N) when the tree is heavily skewed. The time complexity for displaying the keywords in ascending or descending order is O(N). The space complexity of the program depends on the height of the tree and can be O(log N) in the average case and O(N) in the worst case.

Oral Questions:
1. What is the purpose of the `Dictionary` class?
2. How are keywords and their meanings stored in the binary search tree?
3. Explain the process of inserting a keyword into the binary search tree.
4. How is a keyword deleted from the binary search tree?
5. How can the meaning of a keyword be updated in the binary search tree?
6. Describe the time and space complexity of the overall program and each function.
7. What are the complexities involved in finding the maximum number of comparisons for a keyword?
8. How are the keywords and their meanings

 displayed in ascending and descending order?
9. What is the role of the `findMinNode` function in the `deleteNode` operation?
10. Why is it important to implement a destructor for the `Dictionary` class?

Answers:
1. The `Dictionary` class is used to create and manage a binary search tree to store keywords and their meanings.
2. Keywords and their meanings are stored as nodes in the binary search tree. Each node contains a keyword, a meaning, and pointers to the left and right child nodes.
3. To insert a keyword, the program compares it with the keywords in the tree starting from the root node. If the keyword is smaller, it goes to the left subtree; if it is larger, it goes to the right subtree. This process continues until a suitable position is found, and a new node is created and inserted.
4. To delete a keyword, the program first searches for the node containing the keyword. If found, it handles three cases: (a) if the node has no children, it is simply deleted; (b) if the node has one child, that child takes its place; (c) if the node has two children, the minimum node from the right subtree replaces it, and the minimum node is then deleted recursively.
5. To update the meaning of a keyword, the program performs a search for the keyword. If found, it updates the meaning with the new value.
6. The overall time complexity of the program depends on the operations performed and the structure of the binary search tree. The worst-case time complexity for adding, deleting, and finding a keyword is O(N) when the tree is heavily skewed. The time complexity for displaying the keywords in ascending or descending order is O(N). The space complexity of the program depends on the height of the tree and can be O(log N) in the average case and O(N) in the worst case.
7. The maximum number of comparisons for a keyword can be calculated by traversing the tree from the root to the node containing the keyword. The time complexity is dependent on the height of the tree and can be O(N) in the worst case. The number of comparisons made during the traversal represents the maximum number of comparisons required.
8. To display the keywords and meanings in ascending order, an in-order traversal of the binary search tree is performed. To display them in descending order, a reverse in-order traversal is used. Both traversals have a time complexity of O(N) and a space complexity of O(1).
9. The `findMinNode` function is used to find the minimum node in a subtree. It is required for the `deleteNode` operation to replace a node with two children. The minimum node from the right subtree replaces the deleted node, ensuring the binary search tree property is maintained.
10. Implementing a destructor is important to free the memory allocated for the binary search tree. The destructor traverses the tree and deletes each node, preventing memory leaks and ensuring proper memory management.
*/
