class RingBuffer:
  def __init__(self, capacity):
    self.capacity = capacity
    self.current = 0
    self.storage = [None] * capacity


  def append(self, item):
    if self.current < self.capacity:
      self.storage[self.current] = item
      self.current += 1
    else:
      self.current = self.capacity % self.current
      self.storage[self.current] = item
      self.current += 1
    # print(self.storage, len(self.storage))


  def get(self):
    # print(list(filter(None, self.storage)))
    return list(filter(None.__ne__, self.storage))


# r = RingBuffer(5)

# r.get() 

# r.append('a')
# r.append('b')
# r.append('c')
# r.append('d')
# r.get()

# r.append('e')
# r.get()

# r.append('f')
# r.get()

# r.append('g')
# r.append('h')
# r.append('i')
# r.get()