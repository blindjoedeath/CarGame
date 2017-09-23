//
//  SceneManager.cpp
//  Game
//
//  Created by Blind Joe Death on 19.09.17.
//  Copyright © 2017 test. All rights reserved.
//

#include "SceneManager.hpp"
#include <iostream>

typedef std::map<sf::Keyboard::Key, std::function<void()>> action_map;
typedef std::map<sf::Keyboard::Key, bool>  bool_map;

int SceneManager::scr_height = 600;
int SceneManager::scr_width = 1000;
int SceneManager::car_width = 80;
int SceneManager::car_height = 120;
int SceneManager::layers_count = 2;
int SceneManager::players_count = 2;
int SceneManager::y_right_car_pos = 430;
action_map SceneManager::key_actions;
bool_map SceneManager::is_key_pressed;
std::vector<Road*> SceneManager::roads;
std::vector<MovableObject*> SceneManager::cars;
sf::RenderWindow* SceneManager::window;
sf::Music* SceneManager::music;



MovableObject::direction SceneManager::turn_direction(MovableObject::direction dir){
    switch(dir){
        case  MovableObject::direction::BACK:
            return MovableObject::direction::FRONT;
        case MovableObject::direction::FRONT:
            return MovableObject::direction::BACK;
        case  MovableObject::direction::LEFT:
            return MovableObject::direction::RIGHT;
        case MovableObject::direction::RIGHT:
            return MovableObject::direction::LEFT;
    }
    return;
}

bool SceneManager::is_car_pos_right(MovableObject *car, Road *road){
    if (car->get_position().y - y_right_car_pos < 10)
        return true;
    return false;
}

void SceneManager::movement(MovableObject * car, Road * road, MovableObject::direction dir){
    if (is_car_pos_right(car, road) && dir != MovableObject::direction::LEFT && dir != MovableObject::direction::RIGHT)
        road->add_acceleration(turn_direction(dir));
    else car->add_acceleration(dir);
}

void SceneManager::execute_actions(){
    for (action_map::iterator it = key_actions.begin(); it!=key_actions.end(); ++it){
        if (is_key_pressed[it->first]){
            it->second();
        }
    }
}

void SceneManager::set_key_state(sf::Keyboard::Key key,sf::Event::EventType event){
    if (event == sf::Event::KeyPressed)
        is_key_pressed[key] = true;
    if (event == sf::Event::KeyReleased)
        is_key_pressed[key] = false;
}

void SceneManager::set_actions(){
    key_actions[sf::Keyboard::W] = [](){movement(cars[0], roads[0], MovableObject::direction::FRONT);};
    key_actions[sf::Keyboard::S] = [](){movement(cars[0], roads[0], MovableObject::direction::BACK);};
    key_actions[sf::Keyboard::A] = [](){movement(cars[0], roads[0], MovableObject::direction::LEFT);};
    key_actions[sf::Keyboard::D] = [](){movement(cars[0], roads[0], MovableObject::direction::RIGHT);};
    key_actions[sf::Keyboard::Up] = [](){movement(cars[1], roads[1], MovableObject::direction::FRONT);};
    key_actions[sf::Keyboard::Down] = [](){movement(cars[1], roads[1], MovableObject::direction::BACK);};
    key_actions[sf::Keyboard::Left] = [](){movement(cars[1], roads[1], MovableObject::direction::LEFT);};
    key_actions[sf::Keyboard::Right] = [](){movement(cars[1], roads[1], MovableObject::direction::RIGHT);};
    for (action_map::iterator it = key_actions.begin(); it!=key_actions.end(); ++it){
        is_key_pressed[it->first] = false;
    }
}
void SceneManager :: create_window(){
    window = new sf::RenderWindow();
    music = new sf::Music();
    (*window).create(sf::VideoMode(scr_width, scr_height), "Game");
    if (!(*music).openFromFile(resourcePath() + "music.ogg")){
        return EXIT_FAILURE;
    }
    (*music).play();
    sf::IntRect rect;
    for (int i = 0; i < players_count; ++i){
        sf::IntRect size;
        size.width = scr_width/players_count;
        size.height = scr_height * 10;
        sf::Vector2f pos((scr_width/players_count) * i, -(size.height) + scr_height);
        roads.push_back(new Road("road.jpg", size, pos, 1));
        sf::Vector2f car_pos((roads[i]->get_position()).x + roads[i]->get_size().width / 2, scr_height - car_height);
        sf::IntRect car_size;
        car_size.width = car_width;
        car_size.height = car_height;
        cars.push_back(new MovableObject("car.png", car_size, car_pos, 2));
    }
    set_actions();
}

