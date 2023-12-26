#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <algorithm>
#include <array>
#include <string_view>
#include <optional>
#include <deque>

/**
 * @brief get the position of the first digit
 * 
 * @tparam I1 iterator
 * @tparam I2 iterator
 * @param start start iterator
 * @param end end iterator
 * @return iterator pointing to the first digit found or the end iterator 
 */
template<typename I1, typename I2>
auto get_digit_pos(I1 start, I2 end)
{
    for(;start != end; ++start)
    {
        if(*start >= '0' && *start <= '9') { break; }
    }

    return start;
}

/**
 * @brief finds first substring in character sequance
 * 
 * @param start start forward iterator
 * @param end end forward iterator
 * @param search string to find
 * @return returns iterator pointing to the last character of matching substring
 */
auto find_snum(std::string::const_iterator start, std::string::const_iterator end, const std::string& search)
{
    if(std::distance(start, end) < search.size()) return end;

    using std::cbegin;
    using std::cend;

    std::deque<char> window(search.size(), 0);
    for(; start != end; ++start)
    {
        window.emplace_back(*start);
        window.pop_front();

        if(std::equal(cbegin(window), cend(window), cbegin(search), cend(search)))
        {
            break;
        }
    }

    return start;
}

/**
 * @brief finds first substring in character sequance
 * 
 * @param start start reverse iterator
 * @param end end reverse iterator
 * @param search string to find
 * @return returns iterator pointing to the last character of matching substring
 */
auto find_snum(std::string::const_reverse_iterator start, std::string::const_reverse_iterator end, const std::string& search)
{
    if(std::distance(start, end) < search.size()) return end;

    using std::cbegin;
    using std::cend;
    std::deque<char> window(search.size(), 0);
    for(; start != end; ++start)
    {
        window.emplace_front(*start);
        window.pop_back();

        if(std::equal(cbegin(window), cend(window), cbegin(search), cend(search)))
        {
            break;
        }
    }

    return start;
}

/**
 * @brief find digit written out as string
 * 
 * @tparam I1 
 * @tparam I2 
 * @param start start iterator
 * @param end end iterator
 * @return std::optional<uint_fast8_t> returns the found digit or nullopt if no written digit is found
 */
template<typename I1, typename I2>
std::optional<uint_fast8_t> find_string_num(I1 start, I2 end)
{
    static const std::array<std::string, 10> written_digets { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    using std::cbegin;
    using std::cend;

    uint_fast8_t wd_dist = std::numeric_limits<decltype(wd_dist)>::max();
    decltype(written_digets)::const_iterator tmp_num;
    for(auto wd_itr = cbegin(written_digets); wd_itr != cend(written_digets); ++wd_itr)
    { 
        auto it = find_snum(start, end, *wd_itr);
        if(it != end)
        {   
            auto dist = std::distance(start,it);
            if(wd_dist > dist)
            {
                wd_dist = dist;
                tmp_num = wd_itr;
            }
        }
    }

    if(wd_dist < std::numeric_limits<decltype(wd_dist)>::max())
    {
        return std::distance(cbegin(written_digets), tmp_num);
    }

    return std::nullopt;
    
}

/**
 * @brief finds the first digit in sequence
 * 
 * @tparam I1 
 * @tparam I2 
 * @param start start iterator
 * @param end end iterator
 * @return uint_fast8_t first digit found in sequence or 0
 */
template <typename I1, typename I2>
uint_fast8_t get_first_digit(I1 start, I2 end)
{
    auto dpos = get_digit_pos(start, end);
    return find_string_num(start, dpos).value_or(dpos != end? *dpos - '0' : 0);
}

/**
 * @brief combines the first digit with the last digit in line
 * 
 * @param line
 * @return uint_fast8_t result of the first digit * 10 + last digit in line
 */
uint_fast8_t combine_digts(const std::string& line)
{
    using std::cbegin;
    using std::cend;
   
    uint_fast8_t val;
    val = 10 * get_first_digit(cbegin(line), cend(line));
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