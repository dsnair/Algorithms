# Analysis of Algorithms

## Big-O Rules

1. O(f(x)) + O(g(x)) = O(f(x) + g(x)) (independent operations)
2. O(f(x)) * O(g(x)) = O(f(x) * g(x)) (dependent operations)
3. O(c * f(x)) = O(f(x))
3. O(f(x) + c) = O(f(x))
4. O(c) = O(1)

Give an analysis of the running time of each snippet of
pseudocode with respect to the input size n of each of the following:

## Exercise I

```
a)  a = 0
    while (a < n * n * n):
      a = a + n * n
```

<mark>O(n)</mark>

```
n=0, n^3 = 0: loop never runs

n=1, n^3 = 1:
a | a+n^2
---------
0 | 0 + 1^2 = 1

n=2, n^3 = 8:
a | a+n^2
---------
0 | 0 + 2^2 = 4
4 | 4 + 2^2 = 8

n=3, n^3 = 27:
a | a+n^2
---------
0  | 0 + 3^2 = 9
9  | 9 + 3^2 = 18
18 | 18 + 3^2 = 27

n=4, n^3 = 64:
a | a+n^2
---------
0  | 16
16 | 16 + 4^2 = 32
32 | 32 + 4^2 = 48
48 | 48 + 4^2 = 64
```

```
b)  sum = 0
    for i in range(n):
      i += 1
      for j in range(i + 1, n):
        j += 1
        for k in range(j + 1, n):
          k += 1
          for l in range(k + 1, 10 + k):
            l += 1
            sum += 1
```

<mark>O(n^3)</mark>

i-for(), j-for(), k-for() runs once each for each element in the range, so they have O(n). l-for() always has 9 elements in its range: (10+k) - (k+1) = 9, so it has O(9) which is O(1).

Hence, O(n) * O(n) * O(n) * O(1) = O(1 * n * n * n) = O(n^3)

```
c)  def bunnyEars(bunnies):
      if bunnies == 0:
        return 0

      return 2 + bunnyEars(bunnies-1)
```

<mark>O(n)</mark>

```
B | Returns             | # Recursions
--------------------------------------
0 | 0                   | 1
1 | 2 + B(0)
  | 2 + 0               | 2
2 | 2 + B(1)
  | 2 + 2 + B(0)
  | 2 + 2 + 0           | 3
3 | 2 + B(2)
  | 2 + 2 + B(1)
  | 2 + 2 + 2 + B(0)
  | 2 + 2 + 2 + 0       | 4
```

For a given n, the recursion function runs n+1 times, which is O(n).


## Exercise II

Suppose that you have an _n_-story building and plenty of eggs. Suppose also that an egg gets broken if it is thrown off floor _f_ or higher, and doesn't get broken if dropped off a floor less than floor _f_. Devise a strategy to determine the value of _f_ such that the number of dropped eggs is minimized.

Write out your proposed algorithm in plain English or pseudocode and give the runtime complexity of your solution.

```
We can use the Binary Search algorithm to efficiently calculate the minimum f:
    - Start with the middle floor of the building (n/2).
    - Drop the egg from this middle floor:
        - If it breaks, subset the list from [1, ..., n] to [1, ..., n/2].
            - Drop the egg from the middle floor of the new list.
            - If the egg breaks again, further subset the list.
            - Continue until the list gets smaller and smaller such that you can identify the minimum f.
        - If the egg doesn't break, subset the list from [1, ..., n] to [n/2, ..., 1].
            - Repeat the same steps as stated above for this new list instead.

The run-time algorithm for Binary Search is O(log n).
```