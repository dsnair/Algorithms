/*
1. Pick an array element, called pivot. Conventionally, this is the last element.
2. Collect all elements smaller than the pivot in one array, and 
all elements equal to or bigger than the pivot in another array.
3. Recursively, repeat 1-2 for each sub-array, and join the results at the end.
*/

const quickSort = arr => {
  if (arr.length <= 1) return arr
  
  const pivot = arr.pop()
  let lessThanPivot = []
  let greaterThanPivot = []

  arr.forEach(num => num > pivot ? greaterThanPivot.push(num) : lessThanPivot.push(num))
  return [...quickSort(lessThanPivot), pivot, ...quickSort(greaterThanPivot)]
}

quickSort([0, 9, 3, 2, 7, 5, 4, -1])
// quickSort(['d', 'i', 'v', 'y', 'a'])