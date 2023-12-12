#include <iostream>
using namespace std;

void constructOptimalBST(int n, float successProb[], float failureProb[], float weightTable[][20], float costTable[][20], int rootTable[][20]);
void printOptimalBST(int left, int right, int rootTable[][20], float weightTable[][20], float costTable[][20]);

int main()
{
    int n;
    cout << "****** PROGRAM FOR OPTIMAL BST ******\n";
    cout << "Enter the number of nodes: ";
    cin >> n;

    if (n <= 0 || n >= 20) {
        cout << "Invalid number of nodes. The number of nodes should be between 1 and 19.\n";
        return 1;
    }

    float successProb[20], failureProb[20], weightTable[20][20], costTable[20][20];
    int rootTable[20][20];

    cout << "Enter the success probability for each key:\n";
    for (int i = 1; i <= n; i++) {
        cout << "p[" << i << "]: ";
        cin >> successProb[i];
    }

    cout << "Enter the failure probability for each dummy key:\n";
    for (int i = 0; i <= n; i++) {
        cout << "q[" << i << "]: ";
        cin >> failureProb[i];
    }

    constructOptimalBST(n, successProb, failureProb, weightTable, costTable, rootTable);
    printOptimalBST(0, n, rootTable, weightTable, costTable);

    return 0;
}

void constructOptimalBST(int n, float successProb[], float failureProb[], float weightTable[][20], float costTable[][20], int rootTable[][20])
{
    for (int i = 0; i < n; i++) {
        costTable[i][i] = 0.0;
        rootTable[i][i] = 0;
        weightTable[i][i] = failureProb[i];
        weightTable[i][i + 1] = failureProb[i] + failureProb[i + 1] + successProb[i + 1];
        costTable[i][i + 1] = failureProb[i] + failureProb[i + 1] + successProb[i + 1];
        rootTable[i][i + 1] = i + 1;
    }

    costTable[n][n] = 0.0;
    rootTable[n][n] = 0;
    weightTable[n][n] = failureProb[n];

    for (int length = 2; length <= n; length++) {
        for (int i = 0; i <= n - length; i++) {
            weightTable[i][i + length] = failureProb[i + length] + successProb[i + length] + weightTable[i][i + length - 1];
            costTable[i][i + length] = 9999;

            for (int k = i + 1; k <= i + length; k++) {
                if (costTable[i][i + length] > (costTable[i][k - 1] + costTable[k][i + length])) {
                    costTable[i][i + length] = costTable[i][k - 1] + costTable[k][i + length];
                    rootTable[i][i + length] = k;
                }
            }
            costTable[i][i + length] += weightTable[i][i + length];
        }
    }
}

void printOptimalBST(int left, int right, int rootTable[][20], float weightTable[][20], float costTable[][20])
{
    if (left >= right) {
        return;
    }

    cout << "Root: " << rootTable[left][right] << ", Weight: " << weightTable[left][right] << ", Cost: " << costTable[left][right] << endl;

    if (rootTable[left][rootTable[left][right] - 1] != 0) {
        cout << "Left child of " << rootTable[left][right] << ": " << rootTable[left][rootTable[left][right] - 1] << endl;
    }

    if (rootTable[rootTable[left][right]][right] != 0) {
        cout << "Right child of " << rootTable[left][right] << ": " << rootTable[rootTable[left][right]][right] << endl;
    }

    printOptimalBST(left, rootTable[left][right] - 1, rootTable, weightTable, costTable);
    printOptimalBST(rootTable[left][right], right, rootTable, weightTable, costTable);
}
/*
The overall time and space complexity of the program and each function are as follows:

1. `constructOptimalBST` function:
   - Time Complexity: O(n^3) - There are two nested loops iterating over n elements, and inside these loops, there is another loop iterating over the length of the subarray. Therefore, the overall time complexity is O(n^3).
   - Space Complexity: O(n^2) - The function uses two-dimensional arrays (`weightTable`, `costTable`, `rootTable`) of size n x n to store intermediate results. Therefore, the space complexity is O(n^2).

2. `printOptimalBST` function:
   - Time Complexity: O(n^2) - The function recursively calls itself for left and right subtrees, each with a reduced size. In the worst case, the function will be called for n elements, resulting in a time complexity of O(n^2).
   - Space Complexity: O(1) - The function does not use any additional space that grows with the input size.

3. `main` function:
   - Time Complexity: O(n^3) - The time complexity is dominated by the `constructOptimalBST` function, which has a time complexity of O(n^3).
   - Space Complexity: O(n^2) - The space complexity is dominated by the space required for the `weightTable`, `costTable`, and `rootTable` arrays, which have a size of n x n.

The overall time complexity of the program is O(n^3), and the overall space complexity is O(n^2).

Oral Questions:
1. What is the purpose of the program?
2. What is the significance of success probabilities and failure probabilities in constructing an optimal binary search tree?
3. How is the `constructOptimalBST` function filling in the `weightTable`, `costTable`, and `rootTable` arrays?
4. What is the time complexity of the `constructOptimalBST` function, and how is it derived?
5. How is the `printOptimalBST` function recursively printing the optimal binary search tree structure?
6. What is the time complexity of the `printOptimalBST` function, and how is it derived?
7. How does the program handle invalid input for the number of nodes?
8. What is the significance of the 9999 value used in the `costTable` initialization?
9. What is the purpose of the `rootTable` array, and how is it used in constructing the optimal binary search tree?
10. How would you modify the program to handle a larger number of nodes, such as 50?

Answers:
1. The program aims to construct an optimal binary search tree given success probabilities, failure probabilities, and the number of nodes.
2. Success probabilities represent the probability of a key being searched successfully, while failure probabilities represent the probability of a dummy key being searched. They are used to calculate the weights and costs of each node in the binary search tree.
3. The `constructOptimalBST` function fills in the `weightTable`, `costTable`, and `rootTable` arrays using dynamic programming. It iterates over different subarrays of keys and computes the minimum cost for each subarray by considering different possible root nodes.
4. The time complexity of the `constructOptimalBST` function is O(n^3). It has two nested loops iterating over n elements, and inside these loops, there is another loop iterating over the length of the subarray. Therefore, the overall time complexity is O(n^3).
5. The `printOptimalBST` function recursively prints the optimal binary search tree structure. It first prints the root node, its weight, and its cost. Then

, it recursively calls itself for the left and right subtrees to print their structures.
6. The time complexity of the `printOptimalBST` function is O(n^2). The function recursively calls itself for left and right subtrees, each with a reduced size. In the worst case, the function will be called for n elements, resulting in a time complexity of O(n^2).
7. The program handles invalid input for the number of nodes by checking if the input is less than or equal to 0 or greater than or equal to 20. If the input is invalid, it displays an error message and terminates the program.
8. The 9999 value used in the `costTable` initialization represents an initially large value that will be replaced during the computation of the optimal costs. It is used as a placeholder to ensure that the minimum cost comparisons are correct.
9. The `rootTable` array stores the indices of the root nodes for each subarray of keys. It is used to reconstruct the optimal binary search tree structure when printing.
10. To handle a larger number of nodes, such as 50, you would need to modify the size of the arrays `successProb`, `failureProb`, `weightTable`, `costTable`, and `rootTable` to accommodate the larger input size. Additionally, you might need to adjust the range of the loops and update the input validation condition in the `main` function to allow a larger number of nodes.
*/

