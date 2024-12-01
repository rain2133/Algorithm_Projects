#include <iostream>
#include <fstream>
#include <random>
#include <cmath>

using namespace std;

/**
 * @func data_gen
 * @brief 生成测试数据集
 * @param k: 测试集数量
 * @param n: 物品种类
 * @param w: 背包重量限制
 *
 * @return null
 */
void data_gen(int k, int n, int w){
    char out_file[100];
    //输出文件名可参考"test_{k}_{n}_{w}.data"
    sprintf(out_file, "test_%d_%d_%d.data", k, n, w);
    ofstream fout(out_file);
    fout << k << " " << n << " " << w << endl;
    default_random_engine e(time(nullptr));
    //随机数分布对象
    uniform_int_distribution<signed> we(2, 5),v(2, sqrt(w)),p(1, sqrt(w));
    while (k--)
    {
        // 生成weight值
        for (int i = 0; i < n; i++) //生成2~w / 1.5的随机数序列
            fout << we(e) << " ";
        fout << endl;
        // 生成value值
        for (int i = 0; i < n; i++) //生成2~w / 1.5的随机数序列
            fout << v(e) << " ";
        fout << endl;
        // 生成p值 
        for (int i = 0; i < n; i++) //生成1~sqrt(w)的随机数序列
            fout << p(e) << " ";
        fout << endl;
    }
}

int main(int argc, char *argv[])
{
    // k: 生成数据的组数
    // n: 物品的种类（问题的规模）
    // w: 背包重量限制
    if(argc != 4 )
    {
        cout << "参数错误，参数包括: 生成数据的组数k, 物品的种类n, 背包重量限制w" << endl;
        exit(1);
    }

    int k, n, w;
    k = atoi(argv[1]);
    n = atoi(argv[2]);
    w = atoi(argv[3]);
    data_gen(k,n,w);

    return 0;
}
