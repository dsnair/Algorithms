# Linked List to handle collisions
class LinkedPair:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.next = None


# djb2 hash function
def hash(string, max = 2 ** 32):
    h = 5381
    byte_array = string.encode('utf-8')

    for byte in byte_array:
        h = ((h * 33) ^ byte) % max

    return h


def resize(hash_table):
    pass


class HashTable:
    def __init__(self, size):
        self.size = size
        self.table = [None] * size


    # Handle collisions with Linked List
    def insert(self, key, value):
        index = hash(key) % self.size
        if self.table[index]:
            print("You're overwriting the hash table key.")
        else:
            self.table[index] = value
        # print("Insert:", self.table[index])


    # If you try to remove a value that isn't there, print a warning
    def remove(self, key):
        index = hash(key) % self.size
        if self.table[index]:
            self.table[index] = None
        else:
            print("This value doesn't exist in the hash table.")
        # print("Remove:", self.table[index])


    # Return None if the key is not found
    def retrieve(self, key):
        index = hash(key) % self.size
        if index:
            # print("Retrieve:", self.table[index])
            return self.table[index]
        else:
            return None


ht = HashTable(16)
ht.insert("hello", "World!")
ht.retrieve("hello")
ht.remove("hello")