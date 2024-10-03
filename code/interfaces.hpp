#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace restrict {
    class OnEvent {
    public:
        virtual void update_on_event(sf::Event event);
    };

    class AlwaysUpdateGraphics {
    public:
        virtual void update_graphics();
    };
}

namespace sf {
    class Button :
        public sf::Drawable,
        public sf::Transformable,
        public restrict::AlwaysUpdateGraphics,
        public restrict::OnEvent
    {
    private:
        sf::Text                text;
        sf::RectangleShape      box;
        sf::RectangleShape      hovered_box;

        bool                    is_hovered;
        bool                    is_clicked;

    public:
        Button();
        Button(std::string      txt,
               const sf::Font&  font,
               sf::FloatRect    rect,
               sf::Color        text_colour,
               sf::Color        fill_colour,
               sf::Color        hovered_fill_colour,
               sf::Color        border_colour,
               int              border_thickness
        );

        void update_graphics    ();
        void draw               (sf::RenderTarget &target, sf::RenderStates states) const;
        void update_on_event    (sf::Event event);

        void setPosition        (const sf::Vector2f &position);
        void setPosition        (float x, float y);
        void setSize            (const sf::Vector2f &sz);
        void setSize            (float x, float y);

        bool ask_is_hovered     ();
        bool ask_is_clicked     ();
    };

    template <class T>
    void setOriginCenterBox(T& obj) {
        obj.setOrigin(
            obj.getGlobalBounds().width  * .5f,
            obj.getGlobalBounds().height * .5f
        );
    }

    template <class T>
    void setOriginCenter(T& obj) {
        obj.setOrigin(
            obj.getGlobalBounds().width  * .5f,
            obj.getGlobalBounds().height * .6f
        );
    }
}
