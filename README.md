# Final project of Algorithms and Data Structures
This project has been realized for the 'Algoritmi e Principi dell'Informatica' course at Politecnico di Milano.

## Goal
The project aims to manage a direct weighted graph ranking by keeping track of the k "best" graphs given as input.

## Input structure
We firstly provide two different parameters:
- d, which is the maximum number of nodes in a graph;
- k, which is the maximum length of the standings.

(Those parameters are provided just at the beginning of the input, separeted by a space)
Then, a sequence of commands is inserted:
- AggiungiGrafo, which reports to the program to add a new graph and requires the provisioning of an adjacency matrix;
- TopK, that prints in the stdout the top best graph so far.

### AggiungiGrafo
---
It requires to the program to consider a new graph among the ones used during the ranking process. It is followed by an adjacency matrix (the matrix elements are separeted by commas). 
The graph's nodes are to be considered logically labeled with an index integer between 0 and d-1. The edges coming out of the node with label 0 are described by the first row of the matrix. Moreover, the edge wieghts are integers in the interval [0, 2<sup>32</sup>].

### TopK
---
Considering all the inserted graph from the start of the program until the TopK command has been called (numbered starting from 0), TopK requires to print the index of the k graphs with the smallest sum over the values of the paths connecting node 0 to all the other reachable nodes. If we have multiple graphs with the same metric, we will insert in a higher position the graph that arrived first.

### Input example
---
```
3,2
AggiungiGrafo
0,4,3
0,2,0
2,0,0
AggiungiGrafo
0,0,2
7,0,4
0,1,0
AggiungiGrafo
3,1,8
0,0,5
0,9,0
TopK
```

## How to run the code
To obtain the executable of the program perform the following commands:
```
cd src/
make
```
To run the program, given the executable and an input file structured as previously discussed, we perform the following command:
```
./main < inputfile
```

To obtain same input test cases perform the following commands:
```
cd src/
make test_gen
```

To obtain same input test cases and the associated results perform the following commands:
```
cd src/
make test
```
