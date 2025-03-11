# Snake

set(SOURCE_DIR "src")

set(SOURCES Game.cpp Window.cpp Renderer.cpp Cell.cpp EmptyCell.cpp Apple.cpp SnakeBody.cpp SnakeHead.cpp main.cpp Game.hpp Renderer.hpp Window.hpp Cell.hpp EmptyCell.hpp Apple.hpp SnakeBody.hpp SnakeHead.hpp)

add_executable(Snake "${SOURCES}")
target_link_libraries(Snake glfw) 
target_link_libraries(Snake glad)
