#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <string>
#include <cstring>
#include <algorithm>
#include "algorithm.h"

using namespace std;

/**
 * @brief 解决多机调度问题思路一:负载均衡，按照输入任务的顺序，将任务分配给当前负载最轻的机器
 * @param m: 机器数量
 * @param n: 任务数量 
 */
int Muilti_Machine_Schedualing_1(int m, int n, int *task, struct Solution4task *solve){
    // 机器负载
    int *load = new int[m];
    // 初始化机器负载
    for (int i = 0; i < m; i++)
        load[i] = 0;
    // 任务分配
    for (int i = 0; i < n; i++)
    {
        // 机器负载最小值
        int min_load = load[0];
        // 机器负载最小值的索引
        int min_index = 0;
        // 寻找负载最小的机器
        for (int j = 1; j < m; j++)
        {
            if (load[j] < min_load)
            {
                min_load = load[j];
                min_index = j;
            }
        }
        // 任务分配
        solve[i].machine = min_index;
        solve[i].time = load[min_index];
        load[min_index] += task[i];
    }
    // 释放内存
    delete[] load;
    return 0;
}


/**
 * @brief 解决多机调度问题思路二:贪心算法，按照任务的处理时间从大到小排序，将任务分配给当前处理时间最短的机器
 * @param m: 机器数量
 * @param n: 任务数量 
 */
int Muilti_Machine_Schedualing_2(int m, int n, int *task, struct Solution4task *solve){
    // 机器负载
    int *load = new int[m];
    // 初始化机器负载
    for (int i = 0; i < m; i++)
        load[i] = 0;
    // 任务处理时间排序 从大到小
    sort(task, task + n, greater<int>());
    // 任务分配
    for (int i = 0; i < n; i++)
    {
        // 机器负载最小值
        int min_load = load[0];
        // 机器负载最小值的索引
        int min_index = 0;
        // 寻找负载最小的机器
        for (int j = 1; j < m; j++)
        {
            if (load[j] < min_load)
            {
                min_load = load[j];
                min_index = j;
            }
        }
        // 任务分配
        solve[i].machine = min_index;
        solve[i].time = load[min_index];
        load[min_index] += task[i];
    }
    // 释放内存
    delete[] load;
    return 0;
}

