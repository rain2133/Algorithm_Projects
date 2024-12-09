#!/bin/bash

# 测试脚本，下述内容仅为示例
# 使用前先增加执行权限: sudo chmod +x test.sh

echo "test srart"

# ./data_gen 10 100 100
# ./main test_10_100_100.data
# #get average_time of 4 algorithms
# ./analyser test_10_100_100.data
# #get average_calc and average_search
# echo "--------------------------------------------"

./data_gen 2 20 500
./main test_2_20_500.data
./analyser test_2_20_500.data
echo "--------------------------------------------"


# ./data_gen 10 1000 100000
# ./main test_10_1000_100000.data
# ./analyser test_10_1000_100000.data
# echo "--------------------------------------------"
echo "test end"




