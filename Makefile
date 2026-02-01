CC = g++
CFLAGS = -Wall -g -std=c++11
LDFLAGS = -lpthread
# 所有源文件（main.cpp + XTcp.cpp）
SRCS = main.cpp XTcp.cpp
# 自动生成中间目标文件（.cpp -> .o）
OBJS = $(SRCS:.cpp=.o)
TARGET = main

# 最终目标依赖所有.o文件
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# 每个.o文件依赖对应的.cpp和头文件
%.o: %.cpp XTcp.h
	$(CC) $(CFLAGS) -c $< -o $@

# 清理指令
clean:
	rm -f $(TARGET) $(OBJS)
