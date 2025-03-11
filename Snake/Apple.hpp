//
//  Apple.hpp
//  
//
//  Created by Глеб Косачёв on 11/03/2025.
//

#ifndef Apple_hpp
#define Apple_hpp

#include "Cell.hpp"

class Apple : public Cell
{
public:
    Apple(int32_t, int32_t);
    void OnUpdate(Renderer *) override;
    CollisionResult Collide() override;
};

#endif /* Apple_hpp */
