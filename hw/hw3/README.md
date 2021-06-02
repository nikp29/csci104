# PA3 Nikhil Patel

## Part 1: Backtracking Map coloring

- In this program I take a map file and find a way to color countries on a map with only 4 colors using backtracking
- My approach was: have a dictionary where I store each country's assigned color. iterate through each cell in the map and see if its country has a color assigned to it. If not then iterate through all possible colors 1-4 and make recursive calls to see which works
- In cells where if the cell has a valid color then the continue to the next cell, otherwise return false

## Part 2: d-ary heap

- This is a very simple d-ary implementation of a heap. The only difference between this and a binary heap is the parent and child id formulas, otherwise it was basically the same.
