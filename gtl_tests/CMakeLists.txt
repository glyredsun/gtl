cmake_minimum_required(VERSION 3.4)

project(gtl_tests)

set(gtl_dir ../gtl)

add_executable(stack_test stack_test.cpp)
include_directories(stack_test ${gtl_dir})

add_executable(vector_test vector_test.cpp)
include_directories(vector_test ${gtl_dir})

add_executable(list_test list_test.cpp)
include_directories(list_test ${gtl_dir})

add_executable(queue_test queue_test.cpp)
include_directories(queue_test ${gtl_dir})

add_executable(bstree_test bstree_test.cpp)
include_directories(bstree_test ${gtl_dir})

add_executable(avltree_test avltree_test.cpp)
include_directories(avltree_test ${gtl_dir})

add_executable(heap_test heap_test.cpp)
include_directories(heap_test ${gtl_dir})

add_executable(map_test map_test.cpp)
include_directories(map_test ${gtl_dir})

add_executable(sort_test sort_test.cpp)
include_directories(sort_test ${gtl_dir})

add_executable(string_test string_test.cpp)
include_directories(string_test ${gtl_dir})

add_executable(hash_test hash_test.cpp)
include_directories(hash_test ${gtl_dir})

add_executable(type_traits_test type_traits_test.cpp)
include_directories(type_traits_test ${gtl_dir})