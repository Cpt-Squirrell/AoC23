#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

namespace day_utils
{
    std::vector<std::string> ReadLines(std::ifstream file)
    {
        std::vector<std::string> lines{};
        std::string line;
        while (file)
        {
            line.clear();
            std::getline(file, line);
            lines.push_back(line);
        }
        return lines;
    }
    
    std::string ReadFile(std::ifstream file)
    {
        std::string text{};
        std::copy(std::istreambuf_iterator<char>(file),
                  std::istreambuf_iterator<char>(),
                  std::back_inserter(text));
        return text;
    }
    std::vector<std::string> SplitString(std::string::iterator begin,
                                         std::string::iterator end,
                                         char delimiter = ' ')
    {
        std::vector<std::string::iterator> delimiters{};
        std::string::iterator begin_copy(begin);
        std::for_each(begin_copy, end, [&delimiter, &begin_copy, &delimiters](const char &symbol)
            { if (symbol == delimiter) delimiters.push_back(std::string::iterator(begin_copy)); });
        delimiters.push_back(end);
        std::vector<std::string> words{};
        std::string::iterator from{begin};
        for (std::string::iterator iter : delimiters)
        {
            std::string word{};
            std::copy(from, iter, std::back_inserter(word));
            words.push_back(word);
            if (iter != end)
                from = ++iter;
        }
        
        return words;
    }
}