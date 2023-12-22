#include <filesystem>
#include <algorithm>
#include <fstream>
#include <numeric>
#include <vector>
#include <string>

// ===[ Helper Functions ]===
namespace
{
    struct SchematicNumber
    {
        SchematicNumber(int num, int pos, int len, int line):
            isPart(false), number(num), position(pos), num_length(len), line_num(line)
        {}

        bool isPart;
        int number;
        int position;
        int num_length;
        int line_num;

        bool isAdjacent(std::vector<std::string> &lines, int line, int pos) const
        {
            int relative_line = line - line_num;
            if (relative_line < -1 || relative_line > 1)
                return false;

            if (pos >= position - 1 && pos <= position + num_length)
                return true;
            else
                return false;
        }
    };

    struct Gear
    {
        Gear(std::vector<SchematicNumber> numbers): numbers(numbers) {}
        std::vector<SchematicNumber> numbers;
    };

    SchematicNumber ReadSchematicNumber(const std::string &line, int line_pos, int line_num)
    {
        std::string number_string;
        auto pos_it = line.begin() + line_pos;
        std::copy(pos_it, std::find_if(pos_it, line.end(),
                                       [](const char &symbol)
                                       { return !(symbol >= '0' && symbol <= '9'); }),
                  std::back_inserter(number_string));
        return SchematicNumber(std::stoi(number_string), line_pos, number_string.length(), line_num);
    }

    std::vector<SchematicNumber> ReadSchematicLine(const std::string &line, int line_num)
    {
        std::vector<SchematicNumber> numbers;
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] >= '0' && line[i] <= '9')
            {
                numbers.push_back(ReadSchematicNumber(line, i, line_num));
                i += numbers.back().num_length;
            }
        }

        return numbers;
    }

    
}

// ===[ Day Implementations ]===
namespace day_implements
{
    int dThree_pOne(std::filesystem::path path)
    {
        std::vector<SchematicNumber> nums;
        std::vector<std::string> lines;
        std::ifstream file(path);
        while(file)
        {
            std::string line;
            std::getline(file, line);
            if (!line.empty())
                lines.push_back(line);
        }

        for (int i = 0; i < lines.size(); i++)
        {
            std::vector<SchematicNumber> line_nums = ReadSchematicLine(lines[i], i);
            std::copy(line_nums.begin(), line_nums.end(), std::back_inserter(nums));
        }

        for (SchematicNumber &num : nums)
        {
            if (num.line_num != 0)
            {
                auto start = lines[num.line_num - 1].begin() + num.position;
                if (start != lines[num.line_num - 1].begin()) { --start; };
                auto end   = lines[num.line_num - 1].begin() + num.position + num.num_length;
                if (end == lines[num.line_num - 1].end()) { --end; };
                auto it = std::find_if(start, end, [](const char &symbol)
                    { return !(symbol >= '0' && symbol <= '9') && symbol != '.'; });

                if (!(*it >= '0' && *it <= '9') && *it != '.')
                {
                    num.isPart = true;
                    continue;
                }
            }

            auto start = lines[num.line_num].begin() + num.position;
            if (start != lines[num.line_num].begin()) { --start; };
            auto end   = lines[num.line_num].begin() + num.position + num.num_length;
            if (end == lines[num.line_num].end()) { --end; };
            auto it = std::find_if(start, end, [](const char &symbol)
                { return !(symbol >= '0' && symbol <= '9') && symbol != '.'; });
            
            if (!(*it >= '0' && *it <= '9') && *it != '.')
            {
                num.isPart = true;
                continue;
            }

            if (num.line_num != lines.size() - 1)
            {
                auto start = lines[num.line_num + 1].begin() + num.position;
                if (start != lines[num.line_num + 1].begin()) { --start; };
                auto end   = lines[num.line_num + 1].begin() + num.position + num.num_length;
                if (end == lines[num.line_num + 1].end()) { --end; };
                auto it = std::find_if(start, end, [](const char &symbol)
                    { return !(symbol >= '0' && symbol <= '9') && symbol != '.'; });
                
                if (!(*it >= '0' && *it <= '9') && *it != '.')
                {
                    num.isPart = true;
                    continue;
                }
            }
        }

        int part_number = 0;
        for (SchematicNumber num : nums)
        {
            if (num.isPart)
                part_number += num.number;
        }

        return part_number;
    }

    int dThree_pTwo(std::filesystem::path path)
    {
        std::vector<SchematicNumber> nums;
        std::vector<std::string> lines;
        std::ifstream file(path);
        while(file)
        {
            std::string line;
            std::getline(file, line);
            if (!line.empty())
                lines.push_back(line);
        }

        for (int i = 0; i < lines.size(); i++)
        {
            std::vector<SchematicNumber> line_nums = ReadSchematicLine(lines[i], i);
            std::copy(line_nums.begin(), line_nums.end(), std::back_inserter(nums));
        }

        std::vector<Gear> gears;
        int line_num = 0;
        for (const std::string &line : lines)
        {
            int symbol_num = 0;
            for (const char &symbol : line)
            {
                if (symbol == '*')
                {
                    std::vector<SchematicNumber> gear;
                    for (SchematicNumber &num : nums)
                    {
                        if (num.isAdjacent(lines, line_num, symbol_num))
                            gear.push_back(num);
                    }
                    if (gear.size() > 1)
                        gears.push_back(Gear(gear));
                }
                symbol_num++;
            }
            line_num++;
        }

        int ratio = 0;
        for (Gear gear : gears)
        {
            std::vector<int> gear_nums;
            std::transform(gear.numbers.begin(), gear.numbers.end(), std::back_inserter(gear_nums), [](const SchematicNumber &num){ return num.number; });
            ratio += std::accumulate(gear_nums.begin(), gear_nums.end(), 1, std::multiplies<int>());
        }

        return ratio;
    }
}