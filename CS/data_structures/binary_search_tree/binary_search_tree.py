class BinarySearchTree:
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
        self.right = BinarySearchTree(value) 
             
    else:
      if self.left:
        self.left.insert(value)
      else:
        self.left = BinarySearchTree(value)          
  
  def contains(self, target):
    pass

  def get_max(self):
    pass

  def for_each(self, cb):
    pass

bst = BinarySearchTree(5)

bst.insert(2)
bst.insert(3)
bst.insert(7)
bst.insert(6)

print(bst)