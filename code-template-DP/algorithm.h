#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <string>
#include <cstring>

using namespace std;

//声明函数

//Unbounded Knapsack: equation 1
//Unbounded Knapsack: equation 2
//Unbounded Knapsack + 一维数组
//Bounded Knapsack + 朴素算法
//Bounded Knapsack + 二进制分组
//Bounded Knapsack + 单调队列/单调栈(未实现)

void Init_vector_Unbounded(vector<vector<int> >&, vector<vector<int> >&,int, int, int*, int*);
void Init_vector_Unbounded_1dimearr(vector<int >&, vector<vector<int> >&,int, int, int*, int*);
void Init_vector_Bounded(vector<vector<int> >&, vector<vector<int> >&,int, int, int*, int*, int*);
int Knapsack_Unbounded_1(int, int, int*, int*, int*);
int Knapsack_Unbounded_2(int, int, int*, int*, int*);
int Knapsack_Unbounded_1dimearr(int, int, int*, int*, int*);
int Knapsack_Bounded(int, int, int*, int*, int*, int*);
int Knapsack_Bounded_log2(int, int, int*, int*, int*, int*);

int Knapsack_Unbounded_1_analy(int, int, int*, int*, int*, long long&, long long&);
int Knapsack_Unbounded_2_analy(int, int, int*, int*, int*, long long&, long long&);
int Knapsack_Unbounded_1dimearr_analy(int, int, int*, int*, int*, long long&, long long&);//未实现因为跟Knapsack_Unbounded_2_analy关键操作次数相同
int Knapsack_Bounded_analy(int, int, int*, int*, int*, int*,long long&, long long&);
int Knapsack_Bounded_log2_analy(int, int, int*, int*, int*, int*, long long&, long long&);

