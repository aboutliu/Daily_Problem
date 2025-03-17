#!/bin/bash

# 设置 C++ 文件名（不包含 .cpp 后缀）
CPP_FILE="sort_problems"
MD_FILE="brute_force.md"

# 编译 C++ 代码（使用 g++）
g++ -std=c++11 -o "$CPP_FILE" "$CPP_FILE.cpp"

# 检查编译是否成功
if [ $? -eq 0 ]; then
    echo "编译成功！运行程序..."
    ./"$CPP_FILE" "$MD_FILE"  # 运行 C++ 可执行文件，并传入 Markdown 文件路径
else
    echo "编译失败，请检查 C++ 代码！"
fi