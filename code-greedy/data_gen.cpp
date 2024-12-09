#include <iostream>
#include <fstream>
#include <random>
#include <cmath>

using namespace std;

/**
 * @func data_gen
 * @brief 生成测试数据集
 * @param k: 测试集数量
 * @param m: 机器数量
 * @param n: 任务数量
 *
 * @return null
 */
void data_gen(int k, int m, int n){
    char out_file[100];
    //输出文件名可参考"test_{k}_{n}_{w}.data"
    sprintf(out_file, "test_%d_%d_%d.data", k, m, n);
    ofstream fout(out_file);
    fout << k << " " << m << " " << n << endl;
    default_random_engine e(time(nullptr));
    //随机数分布对象
    uniform_int_distribution<signed> task(1,50);
    
    while (k--)
    {
        // 生成任务值
        for (int i = 0; i < n; i++) //生成0~100的随机数序列
            fout << task(e) << " ";
        fout << endl;
    }
}

int main(int argc, char *argv[])
{
    // k: 生成数据的组数
    // m: 机器数量
    // n: 任务数量
    if(argc != 4 )
    {
        cout << "参数错误，参数包括: 生成数据的组数k, 机器数量m, 任务数量n" << endl;
        exit(1);
    }

    int k, m, n;
    k = atoi(argv[1]);
    m = atoi(argv[2]);
    n = atoi(argv[3]);
    data_gen(k,m,n);

    return 0;
}
