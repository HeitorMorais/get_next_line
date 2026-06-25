*This project has been created as part of the 42 curriculum by hemorais*

## Description
This project consists of coding a function in C, `get_next_line`, that returns a line read from a file descriptor. Repeated calls to this function inside a loop allow the reading of a text file or standard input (stdin) one line at a time until the end of the file (EOF) is reached. 

The primary learning objectives of this project are:
* Understanding and implementing **static variables** in C.
* Managing memory dynamically on the **Heap** using `malloc` and `free`.
* Handling buffer-based file reading through the `read` system call, controlled dynamically by a compiler flag macro.

## Instructions
### Compilation
The project does not require a Makefile for the mandatory part, but it must compile properly alongside a test program (e.g., `main.c`) using both standard flags and the `-D BUFFER_SIZE=n` flag, which defines the buffer size dynamically.

To compile with a default buffer size of 42, run:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```
## Resources

* Unix System Calls: Linux man pages for read(2).

* Dynamic Memory: Linux man pages for malloc(3) and free(3).

* C Programming Concepts: Standard documentation regarding the scope, initialization, and lifetime of static variables in C.

## AI Usage Description

Artificial Intelligence was used as a pedagogical guide during this project to strengthen foundational learning without taking shortcuts.

* Tasks: AI was utilized to analyze Valgrind logs and debug a critical segmentation fault error (Stack overflow).

* Parts of the project: It helped identify that allocating a large buffer array (e.g., BUFFER_SIZE=10000000) directly on the local function stack would overflow the application's memory limit. AI was used exclusively to validate architectural hypotheses, ensuring that buffer structures were safely transitioned to the Heap while enforcing proper edge-case protections (such as evaluating invalid file descriptors before allocation). No direct code or algorithmic answers were requested or provided by the AI tool.

## Algorithm Selection & Justification
The chosen algorithm relies on structural separation of concerns, orchestrated through a single static pointer serving as a persistent "backup" accumulation string.

Implementation Strategy:
Dynamic Buffer Allocation: To ensure the function handles massive BUFFER_SIZE values without crashing the program, the temporary reading buffer is allocated dynamically on the Heap using malloc(BUFFER_SIZE + 1). This directly prevents the system stack limit (~8 MB) from bursting when tested with extreme macro constraints.

Persistent Accumulation: Because a single read call might pull multiple lines or fragments of subsequent lines into memory, a static variable acts as a persistent cache. The temporary heap buffer reads chunk data, appends it to the static variable, and is immediately freed before line isolation, mitigating dangling pointer leaks.

Extraction & Update: The static string is parsed to find a newline (\n). Everything up to the newline is sliced into a new substring and prepared as the return value. Concurrently, the static variable is updated to hold only the remaining trailing buffer data, ready for the next sequential call.

Leak Mitigation & Edge Cases: Robust error-checking guards the entry point to immediately return NULL if an invalid file descriptor (such as fd < 0) is intercepted, bypassing allocation entirely. If a read error or EOF occurs, custom cleanup routines clear out the static accumulation variable and securely return NULL, fully eliminating memory leaks.