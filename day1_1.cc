#include <string>
#include <fstream>
#include <iostream>
#include <regex>

std::string ConvertToChar(const std::string match)
{
    if (match.length() == 1)
        return match;
    else
    {
        if (match == "one")
            return std::string{'1'};
        if (match == "two")
            return std::string{'2'};
        if (match == "three")
            return std::string{'3'};
        if (match == "four")
            return std::string{'4'};
        if (match == "five")
            return std::string{'5'};
        if (match == "six")
            return std::string{'6'};
        if (match == "seven")
            return std::string{'7'};
        if (match == "eight")
            return std::string{'8'};
        if (match == "nine")
            return std::string{'9'};
    }
    throw "Not a valid number";
}

int main()
{
    std::ifstream file("day1_1.txt");
    std::string line;
    int sum = 0;
    while(std::getline(file, line, '\n'))
    {
        std::string number{};
        std::regex pattern("(one|two|three|four|five|six|seven|eight|nine|[0-9])");
        
        bool first_matched = false;
        std::string last_match;

        for (std::sregex_iterator match(line.begin(), line.end(), pattern);
            match != std::sregex_iterator(); match++)
        {
            if (!first_matched)
            {
                number.append(ConvertToChar(match->str().c_str()));
                first_matched = true;
            }
            last_match = ConvertToChar(match->str().c_str());
        }

        number.append(last_match);
        std::cout << line << ": " << number << " = " << std::stoi(number) << std::endl;
        sum += std::stoi(number);
    }
    std::cout << sum << std::endl;
}