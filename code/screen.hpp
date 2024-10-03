#pragma once
#include <memory>

#include <SFML/Graphics.hpp>
#include "minefield.hpp"
#include "interfaces.hpp"
#include "sidepanel.hpp"

class Screen;
class ScreenGame;
class ScreenGameLose;

class Screen :
    public sf::Drawable,
    public sf::Transformable,
    public restrict::OnEvent,
    public restrict::AlwaysUpdateGraphics
{
private:
    Screen      *pending_screen = nullptr;
    Minefield   *minefield;

public:
//    virtual ~Screen() = 0;

    virtual void    update_graphics() = 0;
    virtual void    draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
    virtual void    update_on_event(sf::Event event) = 0;
    virtual Screen* detect_change_screen() = 0;

    void        set_pending_screen(Screen *screen);
    void        clear_pending_screen();
    Screen*     get_pending_screen();

    friend class ScreenHome;
    friend class ScreenSettings;
    friend class ScreenGame;
    friend class ScreenGameLose;
    friend class ScreenGameWin;
};

class ScreenHome :
    public Screen
{
private:
    ScreenHomeSidePanel*    sidepanel;

public:
    ScreenHome();
    void        update_graphics();
    void        draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void        update_on_event(sf::Event event);
    Screen*     detect_change_screen();
};

class ScreenSettings :
    public Screen
{
private:
    ScreenSettingsSidePanel*    sidepanel;

    sf::RectangleShape      board_occupation;

public:
    ScreenSettings();
    void        update_graphics();
    void        draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void        update_on_event(sf::Event event);
    Screen*     detect_change_screen();

    void        reload_minefield();
    bool        resize_board(int new_nrow, int new_ncol, int new_nbombs);
    bool        resize_board_delta(int dx, int dy, int db);
    bool        resize_board_more_columns();
    bool        resize_board_less_columns();
    bool        resize_board_more_rows();
    bool        resize_board_less_rows();
    bool        resize_board_more_bombs();
    bool        resize_board_less_bombs();
};

class ScreenGame :
    public Screen
{
private:
    ScreenGameSidePanel*        sidepanel;

public:
    ScreenGame();
    void        update_graphics();
    void        draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void        update_on_event(sf::Event event);
	Screen*     detect_change_screen();
//    ~ScreenGame();

	bool        ask_has_lost() const;
	bool        ask_has_won() const;
};

class ScreenGameLose :
    public Screen
{
public:
    ScreenGameLoseSidePanel*     sidepanel;

    ScreenGameLose(ScreenGame* screen_game);
    void        update_graphics();
    void        draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void        update_on_event(sf::Event event);
	Screen*     detect_change_screen();
};

class ScreenGameWin :
    public Screen
{
    ScreenGameWinSidePanel*     sidepanel;

public:
    ScreenGameWin(ScreenGame* screen_game);
    void        update_graphics();
    void        draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void        update_on_event(sf::Event event);
	Screen*     detect_change_screen();
};
