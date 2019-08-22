class Heap:
  def __init__(self):
    self.storage = []

  def __str__(self):
    return "{}".format(self.storage)

  def insert(self, value):
    # 1. Create a new node at the end of heap
    # 2. Assign new value to the node
    # 3. Compare the value of this child node with its parent
    # 4. If value of parent is less than child, then swap them
    # 5. Repeat step 3 & 4 until Heap property holds

      self.storage.append(value)  # step 1 & 2
      self._bubble_up(len(self.storage) - 1)


  def delete(self):
    # 1. Remove root node
    # 2. Move the last element of last level to root
    # 3. Compare the new parent with its left & right child nodes
    # 4. If value of parent is less than either child, then swap them
    # 5. Repeat step 3 & 4 until Heap property holds
  
    deleted_node = self.storage[0]
    self.storage[0] = self.storage[-1]  # step 2
    self.storage.pop()  # step 1
    self._sift_down(0)
    return deleted_node


  def get_max(self):
    return self.storage[0]


  def get_size(self):
    return len(self.storage)


  def _bubble_up(self, index):
    while index > 0:  # step 5
      parent = (index - 1) // 2  # take quotient

      if (self.storage[index] > self.storage[parent]):  # step 3
        # step 4
        self.storage[index], self.storage[parent] = self.storage[parent], self.storage[index]
        index = parent
      else:
        break


  def _sift_down(self, index):
    left_child = 2 * index + 1
    right_child = 2 * index + 2

    if left_child < len(self.storage):
      if self.storage[index] < self.storage[left_child]:  # step 3
        # step 4
        self.storage[index], self.storage[left_child] = self.storage[left_child], self.storage[index]
        self._sift_down(left_child)  # step 5

    if right_child < len(self.storage):
      if self.storage[index] < self.storage[right_child]:
        self.storage[index], self.storage[right_child] = self.storage[right_child], self.storage[index]
        self._sift_down(right_child)


# h = Heap()

# h.insert(6)
# h.insert(7)
# h.insert(5)
# h.insert(8)
# h.insert(10)
# h.insert(1)
# h.insert(2)
# h.insert(5)

# h.delete()  # deletes and returns root node
# h.delete()
# h.delete()

# print(h)