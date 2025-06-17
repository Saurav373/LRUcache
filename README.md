# LRUcache 🚀

A simple implementation of an **LRU (Least Recently Used)** cache using a doubly linked list and hash map to support `get()` and `put()` operations in **O(1)** time complexity.

---

## Features ⭐

- Stores key-value pairs with a fixed capacity.
- When capacity is exceeded, evicts the least recently used item.
- Supports:
  - `get(key)`: Returns the value if the key exists, else returns -1.
  - `add(key, value)`: Adds a key-value pair or updates an existing key and moves it to the front (most recently used).
- Uses a doubly linked list to maintain usage order.
- Uses an unordered_map (hash map) for fast key-to-node access.

---

## How it works 🔧

- The doubly linked list keeps track of the order of usage:
  - Most recently used nodes are near the head.
  - Least recently used nodes are near the tail.
- On `get` or `add` for an existing key, the node is moved to the head.
- When capacity is full and a new key is added, the tail node (least recently used) is removed.

---

## How to Clone 📥

To clone this repository, run:

```bash
git clone https://github.com/Saurav373/LRUcache.git
```

## Compile and Run ▶️
```bash
g++ -std=c++11 -o lru_cache LRUcache.cpp
./lru_cache
```
