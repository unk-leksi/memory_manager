# 📁 Memory Manager with Reference Counting in C

## 📌 Project Description  
This project implements a simplified memory manager in C that handles dynamically allocated named objects. It provides a reference counting mechanism and supports linking between objects. The manager can print all currently allocated objects in alphabetical order and report how many times each object is referenced by others.

## 🔧 Core Features  
- ✔️ Object Creation – Create uniquely named objects  
- ✔️ Object Destruction – Remove objects from memory  
- ✔️ Object Linking – Establish references between objects  
- ✔️ Reference Counting – Track how many links point to each object  
- ✔️ Alphabetical Listing – Print objects in sorted order  
- ✔️ Memory Manager Setup – Register function pointers in `memory_manager_t`

## 📜 Function Overview  

| Function                      | Description                                                                 |
|------------------------------|-----------------------------------------------------------------------------|
| `create()`                   | Initializes the internal state of the object manager                        |
| `destroy()`                  | Frees all memory and resets the object manager                              |
| `create_object(name)`        | Creates a new object with the given name                                    |
| `destroy_object(name)`       | Deletes the object with the given name                                     |
| `link(from, to)`             | Creates a reference from one object to another                              |
| `print_objects()`            | Prints all currently allocated objects in alphabetical order                |
| `print_link_counts()`        | Prints reference counts for all non-deleted objects in alphabetical order   |
| `setup_memory_manager(mgr)`  | Registers all implemented functions in the `memory_manager_t` struct        |

## 🚀 How It Works  

### 1️⃣ Initialization – `create`  
Sets up data structures for object management.

### 2️⃣ Object Management – `create_object`, `destroy_object`  
Creates and destroys objects by name. Maintains internal registry.

### 3️⃣ Linking – `link`  
Links one object to another, increasing the target's reference count.

### 4️⃣ Diagnostics – `print_objects`, `print_link_counts`  
Prints all current objects and their reference counts, both in alphabetical order.

### 5️⃣ Cleanup – `destroy`  
Frees all resources and clears the internal object registry.

## 📎 File Structure  

- `34_2_08task.cpp` — Main implementation of the object manager 
- `34_2_08main.cpp` — Example usage of the object manager with test cases  
- `os_mem.h` — Provides the `Object` and `memory_manager_t` definitions and function declarations  

## 📦 Example Use  

```c
create();
create_object("a");
create_object("b");
link("a", "b");
print_objects();       // Output: a b
print_link_counts();   // Output: a: 0, b: 1
destroy_object("a");
print_objects();       // Output: b
destroy();
