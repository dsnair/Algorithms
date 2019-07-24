# DATA STRUCTURES

## Array-based

### 1. Queue (line) 
- you get in the back of the line, the person first in line is served first
- Eg: When a server gets multiple client requests, it places them in a queue and serves the first request first

![Image of Queue](https://upload.wikimedia.org/wikipedia/commons/thumb/5/52/Data_Queue.svg/600px-Data_Queue.svg.png)

### 2. Stack (stack of plates)
- imagine a stack of plates at the dinner table. The first plate in the stack gets picked up first.

## Graph-based

### 3. Graph
- a graph has nodes and edges / paths
- If the paths between the nodes are uni-directional, it is called a **directed graph** 
- If the paths between the nodes are bi-directional, it is called an **undirected graph** (because the arrows are no longer needed to indicate direction)
- **Cyclic graph** is a loop, i.e. the starting and the ending node is the same
- **Acyclic graph** has no loops
- **Directed Acyclic Graph (DAG)** is a finite directed graph that has no directed cycles, i.e. it consists of finitely many nodes and edges, with each edge directed from one vertex to another, such that there is no way to start at any vertex v and follow a consistently-directed sequence of edges that eventually loop back to v again.
- A **connected component** of an undirected graph is a subgraph in which any two vertices are connected to each other by paths, and which is connected to no additional vertices in the supergraph
    - Breadth-first search can be used to find a connected component

### 4. Tree
- is a type of graph 
- A tree can only have uni-directional path between its nodes. 
- A tree is also a minimally connected graph, i.e. removing one edge, disconnects it from the rest of the graph. Therefore, a minimally connected graph can have no cycles / loops.

### 5. Linked List
- is a type of tree where a node has ATmost one child node

![Image of Doubly Linked List](https://upload.wikimedia.org/wikipedia/commons/thumb/5/5e/Doubly-linked-list.svg/610px-Doubly-linked-list.svg.png)

### 6. Binary Tree
- is a type of tree where a node has ATmost two child nodes (hence the name)
- Given any node, the left subtree of that node contains values < than that node. And, the right subtree of that node contains values >= than that node.
- The left and right subtree each must also be a binary search tree.
- Binary trees are great to use in search algorithms, in comparison to arrays or linked lists, because you traverse through only a portion of the tree (based on is current node < (or >) the node you are searching?) and not through all the elements as in an array or linked lists. 
- Binary trees are not as good for inserting new elements as arrays and linked lists are.

![Image of Binary Search Tree](https://upload.wikimedia.org/wikipedia/commons/thumb/d/da/Binary_search_tree.svg/300px-Binary_search_tree.svg.png)

### 7. Binary Heap
- are a combination of binary trees and arrays
- Binary heap is a binary tree where every node is larger (or smaller) than its two child nodes. The former is called max heap and the latter is called min heap.
![Image of a Heap in Tree form](https://upload.wikimedia.org/wikipedia/commons/thumb/3/38/Max-Heap.svg/501px-Max-Heap.svg.png)
- The trees are then flattened as an array.
![Image of a Heap in Array form](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d2/Heap-as-array.svg/603px-Heap-as-array.svg.png)
- Heaps are used in sort algorithms (heapsort), graph traversal algorithms, selection algorithms (finding min, max, median)