//
//  MovableObject.hpp
//  Game
//
//  Created by Blind Joe Death on 19.09.17.
//  Copyright © 2017 test. All rights reserved.
//

#ifndef MovableObject_hpp
#define MovableObject_hpp

#include <stdio.h>
#include "GameObject.hpp"

class MovableObject : public GameObject{
    
    private :
    static float x_limit_accel;
    static float y_limit_accel;
    static float x_accel_step;
    static float y_accel_step;
    static float x_limit_speed;
    static float y_limit_speed;
    static float x_friction;
    static float y_friction;
    static float y_min_for_x;
    float x_curr_accel;
    float y_curr_accel;
    float x_curr_speed;
    float y_curr_speed;
    
    public :
    static enum direction{FRONT, BACK, RIGHT, LEFT};
    MovableObject(const char *, sf::IntRect, sf::Vector2f, int);
    void move();
    void add_acceleration(direction);
    void on_collision(direction);
};

#endif /* MovableObject_hpp */
