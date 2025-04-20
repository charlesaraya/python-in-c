# pystructs-in-c

A C implementation of Python’s core data structures — built from scratch to deepen understanding of memory management, generic typing, and algorithmic design in low-level environments.

## Roadmap

### 1. Dynamic Array / List

- **Initialization** of int/float type with capacity. `list()` ✅
- **Length**: get the length of the list. `len(list)` ✅
- **Append**: add an element to the end of the list. `list.append(x)` ✅
- **Extend**: extends the list by appending all the elements from another list. `list.extend(x)` ✅
- **Print**: print the list. `print(list)` ✅
- **Insert**: set an element in the list by index (from head and tail). `list.insert(i, x)` ✅
- **Access**: get an element from the list by index (from head and tail). `list[i]` ✅
- **Membership**: check an element's membership in the list. `x in list` ✅
- **Minimum**: gets the smallest element in the list. `min(list)` ✅
- **Maximum**: gets the biggest element in the list. `max(list)` ✅
- **Pop**: remove an element from the list by index. `list.pop([i])` ✅
- **Search**: search for an element first found in the list and returns the zero-based index. `list.index(x [, start [, end]])` ✅
- **Remove**: remove an element from the list by value. `list.remove(x)` ✅
- **Count**: returns the number of times an element appears in the list. `list.count(x)` ✅
- **Reverse**: reverses the elements of the list in-place. `list.reverse()` ✅
- **Copy**: returns a shallow copy of the list.
- **Sort**: sorts the elements of the list in place.

### Stack (LIFO)

- Push
- Pop
- Peek/top
- Is empty
- Size

### Queue (FIFO)

- Enqueue
- Dequeue
- Peek/front
- Is empty
- Size

### Hash Map / Dictionary
- Basic hashing (modulo-based)
- Chaining or linear probing
- Insert, search, delete
- Key collisions

### Set

- Add
- Remove
- Contains
- Union / Intersection / Difference