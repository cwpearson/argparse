# copyright Carl Pearson, 2022

macro(add_args tgt)
target_compile_options(
  ${tgt}
  PUBLIC
    -Wall;
    -Wextra;
    -Wpedantic;
    -Wcast-align;
    -Wdisabled-optimization;
    -Winit-self;
    -Wlogical-op;
    -Wmissing-include-dirs;
    -Woverloaded-virtual;
    -Wpointer-arith;
    -Wshadow;
    -Wstrict-aliasing;
    -Wswitch-enum;
    -Wundef;
    -Wvla;
    -Wformat=2;
)
endmacro()


add_executable(test_all test_main.cpp
  test_argparse.cpp
)
add_args(test_all)
target_include_directories(test_all SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_include_directories(test_all SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty)
add_test(NAME test_all COMMAND test_all -a)

