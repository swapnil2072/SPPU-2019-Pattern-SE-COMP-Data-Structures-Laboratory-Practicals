#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class BinaryTreeNode {
public:
    string keyword;
    string meaning;
    int height;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

    BinaryTreeNode(string keyword, string meaning) {
        this->keyword = keyword;
        this->meaning = meaning;
        this->height = 1;
        left = NULL;
        right = NULL;
    }
};

class Dictionary {
private:
    BinaryTreeNode* rootNode;

    BinaryTreeNode* insert(BinaryTreeNode* node, string keyword, string meaning);
    BinaryTreeNode* findMinNode(BinaryTreeNode* node);
    BinaryTreeNode* deleteNode(BinaryTreeNode* node, string keyword);
    int getHeight(BinaryTreeNode* node);
    int getBalanceFactor(BinaryTreeNode* node);
    BinaryTreeNode* rotateLeft(BinaryTreeNode* node);
    BinaryTreeNode* rotateRight(BinaryTreeNode* node);
    void updateHeight(BinaryTreeNode* node);
    void inOrderTraversal(BinaryTreeNode* node);
    void reverseInOrderTraversal(BinaryTreeNode* node);
    int countComparisons(BinaryTreeNode* node, string keyword, int count);

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

Dictionary::Dictionary() {
    rootNode = NULL;
}

void Dictionary::addKeyword(string keyword, string meaning) {
    rootNode = insert(rootNode, keyword, meaning);
}

void Dictionary::deleteKeyword(string keyword) {
    rootNode = deleteNode(rootNode, keyword);
}

void Dictionary::updateKeyword(string keyword, string newMeaning) {
    BinaryTreeNode* node = rootNode;
    while (node != NULL) {
        if (keyword == node->keyword) {
            node->meaning = newMeaning;
            break;
        } else if (keyword < node->keyword) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
}

void Dictionary::displayAscending() {
    cout << "Dictionary in ascending order:" << endl;
    inOrderTraversal(rootNode);
    cout << endl;
}

void Dictionary::displayDescending() {
    cout << "Dictionary in descending order:" << endl;
    reverseInOrderTraversal(rootNode);
    cout << endl;
}

int Dictionary::maxComparisons(string keyword) {
    int comparisons = countComparisons(rootNode, keyword, 0);
    return comparisons;
}

Dictionary::~Dictionary() {
    // TODO: Implement destructor to free memory
}

BinaryTreeNode* Dictionary::insert(BinaryTreeNode* node, string keyword, string meaning) {
    if (node == NULL) {
        BinaryTreeNode* newNode = new BinaryTreeNode(keyword, meaning);
        return newNode;
    }

    if (keyword < node->keyword) {
        node->left = insert(node->left, keyword, meaning);
    } else {
        node->right = insert(node->right, keyword, meaning);
    }

    updateHeight(node);

    int balanceFactor = getBalanceFactor(node);

    // Left Left Case
    if (balanceFactor > 1 && keyword < node->left->keyword) {
        return rotateRight(node);
    }

    // Right Right Case
    if (balanceFactor < -1 && keyword > node->right->keyword) {
        return rotateLeft(node);
    }

    // Left Right Case
    if (balanceFactor > 1 && keyword > node->left->keyword) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case
    if (balanceFactor < -1 && keyword < node->right->keyword) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

BinaryTreeNode* Dictionary::findMinNode(BinaryTreeNode* node) {
    if (node == NULL)
        return NULL;

    while (node->left != NULL) {
        node = node->left;
    }

    return node;
}

BinaryTreeNode* Dictionary::deleteNode(BinaryTreeNode* node, string keyword) {
    if (node == NULL) {
        return NULL;
    }

    if (keyword < node->keyword) {
        node->left = deleteNode(node->left, keyword);
    } else if (keyword > node->keyword) {
        node->right = deleteNode(node->right, keyword);
    } else {
        if (node->left == NULL && node->right == NULL) {
            delete node;
            return NULL;
        } else if (node->left == NULL) {
            BinaryTreeNode* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == NULL) {
            BinaryTreeNode* temp = node->left;
            delete node;
            return temp;
        } else {
            BinaryTreeNode* minNode = findMinNode(node->right);
            node->keyword = minNode->keyword;
            node->meaning = minNode->meaning;
            node->right = deleteNode(node->right, minNode->keyword);
        }
    }

    updateHeight(node);

    int balanceFactor = getBalanceFactor(node);

    // Left Left Case
    if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0) {
        return rotateRight(node);
    }

    // Left Right Case
    if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Right Case
    if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0) {
        return rotateLeft(node);
    }

    // Right Left Case
    if (balanceFactor < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

int Dictionary::getHeight(BinaryTreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int Dictionary::getBalanceFactor(BinaryTreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

BinaryTreeNode* Dictionary::rotateLeft(BinaryTreeNode* node) {
    BinaryTreeNode* rightChild = node->right;
    BinaryTreeNode* leftChildOfRightChild = rightChild->left;

    rightChild->left = node;
    node->right = leftChildOfRightChild;

    updateHeight(node);
    updateHeight(rightChild);

    return rightChild;
}

BinaryTreeNode* Dictionary::rotateRight(BinaryTreeNode* node) {
    BinaryTreeNode* leftChild = node->left;
    BinaryTreeNode* rightChildOfLeftChild = leftChild->right;

    leftChild->right = node;
    node->left = rightChildOfLeftChild;

    updateHeight(node);
    updateHeight(leftChild);

    return leftChild;
}

void Dictionary::updateHeight(BinaryTreeNode* node) {
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = max(leftHeight, rightHeight) + 1;
}

void Dictionary::inOrderTraversal(BinaryTreeNode* node) {
    if (node == NULL) {
        return;
    }

    inOrderTraversal(node->left);
    cout << node->keyword << " - " << node->meaning << endl;
    inOrderTraversal(node->right);
}

void Dictionary::reverseInOrderTraversal(BinaryTreeNode* node) {
    if (node == NULL) {
        return;
    }

    reverseInOrderTraversal(node->right);
    cout << node->keyword << " - " << node->meaning << endl;
    reverseInOrderTraversal(node->left);
}

int Dictionary::countComparisons(BinaryTreeNode* node, string keyword, int count) {
    if (node == NULL) {
        return count;
    }

    if (keyword == node->keyword) {
        return count + 1;
    }

    if (keyword < node->keyword) {
        return countComparisons(node->left, keyword, count + 1);
    } else {
        return countComparisons(node->right, keyword, count + 1);
    }
}

int main() {
    Dictionary dictionary;

    int choice;
    bool flag = true;

    while (flag) {
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

        switch (choice) {
            case 1: {
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
            case 2: {
                string keyword;
                cout << "Enter keyword to delete: ";
                cin >> keyword;
                dictionary.deleteKeyword(keyword);
                break;
            }
            case 3: {
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
            case 4: {
                dictionary.displayAscending();
                break;
            }
            case 5: {
                dictionary.displayDescending();
                break;
            }
            case 6: {
                string keyword;
                cout << "Enter keyword to find maximum comparisons: ";
                cin >> keyword;
                int maxComparisons = dictionary.maxComparisons(keyword);
                cout << "Maximum comparisons required: " << maxComparisons << endl;
                break;
            }
            case 7: {
                flag = false;
                break;
            }
            default: {
                cout << "Invalid Choice." << endl;
            }
        }
    }

    return 0;
}
/*
The overall time and space complexity of the program can be analyzed as follows:

1. Time Complexity:
   - The time complexity of the `addKeyword` function is O(log n) in the average case and O(n) in the worst case. This is because the function performs a binary search to find the appropriate position to insert the keyword, and the height of the tree affects the number of comparisons required.
   - The time complexity of the `deleteKeyword` function is also O(log n) in the average case and O(n) in the worst case. Similar to the `addKeyword` function, it performs a binary search to find the keyword to delete and the height of the tree affects the number of comparisons required.
   - The time complexity of the `updateKeyword` function is O(log n) in the average case and O(n) in the worst case. Again, it performs a binary search to find the keyword to update.
   - The time complexity of the `displayAscending` and `displayDescending` functions is O(n) since they perform an in-order traversal of the binary search tree.
   - The time complexity of the `maxComparisons` function is O(log n) in the average case and O(n) in the worst case. It performs a binary search to find the keyword and counts the number of comparisons required.

   Overall, the program has a time complexity of O(n) in the worst case, where n is the number of keywords in the dictionary.

2. Space Complexity:
   - The space complexity of the program is O(n), where n is the number of keywords in the dictionary. This is because the program uses dynamic memory allocation to create binary tree nodes for each keyword, and the space required is proportional to the number of nodes in the tree.

   The space complexity of individual functions is not significant as it depends on the recursive calls and the number of keywords being processed at each level.

Oral Questions:

1. What is the purpose of the `getHeight` function in the `Dictionary` class?
   - The `getHeight` function returns the height of a given node in the binary search tree. It is used to calculate the balance factor of a node, which is the difference between the heights of its left and right subtrees.

2. How does the program maintain the balance of the binary search tree?
   - The program uses rotation operations (`rotateLeft` and `rotateRight`) to maintain the balance of the binary search tree. These rotations are performed when the balance factor of a node becomes greater than 1 or less than -1, indicating an imbalance in the tree.

3. What is the purpose of the `countComparisons` function in the `Dictionary` class?
   - The `countComparisons` function counts the number of comparisons required to find a given keyword in the binary search tree. It is used in the `maxComparisons` function to determine the maximum number of comparisons required to find any keyword in the tree.

4. How is the time complexity of the program affected by the balance of the binary search tree?
   - The time complexity of the program is affected by the balance of the binary search tree. A balanced tree with approximately equal numbers of nodes in the left and right subtrees will result in better average-case performance with a time complexity of O(log n) for search, insertion, and deletion operations. However, an imbalanced tree with a skewed structure can lead to worst-case time complexity of O(n) for these operations.

Answers to the oral questions:

1. The `getHeight` function is used to calculate the height of a given node in the binary search tree. It recursively calculates the height by comparing the heights of the left and right subtrees and returning the maximum height plus one. The height of a node

 is the longest path from that node to a leaf node in the tree.

2. The program maintains the balance of the binary search tree by performing rotation operations. When a node becomes unbalanced (balance factor greater than 1 or less than -1), the appropriate rotation operation is applied to restore balance. The `rotateLeft` and `rotateRight` functions perform left and right rotations, respectively, by adjusting the pointers of the nodes involved in the rotation. These rotations ensure that the tree remains balanced and maintains the search properties of a binary search tree.

3. The `countComparisons` function is used to count the number of comparisons required to find a given keyword in the binary search tree. It takes a node, a keyword, and a count as input parameters. It compares the keyword with the keyword of the current node and recursively traverses the left or right subtree based on the comparison result. If the keyword is found, the function returns the count incremented by one. The count represents the number of comparisons made to find the keyword.

4. The time complexity of the program is affected by the balance of the binary search tree. In a balanced tree, the average-case time complexity for search, insertion, and deletion operations is O(log n), where n is the number of nodes in the tree. This is because the height of a balanced tree grows logarithmically with the number of nodes, ensuring efficient search operations. However, if the tree becomes imbalanced and takes on a skewed structure, the worst-case time complexity can be O(n). This occurs when the tree degenerates into a linked list-like structure, causing search, insertion, and deletion operations to require traversing all nodes in the tree.

Certainly! Here are some oral questions and their answers related to balancing a binary search tree:

1. What is the purpose of balancing a binary search tree?
   - Balancing a binary search tree ensures that the tree maintains its efficiency for search, insertion, and deletion operations. A balanced tree has a height that is logarithmic in the number of nodes, resulting in O(log n) time complexity for these operations.

2. What is a balance factor in a binary search tree?
   - The balance factor of a node in a binary search tree is the difference between the heights of its left and right subtrees. It is used to determine whether a node is balanced, left-heavy, or right-heavy.

3. How is a balance factor calculated for a node in a binary search tree?
   - The balance factor of a node is calculated by subtracting the height of its right subtree from the height of its left subtree. The formula is: balance factor = height(left subtree) - height(right subtree).

4. What are the rotation operations used to balance a binary search tree?
   - There are mainly four rotation operations used to balance a binary search tree: left rotation, right rotation, left-right rotation (also known as LR rotation), and right-left rotation (also known as RL rotation). These operations involve adjusting the pointers of nodes to restructure the tree and restore its balance.

5. How does a left rotation work in balancing a binary search tree?
   - A left rotation is performed on a node to balance a binary search tree. It involves moving the node's right child to the node's position, making the right child the new root of the subtree. The original node becomes the left child of the new root, and the left child of the right child becomes the right child of the original node.

6. When is a rotation operation applied in balancing a binary search tree?
   - A rotation operation is applied when a node's balance factor becomes greater than 1 or less than -1. These values indicate that the node is unbalanced and needs to be rotated to restore balance.

7. How does balancing a binary search tree affect its performance?
   - Balancing a binary search tree improves its performance by maintaining a logarithmic height. This ensures that search, insertion, and deletion operations have a time complexity of O(log n) in the average case, resulting in efficient data retrieval and modification.

Answers to the oral questions:

1. The purpose of balancing a binary search tree is to maintain its efficiency for search, insertion, and deletion operations. A balanced tree has a height that is logarithmic in the number of nodes, ensuring a time complexity of O(log n) for these operations.

2. The balance factor of a node in a binary search tree is the difference between the heights of its left and right subtrees. It is calculated by subtracting the height of the right subtree from the height of the left subtree.

3. Balancing a binary search tree involves performing rotation operations. A left rotation is used to balance a tree when a node becomes left-heavy. It adjusts the pointers of nodes to restructure the tree and restore its balance.

4. The rotation operations used to balance a binary search tree are left rotation, right rotation, left-right rotation (LR rotation), and right-left rotation (RL rotation). These operations help maintain the balance of the tree by repositioning nodes.

5. A left rotation is performed by taking a node and moving its right child to its position, making the right child the new root of the subtree. The original node becomes the left child of the new root, and the left child of the right child becomes the right child of the original node.

6. Rotation operations are applied when a node's balance factor becomes greater than 1 or less than -1, indicating

 that the node is unbalanced. The appropriate rotation is then performed to restore balance.

7. Balancing a binary search tree improves its performance by maintaining a logarithmic height. This ensures that search, insertion, and deletion operations have an average time complexity of O(log n), leading to efficient data retrieval and modification.
*/

