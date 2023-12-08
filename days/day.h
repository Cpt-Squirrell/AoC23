#include <functional>
#include <filesystem>
#include <utility>
#include <chrono>
#include <string>

// ===[ Solution Forward Declarations ]===
namespace day_implements
{
    int dOne_pOne(std::filesystem::path src);
    int dOne_pTwo(std::filesystem::path src);

    int dTwo_pOne(std::filesystem::path src);
    int dTwo_pTwo(std::filesystem::path src);

    int dThree_pOne(std::filesystem::path src);
    int dThree_pTwo(std::filesystem::path src);
}

class Day
{
    int result_one, result_two;
    std::chrono::nanoseconds time_one;
    std::chrono::nanoseconds time_two;

    struct PrivateTag {};
    Day(std::string name,
        std::string description,
        std::filesystem::path src,
        std::function<int (const std::filesystem::path src)> one,
        std::function<int (const std::filesystem::path src)> two,
        PrivateTag);
    
    public:
    Day(std::string name,
        std::filesystem::path src,
        std::function<int (const std::filesystem::path src)> one = nullptr,
        std::function<int (const std::filesystem::path src)> two = nullptr);
    
    Day(std::string name,
        std::string description,
        std::filesystem::path src,
        std::function<int (const std::filesystem::path src)> one = nullptr,
        std::function<int (const std::filesystem::path src)> two = nullptr);

    void Run();
    std::pair<int, int> GetResults() const;
    std::pair<std::chrono::nanoseconds, std::chrono::nanoseconds> GetTimes() const;

    const std::string name;
    const std::string description;
    const std::filesystem::path input_file;
    const std::function<int (const std::filesystem::path src)> PartOne;
    const std::function<int (const std::filesystem::path src)> PartTwo;
};