# Array

## Remove

| Method | Use Case                              | Returns         | Mutable? |
|--------|---------------------------------------|-----------------|----------|
| pop    | remove last element                   | removed element | Yes      |
| shift  | remove first element                  | removed element | Yes      |
| splice | remove 1+ element from specific index | removed element | Yes      |
| filter | remove elements programmatically      | new array       | No       |

## Add

| Method  | Use Case                         | Returns      | Mutable? |
|---------|----------------------------------|--------------|----------|
| pop     | add new element at the end       | array length | Yes      |
| unshift | add 1+ element at the beginning  | array length | Yes      |
| splice  | add element at specific index    | empty array  | Yes      |

## Loop

| Method  | Use Case                                   | Returns         | Mutable? |
|---------|--------------------------------------------|-----------------|----------|
| map     | execute the callback on each array element | new array       | No       |
| forEach | execute the callback on each array element | nothing         | No       |
| reduce  | execute the callback on each array element | a single result | No       |

[Does It Mutate?](https://doesitmutate.xyz/)

# String

## Find

| Method     | Use Case                                 | Returns | Mutable? |
|------------|------------------------------------------|---------|----------|
| startsWith | check if string starts with given string | boolean | No       |
| endsWith   | check if string ends with given string   | boolean | No       |
| includes   | check if string contains given string    | boolean | No       |

## Extract

| Method     | Use Case                     | Returns    | Mutable? |
|------------|------------------------------|------------|----------|
| slice      | return string in given range | new string | No       |
| str[index] | return string at given index | new string | No       |
