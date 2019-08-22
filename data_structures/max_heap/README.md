## Binary Heap

- are a combination of binary trees and arrays
- Binary heap is a binary tree where every node is larger (or smaller) than its two child nodes. The former is called max heap and the latter is called min heap.
![Image of a Heap in Tree form](https://upload.wikimedia.org/wikipedia/commons/thumb/3/38/Max-Heap.svg/501px-Max-Heap.svg.png)
- Every subtree is a binary heap.
- The trees are then flattened as an array.
![Image of a Heap in Array form](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d2/Heap-as-array.svg/603px-Heap-as-array.svg.png)
- Heaps are used in sort algorithms (heapsort), graph traversal algorithms, selection algorithms (finding min, max, median)

### Implementation

Should have the methods `insert`, `delete`, `get_max`, `_bubble_up`, and `_sift_down`.
  * `insert` adds the input value into the heap; this method should ensure that the inserted value is in the correct spot in the heap
  * `delete` removes and returns the 'topmost' value from the heap; this method needs to ensure that the heap property is maintained after the topmost element has been removed. 
  * `get_max` returns the maximum value in the heap _in constant time_.
  * `get_size` returns the number of elements stored in the heap.
  * `_bubble_up` moves the element at the specified index "up" the heap by swapping it with its parent if the parent's value is less than the value at the specified index.
  * `_sift_down` grabs the indices of this element's children and determines which child has a larger value. If the larger child's value is larger than the parent's value, the child element is swapped with the parent.

## Runtime

1. What is the runtime complexity of `_bubble_up`?

2. What is the runtime complexity of `_sift_down`?

3. What is the runtime complexity of `insert`?

4. What is the runtime complexity of `delete`?

5. What is the runtime complexity of `get_max`?

