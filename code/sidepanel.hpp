#pragma once
#include "interfaces.hpp"

class ScreenHomeSidePanel :
    public sf::Drawable,
    public sf::Transformable,
    public restrict::OnEvent,
    public restrict::AlwaysUpdateGraphics
{
private:
    sf::Button  btn_new_game;
    sf::Button  btn_settings;

public:
    ScreenHomeSidePanel();

    void    update_graphics();
    void    draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void    update_on_event(sf::Event event);

    bool    ask_for_new_game();
    bool    ask_for_settings();
};

class ScreenSettingsSidePanel :
    public sf::Drawable,
    public sf::Transformable,
    public restrict::OnEvent,
    public restrict::AlwaysUpdateGraphics
{
private:
    sf::Text    text_nrow, text_ncol, text_times;

    sf::Button  btn_easy, btn_medium, btn_hard;
    sf::Button  btn_back;

    sf::Button  btn_more_rows, btn_less_rows;
    sf::Button  btn_more_cols, btn_less_cols;
    sf::Button  btn_more_bombs, btn_less_bombs;

public:
    ScreenSettingsSidePanel();

    void    update_graphics();
    void    draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void    update_on_event(sf::Event event);

    bool    ask_is_easy_board_chosen();
    bool    ask_is_medium_board_chosen();
    bool    ask_is_hard_board_chosen();
    bool    ask_is_back();

    bool    ask_is_more_rows();
    bool    ask_is_more_cols();
    bool    ask_is_less_rows();
    bool    ask_is_less_cols();
    bool    ask_is_more_bombs();
    bool    ask_is_less_bombs();
};

class ScreenGameSidePanel :
    public sf::Drawable,
    public sf::Transformable,
    public restrict::AlwaysUpdateGraphics,
    public restrict::OnEvent
{
private:
    Minefield*  minefield;

    sf::Clock   clock;
    sf::Text    text_clock;

    sf::Sprite  cursor_box;
    sf::Sprite  tick_box;
    sf::Sprite  flag_box;
    sf::Sprite  bomb_box;

    sf::Text    text_cnt_reveals;
    sf::Text    text_cnt_open;
    sf::Text    text_cnt_flags;
    sf::Text    text_cnt_bombs;

public:
    ScreenGameSidePanel(Minefield* minefield);

    void    update_graphics();
    void    draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void    update_on_event(sf::Event event);

    char*   get_seconds_elapsed();
    void    restart_clock();
};

class ScreenGameLoseSidePanel :
    public ScreenGameSidePanel
{
private:
    sf::RectangleShape  background_panel;

    sf::Button      btn_back;
    sf::Text        text_status;

public:
    ScreenGameLoseSidePanel(Minefield* minefield);

    void    update_graphics();
    void    draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void    update_on_event(sf::Event event);

    bool    ask_is_back();
};

class ScreenGameWinSidePanel :
    public ScreenGameSidePanel
{
private:
    sf::RectangleShape  background_panel;

    sf::Button      btn_back;
    sf::Text        text_status;

public:
    ScreenGameWinSidePanel(Minefield* minefield);

    void    update_graphics();
    void    draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void    update_on_event(sf::Event event);

    bool    ask_is_back();
};
