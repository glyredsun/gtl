project(gtl_tests)

set(gtl_dir ../gtl)

add_executable(stack_test stack_test.cpp)
include_directories(stack_test ${gtl_dir})

add_executable(vector_test vector_test.cpp)
include_directories(vector_test ${gtl_dir})