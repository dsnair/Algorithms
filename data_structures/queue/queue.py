class Queue:
  def __init__(self):
    self.storage = []
    self.length = 0

  def enqueue(self, item):
    self.length += 1
    return self.storage.append(item)
  
  def dequeue(self):
    if self.length:
      self.length -= 1
      return self.storage.pop(0)
    else:
      return None

  def len(self):
    return self.length

  def __str__(self):
    return "{} : {}".format(self.storage, self.length)


q = Queue()

q.enqueue(1)
q.enqueue(2)
q.enqueue(3)

q.dequeue()

print(q)