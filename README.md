# LD-Sketch

----
### Introduction
A sketching structure which can be seamlessly deployed in a distributed architecture.

----
### Paper

__Qun Huang, Patrick, P. C. Lee__  
LD-Sketch: A Distributed Sketching Design for Accurate and Scalable Anomaly Detection in Network Data Streams.  
_INFOCOM 2014_ (AR: 320/1645=19.4%).

----
### Contributor

*   [Qun Huang](https://huangqundl.github.io/)

---
I meet with some problem when runing the LD-SKetch:
1. It didn't enable the C++11 supporting option in the Makefile.
2. When using the operations of the unordered_map pointer, the execution will show errors after compiling successfully.
  Runing in linux: Float exception(core dump)
  Runing in Windows Visual Studio 2017: The vector subscript out of range.
  
1.To solve the above mentioned:

Edit MakeFile，find the line:

```
g++ -o test test.cpp
```
enable -std=c++11  option:

```
g++ -std=c++11 -o test test.cpp
```
2. Find the function "dyn_tbl_init()" in "dyn_tbl.cpp":
the first line:

```
dyn_tbl_t* ret = (dyn_tbl_t*)calloc(1, sizeof(dyn_tbl_t));
```
change into

```
dyn_tbl_t* ret = new dyn_tbl_t;
```
the "calloc()" function  may be unfixed with unordered_map().
