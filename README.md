# Object Manager with Reference Counting

## Overview

This repository contains the implementation of an **object manager** in C, designed to manage the lifecycle and references of dynamically created objects. The manager tracks all allocated objects, supports linking between them, and provides diagnostics such as object listings and reference counts.

The solution adheres to the task requirements of a memory management module (as part of the "Memory Manager" assignment section). It includes a basic reference counting mechanism to track how many other objects link to each object.

## Key Features

- **Object Creation and Deletion:**
  - Objects are created using `create_object`.
  - Objects are deleted using `destroy_object`.
  - All allocated objects are tracked alphabetically.

- **Object Linking and Reference Counting:**
  - Objects can link to other objects using the `link` function.
  - Each object keeps track of how many other objects reference it via the `num_refs` field.
  - Reference counts are displayed with `print_link_counts`.

- **Diagnostics:**
  - `print_objects` lists all currently allocated objects in **alphabetical order**.
  - `print_link_counts` lists all non-destroyed objects along with their reference counts.

## Implementation Details

- The core object structure is defined in the `os_mem.h` file as `Object`.
- A `memory_manager_t` structure from `os_mem.h` is used to manage function pointers to the implemented operations.
- The function `setup_memory_manager` assigns implemented functions to the appropriate fields of the memory manager.
- STL containers and functions are **not allowed** for this assignment.
- All functions are implemented in a single source file:  
  `SS_2_NNtask.cpp`  
  where `SS` is the student number and `NN` is the task number.
- A demonstration of the implementation (main program) is located in:  
  `SS_2_NNmain.cpp`

## Implemented Functions

- `void create(void);`
- `void destroy(void);`
- `void create_object(const char* name);`
- `void destroy_object(const char* name);`
- `void print_objects(void);`
- `void link(const char* from, const char* to);`
- `void print_link_counts(void);`
- `void setup_memory_manager(memory_manager_t* manager);`

## Compilation

Make sure your project includes the `os_mem.h` header and is compiled with a standard C compiler. Example:

```bash
gcc SS_2_NNtask.c SS_2_NNmain.c -o object_manager
