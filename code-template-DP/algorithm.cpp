#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <string>
#include <cstring>
#include "algorithm.h"

using namespace std;


/**
 * @func Init_vector_Unbounded
 * @brief 初始化完全背包的vector
 * @param memo: 最大价值
 * @param num: 方案数量
 * @param n: 物品种类
 * @param w: 背包容量限制
 * @param weights: 物品重量数组
 * @param values: 物品价值数组
 *
 * @return 无
 */

void Init_vector_Unbounded(vector<vector<int> >&memo, vector<vector<int> >&nums,int n, int w, int *weights, int *values){
    for (int i = 0; i < n; i++){
        memo[i].resize(w);
        nums[i].resize(w);
    }
    // avoid the inefficient branch for i = 0 in the following ciculation
    for (int j = 0; j < w; j++){ // avaliable weight capacity - 1
        int k = (j + 1) / weights[0];
        memo[0][j] = k * values[0]; // take as many as possible
        nums[0][j] = k;
    }
}
/**
 * @func Init_vector_Unbounded_1dimearr
 * @brief 初始化完全背包的vector_1dimearr
 * @param memo: 最大价值
 * @param num: 方案数量
 * @param n: 物品种类
 * @param w: 背包容量限制
 * @param weights: 物品重量数组
 * @param values: 物品价值数组
 *
 * @return 无
 */

void Init_vector_Unbounded_1dimearr(vector<int>&memo, vector<vector<int> >&nums,int n, int w, int *weights, int *values){
    for (int i = 0; i < n; i++)
        nums[i].resize(w);

    // avoid the inefficient branch for i = 0 in the following ciculation
    for (int j = 0; j < w; j++){ // avaliable weight capacity - 1
        int k = (j + 1) / weights[0];
        memo[j] = k * values[0]; // take as many as possible
        nums[0][j] = k;
    }
}

/**
 * @func Init_vector_Bounded
 * @brief 初始化多重背包的vector
 * @param memo: 最大价值
 * @param num: 方案数量
 * @param n: 物品种类
 * @param w: 背包容量限制
 * @param weights: 物品重量数组
 * @param values: 物品价值数组
 * @param p: 物品数量数组
 *
 * @return 无
 */

void Init_vector_Bounded(vector<vector<int> >&memo, vector<vector<int> >&nums,int n, int w, int *weights, int *values, int *p){
    for (int i = 0; i < n; i++){
        memo[i].resize(w);
        nums[i].resize(w);
    }
    // avoid the inefficient branch for i = 0 in the following ciculation
    for (int j = 0; j < w; j++){ // avaliable weight capacity - 1
        int k = (j + 1) / weights[0];
        if(k > p[0])
            break;
        memo[0][j] = k * values[0]; // take as many as possible
        nums[0][j] = k;
    }
}
/**
 * @func Knapsack_Unbounded_1
 * @brief 解决完全背包问题思路一
 * @param n: 物品种类
 * @param w: 背包容量限制
 * @param weights: 物品重量数组
 * @param values: 物品价值数组
 * @param solve: 保存解的数组
 *
 * @return 返回背包容纳的最大价值
 */

int Knapsack_Unbounded_1(int n, int w, int *weights, int *values, int *solve)
{
    // memo index start from 0, which means type-1 or weight-1
    vector< vector<int> > memo(n);
    vector< vector<int> > nums(n);
    // initialize the vector memo and nums
    Init_vector_Unbounded(memo, nums, n, w, weights, values);

    for (int i = 1; i < n; i++){ // index of chosen object
    
        for (int j = 0; j < w; j++){ // avaliable weight capacity - 1
        
            int maxvalue = 0, maxk = 0;
            for (int k = 0; k <= (j + 1) / weights[i]; k++){
                int tmp = k * values[i];
                if (j - k * weights[i] >= 0){
                    tmp += memo[i - 1][j - k * weights[i]];
                    if (tmp > maxvalue){
                        maxvalue = tmp;
                        maxk = k;
                    }
                }
            }
            memo[i][j] = maxvalue;
            nums[i][j] = maxk;
        }
    }
    int tmpw = w - 1;
    for (int i = n - 1; i >= 0; i--){
        solve[i] = nums[i][tmpw];
        tmpw -= solve[i] * weights[i];

    }
    return memo[n - 1][w - 1];
}


/**
 * @func Knapsack_Unbounded_2
 * @brief 解决完全背包问题思路二（改进递推方程）
 * @param n: 物品种类
 * @param w: 背包容量限制
 * @param weights: 物品重量数组
 * @param values: 物品价值数组
 * @param solve: 保存解的数组
 * 
 * @return 返回说明
 */
int Knapsack_Unbounded_2(int n, int w, int* weights, int* values, int* solve)
{
    // memo index start from 0, which means type-1 or weight-1
    vector< vector<int> > memo(n);
    vector< vector<int> > nums(n);
    Init_vector_Unbounded(memo, nums, n, w, weights, values);
    for (int i = 1; i < n; i++){ // index of chosen object
    
        for (int j = 0; j < w; j++){ // avaliable weight capacity - 1
        
            int maxvalue = memo[i - 1][j], maxk = 0;
            int tmp = values[i];
            if (j - weights[i] >= 0){
                tmp += memo[i][j - weights[i]];
                if (tmp > maxvalue){
                    maxvalue = tmp;
                    maxk = nums[i][j - weights[i]] + 1;
                }
            }
            
            memo[i][j] = maxvalue;
            nums[i][j] = maxk;
        }
    }
    int tmpw = w - 1;
    for (int i = n - 1; i >= 0; i--){
        solve[i] = nums[i][tmpw];
        tmpw -= solve[i] * weights[i];
    }
    return memo[n - 1][w - 1];
}
/**
 * @func Knapsack_Unbounded_1dimearr
 * @brief 解决完全背包问题思路三（一维数组）
 * @param n: 物品种类
 * @param w: 背包容量限制
 * @param weights: 物品重量数组
 * @param values: 物品价值数组
 * @param solve: 保存解的数组
 * 
 * @return 返回说明
 */
int Knapsack_Unbounded_1dimearr(int n, int w, int* weights, int* values, int* solve)
{
    // memo index start from 0, which means type-1 or weight-1
    vector< int > memo(w);
    vector< vector<int> > nums(n);
    Init_vector_Unbounded_1dimearr(memo, nums, n, w, weights, values);
    for (int i = 1; i < n; i++){ // index of chosen object
    
        for (int j = 0; j < w; j++){ // avaliable weight capacity - 1
        
            int maxvalue = memo[j], maxk = 0;
            int tmp = values[i];
            if (j - weights[i] >= 0){
                tmp += memo[j - weights[i]];
                if (tmp > maxvalue){
                    maxvalue = tmp;
                    maxk = nums[i][j - weights[i]] + 1;
                }
            }
            
            memo[j] = maxvalue;
            nums[i][j] = maxk;
        }
    }
    int tmpw = w - 1;
    for (int i = n - 1; i >= 0; i--){
        solve[i] = nums[i][tmpw];
        tmpw -= solve[i] * weights[i];
    }
    return memo[w - 1];
}

/**
 * @func Knapsack_Bounded_01
 * @brief 解决多重背包问题（朴素算法）
 * @param n: 物品种类
 * @param w: 背包容量限制
 * @param weights: 物品重量数组
 * @param values: 物品价值数组
 * @param p: 物品数量数组
 * @param solve: 保存解的数组
 * 
 * @return 返回说明
 */

int Knapsack_Bounded(int n, int w, int* weights, int* values, int* p, int* solve)
{
    // memo index start from 0, which means type-1 or weight-1
    vector< vector<int> > memo(n);
    vector< vector<int> > nums(n);
    // initialize the vector memo and nums
    Init_vector_Bounded(memo, nums, n, w, weights, values, p);

    for (int i = 1; i < n; i++){ // index of chosen object
    
        for (int j = 0; j < w; j++){ // avaliable weight capacity - 1
        
            int maxvalue = memo[i - 1][j], maxk = 0;
            // take 0 to p[i] items                      here
            for (int k = 1; k <= (j + 1) / weights[i] && k <= p[i]; k++){
                int tmp = k * values[i];
                if (j - k * weights[i] >= 0){
                    tmp += memo[i][j - k * weights[i]];
                    if (tmp > maxvalue){
                        maxvalue = tmp;
                        maxk = nums[i][j - k * weights[i]]+ k;
                    }
                }
            }
            memo[i][j] = maxvalue;
            nums[i][j] = maxk;
        }
    }
    int tmpw = w - 1;
    for (int i = n - 1; i >= 0; i--){
        solve[i] = nums[i][tmpw];
        tmpw -= solve[i] * weights[i];
    }
    return memo[n - 1][w - 1];
};

/**
 * @func Knapsack_Bounded_log2
 * @brief 解决多重背包问题（二进制分组）
 * @param n: 物品种类
 * @param w: 背包容量限制
 * @param weights: 物品重量数组
 * @param values: 物品价值数组
 * @param p: 物品数量数组
 * @param solve: 保存解的数组
 * 
 * @return 返回说明
 */
int Knapsack_Bounded_log2(int n, int w, int* weights, int* values, int* p, int* solve){
    // memo index start from 0, which means type-1 or weight-1
    vector< vector<int> > memo(n);
    vector< vector<int> > nums(n);
    // initialize the vector memo and nums
    Init_vector_Bounded(memo, nums, n, w, weights, values, p);

    for (int i = 1; i < n; i++){ // index of chosen object
    
        for (int j = 0; j < w; j++){ // avaliable weight capacity - 1
        
            int maxvalue = memo[i -1][j], maxk = 0;
            int tmp, k;
            for (k = 1; k <= (j + 1) / weights[i] && k <= p[i]; k *= 2){

                tmp = k * values[i];
                if (j - k * weights[i] >= 0){
                    tmp += memo[i][j - k * weights[i]];
                    if (tmp > maxvalue){
                        maxvalue = tmp;
                        maxk = nums[i][j - k * weights[i]] + k;
                    }
                }
                
            }
            if(k <= p[i]){
                tmp = (p[i] - k) * values[i];
                if (j - (p[i] - k) * weights[i] >= 0){
                    tmp += memo[i][j - (p[i] - k) * weights[i]];
                    if (tmp > maxvalue){
                        maxvalue = tmp;
                        maxk = nums[i][j - (p[i] - k) * weights[i]] + (p[i] - k);
                    }
                }
            }
            memo[i][j] = maxvalue;
            nums[i][j] = maxk;
        }
    }
    int tmpw = w - 1;
    for (int i = n - 1; i >= 0; i--){
        solve[i] = nums[i][tmpw];
        tmpw -= solve[i] * weights[i];
    }
    return memo[n - 1][w - 1];
}



/**
 * @func Knapsack_Unbounded_1_analy
 * @brief 在函数Knapsack_Unbounded_1的基础上进行插桩，记录关键操作次数
 * @param n: 物品种类
 * @param w: 背包容量限制
 * @param weights: 物品重量数组
 * @param values: 物品价值数组
 * @param solve: 保存解的数组
 * @param calc_count: 记录计算次数
 * @param search_count: 记录查找次数
 *
 * @return 返回背包容纳的最大价值
 */
int Knapsack_Unbounded_1_analy(int n, int w, int* weights, int* values, int* solve, long long& calc_count, long long& search_count)
{
    // memo index start from 0, which means type-1 or weight-1
    vector< vector<int> > memo(n);
    vector< vector<int> > nums(n);
    // initialize the vector memo and nums
    Init_vector_Unbounded(memo, nums, n, w, weights, values);

    for (int i = 1; i < n; i++){ // index of chosen object
    
        for (int j = 0; j < w; j++){ // avaliable weight capacity - 1
        
            int maxvalue = 0, maxk = 0;
            for (int k = 0; k <= (j + 1) / weights[i]; k++){
                int tmp = k * values[i];
                search_count++;
                calc_count++;
                if (j - k * weights[i] >= 0){
                    tmp += memo[i - 1][j - k * weights[i]];
                    calc_count++;
                    if (tmp > maxvalue){
                        maxvalue = tmp;
                        maxk = k;
                    }
                }
            }
            memo[i][j] = maxvalue;
            nums[i][j] = maxk;
        }
    }
    int tmpw = w - 1;
    for (int i = n - 1; i >= 0; i--){
        solve[i] = nums[i][tmpw];
        tmpw -= solve[i] * weights[i];
    }
    return memo[n - 1][w - 1];
}

/**
 * @func Knapsack_Unbounded_2_analy
 * @brief 在函数Knapsack_Unbounded_2的基础上进行插桩，记录关键操作次数
 * @param n: 物品种类
 * @param w: 背包容量限制
 * @param weights: 物品重量数组
 * @param values: 物品价值数组
 * @param solve: 保存解的数组
 * @param calc_count: 记录计算次数
 * @param search_count: 记录查找次数
 *
 * @return 返回背包容纳的最大价值
 */
int Knapsack_Unbounded_2_analy(int n, int w, int* weights, int* values, int* solve, long long& calc_count, long long& search_count)
{
    // memo index start from 0, which means type-1 or weight-1
    vector< vector<int> > memo(n);
    vector< vector<int> > nums(n);
    Init_vector_Unbounded(memo, nums, n, w, weights, values);
    for (int i = 1; i < n; i++){ // index of chosen object
    
        for (int j = 0; j < w; j++){ // avaliable weight capacity - 1
        
            int maxvalue = memo[i - 1][j], maxk = 0;
            int tmp = values[i];
            search_count+=2;
            calc_count++;
            //因为查了两次memo[i-1][j]和memo[i][j-weights[i]]
            if (j - weights[i] >= 0){
                tmp += memo[i][j - weights[i]];
                calc_count++;
                if (tmp > maxvalue){
                    maxvalue = tmp;
                    maxk = nums[i][j - weights[i]] + 1;
                }
            }
            
            memo[i][j] = maxvalue;
            nums[i][j] = maxk;
        }
    }
    int tmpw = w - 1;
    for (int i = n - 1; i >= 0; i--){
        solve[i] = nums[i][tmpw];
        tmpw -= solve[i] * weights[i];
    }
    return memo[n - 1][w - 1];
}

/**
 * @func Knapsack_Bounded_analy
 * @brief 在函数Knapsack_Bounded的基础上进行插桩，记录关键操作次数
 * @param n: 物品种类
 * @param w: 背包容量限制
 * @param weights: 物品重量数组
 * @param values: 物品价值数组
 * @param p: 物品数量数组
 * @param solve: 保存解的数组
 * @param calc_count: 记录计算次数
 * @param search_count: 记录查找次数
 *
 * @return 返回背包容纳的最大价值
 */
int Knapsack_Bounded_analy(int n, int w, int* weights, int* values, int* p, int* solve,long long& calc_count, long long& search_count)
{
    // memo index start from 0, which means type-1 or weight-1
    vector< vector<int> > memo(n);
    vector< vector<int> > nums(n);
    // initialize the vector memo and nums
    Init_vector_Bounded(memo, nums, n, w, weights, values, p);

    for (int i = 1; i < n; i++){ // index of chosen object
    
        for (int j = 0; j < w; j++){ // avaliable weight capacity - 1
        
            int maxvalue = memo[i - 1][j], maxk = 0;
            search_count++;
            for (int k = 1; k <= (j + 1) / weights[i] && k <= p[i]; k++){
                int tmp = k * values[i];
                search_count++;
                calc_count++;
                if (j - k * weights[i] >= 0){
                    tmp += memo[i][j - k * weights[i]];
                    calc_count++;
                    if (tmp > maxvalue){
                        maxvalue = tmp;
                        maxk = nums[i][j - k * weights[i]] + k;
                    }
                }
                
            }
            memo[i][j] = maxvalue;
            nums[i][j] = maxk;
        }
    }
    int tmpw = w - 1;
    for (int i = n - 1; i >= 0; i--){
        solve[i] = nums[i][tmpw];
        tmpw -= solve[i] * weights[i];
    }
    return memo[n - 1][w - 1];
}

/**
 * @func Knapsack_Bounded_log2_analy
 * @brief 在函数Knapsack_Bounded_log2的基础上进行插桩，记录关键操作次数
 * @param n: 物品种类
 * @param w: 背包容量限制
 * @param weights: 物品重量数组
 * @param values: 物品价值数组
 * @param p: 物品数量数组
 * @param solve: 保存解的数组
 * @param calc_count: 记录计算次数
 * @param search_count: 记录查找次数
 *
 * @return 返回背包容纳的最大价值
 */

int Knapsack_Bounded_log2_analy(int n, int w, int* weights, int* values, int* p, int* solve, long long& calc_count, long long& search_count)
{
    // memo index start from 0, which means type-1 or weight-1
    vector< vector<int> > memo(n);
    vector< vector<int> > nums(n);
    // initialize the vector memo and nums
    Init_vector_Bounded(memo, nums, n, w, weights, values, p);

    for (int i = 1; i < n; i++){ // index of chosen object
    
        for (int j = 0; j < w; j++){ // avaliable weight capacity - 1
        
            int maxvalue = memo[i -1][j], maxk = 0;
            int tmp, k;
            search_count++;
            for (k = 1; k <= (j + 1) / weights[i] && k <= p[i]; k *= 2){
                tmp = k * values[i];
                search_count++;
                calc_count++;
                if (j - k * weights[i] >= 0){
                    tmp += memo[i][j - k * weights[i]];
                    calc_count++;
                    if (tmp > maxvalue){
                        maxvalue = tmp;
                        maxk = nums[i][j - k * weights[i]] + k;
                    }
                }
                
            }
            if(k <= p[i]){
                tmp = (p[i] - k) * values[i];
                search_count++;
                calc_count++;
                if (j - (p[i] - k) * weights[i] >= 0){
                    tmp += memo[i][j - (p[i] - k) * weights[i]];
                    calc_count++;
                    if (tmp > maxvalue){
                        maxvalue = tmp;
                        maxk = nums[i][j - (p[i] - k) * weights[i]] + (p[i] - k);
                    }
                }
            }
            memo[i][j] = maxvalue;
            nums[i][j] = maxk;
        }
    }
    int tmpw = w - 1;
    for (int i = n - 1; i >= 0; i--){
        solve[i] = nums[i][tmpw];
        tmpw -= solve[i] * weights[i];
    }
    return memo[n - 1][w - 1];
}