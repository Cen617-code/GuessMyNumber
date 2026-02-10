# 1. 编译器定义
CXX = clang++
CXXFLAGS = -std=c++2b -Wall

# 2. 自动搜寻
# 使用 wildcard 函数找出当前目录下所有的 .cpp 文件
SRCS = $(wildcard *.cpp)

# 使用模式替换，把 SRCS 列表里的 .cpp 全部换成 .o
# 例如: main.cpp -> main.o, Leaderboard.cpp -> Leaderboard.o
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

# 3. 最终目标
TARGET = my_game

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# 4. 模式规则 (Pattern Rule)
# %.o : %.cpp 的意思是：所有的 .o 文件都依赖于同名的 .cpp 文件
# $< 代表第一个依赖文件 (即 .cpp)
# $@ 代表目标文件 (即 .o)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 5. 伪目标 (防止目录下刚好有名为 clean 的文件导致命令失效)
.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)