#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <filesystem>

#include "day_utils.hpp"

// ===[ Helper Functions ]===
namespace
{
    struct Card
    {
        std::vector<int> winning_numbers;
        std::vector<int> numbers;
        int CalculateScore() const
        {
            int sum = 0;
            for (int num : numbers)
            {
                if (std::find(winning_numbers.begin(),
                    winning_numbers.end(), num) != winning_numbers.end())
                    sum += num;
            }
            return sum;
        }
    };
}

// ===[ Day Implementations ]===
namespace day_implements
{
    int dFour_pOne(std::filesystem::path path)
    {
        std::vector<std::string> lines = day_utils::ReadLines(path);
        std::vector<Card> cards;
        int score_sum = 0;
        for (std::string line : lines)
        {
            auto start = std::find(line.begin(), line.end(), ':');
            if (start != line.end()) start++;
            
            auto split = std::find(start, line.end(), '|');
            
            Card card;
            std::vector<std::string> strings = day_utils::SplitString(start, split);
            for (std::string str : strings)
            {
                str.erase(std::remove_if(str.begin(),
                                         str.end(),
                                         [](const char &symbol)
                                         { return !(symbol <= 9 && symbol >= 0); }
                                        ),
                          str.end());
            }
            std::transform(strings.begin(), strings.end(), std::back_inserter(card.winning_numbers),
                [](std::string string){ return stoi(string); });
                
            strings.clear();
            for (std::string str : strings)
            {
                str.erase(std::remove_if(str.begin(),
                                         str.end(),
                                         [](const char &symbol)
                                         { return !(symbol <= 9 && symbol >= 0); }
                                        ),
                          str.end());
            }
            strings = day_utils::SplitString(++split, line.end());
            std::transform(strings.begin(), strings.end(), std::back_inserter(card.numbers),
                [](std::string string){ return stoi(string); });
                
            score_sum += card.CalculateScore();
        }
        return score_sum;
    }

    int dFour_pTwo(std::filesystem::path path)
    {
        return 0;
    }

} // namespace day_implements
