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
        index = hash(key, self.size)
       
        if self.table[index]:
            lp = LinkedPair(key, value)
            lp.next = self.table[index]
            self.table[index] = lp
        else:
            self.table[index] = LinkedPair(key, value)


    def remove(self, key):
        index = hash(key, self.size)

        if self.table[index]:
            lp = self.table[index]
            if lp.key == key:
                self.table[index] = lp.next
            else:
                while lp.next is not None:
                    if lp.next.key == key:
                        lp.next = lp.next.next
                    else:
                        lp = lp.next
        else:
            print("This value doesn't exist in the hash table.")


    # Return None if the key is not found
    def retrieve(self, key):
        index = hash(key, self.size)

        # if hash table index is not empty,
        if self.table[index]:
            # loop through linked list until key is found
            lp = self.table[index]
            if lp.key == key:
                return lp.value
            else:
                while lp.next is not None:
                    if lp.next.key == key:
                        return lp.next.value
                    else:
                        lp = lp.next
        else:
            # return None if key is not found
            return None


ht = HashTable(16)

ht.insert("key0", "value0")
ht.insert("key0", "value1")

print(ht.retrieve("key0"))

ht.remove("nonexistent-key")