编译命令：
g++ -o tdoa_test tdoa_test.cpp tdoa.cpp -I/opt/xlmf_tdoa/include -L/opt/xlmf_tdoa/lib -litpp -lgtest -lgtest_main -pthread

如果缺少库就安装：
yum install gtest gtest-devel
