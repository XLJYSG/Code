# 定义编译器
CC = g++

# 定义编译选项
CFLAGS = -Iinclude -Wall -g

# 定义源文件目录和目标文件目录
SRCDIR = src
BUILDDIR = build

# 定义可执行文件
TARGET = $(BUILDDIR)/village.exe

# 定义源文件列表, 包含$(SRCDIR)这一目录
SRCS=$(wildcard $(SRCDIR)/*.cpp)

# 定义目标文件列表
OBJS=$(SRCS:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# 默认规则
all: $(TARGET)

# 生成可执行文件, $@代表目标, $^代表依赖
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^


# 生成目标文件
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	if not exist $(BUILDDIR) mkdir $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 清理规则
clean:
	del /q $(BUILDDIR)\*.o
	rmdir /s /q $(BUILDDIR)

run: $(TARGET)
	$(TARGET)

.PHONY: all clean run