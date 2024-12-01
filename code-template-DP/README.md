##环境依赖
g++
Jupyter

##目录结构描述
├── Makefile        // makefile
├── README.md       // readme help \
├── algorithm.cpp   // 算法实现 \
├── algorithm.h     // 算法声明头文件 \
├── analyser.cpp    // 插桩代码测试 \
├── data_gen.cpp    // 测试集数据生成 \
├── main.cpp        // 主文件 \
├── plt.ipynb       // 绘图脚本 \
├── results         
│   └── res.csv     // 结果统计csv \
├── test.cpp        // 测试函数实现 \
├── test.h          // 测试函数声明头文件 \
└── test.sh         // 辅助测试的bash脚本 \
##测试步骤
1. 编译
make

2.添加sh脚本执行权限
sudo chmod +x test.sh

3.(可选)修改sh脚本自定义测试

4.运行脚本
bash test.sh
(通过bash脚本进行批量生成数据集和批量测试)

5.绘图
在plt.ipynb中运行所有代码即可

