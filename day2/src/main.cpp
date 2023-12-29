
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

            Cubes higest_values {0, 0 ,0};
            for(const auto& play : plays)
            {
                if(play.red > higest_values.red) { higest_values.red = play.red; }
                if(play.green > higest_values.green) { higest_values.green = play.green; }
                if(play.blue > higest_values.blue) { higest_values.blue = play.blue; }
            }

            total += higest_values.blue * higest_values.red * higest_values.green;
           
        }

        cout << "Total value: " << total << '\n';

    } else 
    {
        cerr << "couldn't open file stream error\n";
    }
}