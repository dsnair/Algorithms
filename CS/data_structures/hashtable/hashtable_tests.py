import unittest

from hashtable import HashTable


class TestHashTable(unittest.TestCase):

    def test_hash_table_creation(self):
        ht = HashTable(8)

        self.assertEqual(len(ht.table), 8)
        self.assertTrue(ht.table is not None)

    def test_hash_table_retrieval_of_initialized_value(self):
        ht = HashTable(8)

        return_value = ht.retrieve("key-0")
        self.assertTrue(return_value is None)

    def test_hash_table_insertion_and_retrieval(self):
        ht = HashTable(8)

        ht.insert("key-0", "new-val-0")
        return_value = ht.retrieve("key-0")
        self.assertTrue(return_value == "new-val-0")

    def test_hash_table_removal(self):
        ht = HashTable(8)

        ht.insert("key-1", "new-val-1")
        ht.remove("key-1")
        return_value = ht.retrieve("key-1")
        self.assertTrue(return_value is None)


if __name__ == '__main__':
    unittest.main()