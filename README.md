This C++ project focuses on implementing and performing operations on Fibonacci Heaps, a type of data structure that is particularly useful for various applications, such as graph algorithms. The project encompasses the following components:

Fibonacci Heap Class: The Fibonacci_Heap class is designed to manage Fibonacci Heaps, and it includes the following features:

  1. Creation of a new heap or initializing an empty one.
  2. Insertion of new nodes into the heap.
  3. Extraction of the minimum node from the heap.
  4. Merging two Fibonacci Heaps together.
  5. Decreasing the key of a specific node within the heap.
  6. Cutting and cascading-cut operations to maintain the heap's structure.
  7. Deletion of a node from the heap.
  8. Search and retrieval operations within the heap.
     
Node Structure: The project defines a nod structure to represent nodes within the Fibonacci Heap. Each node contains various attributes, including its value, parent, child, and mark status, among others.

File Input/Output: The project utilizes input and output streams (ifstream and ofstream) to read input data from the "mergeheap.in" file and write the results to the "mergeheap.out" file.

Main Function: The main function serves as the entry point of the program and is responsible for reading and interpreting input data and executing various operations on Fibonacci Heaps based on the provided queries. Supported operations include:

  1. Insertion of nodes into specific heaps.
  2. Extraction of the minimum node from a heap.
  3. Merging two heaps together.
  4. Other queries specified in the input file.

The project allows for the dynamic management of multiple Fibonacci Heaps, each identified by an index. It performs the designated operations on these heaps, as specified by the input data.

Overall, this project is a valuable exercise in implementing and operating on Fibonacci Heaps, a data structure known for its efficiency in various algorithms, including Dijkstra's algorithm and Prim's algorithm. It demonstrates how to create and manipulate these data structures efficiently and serves as a foundation for solving complex graph-related problems.
