#include <filesystem>
#include <fstream>
#include <vector>
#include <string>

// ===[ Helper Functions ]===
namespace
{
    const int CUBES_RED   = 12;
    const int CUBES_GREEN = 13;
    const int CUBES_BLUE  = 14;

    struct Game
    {
        Game(int ID):
            game_ID{ID}
        {}

        const int game_ID;

        struct Hand
        {
            Hand(int red, int green, int blue):
                cubes_red{red}, cubes_green{green}, cubes_blue{blue}
            {}

            const int cubes_red;
            const int cubes_green;
            const int cubes_blue;
        };

        std::vector<Hand> hands;

        bool isValid() const
        {
            for (Hand hand : hands)
            {
                if (hand.cubes_red > CUBES_RED ||
                    hand.cubes_green > CUBES_GREEN ||
                    hand.cubes_blue > CUBES_BLUE)
                    return false;
            }
            return true;
        }

        int CalculatePower()
        {
            int max_red = 0, max_green = 0, max_blue = 0;
            for (Hand hand : hands)
            {
                if (hand.cubes_red > max_red)
                    max_red = hand.cubes_red;
                if (hand.cubes_green > max_green)
                    max_green = hand.cubes_green;
                if (hand.cubes_blue > max_blue)
                    max_blue = hand.cubes_blue;
            }

            return max_red * max_green * max_blue;
        }

    };

    Game ReadGame(std::string line)
    {
        std::string ID_string;
        std::copy(std::find_if(line.begin(), line.end(), [](const char &symbol)
                               { return symbol >= '0' && symbol <= '9'; }),
                  std::find(line.begin(), line.end(), ':'),
                  std::back_inserter(ID_string));
        int ID = std::stoi(ID_string);
        Game game(ID);

        // Discard "game x: "
        line.erase(0, line.find(':') + 1);

        while (line.size() > 0)
        {
            // Find next semicolon or EOL
            std::string semicolon_substr;
            std::copy(line.begin(),
                      std::find(line.begin() + 1,
                                line.end(), ';'),
                      std::back_inserter(semicolon_substr));
            
            // Track number of colours
            int reds = 0, greens = 0, blues = 0;

            while (semicolon_substr.size() > 0)
            {
                // Find next comma
                std::string comma_substr;
                std::copy(semicolon_substr.begin(),
                          std::find(semicolon_substr.begin() + 1,
                                    semicolon_substr.end(), ','),
                          std::back_inserter(comma_substr));

                // Store number and colour
                std::string number, colour;
                std::copy_if(comma_substr.begin(),
                             comma_substr.end(),
                             std::back_inserter(number),
                             [](const char &symbol)
                                { return symbol >= '0' && symbol <= '9'; });
                std::copy_if(comma_substr.begin(),
                             comma_substr.end(),
                             std::back_inserter(colour),
                             [](const char &symbol)
                                {
                                    return !((symbol >= '0' && symbol <= '9') ||
                                              symbol == ' ' ||
                                              symbol == ',' ||
                                              symbol == ';');
                                });
                
                // Sort into red, green, blue
                if (colour == "red")
                    reds += std::stoi(number);
                if (colour == "green")
                    greens += std::stoi(number);
                if (colour == "blue")
                    blues += std::stoi(number);

                // Delete up 'til comma
                semicolon_substr.erase(semicolon_substr.begin(),
                                       std::find(semicolon_substr.begin() + 1,
                                       semicolon_substr.end(), ','));
            }

            // Delete the substring from line
            line.erase(line.begin(), std::find(line.begin() + 1, line.end(), ';'));

            // Add a new hand to game
            game.hands.push_back(Game::Hand(reds, greens, blues));
        }

        return game;
    }
}

// ===[ Day Implementations ]===
namespace day_implements
{
    int dTwo_pOne(std::filesystem::path path)
    {
        int game_total = 0;
        std::ifstream file(path);
        while (file)
        {
            std::string line;
            std::getline(file, line);
            if (!line.empty())
            {
                Game game = ReadGame(line);
                if (game.isValid())
                    game_total += game.game_ID;
            }
        }

        return game_total;
    }

    int dTwo_pTwo(std::filesystem::path path)
    {
        std::vector<Game> games;
        std::ifstream file(path);
        while (file)
        {
            std::string line;
            std::getline(file, line);
            if (!line.empty())
            {
                Game game = ReadGame(line);
                games.push_back(game);
            }
        }

        int power = 0;
        for (Game game : games)
        {
            power += game.CalculatePower();
        }
        return power;
    }
}