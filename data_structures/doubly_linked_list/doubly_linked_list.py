# Each ListNode holds a reference to its previous node and its next node in the List
class ListNode:
  def __init__(self, value, prev=None, next=None):
    self.value = value
    self.prev = prev
    self.next = next

  # Wrap the given value in a ListNode and insert it after this node. 
  # Note that this node could already have a next node it is point to.
  def insert_after(self, value):
    current_next = self.next
    self.next = ListNode(value, self, current_next)
    if current_next:
      current_next.prev = self.next

  # Wrap the given value in a ListNode and insert it before this node. 
  # Note that this node could already have a previous node it points to.
  def insert_before(self, value):
    current_prev = self.prev
    self.prev = ListNode(value, current_prev, self)
    if current_prev:
      current_prev.next = self.prev

  # Rearrange this ListNode's previous and next pointers accordingly, 
  # effectively deleting this ListNode.
  def delete(self):
    if self.prev:
      self.prev.next = self.next
    if self.next:
      self.next.prev = self.prev



# doubly-linked list class holds references to the list's head and tail nodes
class DoublyLinkedList:
  def __init__(self, node=None):
    self.head = node
    self.tail = node
    self.length = 1 if node else 0


  def __len__(self):
    return self.length


  def add_to_head(self, value):
    new_node = ListNode(value)
    self.length += 1

    if self.head:
      self.head.prev = new_node
      new_node.next = self.head
      self.head = new_node
    else:
      self.head = new_node
      self.tail = new_node


  def remove_from_head(self):
    if self.head == self.tail:
      old_head = self.head
      self.head = None
      self.tail = None
      self.length -= 1
      return old_head.value

    elif self.head != self.tail:
      old_head = self.head
      self.head = old_head.next
      self.length -= 1
      self.head.prev = None
      self.head.next = old_head.prev
      return old_head.value

    else:  # if no head
      return None


  def add_to_tail(self, value):
    new_node = ListNode(value)
    self.length += 1

    if self.head:
      self.tail.next = new_node
      new_node.prev = self.tail
      self.tail = new_node
    else:
      self.head = new_node
      self.tail = new_node


  def remove_from_tail(self):
    if self.head == self.tail:
      old_tail = self.tail
      self.head = None
      self.tail = None
      self.length -= 1
      return old_tail.value

    elif self.head != self.tail:
      old_tail = self.tail
      self.tail = self.tail.prev
      self.length -= 1
      self.tail.next = None
      return old_tail

    else:  # if no tail
      return None


  def move_to_front(self, node):
    self.add_to_head(node.value)
    self.delete(node)


  def move_to_end(self, node):
    self.add_to_tail(node.value)
    self.delete(node)


  def delete(self, node):
    self.length -= 1

    if node is self.head and node is self.tail:
      self.head = None
      self.tail = None

    elif node is self.head:
      self.head = node.next

    elif node is self.tail:
      self.tail = node.prev


  def get_max(self):
    max_val = self.head.value
    current_head = self.head

    while current_head:
      if current_head.value > max_val:
        max_val = current_head.value

      current_head = current_head.next

    return max_val
