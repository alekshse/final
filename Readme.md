- make for build   
- make run for build & run

compiled well om macos

```bash
➜  DB make run
g++ -g -std=c++11   -c -o main.o main.cpp
g++ -g -std=c++11   -c -o record.o record.cpp
g++ -g -std=c++11   -c -o register.o register.cpp
g++ -g -std=c++11 -o DB.out main.o record.o register.o
./DB.out


Employee database
=================
(L) Load a file
(C) Clear a dataset
(N) Print number of records in a dataset
(P) Print all records
(E) Print an employee by their name
(A) Print all employees with an age in a given range
(D) Print employees distributed by departments
(S) Print all subordinates of a given employee
(W) Print employees working on given days
(X) Exit
Choose an action: X
=================
Exiting...
=================
```