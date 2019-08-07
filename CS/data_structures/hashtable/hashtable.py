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
    # double hash table size
    ht = HashTable(2 * hash_table.size) 

    # copy old hash table into new one
    for item in hash_table.table:
        while item != None:
            ht.insert(item.key, item.value)
            item = item.next
            
    return ht


class HashTable:
    def __init__(self, size):
        self.size = size
        self.table = [None] * size


    # Handle collisions with Linked List
    def insert(self, key, value):
        index = hash(key, self.size)
        lp = LinkedPair(key, value)

        # if there is collision,
        if self.table[index]:
            # store the value of the colliding key in the next linked list node
            lp.next = self.table[index]
        
        self.table[index] = lp


    def remove(self, key):
        index = hash(key, self.size)

        # if hash table index has values
        if self.table[index]:
            lp = self.table[index]
            # and you found the key,
            if lp.key == key:
                # replace that value with the next key's value
                self.table[index] = lp.next
            else:
                # else loop through linked list until you find the key
                while lp.next != None:
                    if lp.next.key == key:
                        lp.next = lp.next.next
                    else:
                        lp = lp.next
        else:
            print("This value doesn't exist in the hash table.")


    def retrieve(self, key):
        index = hash(key, self.size)

        # if hash table index has values,
        if self.table[index]:
            # loop through linked list until key is found
            lp = self.table[index]
            if lp.key == key:
                return lp.value
            else:
                while lp.next != None:
                    if lp.next.key == key:
                        return lp.next.value
                    else:
                        lp = lp.next
        else:
            # return None if key is not found
            return None


ht = HashTable(1)

ht.insert("key0", "value0")
ht.insert("key0", "value1")
print(ht.retrieve("key0"))

ht.remove("nonexistent-key")

new = resize(ht)
print(len(new.table))
print(new.retrieve("key0"))