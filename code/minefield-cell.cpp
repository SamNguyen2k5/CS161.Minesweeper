#include "minefield.hpp"
#include "context.hpp"
#include <iostream>

MinefieldCell::MinefieldCell(int id_row, int id_col, sf::FloatRect rect, bool is_bomb):
    id_row(id_row),
    id_col(id_col),
    number_under(is_bomb ? -1 : 0),
    is_opened(false),
    is_flagged(false),
    is_hovered(false)
{
    sf::Vector2f box_pos(rect.left, rect.top), box_size(rect.width, rect.height);

    // Box
    box.setPosition(box_pos);
    box.setSize(box_size);
    box.setFillColor(get_colour_box());
    box.setOutlineColor(context.COLOUR_OUTLINE);
    box.setOutlineThickness(context.BOARD_OUTLINE_THICKNESS);

    // Hovered box
    hovered_box = box;
    hovered_box.setFillColor(context.COLOUR_BOX_HOVERED);

    // Text
    text.setFont(context.FONT_CELL);
    text.setCharacterSize(box.getSize().y / 1.75f);
    text.setStyle(sf::Text::Bold);
    text.setPosition(box.getPosition() + box.getSize() / 2.f);

    // Bomb
    bomb.setTexture(context.TEXTURE_BOMB);
    float rate = box_size.y / bomb.getGlobalBounds().height / 1.6f;
    bomb.setScale(rate, rate);
    sf::Vector2f bomb_size(
        bomb.getGlobalBounds().width,
        bomb.getGlobalBounds().height
    );
    bomb.setPosition(box_pos + box_size / 2.f - bomb_size / 2.f);
}

void MinefieldCell::update_graphics() {
    box.setFillColor(get_colour_box());

    text.setFillColor(context.GET_COLOUR_CELL(number_under));
    text.setString(std::to_string(number_under));
    text.setOrigin(
        text.getGlobalBounds().width  / 2.f,
        text.getGlobalBounds().height
    );
}

void MinefieldCell::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(box);                       // Layer 1:  box

    if (is_opened and number_under != -1)
        target.draw(text);                  // Layer 2a: text

    if (is_opened and number_under == -1)
        target.draw(bomb);

    if (is_hovered)
        target.draw(hovered_box);
}

int MinefieldCell::get_number_under() const { return number_under; }
bool MinefieldCell::ask_is_opened() const { return is_opened; }
bool MinefieldCell::ask_is_flagged() const { return is_flagged; }
bool MinefieldCell::ask_is_bomb() const { return number_under == -1; }

sf::Color MinefieldCell::get_colour_box() const {
    if (is_opened)
        return (number_under == -1)
            ? context.COLOUR_BOX_BOMB
            : context.COLOUR_BOX_OPENED;
    if (is_flagged)
        return context.COLOUR_BOX_FLAGGED;
    return context.COLOUR_BOX_CLOSED;
}

void MinefieldCell::update_number(std::function<void(int&)> fn) { fn(number_under); }
void MinefieldCell::inc_number() { ++number_under; }
void MinefieldCell::set_bomb() { number_under = -1; }
void MinefieldCell::set_open(bool value) { is_opened = value; }
void MinefieldCell::set_hover(bool is_hovering) { is_hovered = is_hovering; }
void MinefieldCell::toggle_flag() { is_flagged = not is_flagged; }
