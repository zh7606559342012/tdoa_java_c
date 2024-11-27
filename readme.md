tdoa_chan.pc需要放到/usr/lib/pkgconfig/路径找文件路径
/opt/xlmf_oms/jdk-11.0.19/include/
和
/opt/xlmf_oms/jdk-11.0.19/include/linux/
这个路径的.h放到/usr/lib下

在meson路径下，即tdoa_java_c下
mkdir build
cd build
meson setup ..
ninja
生成libxlmf_tdoa.so

在发的算法包的路径
mkdir build
cd build
cmake ..
make
生成算法的test_case