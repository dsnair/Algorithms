# Array

## Remove

| Method | Use Case                           | Returns         | Mutable? |
|--------|------------------------------------|-----------------|----------|
| pop    | remove last element                | removed element | Yes      |
| shift  | remove first element               | removed element | Yes      |
| splice | remove element from specific index | removed element | Yes      |
| filter | remove elements programmatically   | new array       | No       |

## Add

| Method  | Use Case                         | Returns      | Mutable? |
|---------|----------------------------------|--------------|----------|
| pop     | add new element at the end       | array length | Yes      |
| unshift | add new element at the beginning | array length | Yes      |

## Loop

| Method  | Use Case                                    | Returns                                    |
|---------|---------------------------------------------|--------------------------------------------|
| map     | executes the callback on each array element | mutated array                              |
| forEach | executes the callback on each array element | nothing, but the original array is mutated |
| reduce  | executes the callback on each array element | a single result                            |