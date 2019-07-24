class Heap:
  def __init__(self):
    self.storage = []

  def __str__(self):
    return "{}".format(self.storage)

  def insert(self, value):
      self.storage.append(value)
      self._bubble_up(len(self.storage) - 1)


  def delete(self):
    pass


  def get_max(self):
    pass


  def get_size(self):
    pass


  def _bubble_up(self, index):
    while index > 0:
      parent = (index - 1) // 2  # take quotient

      if (self.storage[index] > self.storage[parent]):
        self.storage[index], self.storage[parent] = self.storage[parent], self.storage[index]
        index = parent
      else:
        break


  def _sift_down(self, index):
    pass

  
h = Heap()
h.insert(6)
h.insert(8)
h.insert(10)
h.insert(9)
h.insert(1)
h.insert(9)
h.insert(9)
h.insert(5)

print(h)