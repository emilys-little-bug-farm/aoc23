#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sched.h>
#include <string>
#include <algorithm>
#include <functional>

template <typename I1, typename I2>
uint_fast8_t get_first_digit(I1 start, I2 end)
{
    uint_fast8_t d = 0;
    for(;start != end; ++start)
    {
        if(*start >= '0' && *start <= '9')
        {
            d = *start - '0';
            break;
        }
    }
    return d;
}

uint_fast8_t combine_digts(const std::string& line)
{
    using namespace std;
    using namespace std::placeholders;

    uint_fast8_t val;
    val = 10* get_first_digit(cbegin(line), cend(line));
    val += get_first_digit(crbegin(line), crend(line));

    return val;
}

int main()
{
    using namespace std;

    ifstream ifs("../aoc_inputs/input.txt");

    if(ifs)
    {
        uint32_t total = 0;
        string line;
        while (getline(ifs,line)) {
            total += combine_digts(line);
        }

        cout << "Total value: " << total << '\n';

    } else 
    {
        cerr << "couldn't open file stream error\n";
    }
}