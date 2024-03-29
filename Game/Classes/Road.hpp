//
//  Road.hpp
//  Game
//
//  Created by Blind Joe Death on 20.09.17.
//  Copyright © 2017 test. All rights reserved.
#ifndef Road_hpp
#define Road_hpp
#include <stdio.h>
#include "MovableObject.hpp"
class Road : public MovableObject{
    private :
    std :: vector<GameObject*> obstruction;
    int get_dist_from_surf(sf::Vector2f , sf::Vector2f , sf::IntRect , sf::IntRect );
    static sf::Vector2i max_obstr_size;
    static sf::Vector2i min_obstr_size;
    static float lim_obstr_filled_part;
    static int min_obstr_dist;
    GameObject * add_obstruction(GameObject *);
    public :
    Road(const char *, sf::IntRect, sf::Vector2f, int);
    bool check_collision(MovableObject *);
    void gen_obstr();
};
#endif /* Road_hpp */
