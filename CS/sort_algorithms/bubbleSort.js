/*
 The bubble sort algorithm:
  - It compares the first element of an array with the second element.
  - If the 1st element is greater than the 2nd element, then it swaps them.
  - Then, it compares the 2nd and 3rd elements and swaps them if the 2nd is larger.
  - Then, it compares the 3rd and 4th elements and does the same.
  - This continues and the larger elements begin to "bubble" towards the end.
  - The loop then restarts and repeats this process until it makes a clean pass without performing any swaps.
*/

const bubbleSort = arr => {
  let len = arr.length;
  for (let i = 0; i < len; i++) {
      for (let j = 0; j < len; j++) {
          if (arr[j] > arr[j + 1]) {
              let val = arr[j];
              arr[j] = arr[j + 1];
              arr[j + 1] = val;
          }
      }
  }
  return arr;
};

bubbleSort([3,2,1])
