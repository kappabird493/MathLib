cmake_minimum_required(VERSION 3.10)
project(MathLib LANGUAGES CXX)

# C++ 標準（任意で変更可能）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ライブラリ (ヘッダのみ)
add_library(math INTERFACE)

# include ディレクトリを公開
target_include_directories(math INTERFACE include)

# 実行ファイル(example)
add_executable(example1 example/main.cpp)
add_executable(example2 example/main2.cpp)


# example に math をリンク
target_link_libraries(example1 PRIVATE math)
target_link_libraries(example2 PRIVATE math)

