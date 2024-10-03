#pragma once
#include "interfaces.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>
#include <vector>

// Pre-definition
class MinefieldCell;
class Minefield;

class MinefieldCell :
    public sf::Drawable,
    public sf::Transformable,
    public restrict::AlwaysUpdateGraphics
{
private:
    int     id_row, id_col;
    int     number_under;
    bool    is_opened, is_flagged, is_hovered;

    sf::RectangleShape  box;
    sf::RectangleShape  hovered_box;
    sf::Text            text;
    sf::Sprite          bomb;

public:
    MinefieldCell(int id_row, int id_col, sf::FloatRect rect, bool is_bomb);

    void        update_graphics();
    void        draw(sf::RenderTarget &target, sf::RenderStates states) const;

    // Getters
    int         get_number_under() const;
    bool        ask_is_opened() const;
    bool        ask_is_flagged() const;
    bool        ask_is_bomb() const;
    sf::Color   get_colour_box() const;

    // Setters
    void        update_number(std::function<void(int&)> fn);
    void        inc_number();
    void        set_bomb();

    void        set_open(bool value = true);
    void        set_hover(bool is_hovering);
    void        toggle_flag();
};

class Minefield :
    public sf::Drawable,
    public sf::Transformable,
    public restrict::OnEvent,
    public restrict::AlwaysUpdateGraphics
{
private:
    int         nrow;
    int         ncol;
    int         value_3bv, value_max_reveals;
    bool        is_bombed;

    int         cnt_reveals;
    int         cnt_open;
    int         cnt_flagged;
    int         cnt_bombs;
    int         cnt_bombs_flagged;

    std::vector<std::vector<MinefieldCell>> cell_matrix;

private:
	void        init_variables();

public:
    Minefield();
    Minefield(int nrow, int ncol);
//    virtual ~Minefield() = 0;

    void        init();

    int             get_nrow() const;
    int             get_ncol() const;
    float           get_cell_width() const;
    sf::FloatRect   get_cell_rect(int row, int col) const;
    float           get_board_horizontal_occupation() const;
    void            for_neighbours(int row, int col, std::function<void(int, int)> fn);

    float static    get_cell_width(int nrow);
    float static    get_board_horizontal_occupation(int nrow, int ncol);

    void        update_graphics();
    void        draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void        update_on_event(sf::Event event);

    void        set_white_board(int _nrow, int _ncol);
    void        set_bomb(int row, int col);

    void        open_cell(int row, int col);
    void        flag_cell(int row, int col);
    void        set_end_game_lost();

	bool        ask_has_lost() const;
	bool        ask_has_won() const;

	int         ask_count_reveals() const;
	int         ask_count_bombs() const;
	int         ask_count_bombs_flagged() const;
	int         ask_count_closed_cells() const;
	int         ask_count_opened_cells() const;
	int         ask_count_flagged_cells() const;
	int         ask_3bv() const;
	int         ask_max_reveals() const;
};

class MinefieldBlank:
    public Minefield
{
public:
    MinefieldBlank(int nrow, int ncol);
};

class MinefieldRandom :
    public Minefield
{
public:
    MinefieldRandom(int nrow, int ncol, int nbomb);
};

class MinefieldScore {
public:
    int         cells_closed;
    int         cnt_reveals;
    int         value_3bv;

    double      eff;
    std::string id_date_time;

    MinefieldScore(Minefield* minefield);
    void add_to_leaderboard();
};
