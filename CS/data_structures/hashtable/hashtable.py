# Basic hash table key/value pair
class Pair:
    def __init__(self, key, value):
        self.key = key
        self.value = value


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


# If you are overwriting a value with a different key, print a warning.
def hash_table_insert(hash_table, key, value):
    pass


# '''
# Fill this in.

# If you try to remove a value that isn't there, print a warning.
# '''
def hash_table_remove(hash_table, key):
    pass


# '''
# Fill this in.

# Should return None if the key is not found.
# '''
def hash_table_retrieve(hash_table, key):
    pass


def Testing():
    ht = BasicHashTable(16)

    hash_table_insert(ht, "line", "Here today...\n")

    hash_table_remove(ht, "line")

    if hash_table_retrieve(ht, "line") is None:
        print("...gone tomorrow (success!)")
    else:
        print("ERROR:  STILL HERE")


Testing()