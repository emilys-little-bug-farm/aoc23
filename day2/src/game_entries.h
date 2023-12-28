#pragma once
#include <cstdint>
#include <string>
#include <list>

/**
 * @brief describes the combination of cubes thrown in a play
 * 
 */
struct Cubes
{
    uint16_t green;
    uint16_t red;
    uint16_t blue;
};

/**
 * @brief processes the string of a single game
 * 
 * @param line 
 * @return std::pair<uint16_t, std::list<Cubes>> 
 */
std::pair<uint16_t, std::list<Cubes>> process_game_string(const std::string&);

