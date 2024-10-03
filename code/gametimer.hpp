#pragma once
#include <SFML/Graphics.hpp>
#include "interfaces.hpp"

class GameTimer :
    public sf::Drawable,
    public sf::Transformable,
    public restrict::AlwaysUpdateGraphics,
    public restrict::OnEvent
{
private:
    sf::Clock   clock;
    sf::Text    text;

public:
    GameTimer();

    void    update_graphics();
    void    draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void    update_on_event(sf::Event event);

    char*   get_seconds_elapsed();
};
