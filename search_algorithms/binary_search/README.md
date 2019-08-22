# Search Algorithms

## Array-based

![binary v sequential](https://www.mathwarehouse.com/programming/images/binary-vs-linear-search/binary-and-linear-search-animations.gif "Binary v Sequential Search")

### 1. Linear Search
- iterate through each item in the data until (1) you find what you are searching for, or (2) conclude the item being search is not in the data.
- O(n) -- This is a time consuming algorithm. Eg: searching if a user exists in a database of millions of users

### 2. Binary Search
- data must be SORTED 
- calculate the median value of the data 
- check if the median is < the item being search. If yes, eliminate the entire left tree and repeat the process on the right side.
- similarly, if the median is > the item being searched, eliminate the right tree and repeat the search process on the left side.
- O(log n) -- This is a more efficient search algorithm than linear search because you don't have to go through the entire data

## Graph-based

### 3. Breadth-first Search (BFS)
- select a starting node. For trees, this is the root. For undirected graphs, indicate which node is the starting node.
- BFS searches the children of a given parent node. If the children have siblings, they go in a queue and get searched one at a time.
- If none of the children have what you are looking for, repeat the process with the children's children until you reach the leaf nodes.
- Eg: given a network of your facebook friends, finding a new friend through your mutual friends

### 4. Depth-first Search
- similar to bread-first search, except all the branches of a tree go in a stack and get an entire branch gets searched from start (child of parent node) to end (leaf node)
- Eg: given an entry point in a maze, finding a path to the exit point