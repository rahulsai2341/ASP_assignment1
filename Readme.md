This repository contains three codes - Mapper.c, Reducer.c and Combiner.c.

* Mapper takes tuples of the form (1111,P,history) and processes them to get (1111,history,50) based on a scoring scheme (P=50, L=20, D=-10, C=30, S=40). Each tuple is printed in a new line into STDOUT.

* Reducer reads tuples from STDIN and adds the score of a used for each subject.

* Combiner uses system calls such as pipe, dup2, fork and exec to combine Mapper and Reducer.

## Instructions:
* Navigate to the folder
* Run "make"
* To execute mapper, run "./mapper input.txt"
* To execute reducer, run "./reducer" and input tuples in STDIN
* To execute combiner, run "./combiner input.txt"

## Details:  
Sai Rahul Kasula  
sairahulkasula@ufl.edu  
4561-7441  
