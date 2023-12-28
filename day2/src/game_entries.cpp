#include "game_entries.h"

#include <array>
#include <cstdint>
#include <cstdlib>
#include <iterator>
#include <bits/ranges_util.h>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <list>
#include <cassert>
#include <functional>

/**
 * @brief Splits on a string view
 * 
 * @param sv string view to split
 * @param delim character to split on
 * @return std::vector<std::string_view> split elements
 */
std::vector<std::string_view> split_view(std::string_view sv, char delim)
{
    std::vector<std::string_view> splits;

    for(auto tmp_sv = sv; !tmp_sv.empty();  )
    {
        auto split_pos = std::ranges::find(tmp_sv, delim);
        splits.emplace_back(std::string_view{begin(tmp_sv), split_pos});
        tmp_sv = std::string_view{split_pos == end(sv)? split_pos : split_pos + 1, end(sv)};
    }

    return splits;
}

/**
 * @brief converts the string of a single throw into a Cubes object
 * 
 * @param play the string which describes that play
 * @return Cubes 
 */
Cubes get_throws(std::string_view play)
{
    using std::string_literals::operator""s;
    static std::unordered_map<std::string, uint16_t Cubes::* > color_names {
        { "red"s , &Cubes::red},
        {"green"s, &Cubes::green},
        {"blue", &Cubes::blue}
    };
    
    Cubes throws {0,0,0};
    auto throws_str = split_view(play, ',');

    std::ranges::for_each(throws_str, [&throws](std::string_view sv){
        const auto one_throw = split_view(sv, ' ');
        assert(one_throw.size() == 3); // expected to be count color

        auto color_ptr = color_names[std::string{one_throw[2]}];

        std::bind(color_ptr, &throws)() += static_cast<uint16_t>(strtoul(std::string{one_throw[1]}.c_str(), nullptr, 10));

    });

    
    return throws;

}

/**
 * @brief adds two Cubes together
 * 
 * @param lha 
 * @param rha 
 */
void operator+=(Cubes& lha, const Cubes& rha)
{
    lha.blue += rha.blue;
    lha.green += rha.green;
    lha.red += rha.red;
}

/**
 * @brief processes the string of a single game
 * 
 * @param line 
 * @return std::pair<uint16_t, std::list<Cubes>> 
 */
std::pair<uint16_t, std::list<Cubes>> process_game_string(const std::string& line)
{
    using namespace std;
            
    const auto& colon_split = split_view(line, ':');
    
    assert(colon_split.size() == 2); // expect game string and throws

    const std::string game_num_str = std::string{split_view(colon_split[0], ' ')[1]};
    const auto game_num = strtoul(game_num_str.c_str(), nullptr, 10);

    list<Cubes> games;
    const auto games_str = split_view(colon_split[1], ';');
    std::ranges::for_each(games_str, [&games](string_view game_str) {
        games.emplace_back(get_throws(game_str));
    });

    return {game_num, games};
}
