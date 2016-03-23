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