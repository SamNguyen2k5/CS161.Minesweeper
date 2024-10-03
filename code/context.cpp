#include "context.hpp"

Context::Context() {}

const sf::Color& Context::GET_COLOUR_CELL(int number_under) const {
    if (number_under == -1)
        return COLOUR_CELL_BOMB;
    return COLOUR_CELLS[number_under];
}

int Context::GET_RANDOM(int min_v, int max_v) {
    return RNG() % (max_v - min_v + 1) + min_v;
}

bool Context::load_from_default() {
    // Data read-from
    WINDOW_SIZE     = sf::FloatRect(0, 0, 1600, 900);
    WINDOW_TITLE    = "Minesweeper Beta 0.1";

    BOARD_MARGIN            = 50;
    BOARD_MAXIMUM_WIDTH     = 1200;
    BOARD_ROWS              = 16;
    BOARD_COLUMNS           = 16;
    BOARD_BOMBS             = 20;
    BOARD_OUTLINE_THICKNESS = 1;

    TIMER_MARGIN            = 50;
    TIMER_FONTSIZE          = 48;

//    RANDOM_SEED     = 20050701;
    RANDOM_SEED     = time(NULL);
    RNG.seed(RANDOM_SEED);

//    if (not FONT_CELL.loadFromFile("assets/fonts/ModernDOS8x14.ttf"))
//        throw EXIT_FAILURE;
//    if (not FONT_TIMER.loadFromFile("assets/fonts/ModernDOS8x14.ttf"))
//        throw EXIT_FAILURE;
    if (not FONT_CELL.loadFromFile("assets/fonts/ModernDOS8x14.ttf"))
        return false;
    if (not FONT_TIMER.loadFromFile("assets/fonts/SpaceMono-Regular.ttf"))
        return false;
    if (not FONT_TEXT.loadFromFile("assets/fonts/SpaceMono-Regular.ttf"))
        return false;

    COLOUR_CELLS[0]     = sf::Color(0xea, 0xea, 0xea);
    COLOUR_CELLS[1]     = sf::Color(0x01, 0x00, 0xfb);
    COLOUR_CELLS[2]     = sf::Color(0x04, 0x7f, 0x03);
    COLOUR_CELLS[3]     = sf::Color::Red;
    COLOUR_CELLS[4]     = sf::Color(0x01, 0x00, 0x7f);
    COLOUR_CELLS[5]     = sf::Color(0x7c, 0x02, 0x01);
    COLOUR_CELLS[6]     = sf::Color(0x02, 0x80, 0x7f);
    COLOUR_CELLS[7]     = sf::Color(0xff, 0x7f, 0x27);
    COLOUR_CELLS[8]     = sf::Color(0xf0, 0xcb, 0x07);
    COLOUR_CELL_BOMB    = sf::Color::White;

    COLOUR_BOX_OPENED   = sf::Color(0xf0, 0xf0, 0xf0);
    COLOUR_BOX_CLOSED   = sf::Color(0x33, 0x33, 0x33);
    COLOUR_BOX_HOVERED  = sf::Color(0xff, 0xff, 0x00, 0x55);
    COLOUR_BOX_FLAGGED  = sf::Color(0xaa, 0x00, 0x00);
    COLOUR_BOX_BOMB     = sf::Color::Red;

    COLOUR_BACKGROUND_WIN   = sf::Color(0x00, 0xaa, 0x00);
    COLOUR_BACKGROUND_LOSE  = sf::Color(0xaa, 0x00, 0x00);

    COLOUR_OUTLINE      = sf::Color::White;
    COLOUR_TIMER        = sf::Color::White;
    COLOUR_TEXT         = sf::Color::White;

    if (not TEXTURE_BOMB.loadFromFile("assets/images/bomb.png"))
        return false;
    if (not TEXTURE_TICK_BOX.loadFromFile("assets/images/tick-box.png"))
        return false;
    if (not TEXTURE_FLAG_BOX.loadFromFile("assets/images/flag-box.png"))
        return false;
    if (not TEXTURE_BOMB_BOX.loadFromFile("assets/images/bomb-box.png"))
        return false;

    DEFAULT_SIZE_ROWS_EASY      = 16;
    DEFAULT_SIZE_COLUMNS_EASY   = 16;
    DEFAULT_SIZE_BOMBS_EASY     = 16 * 16 * .11;

    DEFAULT_SIZE_ROWS_MEDIUM    = 20;
    DEFAULT_SIZE_COLUMNS_MEDIUM = 25;
    DEFAULT_SIZE_BOMBS_MEDIUM   = 20 * 25 * .17;

    DEFAULT_SIZE_ROWS_HARD      = 30;
    DEFAULT_SIZE_COLUMNS_HARD   = 50;
    DEFAULT_SIZE_BOMBS_HARD     = 30 * 50 * .20;

    // Derived objects
    window_divider.setSize(sf::Vector2f(context.BOARD_OUTLINE_THICKNESS, context.WINDOW_SIZE.height));
    window_divider.setPosition(sf::Vector2f(context.BOARD_MAXIMUM_WIDTH, 0));
    window_divider.setFillColor(context.COLOUR_OUTLINE);

    global_clock = sf::Clock();
    return true;
}

bool Context::load_from_file(const std::string& filename) {
    ContextReader* reader = new ContextReader(filename);

    #define LOAD_INT(x) (x) = reader->get_int(std::string(#x));
    #define LOAD_STR(x) (x) = reader->get_str(std::string(#x));
    #define LOAD_COLOUR(x) (x) = sf::Color(reader->get_hex(std::string(#x)));
    #define LOAD_OBJ(x) \
        if (not (x).loadFromFile(reader->get_str(std::string(#x) + std::string("_PATH")))) \
            return false;

    // Data read-from
    WINDOW_SIZE     = sf::FloatRect(
        0, 0,
        reader->get_int("WINDOW_SIZE_WIDTH"),
        reader->get_int("WINDOW_SIZE_HEIGHT")
    );

    LOAD_STR    (WINDOW_TITLE)

    LOAD_INT    (BOARD_MARGIN)
    LOAD_INT    (BOARD_MAXIMUM_WIDTH)

    LOAD_INT    (BOARD_ROWS)
    LOAD_INT    (BOARD_COLUMNS)
    LOAD_INT    (BOARD_BOMBS)
    LOAD_INT    (BOARD_OUTLINE_THICKNESS)

    LOAD_INT    (TIMER_MARGIN)
    LOAD_INT    (TIMER_FONTSIZE)

    LOAD_INT    (RANDOM_SEED)
    if (RANDOM_SEED == 0)
        RANDOM_SEED = time(NULL);

    LOAD_OBJ    (FONT_CELL);
    LOAD_OBJ    (FONT_TIMER);
    LOAD_OBJ    (FONT_TEXT);

    LOAD_COLOUR (COLOUR_CELLS[0])
    LOAD_COLOUR (COLOUR_CELLS[1])
    LOAD_COLOUR (COLOUR_CELLS[2])
    LOAD_COLOUR (COLOUR_CELLS[3])
    LOAD_COLOUR (COLOUR_CELLS[4])
    LOAD_COLOUR (COLOUR_CELLS[5])
    LOAD_COLOUR (COLOUR_CELLS[6])
    LOAD_COLOUR (COLOUR_CELLS[7])
    LOAD_COLOUR (COLOUR_CELLS[8])
    LOAD_COLOUR (COLOUR_CELL_BOMB)

    LOAD_COLOUR (COLOUR_BOX_OPENED)
    LOAD_COLOUR (COLOUR_BOX_CLOSED)
    LOAD_COLOUR (COLOUR_BOX_HOVERED)
    LOAD_COLOUR (COLOUR_BOX_FLAGGED)
    LOAD_COLOUR (COLOUR_BOX_BOMB)

    LOAD_COLOUR (COLOUR_BACKGROUND_WIN)
    LOAD_COLOUR (COLOUR_BACKGROUND_LOSE)

    LOAD_COLOUR (COLOUR_OUTLINE)
    LOAD_COLOUR (COLOUR_TIMER)
    LOAD_COLOUR (COLOUR_TEXT)

    LOAD_OBJ    (TEXTURE_BOMB)
    LOAD_OBJ    (TEXTURE_CURSOR_BOX)
    LOAD_OBJ    (TEXTURE_TICK_BOX)
    LOAD_OBJ    (TEXTURE_FLAG_BOX)
    LOAD_OBJ    (TEXTURE_BOMB_BOX)

    LOAD_INT    (DEFAULT_SIZE_ROWS_EASY)
    LOAD_INT    (DEFAULT_SIZE_COLUMNS_EASY)
    LOAD_INT    (DEFAULT_SIZE_BOMBS_EASY)

    LOAD_INT    (DEFAULT_SIZE_ROWS_MEDIUM)
    LOAD_INT    (DEFAULT_SIZE_COLUMNS_MEDIUM)
    LOAD_INT    (DEFAULT_SIZE_BOMBS_MEDIUM)

    LOAD_INT    (DEFAULT_SIZE_ROWS_HARD)
    LOAD_INT    (DEFAULT_SIZE_COLUMNS_HARD)
    LOAD_INT    (DEFAULT_SIZE_BOMBS_HARD)

    // Derived objects
    RNG.seed(RANDOM_SEED);
    window_divider.setSize(sf::Vector2f(context.BOARD_OUTLINE_THICKNESS, context.WINDOW_SIZE.height));
    window_divider.setPosition(sf::Vector2f(context.BOARD_MAXIMUM_WIDTH, 0));
    window_divider.setFillColor(context.COLOUR_OUTLINE);

    global_clock = sf::Clock();

    delete reader;
    return true;

    #undef LOAD_INT
    #undef LOAD_STR
    #undef LOAD_COLOUR
    #undef LOAD_OBJ
}

Context context;
