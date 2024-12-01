#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

//test 5 for完全背包
//test 6 for多重背包
//test 7 for完全背包+解析
//test 8 for多重背包+解析
long double test_5(char*, int (fun)(int, int, int*, int*, int*));
long double test_6(char*, int (fun)(int, int, int*, int*, int*, int*));
long double test_7(char*, int (fun)(int, int, int*, int*, int*, int&, int&));
long double test_8(char*, int (fun)(int, int, int*, int*, int*, int*, int&, int&));
