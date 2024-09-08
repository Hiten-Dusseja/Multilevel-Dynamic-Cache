# Multilevel Caching System
# Overview
This project implements a dynamic multilevel caching system that supports two types of eviction policies:

LRU (Least Recently Used)
LFU (Least Frequently Used)
The system allows users to create multiple levels of caches, where each level may follow either the LRU or LFU eviction policy. The goal of this project is to manage cache storage efficiently by promoting or evicting cache entries between different levels based on access patterns.

Classes
1. Cache (Base Class)
This is the base class for the cache levels, which provides a common interface for the LRU and LFU caches. It holds common attributes such as capacity (the total capacity of the cache) and data (the actual cache storage in the form of an unordered map).

Key Functions:

getcurrcapacity(): Returns the current number of items in the cache.
gettotalcapacity(): Returns the total capacity of the cache.
put(key, value): Adds a new entry to the cache and evicts the least used/least recently used item if necessary.
get(key): Retrieves the value associated with the key, or returns an empty string if the key does not exist.
show(): Displays the contents of the cache.
2. LRU (Derived Class)
This class inherits from Cache and implements the Least Recently Used (LRU) eviction policy. A deque (dqforlru) is used to maintain the order of the keys, where the front of the deque represents the least recently used item and the back represents the most recently used item.

Key Operations:

Get: On every access, the key is removed from its current position in the deque and moved to the back to mark it as recently used.
Put: If the cache is full, the least recently used key (at the front of the deque) is removed to make room for the new key.
3. LFU (Derived Class)
This class inherits from Cache and implements the Least Frequently Used (LFU) eviction policy. A priority queue (pqforlfu) is used to maintain the keys along with their frequency of access, where the key with the least access count is at the top of the queue.

Key Operations:

Get: On every access, the frequency of the key is incremented, and it is repositioned in the priority queue accordingly.
Put: If the cache is full, the least frequently used key (at the top of the priority queue) is removed to make room for the new key.
Workflow
Adding a Cache Level
Users can add a new cache level with a specified capacity and eviction policy (either LRU or LFU).
The newly added cache level is appended to the ListOfCache.
Getting a Value from Cache
The system checks each cache level sequentially for the key, starting from the first level (L1).
If the key is found, it is promoted to the higher level (L1) for faster access in the future.
If the cache level (L1) becomes full after promotion, the least recently/frequently used item is evicted to the next cache level (L2), and the process continues down the levels.
Putting a Value into Cache
A new key-value pair is inserted into the first cache level (L1). If L1 is full, the least recently/frequently used item is evicted to the next cache level (L2), and this process continues down the chain of cache levels.
Removing a Cache Level
Users can remove any cache level by specifying its index. The cache object is deleted, and the cache level is removed from the ListOfCache.
Displaying Cache Contents
The contents of all cache levels are displayed sequentially, with each level's data shown independently.

# Example
Adding Cache Levels:

Add an LRU cache with capacity 2 as Level 1.
Add an LFU cache with capacity 2 as Level 2.
Putting Values:

Put a key-value pair in Level 1 (e.g., "1"->"100").
If Level 1 is full, the least recently used entry is evicted and moved to Level 2.
Getting Values:

If you request a key from any cache level and it's found in Level 2, it is promoted to Level 1, and the least recently used entry in Level 1 is pushed to Level 2.
Removing a Cache Level:

Remove a cache level by specifying its index.
Displaying Cache:

Display the contents of all the cache levels with their current data.

# Usage
Add a cache level by specifying the capacity and eviction policy (LRU/LFU).
Use put to store key-value pairs.
Use get to retrieve values and automatically promote entries if necessary.
Remove cache levels if no longer needed.
Display all cache levels to view their contents.
Conclusion
This caching system provides a flexible way to manage multiple levels of cache using different eviction strategies (LRU and LFU). This setup is useful in optimizing cache efficiency and performance based on usage patterns.
