# HW6: Hashtables

## Part 1:

- For this part I created a hashtable class (`Hashtable.h` and `Hashtable.cpp` files)
- I followed the instructions for the assignment pretty much to the letter so there isn't really a need for further explanation

## Part 2:

- For this part we were tasked with creating `counting.cpp`, which creates a HashTable/AVL Tree, and populates it with the contents of the input text file
- the program records how long it takes to input the words from the text file into the specified data strucutre
- the user can specify which data structure, what type of probing to use, and whether to use the hashtable in debug mode
- to use, run `make` or `make counting` and run the executable with this structure `./counting [input] [output] x d r n`
- `[input]` will be an input text file, which you will run your program on.
  - `[output]` will be an output text file, which you will store your results in.
  - `x` will be an integer with value 0, 1, 2, or 3. If x=0, use linear probing. If x=1, use quadratic probing. If x=2, use double-hashing. If x=3, use your AVL Tree from HW4 (if your AVL Tree isn’t working, use the STL map, but that’s much less interesting).
  - `d` will be an integer with value 0 or 1. If d=0, then create a normal HashTable. If d=1, then create a debug-mode HashTable. This value is ignored by your program if x=3. `r` will be an integer that says how often to repeat the whole program. (This is useful to measure the time when the input is small and the time is otherwise reported as 0.)
  - `n` is an optional parameter that will limited the number of words placed in the vector from the input file to n words
- the program stops timing before the contents of the hashtable or AVL tree are output to the output file

### Results

- The results of running the program with various input parameters can be found in `timingResults.csv`, and a graph can be found in `resultgraph.png`
- For each probing mode, with both debug mode enabled and disabled, I ran the program with input sizes of 10, 100, 1000, and 1000 words, and 1000 repetitions.
- My findings were that comparing across different probing modes and debug and not debug, Hashtable runtimes were all about the same. This is probably because the probing function to find the next index takes constant time, and regardless of whether my hash table was in double hashing mode, I always created the second hash just to make the code look more elegant (I asked a TA about this in office hours and he said it was fine). As the number of words inserted into the hash table increased, the time to insert all words scaled roughly linearly
- quadratic probing was the slowest, with linear probing following a close second, and double hashing being the most efficient hashtable probing method
- Accross different input sizes the AVL tree also scaled roughly linearly, especially for input sizes > 100
- the AVL tree was also significantly faster than the Hashtable. As the number of inserted words became >= 100 words, the AVL tree times were essentially the Hashtable times multiplied by a constant. While at first I was surprised by this, it actually makes a lot of sense, since inserting n words takes O(nlogn), and as n increases log(n) increases at such a low rate that it is almost constant. This means that the runtime as n becomes really large becomes essentially O(n). Thus, the insert times for both Hashtables and AVL trees would essentially be O(n), and hash tables probably take a while to generate their hashes and find the correct insert bucket which would explain the linearly scaled difference in insert times between Hashtables and AVL trees where AVL trees are faster
