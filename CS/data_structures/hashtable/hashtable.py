# All storage values are initialized to None
class BasicHashTable:
    def __init__(self, size):
        self.size = size
        self.table = [None] * size


# Implement the djb2 hash function
def hash(string, max = 2 ** 32):
    h = 5381
    byte_array = string.encode('utf-8')

    for byte in byte_array:
        h = ((h * 33) ^ byte) % max

    return h


# If you are overwriting a value with a different key, print a warning
def hash_table_insert(hash_table, key, value):
    index = hash(key) % hash_table.size
    if hash_table.table[index]:
        print("You're overwriting the hash table key.")
    else:
        hash_table.table[index] = value
    # print(hash_table.table[index])


# If you try to remove a value that isn't there, print a warning
def hash_table_remove(hash_table, key):
    index = hash(key) % hash_table.size
    if hash_table.table[index]:
        hash_table.table[index] = None
    else:
        print("This value doesn't exist in the hash table.")
    # print(hash_table.table[index])


# Should return None if the key is not found
def hash_table_retrieve(hash_table, key):
    index = hash(key) % hash_table.size
    if index:
        return hash_table.table[index]
    else:
        return None


def Testing():
    ht = BasicHashTable(16)
    hash_table_insert(ht, "hello", "World!")
    hash_table_remove(ht, "hello")

    if hash_table_retrieve(ht, "hello") is None:
        print("Success!")
    else:
        print("Error!")

Testing()