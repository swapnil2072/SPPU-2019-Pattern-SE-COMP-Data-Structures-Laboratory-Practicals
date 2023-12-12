#include<iostream>
using namespace std;

class Heap {
   int maxHeap[20];
   int minHeap[20];
   int marks;
   int numberOfStudent;
public:
   Heap() {
      maxHeap[0] = 0;
      minHeap[0] = 0;
   }
   void getData();
   void insertMaxHeap(int marks);
   void upAdjustMaxHeap(int i);
   void insertMinHeap(int marks);
   void upAdjustMinHeap(int i);
   void displayMinMax();
};

void Heap::getData() {
   cout << "\nEnter the number of students: ";
   cin >> numberOfStudent;

   for (int i = 0; i < numberOfStudent; i++) {
      cout << "Enter the marks of student " << i + 1 << ": ";
      cin >> marks;
      insertMaxHeap(marks);
      insertMinHeap(marks);
   }
}

void Heap::insertMaxHeap(int marks) {
   int n = maxHeap[0];
   maxHeap[n + 1] = marks;
   maxHeap[0] = n + 1;

   upAdjustMaxHeap(n + 1);
}

void Heap::upAdjustMaxHeap(int i) {
   int temp;
   while (i > 1 && maxHeap[i] > maxHeap[i / 2]) {
      temp = maxHeap[i];
      maxHeap[i] = maxHeap[i / 2];
      maxHeap[i / 2] = temp;
      i = i / 2;
   }
}

void Heap::insertMinHeap(int marks) {
   int n = minHeap[0];
   minHeap[n + 1] = marks;
   minHeap[0] = n + 1;

   upAdjustMinHeap(n + 1);
}

void Heap::upAdjustMinHeap(int i) {
   int temp;
   while (i > 1 && minHeap[i] < minHeap[i / 2]) {
      temp = minHeap[i];
      minHeap[i] = minHeap[i / 2];
      minHeap[i / 2] = temp;
      i = i / 2;
   }
}

void Heap::displayMinMax() {
   cout << "\nMax marks: " << maxHeap[1];
   cout << "\n******Max Heap*******";
   for (int i = 1; i <= numberOfStudent; i++) {
      cout << "\n" << maxHeap[i];
   }

   cout << "\nMin marks: " << minHeap[1];
   cout << "\n******Min Heap******";
   for (int i = 1; i <= numberOfStudent; i++) {
      cout << "\n" << minHeap[i];
   }
}

int main() {
   cout << "********************************||HEAP||*************************************\n";
   Heap h;
   h.getData();
   h.displayMinMax();
   return 0;
}
/*
The overall time and space complexity of the program can be analyzed as follows:

1. `main()` function:
   - Time complexity: The time complexity of the `main()` function is determined by the operations performed in the `getData()` and `displayMinMax()` functions. Both of these functions involve iterating over the `numberOfStudent` inputs, resulting in a time complexity of O(numberOfStudent).
   - Space complexity: The `main()` function does not use any additional data structures that scale with the input size, so the space complexity is O(1).

2. `getData()` function:
   - Time complexity: The `getData()` function has a loop that iterates `numberOfStudent` times. Within each iteration, the `insertMaxHeap()` and `insertMinHeap()` functions are called, which have an average time complexity of O(log n), where n is the current number of elements in the respective heaps. Therefore, the overall time complexity of `getData()` is O(numberOfStudent * log n).
   - Space complexity: The space complexity of `getData()` is O(1) as it does not use any additional data structures that scale with the input size.

3. `insertMaxHeap()` and `insertMinHeap()` functions:
   - Time complexity: Both functions have an average time complexity of O(log n), where n is the number of elements in the respective heaps. This is because the `upAdjustMaxHeap()` and `upAdjustMinHeap()` functions are called, which perform upward adjustments in the heap to maintain the heap property.
   - Space complexity: The space complexity of both functions is O(1) as they do not use any additional data structures that scale with the input size.

4. `upAdjustMaxHeap()` and `upAdjustMinHeap()` functions:
   - Time complexity: Both functions have a time complexity of O(log n), where n is the number of elements in the respective heaps. This is because in the worst case, the element being inserted may need to move all the way up to the root of the heap, which takes log n comparisons and swaps.
   - Space complexity: The space complexity of both functions is O(1) as they do not use any additional data structures that scale with the input size.

5. `displayMinMax()` function:
   - Time complexity: The `displayMinMax()` function contains two loops, each iterating `numberOfStudent` times. Therefore, the time complexity is O(numberOfStudent).
   - Space complexity: The space complexity of `displayMinMax()` is O(1) as it does not use any additional data structures that scale with the input size.

Oral questions related to the program:

1. What is the purpose of the `getData()` function?
2. How are elements inserted into the max heap and min heap simultaneously?
3. What is the significance of the `upAdjustMaxHeap()` and `upAdjustMinHeap()` functions?
4. What is the time complexity of inserting an element into the max heap and min heap?
5. How does the `displayMinMax()` function provide the maximum and minimum marks from the heaps?
6. What is the space complexity of the `getData()` function?
7. Why is the `upAdjustMaxHeap()` function called after inserting an element into the max heap?

Answers to the oral questions:

1. The `getData()` function is used to input the number of students and their marks. It inserts the marks into both the max heap and min heap.

2. The `insertMaxHeap()` and `insertMinHeap()` functions are called within the `getData()` function to insert elements into the max heap and min heap, respectively. This ensures that the elements are simultaneously inserted into both heaps.

3. The `upAdjustMaxHeap()` and `up

AdjustMinHeap()` functions are responsible for maintaining the heap property (i.e., the maximum element at the root in the max heap, and the minimum element at the root in the min heap) after inserting an element. They perform upward adjustments by swapping elements as necessary.

4. The time complexity of inserting an element into the max heap and min heap is O(log n), where n is the current number of elements in the respective heaps. This is because the `upAdjustMaxHeap()` and `upAdjustMinHeap()` functions perform comparisons and swaps while traversing up the heap to maintain the heap property.

5. The `displayMinMax()` function accesses the maximum and minimum marks by accessing the first elements of the max heap (`maxHeap[1]`) and min heap (`minHeap[1]`), respectively. It then iterates through the heaps to display all the marks.

6. The space complexity of the ` getData() ` function is O(1) as it does not use any additional data structures that scale with the input size. The only variables used are `numberOfStudent` and `marks`, which are constant in size.

7. The `upAdjustMaxHeap()` function is called after inserting an element into the max heap to ensure that the heap property is maintained. If the newly inserted element violates the heap property by being greater than its parent, it performs swaps with its parent until the element is in its correct position in the heap.
*/

