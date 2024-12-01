#include <iostream>
#include <fstream>
#include <random>
#include <cmath>
#include "algorithm.h"
#include "test.h"

using namespace std;

/**
 * @func analy_fun_ub
 * @brief 插桩算法测试for unbounded knapsack
 * @param data_file: 测试集文件
 * @param cntcalc: 计算计数器
 * @param cntsearch: 查找计数器
 * @param fun: 测试的算法函数
 *
 * @return 重复测试的次数（测试数据的组数）
 */
int analy_fun_ub(char *data_file, long long &cntcalc, long long &cntsearch, int (fun)(int, int, int*, int*, int*, long long&, long long&))
{
    ifstream fin(data_file);

    int result; //保存每个测试用例的最大价值
    int repeat; //记录测试数据组数

    // k: 生成数据的组数
    // n: 物品的种类（问题的规模）
    // w: 背包重量限制
    int k, n, w;
    fin >> k >> n >> w;
    repeat = k;
    cout << "数据集组数：" << k << " , 物品种类：" << n << " , 背包容量限制： " << w << endl;
    int* weights = new int[n], * values = new int[n], * p = new int[n];
    int* solve = new int[n];
    while (k--) {
        for (int i = 0; i < n; i++) {
            fin >> weights[i];
        }
        for (int i = 0; i < n; i++) {
            fin >> values[i];
        }
        for (int i = 0; i < n; i++) {
            fin >> p[i];
            solve[i] = 0;
        }

        result = fun(n, w, weights, values, solve, cntcalc, cntsearch);

    }

    delete[] weights;
    delete[] values;
    delete[] solve;

    return repeat;
}


/**
 * @func analy_fun_b
 * @brief 插桩算法测试for bounded knapsack
 * @param data_file: 测试集文件
 * @param cntcalc: 计算计数器
 * @param cntsearch: 查找计数器
 * @param fun: 测试的算法函数
 *
 * @return 重复测试的次数（测试数据的组数）
 */
int analy_fun_b(char *data_file, long long &cntcalc, long long &cntsearch, int (fun)(int, int, int*, int *,int*, int*, long long&, long long&))
{
    ifstream fin(data_file);

    int result; //保存每个测试用例的最大价值
    int repeat; //记录测试数据组数

    // k: 生成数据的组数
    // n: 物品的种类（问题的规模）
    // w: 背包重量限制
    int k, n, w;
    fin >> k >> n >> w;
    repeat = k;
    cout << "数据集组数：" << k << " , 物品种类：" << n << " , 背包容量限制： " << w << endl;
    int* weights = new int[n], * values = new int[n], * p = new int[n];
    int* solve = new int[n];
    while (k--) {
        for (int i = 0; i < n; i++) {
            fin >> weights[i];
        }
        for (int i = 0; i < n; i++) {
            fin >> values[i];
        }
        for (int i = 0; i < n; i++) {
            fin >> p[i];
            solve[i] = 0;
        }

        result = fun(n, w, weights, values, p, solve, cntcalc, cntsearch);

    }

    delete[] weights;
    delete[] values;
    delete[] solve;

    return repeat;
}

int main(int argc, char *argv[])
{
    //input: data_file
    if (argc != 2)
    {
        cout<< "参数错误，参数：数据集文件，如test_x_x_x.data" << endl;
        exit(1);
    }
    long long cntcalc1 = 0, cntcalc2 = 0, cntcalc3 = 0, cntcalc4 = 0;
    long long cntsearch1 = 0, cntsearch2 = 0, cntsearch3 = 0, cntsearch4 = 0;
    int average_calc1 = 0, average_calc2 = 0, average_calc3 = 0, average_calc4 = 0;
    int average_search1 = 0, average_search2 = 0, average_search3 = 0, average_search4 = 0;
    int repeat1, repeat2, repeat3, repeat4;

    repeat1 = analy_fun_ub(argv[1], cntcalc1, cntsearch1, Knapsack_Unbounded_1_analy);
    average_calc1 = cntcalc1 / repeat1;
    average_search1 = cntsearch1 / repeat1;
    cout << "average_calc: " << average_calc1 << endl;
    cout <<  "average_search: " << average_search1 << endl;

    repeat2 = analy_fun_ub(argv[1], cntcalc2, cntsearch2, Knapsack_Unbounded_2_analy);
    average_calc2 = cntcalc2 / repeat2;
    average_search2 = cntsearch2 / repeat2;
    cout << "average_calc: " << average_calc2 << endl;
    cout <<  "average_search: " << average_search2 << endl;

    
    repeat3 = analy_fun_b(argv[1], cntcalc3, cntsearch3, Knapsack_Bounded_analy);
    average_calc3 = cntcalc3 / repeat3;
    average_search3 = cntsearch3 / repeat3;
    cout << "average_calc: " << average_calc3 << endl;
    cout <<  "average_search: " << average_search3 << endl;

    repeat4 = analy_fun_b(argv[1], cntcalc4, cntsearch4, Knapsack_Bounded_log2_analy);
    average_calc4 = cntcalc4 / repeat4;
    average_search4 = cntsearch4 / repeat4;
    cout << "average_calc: " << average_calc4 << endl;
    cout <<  "average_search: " << average_search4 << endl;


    ofstream fapp("results/res.csv", ios::app);
    fapp << "average_calc," << average_calc1 << "," << average_calc2 << "," << average_calc3 << "," << average_calc4 << endl;
    fapp << "average_search," << average_search1 << "," << average_search2 << "," << average_search3 << "," << average_search4 << endl;

    fapp.close();

    return 0;
}