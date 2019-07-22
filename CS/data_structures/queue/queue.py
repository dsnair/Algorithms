class Queue:
  def __init__(self):
    # what data structure should we use to store queue elements?
    self.storage = []

  def enqueue(self, item):
    return self.storage.append(item)
  
  def dequeue(self):
    return self.storage.pop(0) if len(self.storage) != 0 else None

  def len(self):
    return len(self.storage)

  def __str__(self):
    return "{}".format(self.storage)


q = Queue()

q.enqueue(1)
q.enqueue(2)
q.enqueue(3)

q.dequeue()

print(q)