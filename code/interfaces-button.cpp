#include "interfaces.hpp"
#include <iostream>

sf::Button::Button() {}
sf::Button::Button(std::string      txt,
                   const sf::Font&  font,
                   sf::FloatRect    rect,
                   sf::Color        text_colour,
                   sf::Color        fill_colour,
                   sf::Color        hovered_fill_colour,
                   sf::Color        border_colour,
                   int              border_thickness
) {
    sf::Vector2f box_pos(rect.left, rect.top), box_size(rect.width, rect.height);

    // Box
    box.setPosition(box_pos);
    box.setSize(box_size);
    box.setFillColor(fill_colour);
    box.setOutlineColor(border_colour);
    box.setOutlineThickness(border_thickness);

    // Hovered box
    hovered_box = box;
    hovered_box.setFillColor(hovered_fill_colour);

    // Text
    text.setFont(font);
    text.setCharacterSize(box.getSize().y / 1.75f);
    text.setStyle(sf::Text::Bold);
    text.setPosition(box.getPosition() + box.getSize() / 2.f);

    text.setString(txt);
    text.setFillColor(text_colour);
    text.setOrigin(
        text.getGlobalBounds().width  * .5f,
        text.getGlobalBounds().height * .6f
    );

    // Variables
    is_hovered = false;
}

void sf::Button::setPosition(const Vector2f &position) {
    // Box
    box.setPosition(position);
    // Hovered box
    hovered_box.setPosition(position);

    // Text
    text.setPosition(box.getPosition() + box.getSize() / 2.f);
    text.setOrigin(
        text.getGlobalBounds().width  * .5f,
        text.getGlobalBounds().height * .6f
    );
}

void sf::Button::setPosition(float x, float y) {
    sf::Vector2f box_pos(x, y);

    // Box
    box.setPosition(box_pos);
    // Hovered box
    hovered_box.setPosition(box_pos);

    // Text
    text.setPosition(box.getPosition() + box.getSize() / 2.f);
    text.setOrigin(
        text.getGlobalBounds().width  * .5f,
        text.getGlobalBounds().height * .6f
    );
}

void sf::Button::setSize(const sf::Vector2f& sz) {
    // Box
    box.setSize(sz);

    // Hovered box
    hovered_box.setSize(sz);

    // Text
    text.setCharacterSize(box.getSize().y / 1.75f);
    text.setPosition(box.getPosition() + box.getSize() / 2.f);
    text.setOrigin(
        text.getGlobalBounds().width  * .5f,
        text.getGlobalBounds().height * .6f
    );
}

void sf::Button::setSize(float x, float y) {
    sf::Vector2f box_size(x, y);

    // Box
    box.setSize(box_size);

    // Hovered box
    hovered_box.setSize(box_size);

    // Text
    text.setCharacterSize(box.getSize().y / 1.75f);
    text.setPosition(box.getPosition() + box.getSize() / 2.f);
    text.setOrigin(
        text.getGlobalBounds().width  * .5f,
        text.getGlobalBounds().height * .6f
    );
}

void sf::Button::update_graphics() {

}

void sf::Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(box);
    target.draw(text);
    if (is_hovered)
        target.draw(hovered_box);
}

void sf::Button::update_on_event(sf::Event event) {
    is_clicked = false;

    if (event.type == sf::Event::MouseMoved) {
        is_hovered = box.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y);
        return;
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (not box.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
            return;

        if (event.mouseButton.button == sf::Mouse::Left) {
            is_clicked = true;
            return;
        }
    }
}

bool sf::Button::ask_is_clicked() { return is_clicked; }
bool sf::Button::ask_is_hovered() { return is_hovered; }
