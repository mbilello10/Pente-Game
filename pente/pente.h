#pragma once
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <cctype>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
//Note: no "using namespace std" here!

//Constants used throughout the program
const int  SIZE  = 19; //For testing, you might want to shrink this temporarily
const char WHITE = 'W';
const char BLACK = 'B';
const char OPEN  = '.';

//Used for all the code that goes in 4 directions
const std::vector<std::pair<int,int>> moves4 = {{0,1},{1,0},{1,1},{1,-1}};
//Used for all the code that goes in 8 directions
const std::vector<std::pair<int,int>> moves8 = {{0,1},{1,0},{1,1},{1,-1},{0,-1},{-1,0},{-1,-1},{-1,1}};

//Uppercases a string
void uppercaseify(std::string &);

//Quits the program with an error message
void die(const std::string &);

