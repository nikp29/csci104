# Nikhil Patel, HW2

## Compiling and running

To compile code, simply run:

```bash
make all
```

After code has compiled, run

```bash
./amazon <database filename>
```

## Code organization info

- The datastore uses a `Product*` vector in order to dump products, and deallocate them in the correct order. In order to have a quick search time, the datastore uses a `map<string, set<Product*>*>` so that the program doesnt need to search individually through each Product in the Product vector

- The amazon.cpp file does not verify that ADD, BUYCART, and VIEWCART commands are typed with the correct username or hit number, so there are two spots where errors are declared
