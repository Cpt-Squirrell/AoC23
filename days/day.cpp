#include <iostream>
#include "day.h"

// ===[ Private Constructor ]===
Day::Day(
    std::string name,
    std::string description,
    std::filesystem::path src,
    std::function<int (const std::filesystem::path src)> one,
    std::function<int (const std::filesystem::path src)> two,
    Day::PrivateTag):
        name(name),
        input_file(src),
        description(description),
        PartOne(one), PartTwo(two)
{
    if (input_file.empty())
        std::cerr << name << " has no input data!\n";
}

// ===[ Public Constructors ]===
Day::Day(
    std::string name,
    std::filesystem::path src,
    std::function<int (const std::filesystem::path src)> one,
    std::function<int (const std::filesystem::path src)> two):
        Day(name, std::string(), src, one, two, Day::PrivateTag()) {};

Day::Day(
    std::string name,
    std::string description,
    std::filesystem::path src,
    std::function<int (const std::filesystem::path src)> one,
    std::function<int (const std::filesystem::path src)> two):
        Day(name, description, src, one, two, Day::PrivateTag()) {};

// -={ Calls and measures the solutions }=-
void Day::Run()
{
    if (!PartOne)
        std::cerr; // TODO: << name << " has no solution for part one.\n";
    else
    {
        std::chrono::time_point before = std::chrono::high_resolution_clock::now();
        result_one = PartOne(input_file);
        std::chrono::time_point after = std::chrono::high_resolution_clock::now();
        time_one = std::chrono::duration(after - before);
    }

    if (!PartTwo)
        std::cerr; // TODO: << name << " has no solution for part two.\n";
    else
    {
        std::chrono::time_point before = std::chrono::high_resolution_clock::now();
        result_two = PartTwo(input_file);
        std::chrono::time_point after = std::chrono::high_resolution_clock::now();
        time_two = std::chrono::duration(after - before);
    }
}

std::pair<int, int> Day::GetResults() const
{ return std::pair<int, int>{result_one, result_two}; }

std::pair<std::chrono::nanoseconds, std::chrono::nanoseconds> Day::GetTimes() const
{ return std::pair<std::chrono::nanoseconds, std::chrono::nanoseconds>{time_one, time_two}; }