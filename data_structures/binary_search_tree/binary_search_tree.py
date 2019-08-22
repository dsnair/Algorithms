class BinarySearchTreeNode:
  def __init__(self, value):
    self.value = value
    self.left = None
    self.right = None


  def __str__(self):
    return "{} {} {}".format(self.value, self.left, self.right)


  def insert(self, value):
    # print(self.value, self.left, self.right)

    if self.value < value:
      if self.right:
        self.right.insert(value)
      else:
        self.right = BinarySearchTreeNode(value) 
             
    else:
      if self.left:
        self.left.insert(value)
      else:
        self.left = BinarySearchTreeNode(value)          
  

  def contains(self, target):
    if target < self.value:
      return self.left.contains(target) if self.left else False
    elif target > self.value:
      return self.right.contains(target) if self.right else False
    else:
      return True


  def get_max(self):
    if self.right:
      return self.right.get_max()
    else:
      return self.value


  def for_each(self, cb):    
    cb(self.value)  # cb is defined in test_binary_search_tree.py

    if self.left:
        self.left.for_each(cb)

    if self.right:
        self.right.for_each(cb)


bst = BinarySearchTreeNode(5)
bst.insert(2)
bst.insert(3)
bst.insert(7)
bst.insert(6)

# print(bst)

# print(bst.contains(2))
# print(bst.contains(6))
# print(bst.contains(8))

# print(bst.get_max())