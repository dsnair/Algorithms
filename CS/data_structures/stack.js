/*
Stack is a LIFO construct: Last In, First Out. 
Think of a stack of plates in a dining hall or restaurant's plate dispenser:
 - The first plate gets a bunch of plates put on top of it. 
 - The last plate you put on the stack of plates is the first one you could remove.
*/

class Stack {
  constructor() {
    this.storage = []
  }
  add(item) {
    return this.storage.push(item)
  }
  remove() {
    return this.storage.pop()
  }
  numOfItems() {
    return this.storage.length === 0 ? 
      "There are no items in your stack." :
      this.storage.length
  }
}

const myStack = new Stack()
console.log(myStack.numOfItems())

myStack.add('first')
myStack.add('second')
myStack.add('third')
console.log(myStack.numOfItems())

console.log(myStack.storage)
myStack.remove()

console.log(myStack.storage)
myStack.remove()

console.log(myStack.storage)
myStack.remove()

console.log(myStack.storage)
console.log(myStack.numOfItems())
