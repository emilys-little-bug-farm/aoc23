
#include <cstdlib>
#include <iterator>
#include <algorithm>
#include <bits/ranges_algo.h>
#include <bits/ranges_util.h>
#include <ranges>
#include <string_view>
#include <vector>
#include <fstream>
#include <iostream>

#include "game_entries.h"

int main()
{
    using namespace std;
    using std::operator""sv;
    ifstream ifs("../aoc_inputs/input.txt");

    if(ifs)
    {
        uint32_t total = 0;
        string line;
        string delim = ":";
        while (getline(ifs,line)) 
        {
           
            const auto[game_id, plays] = process_game_string(line);

            bool game_possible = true;
            for(const auto& play : plays)
            {
                // only 12 red cubes, 13 green cubes, and 14 blue cubes
                if(play.red > 12 || play.green > 13 || play.blue > 14)
                {
                   game_possible = false;
                }
            }

            if(game_possible)
            {
                std::cout << "id " << game_id << '\n';
                total += game_id;
            }

        }

        cout << "Total value: " << total << '\n';

    } else 
    {
        cerr << "couldn't open file stream error\n";
    }
}