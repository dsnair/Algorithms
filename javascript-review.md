# A. Concepts

## 1. Data Types

1. Number. JS has only one type of number (64-bit/double precision floating point). Thus, `1, 1.0, 1e10` are all the same.
2. String
3. Boolean
4. Array
5. Object = {key: 'value'}
6. Set

- `undefined` is a declared variable whose value is not yet set.

```javascript
let a
console.log(a) // undefined
```

- `null` is an empty assigned value.

```javascript
let a = null
console.log(a) // null
```

| Data   | Mutable? | Ordered Items? | Unique Items? | Item Access |
| ------ | -------- | -------------- | ------------- | ----------- |
| Array  | Yes      | Yes            | No            | Index       |
| Object | Yes      | No             | Yes           | Key         |
| Set    | Yes      | No             | Yes           | .has()      |
| String | No       | Yes            | No            | Index       |

## 2. Ternary Operator

boolean_condition ? truth_statement : false_statement

## 3. Template Literal

## 4. Destructuring

unpacks values from arrays or object properties into distinct variables

```javascript
let obj = { a: 1, b: true }
let { a, b } = obj

console.log(a) // 1
console.log(b) // true
```

```javascript
let arr = [1, 2]
let [one, two] = arr

console.log(one) // 1
console.log(two) // 2
```

# B. Common Functions

## 1. Array

### a. Remove

| Method | Use Case                              | Returns            | Mutable? |
| ------ | ------------------------------------- | ------------------ | -------- |
| pop    | remove last element                   | removed element    | Yes      |
| shift  | remove first element                  | removed element    | Yes      |
| splice | remove 1+ element from specific index | removed element(s) | Yes      |
| filter | remove elements programmatically      | new array          | No       |

### b. Add

| Method  | Use Case                        | Returns      | Mutable? |
| ------- | ------------------------------- | ------------ | -------- |
| pop     | add new element at the end      | array length | Yes      |
| unshift | add 1+ element at the beginning | array length | Yes      |
| splice  | add element at specific index   | empty array  | Yes      |

```javascript
let x = [1, 2, 3, 4, 5]

console.log(x.splice(1, 2)) // [2, 3]
console.log(x) // [1, 4, 5]

console.log(x.splice(1, 0, 6)) // []
console.log(x) // [1, 6, 4, 5]
```

### c. Extract

| Method | Use Case     | Returns   | Mutable? |
|--------|--------------|-----------|----------|
| slice  | subset array | new array | No       |

```javascript
let x = [1, 2, 3]
console.log(x.slice(0, 2)) // [1, 2]
console.log(x.slice(-2)) // [2, 3]
```

`indexOf` is useful for finding the indices of items when using `splice` and `slice`.

### d. Loop

| Method  | Use Case                                   | Returns         | Mutable? |
| ------- | ------------------------------------------ | --------------- | -------- |
| map     | execute the callback on each array element | new array       | No       |
| forEach | execute the callback on each array element | nothing         | No       |
| reduce  | execute the callback on each array element | a single result | No       |

[Does It Mutate?](https://doesitmutate.xyz/)

## 2. String

### a. Find

| Method     | Use Case                                 | Returns | Mutable? |
| ---------- | ---------------------------------------- | ------- | -------- |
| startsWith | check if string starts with given string | boolean | No       |
| endsWith   | check if string ends with given string   | boolean | No       |
| includes   | check if string contains given string    | boolean | No       |

### b. Extract

| Method     | Use Case                     | Returns    | Mutable? |
| ---------- | ---------------------------- | ---------- | -------- |
| slice      | return string in given range | new string | No       |
| str[index] | return string at given index | new string | No       |

## 3. Object

```javascript
let obj = { a: 1, b: true }
```

1. `'a' in obj` returns a boolean for if the key is in the object
2. `Object.keys(obj)` returns an array of the object keys
3. `Object.values(obj)` returns an array of the object values
4. `obj.c = 'c'` changes the value of the key, if it exists, or creates the key, if it doesn't exist
