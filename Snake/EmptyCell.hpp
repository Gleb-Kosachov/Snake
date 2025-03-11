//
//  EmptyCell.hpp
//  
//
//  Created by Глеб Косачёв on 11/03/2025.
//

#ifndef EmptyCell_hpp
#define EmptyCell_hpp

#include "Cell.hpp"

class EmptyCell : public Cell
{
public:
    EmptyCell(int32_t, int32_t);
    void OnUpdate(Renderer *) override;
    CollisionResult Collide() override;
};

#endif /* EmptyCell_hpp */
