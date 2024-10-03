#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <random>
#include <string>
#include <map>

class ContextReader {
private:
    std::map<std::string, int> mp_int;
    std::map<std::string, unsigned int> mp_hex;
    std::map<std::string, std::string> mp_str;

public:
    ContextReader();
    ContextReader(const std::string& filename);

    void report_error();
    void load_file(const std::string& filename);
    void load_file(const char* filename);

    int get_int(const std::string& token);
    int get_int(const char* token);
    unsigned int get_hex(const std::string& token);
    unsigned int get_hex(const char* token);
    std::string get_str(const std::string& token);
    std::string get_str(const char* token);
};

class Context {
public:
    sf::FloatRect           WINDOW_SIZE;
    std::string             WINDOW_TITLE;

    int                     BOARD_MARGIN;
    int                     BOARD_MAXIMUM_WIDTH;
    int                     BOARD_ROWS;
    int                     BOARD_COLUMNS;
    int                     BOARD_BOMBS;
    int                     BOARD_OUTLINE_THICKNESS;

    int                     TIMER_MARGIN;
    int                     TIMER_FONTSIZE;

    int                     RANDOM_SEED;
    std::mt19937            RNG;

    sf::Font                FONT_CELL;
    sf::Font                FONT_TIMER;
    sf::Font                FONT_TEXT;

    std::array<sf::Color, 9>    COLOUR_CELLS;
    sf::Color                   COLOUR_CELL_BOMB;

    sf::Color                   COLOUR_BOX_OPENED;
    sf::Color                   COLOUR_BOX_CLOSED;
    sf::Color                   COLOUR_BOX_HOVERED;
    sf::Color                   COLOUR_BOX_FLAGGED;
    sf::Color                   COLOUR_BOX_BOMB;

    sf::Color                   COLOUR_BACKGROUND_WIN;
    sf::Color                   COLOUR_BACKGROUND_LOSE;

    sf::Color                   COLOUR_OUTLINE;
    sf::Color                   COLOUR_TIMER;
    sf::Color                   COLOUR_TEXT;

    sf::Texture                 TEXTURE_BOMB;
    sf::Texture                 TEXTURE_CURSOR_BOX;
    sf::Texture                 TEXTURE_TICK_BOX;
    sf::Texture                 TEXTURE_FLAG_BOX;
    sf::Texture                 TEXTURE_BOMB_BOX;

    int                     DEFAULT_SIZE_ROWS_EASY;
    int                     DEFAULT_SIZE_COLUMNS_EASY;
    int                     DEFAULT_SIZE_BOMBS_EASY;

    int                     DEFAULT_SIZE_ROWS_MEDIUM;
    int                     DEFAULT_SIZE_COLUMNS_MEDIUM;
    int                     DEFAULT_SIZE_BOMBS_MEDIUM;

    int                     DEFAULT_SIZE_ROWS_HARD;
    int                     DEFAULT_SIZE_COLUMNS_HARD;
    int                     DEFAULT_SIZE_BOMBS_HARD;

public:
    sf::RectangleShape      window_divider;
    sf::Clock               global_clock;

public:
    Context();
    const sf::Color& GET_COLOUR_CELL(int number_under) const;
    int GET_RANDOM(int min_v, int max_v);

    bool load_from_default();
    bool load_from_file(const std::string& filename);
};

extern Context context;
