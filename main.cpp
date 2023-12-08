#include <utility>
#include <vector>
#include <iostream>
#include <iomanip>
#include <format>

#include "days/day.h"

#if defined(_WIN32) || defined(_WIN64)
    #define WINDOWS
    #include <Windows.h>
#endif

class TerminalTable
{
    // -={ Header in format <title, padding> }=-
    std::vector<std::pair<std::string, int>> header;
    std::vector<size_t> spacing;

    public:
    // ===[ Draw Functions ]===
    void DrawTopLine()
    {
        std::cout << "┌";
        for (int field = 0; field < spacing.size(); field++)
        {
            for (int i = 0; i < spacing[field]; i++)
            {
                std::cout << "─";
            }
            if (field != spacing.size() - 1)
                std::cout << "┬";
        }
        std::cout << "┐" << std::endl;
    }

    void DrawLine(bool thicc = false)
    {
        thicc ? std::cout << "╞" : std::cout << "├";
        for (int field = 0; field < spacing.size(); field++)
        {
            for (int i = 0; i < spacing[field]; i++)
            {
                thicc ? std::cout << "═" : std::cout << "─";
            }
            if (field != spacing.size() - 1)
                thicc ? std::cout << "╪" : std::cout << "┼";
        }
        thicc ? std::cout << "╡" : std::cout << "┤";
        std::cout << std::endl;
    }

    void DrawBottomLine()
    {
        std::cout << "└";
        for (int field = 0; field < spacing.size(); field++)
        {
            for (int i = 0; i < spacing[field]; i++)
            {
                std::cout << "─";
            }
            if (field != spacing.size() - 1)
                std::cout << "┴";
        }
        std::cout << "┘" << std::endl;
    }

    // -={ Draw text with lines between ( pair<text, box_size> ) }=-
    void DrawText(std::vector<std::string> content)
    {
        std::cout << std::setw(0) << std::setfill(' ') << "│";
        for (int i = 0; i < spacing.size(); i++)
        {
            std::cout << std::setw(spacing[i]);
            if (i < content.size())
            {
                if (!content[i].empty())
                {
                    if (content[i].size() > spacing[i] - 1)
                        std::cout << content[i].substr(0, spacing[i] - 1);
                    else
                        std::cout << content[i];
                }
            }
            else
                std::cout << " ";

            std::cout << std::setw(0) << "│";
        }
        std::cout << std::endl;
    }

    void DrawHeader()
    {
        std::vector<std::string> text(header.size());
        std::transform(header.begin(), header.end(), text.begin(),
            [](std::pair<std::string, int> pair) { return pair.first; });
        DrawText(text);
    }

    void SetHeader(std::vector<std::pair<std::string, int>> header)
    {
        this->header = header;
        spacing.clear();
        for (std::pair<std::string, int> title : header)
        {
            spacing.push_back(title.first.size() + title.second);
        }
    }
};

std::string FormatTime(uint64_t millis)
{
    constexpr uint64_t PerSecond = 1000;
    constexpr uint64_t PerMinute = PerSecond * 60;
    constexpr uint64_t PerHour   = PerMinute * 60;

    uint64_t hours = millis / PerHour;
    uint64_t minutes = (millis %= PerHour)   / PerMinute;
    uint64_t seconds = (millis %= PerMinute) / PerSecond;
    millis %= PerSecond;

    return std::format("{:02}:{:02}:{:02}:{:03}ms", hours, minutes, seconds, millis);
}

int main()
{
    #if defined(WINDOWS) // Enable UTF8 printing
        ::SetConsoleOutputCP(CP_UTF8);
    #endif

    TerminalTable table;
    table.SetHeader(std::vector<std::pair<std::string, int>>{
        { "Day", 6 },
        { "Description", 10 },
        { "Solution 1", 2 },
        { "Timer 1", 8 },
        { "Solution 2", 2 },
        { "Timer 2", 8 },
    });

    const std::vector<Day> days
    {
        Day("Day 1", "The trebuchet",
            std::filesystem::path{"input_data/day_one.txt"},
            day_implements::dOne_pOne,
            day_implements::dOne_pTwo),

        Day("Day 2", "The island",
            std::filesystem::path{"input_data/day_two.txt"},
            day_implements::dTwo_pOne,
            day_implements::dTwo_pTwo),

        Day("Day 3", "The gondola",
            std::filesystem::path{"input_data/day_three.txt"},
            day_implements::dThree_pOne,
            day_implements::dThree_pTwo),

        Day("Day 4", "The island island",
            std::filesystem::path{}),

    };

    std::cout << std::left;
    table.DrawTopLine();
    table.DrawHeader();
    table.DrawLine(true);
    for (Day day : days)
    {
        day.Run();
        table.DrawText(std::vector<std::string> {
            day.name,
            day.description,
            day.PartOne ?
                std::to_string(day.GetResults().first)
                : std::string{"DnF"},
            day.PartOne ? FormatTime(std::chrono::duration_cast<std::chrono::milliseconds>(day.GetTimes().first).count()) : std::string{"DnF"},
            day.PartTwo ?
                std::to_string(day.GetResults().second)
                : std::string{"DnF"},
            day.PartTwo ? 
                std::string
                {
                    FormatTime(std::chrono::duration_cast<std::chrono::milliseconds>(day.GetTimes().second).count())

                    /*
                    std::to_string(std::chrono::duration_cast<std::chrono::minutes>(day.GetTimes().second).count()) + ":" +
                    std::to_string(std::chrono::duration_cast<std::chrono::seconds>(day.GetTimes().second).count()) + ":" +
                    std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(day.GetTimes().second).count()) + ":" +
                    std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(day.GetTimes().second).count())
                    */
                    
                    /*
                    // THIS IS ALL @Darian's FAULT!                                                     --I'm innocent--
                        std::to_string(std::chrono::duration_cast<std::chrono::minutes>(day.GetTimes().second).count()) + ":" +
                        std::to_string(std::chrono::duration_cast<std::chrono::seconds>(day.GetTimes().second).count() % 
                            ((std::chrono::duration_cast<std::chrono::minutes>(day.GetTimes().second).count() > 0) ?
                                std::chrono::duration_cast<std::chrono::minutes>(day.GetTimes().second).count() : 1)) + ":" +
                        std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(day.GetTimes().second).count() %
                            ((std::chrono::duration_cast<std::chrono::seconds>(day.GetTimes().second).count() %
                                ((std::chrono::duration_cast<std::chrono::minutes>(day.GetTimes().second).count() > 0) ?
                                    std::chrono::duration_cast<std::chrono::minutes>(day.GetTimes().second).count() : 1)) > 0 ?
                                        std::chrono::duration_cast<std::chrono::seconds>(day.GetTimes().second).count() : 1)) + ":" +
                        std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(day.GetTimes().second).count() %
                            (((std::chrono::duration_cast<std::chrono::milliseconds>(day.GetTimes().second).count() %
                                ((std::chrono::duration_cast<std::chrono::seconds>(day.GetTimes().second).count() %
                                    ((std::chrono::duration_cast<std::chrono::minutes>(day.GetTimes().second).count() > 0) ?
                                        std::chrono::duration_cast<std::chrono::minutes>(day.GetTimes().second).count() : 1)) > 0 ?
                                            std::chrono::duration_cast<std::chrono::seconds>(day.GetTimes().second).count() : 1)) > 0) ?
                                                std::chrono::duration_cast<std::chrono::milliseconds>(day.GetTimes().second).count() : 1))
                    */
                } : std::string{"DnF"},
        });
    }
    table.DrawBottomLine();
}