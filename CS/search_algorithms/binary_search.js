// recursive implementation of Binary Search
const binary_search = (array, value, low, high) => {
  if (high >= low) {
    middle = low + Math.floor((high - low) / 2)

    // if value is smaller than middle, narrow search to left sub-array
    if (value < array[middle])
      return binary_search(array, value, low, middle - 1)

    // if value is bigger than middle, narrow search to right sub-array
    if (value > array[middle])
      return binary_search(array, value, middle + 1, high)

    // if value is at the middle
    if (value == array[middle]) return middle
  } else {
      return -1  // value not found
  }
}

let arr1 = [-9, -8, -6, -4, -3, -2, 0, 1, 2, 3, 5, 7, 8, 9]
let arr2 = []

console.log(binary_search(arr1, -8, 0, arr1.length-1))
console.log(binary_search(arr2, -8, 0, arr2.length-1))