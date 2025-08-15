# Simulated Heap Memory Allocator in C

This project implements a **simulated heap memory allocator** in C, mimicking the behavior of `malloc` and `free` using a custom-managed memory pool. It demonstrates memory allocation, deallocation, and free-list management, including block merging to minimize fragmentation.

---

## Features

- **Simulates a heap of 256 KB (+ threshold)**
- **Custom `Allocate` and `Deallocate` functions** (replacement for `malloc`/`free`)
- **Free-list management with block merging** (coalescing adjacent free blocks)
- **Tracks allocated and free blocks with linked lists**
- **Displays internal state for debugging and verification**
- **Prevents allocation of zero-sized blocks**
- **Handles external fragmentation and allocation failures gracefully**

---

## How It Works

- **Memory Pool:** A static array (`simulatedHeap`) acts as the heap.
- **MetaData:** Each block (free or allocated) has a header storing its size and a next pointer.
- **Free List:** Linked list of free blocks.
- **Allocated List:** Linked list of allocated blocks (for demonstration and debugging).
- **Block Splitting:** Large free blocks are split when allocating smaller blocks.
- **Block Merging:** Adjacent free blocks are merged during deallocation to reduce fragmentation.

---

## Usage

### 1. Clone the Repository

```bash
git clone https://github.com/Abhiram163/Heap-Management-Linked-Lists-
cd Heap-Management-Linked-Lists-
```

### 2. Compile

```bash
gcc -o heap_allocator main.c
```

### 3. Run

```bash
./heap_allocator
```

### 4. Example Output

```
----Heap simulation Successfull----

Memory Allocation successfull

Memory Allocation successfull

Memory Allocation successfull

Memory Allocation successfull

Free List = 

AddressofBlock = 0x... 
size = ...

Allocated List = 

AddressofBlock = 0x...
size = ...
...

Memory successfully Freed Up

Free List = 
...
Allocated List = 
...

...

-------Heap allocation and deallocation done successfully-------
```

---

## File Structure

- `main.c` — Main source file with all logic
- `README.md` — This documentation

---

## Code Structure

- **MetaData struct:** Header for each block (size, next pointer)
- **Allocate:** Allocates memory from the free list, splits blocks if needed
- **Deallocate:** Returns memory to the free list, merges adjacent free blocks
- **DisplayLists:** Prints the current state of free and allocated lists for debugging
- **Main:** Demonstrates allocation and deallocation, showing list states after each operation

---

## Limitations

- **Not thread-safe** (no synchronization)
- **No support for realloc or calloc**
- **No error checking for pointer validity beyond simple checks**
- **For demonstration/educational purposes only** (not a replacement for real allocators)

---

## Contributing

Pull requests are welcome! If you have suggestions for improvements, bug fixes, or want to add features (like `realloc`, better fragmentation handling, or statistics), feel free to fork and submit a PR.

---

## License

This project is open source and available under the [MIT License](LICENSE).

---

## Author

- Abhiram Vadhri

---

## Acknowledgments

- Inspired by operating systems and memory management coursework.
- Useful for understanding how dynamic memory allocation works under the hood.

---

**Happy Hacking!**

---

> _Feel free to customize the author, repository URL, and add more sections as needed for your GitHub profile!_
