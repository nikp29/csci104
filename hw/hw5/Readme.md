# PA5

- For this PA I made a program to classify fruits based off of traits when given an input file with a bunch of fruits and their associated traits. The program has 3 parts. The initial train file parsing part records the number of each type of fruit, the number of fruits with each trait, and for each fruit the number of that kind of fruit with each trait
- the next part then calculates the probabilty of each trait for the given fruit, as well as the probability of that trait in all fruits except the given fruit
- finally the last part classifies fruit given a set of traits by using bayes theorem

* to run, simply type `make` and then `./bayes <train file> <classify file> <output file>`
