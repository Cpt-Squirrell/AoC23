#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <filesystem>

// ===[ Helper Functions ]===
namespace
{
    std::string ConvertToChar(const std::string match)
    {
        if (match.length() == 1)
            return match;
        else
        {
            if (match == "one")
                return std::string{ '1' };
            if (match == "two")
                return std::string{ '2' };
            if (match == "three")
                return std::string{ '3' };
            if (match == "four")
                return std::string{ '4' };
            if (match == "five")
                return std::string{ '5' };
            if (match == "six")
                return std::string{ '6' };
            if (match == "seven")
                return std::string{ '7' };
            if (match == "eight")
                return std::string{ '8' };
            if (match == "nine")
                return std::string{ '9' };
        }
        throw "Not a valid number";
    }
}



// ===[ Day Implementations ]===
namespace day_implements
{

    int dOne_pOne(std::filesystem::path path)
    {
        std::ifstream file{ path };
        std::string line;
        int sum = 0;
        while (std::getline(file, line, '\n'))
        {
            std::string first;
            auto first_it = std::find_if(line.begin(), line.end(), [](char symbol)
                { return symbol >= '1' && symbol <= '9'; });
            if (first_it == line.end()) // Make sure there is a number in the line
                continue; // Actually is redundant
            else
                first = *first_it;

            std::string last{
                *std::find_if(
                        std::reverse_iterator<std::string::iterator>
                        (line.end()),
                        std::reverse_iterator<std::string::iterator>
                        (line.begin()), [](char symbol)
                        { return symbol >= '1' && symbol <= '9'; }) };
            sum += std::stoi(first + last);
        }
        return sum;
    }

    int dOne_pTwo(std::filesystem::path path)
    {
        std::vector<std::string> tokens
        {
            "1", "2", "3", "4", "5", "6", "7", "8", "9",
            "one", "two", "three", "four", "five", "six",
            "seven", "eight", "nine"
        };

        std::ifstream file(path);
        std::string line;
        int sum = 0;
        while (std::getline(file, line, '\n'))
        {
            std::string first_substr{};
            std::string first_symbol{};
            bool break_copy = false;
            std::copy_if(line.begin(), line.end(),
                std::back_insert_iterator<std::string>(first_substr),
                [&break_copy, &first_substr, &tokens, &first_symbol](const char)
                {
                    if (break_copy)
                        return false;
                    
                    for (std::string token : tokens)
                    {
                        auto substr_it = std::search(
                            first_substr.begin(),
                            first_substr.end(),
                            token.begin(),
                            token.end());

                        if (substr_it != first_substr.end())
                        {
                            std::copy(substr_it, first_substr.end(),
                                std::back_insert_iterator<std::string>(first_symbol));
                            first_symbol = ConvertToChar(first_symbol);
                            break_copy = true;
                            return false;
                        }
                    }
                    return true;
                }
            );
            if (!break_copy) // Check one more time!
            {
                for (std::string token : tokens)
                {
                    auto substr_it = std::search(
                        first_substr.begin(),
                        first_substr.end(),
                        token.begin(),
                        token.end());

                    if (substr_it != first_substr.end())
                    {
                        std::copy(substr_it, first_substr.end(),
                            std::back_insert_iterator<std::string>(first_symbol));
                        first_symbol = ConvertToChar(first_symbol);
                    }
                }
            }
            

            std::string last_substr{};
            std::string last_symbol{};
            break_copy = false;
            std::copy_if(std::reverse_iterator<std::string::iterator>(line.end()),
                std::reverse_iterator<std::string::iterator>(line.begin()),
                std::inserter(last_substr, last_substr.begin()),
                [&break_copy, &last_substr, &tokens, &last_symbol](const char) {
                    if (break_copy)
                        return false;
                    
                    // Reverse the string
                    std::reverse(last_substr.begin(), last_substr.end());
                    for (std::string token : tokens)
                    {
                        auto substr_it = std::search(last_substr.begin(),
                            last_substr.end(),
                            token.begin(),
                            token.end());

                        if (substr_it != last_substr.end())
                        {
                            std::copy(last_substr.begin(), last_substr.begin() + token.size(),
                                std::back_insert_iterator<std::string>(last_symbol));
                            last_symbol = ConvertToChar(last_symbol);
                            break_copy = true;
                            return false;
                        }
                    }
                    // Reverse the string before giving it back to std::copy_if
                    std::reverse(last_substr.begin(), last_substr.end());
                    return true;
                }
            );
            if (!break_copy) // Check one more time!
            {
                std::reverse(last_substr.begin(), last_substr.end());
                for (std::string token : tokens)
                {
                    auto substr_it = std::search(last_substr.begin(),
                        last_substr.end(),
                        token.begin(),
                        token.end());

                    if (substr_it != last_substr.end())
                    {
                        std::copy(last_substr.begin(), last_substr.begin() + token.size(),
                            std::back_insert_iterator<std::string>(last_symbol));
                        last_symbol = ConvertToChar(last_symbol);
                    }
                }
                std::reverse(last_substr.begin(), last_substr.end());
            }
            sum += std::stoi(first_symbol + last_symbol);
        }
        return sum;
    }

} // ~namespace day_implements
