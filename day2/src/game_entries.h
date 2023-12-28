#pragma once
#include <cstdint>
#include <string>
#include <list>


struct Cubes
{
    uint16_t green;
    uint16_t red;
    uint16_t blue;
};

std::pair<uint16_t, Cubes> process_game_string(const std::string&);

