# Cmake简介
CMake是一个跨平台的安装（编译）工具，可以用简单的语句来描述所有平台的安装(编译过程)。他能够输出各种各样的makefile或者project文件。
简单描述，跨平台、跨平台、跨平台编译工具。

## 1、使用介绍
比如你要在PC机器上（ubuntu）上编译一个cpp，
### Step1. 编辑一个main.cpp
'''
int main()
{
    cout << "hello" << endl;
}
'''
### Step2. 编写一个CMakeLists.txt 如下
'''
PROJECT(hello)
SET(SRC_LIST main.cpp)
add_compile_options(-std=c++11) #如果要使用C11特性，可以添加这个
ADD_EXECUTABLE(hello ${SRC_LIST})
'''
### Step3. 新建目录build，用于存放相应平台的makefile
'''
cd build
cmake ..（这个的..表示使用上层目录的CMakeLists.txt）  #跨平台只需要修改这里，添加一写编译选项。
make
'''

## 2、如果跨平台
如果要让这个cpp生成的bin运行于android平台，只需要在
Step3里，修改为：
export ANDROID_NDK=/home/coolpad/Android/NDK/android-ndk-r17
cmake -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK/build/cmake/android.toolchain.cmake -DANDROID_ABI="arm64-v8a" -DANDROID_PLATFORM=android-21 .

其实编译android的bin还有其他的两种方式：
### 2.1、使用Anroid.mk
'''
include $(CLEAR_VARS)
LOCAL_SRC_FILES += $(FILE_LIST) linear.cpp tron.cpp daxpy.c ddot.c dnrm2.c dscal.c
LOCAL_MODULE := liveness
include $(BUILD_EXECUTABLE)
'''
### 2.2 使用ndk-build的工具编译

