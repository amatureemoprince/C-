# Makefile.mk

# 定义编译器
CC = gcc

# 定义编译选项
CFLAGS = -I./ds -Wall -g

# 定义源文件列表
SOURCES = binary_tree.c ds/ds.c

# 定义目标可执行文件名
TARGET = binary_tree

# 默认目标
all: $(TARGET)

# 编译规则
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

# 清理生成的文件
clean:
	rm -f $(TARGET) *.o
