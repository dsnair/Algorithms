## Linked List

Linked List is a type of tree where a node has ATmost one child node

![Image of Doubly Linked List](https://upload.wikimedia.org/wikipedia/commons/thumb/5/5e/Doubly-linked-list.svg/610px-Doubly-linked-list.svg.png)

### Implementation

* The `ListNode` class, which represents a single node in the doubly-linked list, has already been implemented for you. Inspect this code and try to understand what it is doing to the best of your ability.
* The `DoublyLinkedList` class itself should have the methods: `add_to_head`, `add_to_tail`, `remove_from_head`, `remove_from_tail`, `move_to_front`, `move_to_end`, `delete`, and `get_max`.
  * `add_to_head` replaces the head of the list with a new value that is passed in.
  * `add_to_tail` replaces the tail of the list with a new value that is passed in.
  * `remove_from_head` removes the head node and returns the value stored in it.
  * `remove_from_tail` removes the tail node and returns the value stored in it.
  * `move_to_front` takes a reference to a node in the list and moves it to the front of the list, shifting all other list nodes down. 
  * `move_to_end` takes a reference to a node in the list and moves it to the end of the list, shifting all other list nodes up. 
  * `delete` takes a reference to a node in the list and removes it from the list. The deleted node's `previous` and `next` pointers should point to each afterwards.
  * `get_max` returns the maximum value in the list. 
* The `head` property is a reference to the first node and the `tail` property is a reference to the last node.

## Runtime

1. What is the runtime complexity of `ListNode.insert_after`?

2. What is the runtime complexity of `ListNode.insert_before`?

3. What is the runtime complexity of `ListNode.delete`?

4. What is the runtime complexity of `DoublyLinkedList.add_to_head`?

5. What is the runtime complexity of `DoublyLinkedList.remove_from_head`?

6. What is the runtime complexity of `DoublyLinkedList.add_to_tail`?

7. What is the runtime complexity of `DoublyLinkedList.remove_from_tail`?

8. What is the runtime complexity of `DoublyLinkedList.move_to_front`?

9. What is the runtime complexity of `DoublyLinkedList.move_to_end`?

10. What is the runtime complexity of `DoublyLinkedList.delete`?

    a. Compare the runtime of the doubly linked list's `delete` method with the worst-case runtime of the JS `Array.splice` method. Which method generally performs better?