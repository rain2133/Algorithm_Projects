#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <string>
#include <cstring>
#include <fstream>
#include "algorithm.h"
#include "test.h"

using namespace std;


/**
 * @func PrintArray
 * @brief 输出指针数组
 * @param n: 数组长度
 * @param nums: 整型指针数组
 *
 * @return null
 */
void PrintArray(int n, int* nums)
{
    for (int i = 0; i < n; i++)
    {
        cout << nums[i] << " ";
    }
    cout << endl;
}

/**
 * @func PrintStruct
 * @brief 输出结构体数组
 * @param n: 数组长度
 * @param solution: 结构体指针数组
 *
 * @return null
 */
void PrintStruct(int n,struct Solution4task *solution)
{
    for (int i = 0; i < n; i++)
    {
        cout << "(" << solution[i].machine << "," << solution[i].time << ") ";
    }
    cout << endl;
}
/**
 * @func test
 * @brief 测试算法运行时间并输出每组测试用例的结果
 * @param data_file: 测试数据集文件
 * @param fun: 测试算法的实现函数
 *
 * @return 算法的平均运行时间
 */

long double test(char* data_file, int (fun)(int, int, int*, struct Solution4task*)){
    
    double sum_time = 0;
    clock_t start_time, end_time;

    ifstream fin(data_file);

    int result; //保存每个测试用例的m最短时间
    int repeat; //记录测试数据组数
    // k: 生成数据的组数
    // m: 机器数量
    // n: 任务数量
    int k, m, n;
    fin >> k >> m >> n;
    repeat = k;
    cout << "数据集组数：" << k << " , 机器数量：" << m << " , 任务数量： " << n << endl;
    int* task = new int[n];
    Solution4task* solve = new Solution4task[n];
    while (k--) {
        for (int i = 0; i < n; i++) {
            fin >> task[i];
            solve[i] = {0,0};
        }
        cout << "task time:" << endl;
        PrintArray(n, task);
        // 仅记录算法运行时间
        start_time = clock();
        result = fun(m, n, task, solve);
        end_time = clock();

        sum_time += (double)(end_time - start_time) / CLOCKS_PER_SEC;
        cout << "max value is " << result << endl;
        cout << "the solution is "; 
        PrintStruct(n, solve);
    }
    delete[] task;
    delete[] solve;
    long double average_time = sum_time / repeat;
    return average_time;

}