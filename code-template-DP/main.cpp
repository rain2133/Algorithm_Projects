#include <ctime>
#include <cstdlib>
#include <stack>
#include <string>
#include <cstring>
#include "algorithm.h"
#include "test.h"

using namespace std;

int main(int argc, char *argv[])
{
    //input: data_file
    if (argc != 2)
    {
        cout<< "参数错误，参数：数据集文件，如test_x_x_x.data" << endl;
        exit(1);
    }
    long double average_time_1, 
                average_time_2,
                average_time_3,
                average_time_4;
    average_time_1 = test_5(argv[1], Knapsack_Unbounded_1);
    average_time_2 = test_5(argv[1], Knapsack_Unbounded_2);
    average_time_3 = test_6(argv[1], Knapsack_Bounded);
    average_time_4 = test_6(argv[1], Knapsack_Bounded_log2);
    cout << average_time_1 << endl;
    cout << average_time_2 << endl;
    cout << average_time_3 << endl;
    cout << average_time_4 << endl;
    //输出平均时间到csv文件 覆盖写
    ofstream fout("results/res.csv");
    fout << "Evaluation," << "Unbounded_1," << "Unbounded_2," << "Bounded," << "Bounded_log2" << endl;
    fout << "average_time(s),"<< average_time_1 << "," << average_time_2 << ",";
    fout << average_time_3 << "," << average_time_4 << endl;
    fout.close();
    return 0;

    /**
     * 供参考：
     * 可能的输入：数据集文件、n（物品种类）、w（背包重量上限）
     * 1. 读取data_gen生成的测试集文件
     * 2. 使用不同算法对于测试集进行求解
     * 3. 记录算法性能并保存到文件
     * coding
     */
}
