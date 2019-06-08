#ifndef EXTRACT_H
#define EXTRACT_H
#include <iostream> 
#include <regex> 
#include <string>
#include <string.h>
#include "util.h"
using namespace std;

unsigned int strtoint(string str);
string Extract(string &str);
unsigned long long Convert_IP(string &str);
long long Convert_length(string &str);

unsigned long long Get_key(string ex);
void Print_Ip(unsigned long long* ip);
string Print_Heavy_Key(unsigned long long* ip);
void read_flowkey(char* line, tuple_t* p);
void print_tuple(FILE* f, tuple_t* t);
#endif
