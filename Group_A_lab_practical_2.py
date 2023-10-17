# implemented using with and without replacement.

# Implement all the functions of a dictionary (ADT) using hashing and handle collisions
# using chaining with / without replacement.
# Data: Set of (key, value) pairs, Keys are mapped to values, Keys must be comparable,
# Keys must be unique. Standard Operations: Insert(key, value), Find(key), Delete(key)


class HashTable:
    def __init__(self, size):
        self.size = size
        self.dictionary = [[-1, -1] for i in range(size)]
        self.is_occupied = [False] * size
        self.chain = [-1] * size

    def hash_function(self, number):
        return number % self.size

    def insert_without_replacement(self, key, value):
        index = self.hash_function(key)

        if not self.is_occupied[index]:
            self.dictionary[index][0] = key
            self.dictionary[index][1] = value
            self.is_occupied[index] = True
        else:
            collision_index = index
            while self.chain[collision_index] != -1:
                collision_index = self.chain[collision_index]
            while self.is_occupied[index]:
                index = (index + 1) % self.size

            self.dictionary[index][0] = key
            self.dictionary[index][1] = value
            self.is_occupied[index] = True
            self.chain[collision_index] = index

    def insert_with_replacement(self, key, value):
        index = self.hash_function(key)
        if not self.is_occupied[index]:
            self.dictionary[index][0] = key
            self.dictionary[index][1] = value
            self.is_occupied[index] = True

        elif self.dictionary[index][0] % self.size != index:
            key_to_be_replaced = self.dictionary[index][0]
            value_to_be_replaced = self.dictionary[index][1]
            value_in_chain = self.chain[index]

            self.dictionary[index][0] = key
            self.dictionary[index][1] = value
            self.chain[index] = -1
            self.is_occupied[index] = True
            updating_chain_value = index

            while self.is_occupied[index]:
                index = (index + 1) % self.size

            self.dictionary[index][0] = key_to_be_replaced
            self.dictionary[index][1] = value_to_be_replaced
            self.is_occupied[index] = True
            self.chain[index] = value_in_chain

            for i in range(self.size):
                if self.chain[i] == updating_chain_value:
                    self.chain[i] = index

        else:
            collision_index = index

            while self.chain[collision_index] != -1:
                collision_index = self.chain[collision_index]
            while self.is_occupied[index]:
                index = (index + 1) % self.size

            self.dictionary[index][0] = key
            self.dictionary[index][1] = value
            self.is_occupied[index] = True
            self.chain[collision_index] = index

    def display(self):
        print("Hash Table:")
        print("------------------------")
        print(f"{'Index':<6} {'Key':<6} {'Value':<6} {'Chain':<6}")
        print("------------------------")

        for index, (key, value) in enumerate(self.dictionary):
            chain_index = self.chain[index]
            chain_str = f"-> {chain_index}" if chain_index != -1 else chain_index
            print(f"{index:<6} {key:<6} {value:<6} {chain_str:<6}")

        print("------------------------")

    def find(self, key):
        index = self.hash_function(key)
        if self.dictionary[index][0] == key:
            print("element found ", key)
        else:
            while self.chain[index] != -1:
                index = self.chain[index]
                if self.dictionary[index][0] == key:
                    print("element found ", key)
                    break
            else:
                print("element not found.")

    def delete(self, key):
        index = self.hash_function(key)
        if self.dictionary[index][0] == key:
            self.dictionary[index][0] = -1
            self.dictionary[index][1] = -1
            self.is_occupied[index] = False
            print("element found and deleted ", key)
        else:
            while self.chain[index] != -1:
                index = self.chain[index]
                if self.dictionary[index][0] == key:
                    self.dictionary[index][0] = -1
                    self.dictionary[index][1] = -1
                    self.is_occupied[index] = False
                    print("element found and deleted ", key)
                    break
            else:
                print("element not found.")


def menu():
    print("------------------------Menu----------------------------")
    print("1. Insert a key-value pair without replacement")
    print("2. Insert a key-value pair with replacement")
    print("3. Display the Hash Table")
    print("4. Find a value based on key")
    print("5. Delete a key-value pair")
    print("6. Exit")


hash_table = HashTable(10)

while True:
    menu()
    choice = input("Enter your choice (1-6): ")

    if choice == "1":
        key = int(input("Enter a key: "))
        value = input("Enter a value: ")
        hash_table.insert_without_replacement(key, value)
        print("Key-Value pair inserted successfully!")
        hash_table.display()

    elif choice == "2":
        key = int(input("Enter a key: "))
        value = input("Enter a value: ")
        hash_table.insert_with_replacement(key, value)
        print("Key-Value pair inserted successfully!")
        hash_table.display()

    elif choice == "3":
        hash_table.display()

    elif choice == "4":
        key = int(input("Enter a key to find: "))
        hash_table.find(key)

    elif choice == "5":
        key = int(input("Enter a key to delete: "))
        hash_table.delete(key)

    elif choice == "6":
        print("Exiting...")
        break

    else:
        print("Invalid choice. Please try again.")


"""

The overall time and space complexity of the program depends on the size of the hash table, denoted by the variable `size`. Let's analyze the time and space complexity of each function and the program as a whole:

1. `HashTable.__init__(self, size)`: This function initializes the hash table, the chain array, and the is_occupied array with a given size. It has a time complexity of O(size) and a space complexity of O(size).

2. `HashTable.hash_function(self, number)`: This function calculates the hash value for a given number. It performs a modulo operation and has a time complexity of O(1). The space complexity is O(1) since it doesn't use any additional memory.

3. `HashTable.insert(self, key, value)`: This function inserts a key-value pair into the hash table. In the worst case, when all slots are occupied and collisions occur, it may require traversing the entire hash table and the chain array, resulting in a time complexity of O(size). The space complexity is O(1) since it only modifies existing arrays.

4. `HashTable.display(self)`: This function displays the contents of the hash table. It iterates through the hash table and the chain array once, resulting in a time complexity of O(size). The space complexity is O(1) since it only accesses existing arrays.

5. `HashTable.find(self, key)`: This function searches for a value based on a given key in the hash table. In the worst case, when the key is not found or it requires traversing the chain array, the time complexity is O(size). The space complexity is O(1) since it only accesses existing arrays.

6. `HashTable.delete(self, key)`: This function deletes a key-value pair from the hash table. In the worst case, when the key is not found or it requires traversing the chain array, the time complexity is O(size). The space complexity is O(1) since it only modifies existing arrays.

7. `menu()`: This function displays the menu options to the user. It has a time complexity of O(1) and a space complexity of O(1).

Overall, the time complexity of the program is dominated by the size of the hash table, denoted by `size`. The worst-case time complexity is O(size) for insertion, deletion, and search operations. The space complexity is also O(size) for the hash table, chain array, and is_occupied array.

Oral questions related to the program:

1. What is the purpose of the `HashTable` class in this program?
2. How is collision resolved in this hash table implementation?
3. What is the purpose of the `chain` array?
4. How does the `hash_function` determine the index for a given key?
5. Explain the process of inserting a key-value pair into the hash table.
6. How does the program handle collisions during insertion?
7. What is the purpose of the `is_occupied` array?
8. How does the `display` function iterate through the hash table and chain array?
9. How does the `find` function search for a value based on a given key?
10. How is the deletion of a key-value pair implemented in the `delete` function?

Answers:

1. The `HashTable` class represents a hash table data structure. It provides methods for inserting key-value pairs, searching for values based on keys, and deleting key-value pairs.

2. Collision is resolved using linear probing. When a collision occurs during insertion, the program sequentially searches for the next available slot until an empty slot is found.

3. The `chain` array is used to handle collisions. It stores the index of the next slot in

 case of collisions. It helps in traversing the chain of slots to find the next available slot during insertion and the correct slot during search operations.

4. The `hash_function` calculates the hash value for a given key by performing a modulo operation on the key with the size of the hash table. The result gives the index where the key-value pair should be stored.

5. To insert a key-value pair, the `insert` function first calculates the index using the `hash_function`. If the slot at that index is unoccupied, the key-value pair is stored there. If the slot is occupied, the program searches for the next available slot using linear probing and stores the key-value pair there.

6. During insertion, when a collision occurs and the next available slot is found, the `chain` array is updated. It stores the index of the next slot, forming a chain of slots for collision resolution.

7. The `is_occupied` array is used to track whether a slot in the hash table is occupied or not. It helps in determining the availability of slots during insertion and search operations.

8. The `display` function iterates through the hash table and chain array using a loop. It prints the index, key, value, and chain index of each slot in a formatted manner.

9. The `find` function calculates the index using the `hash_function` for the given key. It compares the key at that index with the search key. If they match, the element is found. If not, it follows the chain of slots by using the `chain` array until either the element is found or the end of the chain is reached.

10. The `delete` function searches for the given key in the hash table. If the key is found at the initial index, the corresponding slot is marked as unoccupied. Otherwise, it follows the chain of slots by using the `chain` array until either the key is found or the end of the chain is reached. If the key is found, the corresponding slot is marked as unoccupied.

"""
