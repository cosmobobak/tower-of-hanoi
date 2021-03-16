# tower-of-hanoi
A C++ implementation of an algorithm to solve the Tower of Hanoi problem.
 
 In order to use:
 
 1. Compile with gcc (-std=c++2a -Ofast recommended)
 2. Run the generated file in a terminal.

Example use: 
```
$ git clone https://github.com/cosmobobak/tower-of-hanoi
$ cd tower-of-hanoi
$ g++ -Ofast -std=c++2a hanoi.cpp -o hanoi
$ .\hanoi
How many discs should the Tower of Hanoi have?
--> 1
Would you like the program to print the Tower as it is solved? [Yy/Nn]
--> Y
Trying to solve it in 1 steps!

 |  |  |
*|* |  |

 |  |  |
 |  | *|*
Solved in 1 steps!
Would you like to get a printout of the moves to make in order? [Yy/Nn]
--> Y
1. Move piece from peg A to C.
```

Disc counts in excess of 15 are not recommended.
