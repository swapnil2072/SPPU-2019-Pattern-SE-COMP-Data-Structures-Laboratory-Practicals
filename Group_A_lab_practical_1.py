# Consider telephone book database of N clients. Make use of a hash table implementation
# to quickly look up client‘s telephone number. Make use of two collision handling
# techniques and compare them using number of comparisons required to find a set of
# telephone numbers


class HashTable:
    def __init__(self, size):
        self.size = size
        self.linear_hashtable = [0] * size
        self.quadratic_hashtable = [0] * size
        self.linear_visited = [False] * size
        self.quadratic_visited = [False] * size

    def linear_probing(self, num):
        index = num % self.size
        if not self.linear_visited[index]:
            self.linear_hashtable[index] = num
            self.linear_visited[index] = True
        else:
            while self.linear_visited[index]:
                index = (index + 1) % self.size

            self.linear_hashtable[index] = num
            self.linear_visited[index] = True

    def quadratic_probing(self, num):
        index = num % self.size
        if not self.quadratic_visited[index]:
            self.quadratic_hashtable[index] = num
            self.quadratic_visited[index] = True
        else:
            for k in range(1, self.size):
                t = (index + k * k) % self.size
                if not self.quadratic_visited[t]:
                    self.quadratic_hashtable[t] = num
                    self.quadratic_visited[t] = True
                    break

    def find(self, num, probing_type):
        if probing_type == "linear":
            hashtable = self.linear_hashtable
        elif probing_type == "quadratic":
            hashtable = self.quadratic_hashtable
        else:
            print("Invalid probing type")
            return

        index = num % self.size
        if hashtable[index] == num:
            print("Found", num)
        else:
            if probing_type == "linear":
                for i in range(1, self.size):
                    index = (index + 1) % self.size
                    if hashtable[index] == num:
                        print("Found", num)
                        break
                else:
                    print("Not found", num)
            elif probing_type == "quadratic":
                for k in range(1, self.size):
                    t = (index + k * k) % self.size
                    if hashtable[t] == num:
                        print("Found", num)
                        break
                else:
                    print("Not found", num)


def main():
    size = 10
    hash_table = HashTable(size)
    probing_mode = 0

    while True:
        print("1. Linear probing.")
        print("2. Quadratic probing.")
        print("3. Find element.")
        print("4. Exit.")

        try:
            choice = int(input("Enter your choice: "))
        except ValueError:
            print("Invalid choice. Please enter a number.")
            continue

        if choice == 1:
            num_elements = int(input("Enter the number of elements: "))
            for _ in range(num_elements):
                try:
                    phone_num = int(input("Enter phone number: "))
                    hash_table.linear_probing(phone_num)
                    print(
                        "Hashtable using linear probing:", hash_table.linear_hashtable
                    )
                    probing_mode = 1
                except ValueError:
                    print("Invalid input. Please enter a number.")
                    continue

        elif choice == 2:
            num_elements = int(input("Enter the number of elements: "))
            for _ in range(num_elements):
                try:
                    phone_num = int(input("Enter phone number: "))
                    hash_table.quadratic_probing(phone_num)
                    print(
                        "Hashtable using quadratic probing:",
                        hash_table.quadratic_hashtable,
                    )
                    probing_mode = 2
                except ValueError:
                    print("Invalid input. Please enter a number.")
                    continue

        elif choice == 3:
            num_to_find = int(input("Enter the number to be found: "))
            if probing_mode == 1:
                hash_table.find(num_to_find, "linear")
            elif probing_mode == 2:
                hash_table.find(num_to_find, "quadratic")
        elif choice == 4:
            print("End of Program")
            break
        else:
            print("Enter a valid choice")


if __name__ == "__main__":
    main()


"""
The overall time and space complexity of the program depends on the size of the hash table, denoted by the variable `size`.
  Let's analyze the time and space complexity of each function and the program as a whole:

1. `HashTable.__init__(self, size)`: This function initializes the hash table and visited arrays with a given size.
   It has a time complexity of O(size) and a space complexity of O(size).

2. `HashTable.linear_probing(self, number)`: This function performs linear probing to insert a number into the hash table. 
  In the worst case, when all slots are occupied and a collision occurs, it may require traversing the entire hash table, resulting in a time complexity of O(size). 
  The space complexity is O(1) since it only modifies existing arrays.

3. `HashTable.quadratic_probing(self, number)`: This function performs quadratic probing to insert a number into the hash table. In the worst case, when all slots are occupied and a collision occurs, it may require traversing the entire hash table, resulting in a time complexity of O(size). The space complexity is O(1) since it only modifies existing arrays.

4. `HashTable.find(self, num_to_find, probing_type)`: This function searches for a number in the hash table using either linear or quadratic probing. In the worst case, when the number is not found or it requires traversing the entire hash table, the time complexity is O(size). The space complexity is O(1) since it only accesses existing arrays.

5. `main()`: The main function interacts with the user and calls the other functions based on the user's input. It has a time complexity of O(size) for each insertion and search operation, depending on the choice made by the user. The space complexity is O(size) for the hash table and visited arrays.

Overall, the time complexity of the program is dominated by the size of the hash table, denoted by `size`. The worst-case time complexity is O(size) for insertion and search operations. The space complexity is also O(size) for the hash table and visited arrays.

Oral questions related to the program:

1. What is the purpose of the `HashTable` class in this program?
2. What is the difference between linear probing and quadratic probing?
3. How is collision resolved in linear probing? What about quadratic probing?
4. Explain the purpose of the `visited` arrays in the `HashTable` class.
5. What is the time complexity of finding an element in the hash table?
6. How does the choice made by the user affect the probing mode in the program?
7. What is the exit condition of the program's main loop?
8. How does the size of the hash table affect the performance of the program?
9. Is the program limited to storing phone numbers, or can it store any type of data?

Answers:

1. The `HashTable` class represents a hash table data structure. It provides methods for inserting elements using linear or quadratic probing and searching for elements in the hash table.

2. Linear probing and quadratic probing are collision resolution techniques used in hash tables. Linear probing searches for the next available slot by incrementing the index linearly, while quadratic probing uses a quadratic function to probe for the next available slot.

3. In linear probing, collision is resolved by searching for the next available slot sequentially. If a slot is occupied, the algorithm continues to search the next slot until an empty slot is found. In quadratic probing, collision is resolved by incrementing the index using a quadratic function until an empty slot is found.

4. The `visited` arrays in the `HashTable` class are used to keep track of whether a slot in the hash table has been visited (occupied) or not

. This information is essential for the probing functions to determine the next available slot during insertion and search operations.

5. The time complexity of finding an element in the hash table depends on the probing mode. In the worst case, when the element is not found and all slots are probed, the time complexity is O(size). However, if the hash function distributes the elements evenly, the average time complexity can be considered O(1).

6. The choice made by the user determines whether linear or quadratic probing is used for insertion and search operations. The program sets a probing mode variable (`probing_mode`) accordingly, and this variable is used to select the appropriate probing method when searching for an element.

7. The exit condition of the main loop is triggered when the user selects the "Exit Program" option (choice 4). This breaks the loop and terminates the program.

8. The size of the hash table directly affects the performance of the program. A larger hash table allows for a larger number of elements to be stored without collisions. However, it also increases the time and space complexity of the program.

9. The program is not limited to storing phone numbers. It can store any integer values provided by the user. However, it is not designed to handle other data types such as strings or objects.
"""
