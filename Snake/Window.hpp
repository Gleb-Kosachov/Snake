//
//  Window.hpp
//  Snake
//
//  Created by Глеб Косачёв on 06/03/2025.
//

#include <cstdint>
#include <utility>

class Window
{
    void *window;
public:
    Window();
    ~Window();
    
    bool ShouldClose();
    void UpdateImage();
    void HandleEvents();
    std::pair<int32_t, int32_t> GetUserInput();
};
