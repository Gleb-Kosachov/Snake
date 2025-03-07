# Snake

set(SOURCE_DIR "src")

set(SOURCES Game.cpp Window.cpp Renderer.cpp Cell.cpp main.cpp Game.hpp Renderer.hpp Window.hpp Cell.hpp)

add_executable(Snake "${SOURCES}")
target_link_libraries(Snake glfw) 
target_link_libraries(Snake glad)
