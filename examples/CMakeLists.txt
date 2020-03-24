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

macro(add_example EXE SRCS)
  add_executable(${EXE} ${SRCS})
  add_args(${EXE})
  target_include_directories(${EXE} SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
endmacro()

add_example(example1 example1.cpp)

