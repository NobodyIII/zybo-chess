SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")

add_executable(zybo-chess.elf main.c board.c minimax.c async_ai.c chessDisplay.c chessControl.c)
target_link_libraries(zybo-chess.elf ${330_LIBS} intervalTimer buttons_switches)
set_target_properties(zybo-chess.elf PROPERTIES LINKER_LANGUAGE CXX)
