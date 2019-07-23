## Binary Search Trees

- is a type of tree where a node has ATmost two child nodes (hence the name)
- Given any node, the left subtree of that node contains values < than that node. And, the right subtree of that node contains values >= than that node.
- The left and right subtree each must also be a binary search tree.
- There must be no duplicate nodes.

![Image of Binary Search Tree](https://upload.wikimedia.org/wikipedia/commons/thumb/d/da/Binary_search_tree.svg/300px-Binary_search_tree.svg.png)

### Implementation

Should have the methods `insert`, `contains`, `get_max`.
  * `insert` adds the input value to the binary search tree, adhering to the rules of the ordering of elements in a binary search tree.
  * `contains` searches the binary search tree for the input value, returning a boolean indicating whether the value exists in the tree or not.
  * `get_max` returns the maximum value in the binary search tree.
  * `for_each` performs a traversal of _every_ node in the tree, executing the passed-in callback function on each tree node value. There is a myriad of ways to perform tree traversal; in this case any of them should work. 

## Runtime

1. What is the runtime complexity of `insert`? 

2. What is the runtime complexity of `contains`?

3. What is the runtime complexity of `get_max`?