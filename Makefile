# 编译器：C++必须用g++，不能用gcc
CXX = g++
# 编译参数：i-Wall显示警告，-g生成调试信息，方便调试Socket程序
CXXFLAGS = -Wall -g -std=c++11
# 目标可执行文件名：和你的源文件一致 → testsockte
TARGET = main
# 实际源文件：你的C++文件 → testsockte.cpp（无中间e，cpp后缀）
SRC = main.cpp

# 核心编译规则：执行make就会编译SRC生成TARGET
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) -lpthread

# 清理规则：执行make clean删除可执行文件，方便重新编译
clean:
	rm -rf $(TARGET) *.o
