# 5 live-coding C interview tasks 
**commonly used**, **practical**, and **scale well in difficulty**. Each one tests something different (pointers, memory, strings, bitwise ops, APIs). No tricks — just real C.

---

## **Task 1 — Reverse a string in place**

**Skills tested:** pointers, strings, memory safety

### Problem

Write a function that reverses a **null-terminated string in place**.

### Function signature

```c
void reverse_string(char *str);
```

### Example

```
Input:  "hello"
Output: "olleh"
```

### Constraints

* No extra buffers
* Must handle empty string and `NULL`

---

## **Task 2 — Find the first non-repeating character**

**Skills tested:** arrays, ASCII, logic

### Problem

Return the first character in a string that does **not repeat**.
Return `'\0'` if none exists.

### Function signature

```c
char first_unique_char(const char *str);
```

### Example

```
Input:  "swiss"
Output: 'w'
```

---

## **Task 3 — Implement `strdup`**

**Skills tested:** heap memory, ownership, API design

### Problem

Implement your own version of `strdup`.

### Function signature

```c
char *my_strdup(const char *src);
```

### Requirements

* Allocate memory dynamically
* Caller must be able to `free()` it
* Return `NULL` on allocation failure

---

## **Task 4 — Check if a number is power of two**

**Skills tested:** bitwise operations, edge cases

### Problem

Return `1` if `n` is a power of two, otherwise `0`.

### Function signature

```c
int is_power_of_two(unsigned int n);
```

### Examples

```
1  → true
2  → true
3  → false
16 → true
0  → false
```

---

## **Task 5 — Remove duplicates from sorted array (in place)**

**Skills tested:** pointers, arrays, in-place algorithms

### Problem

Given a **sorted** integer array, remove duplicates **in place**.
Return the new logical length.

### Function signature

```c
size_t remove_duplicates(int *arr, size_t len);
```

### Example

```
Input:  [1,1,2,2,3,4,4]
Output: [1,2,3,4], return 4
```
