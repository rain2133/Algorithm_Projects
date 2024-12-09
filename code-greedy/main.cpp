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
                average_time_2;
    average_time_1 = test(argv[1], Muilti_Machine_Schedualing_1);
    average_time_2 = test(argv[1], Muilti_Machine_Schedualing_2);
    return 0;

}
