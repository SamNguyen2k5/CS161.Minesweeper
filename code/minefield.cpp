#include "minefield.hpp"
#include "context.hpp"
#include <iostream>
#include <iomanip>

Minefield::Minefield() {}

Minefield::Minefield(int nrow, int ncol) {
    set_white_board(nrow, ncol);
}

void Minefield::init_variables() {
    is_bombed = false;
    cnt_reveals = 0;
    cnt_open = 0;
    cnt_flagged = 0;
    cnt_bombs = 0;
    cnt_bombs_flagged = 0;

    for (int row = 0; row < nrow; row++)
    for (int col = 0; col < ncol; col++) {
        MinefieldCell &cell = cell_matrix.at(row).at(col);
        if (cell.ask_is_bomb() and cell.ask_is_flagged())
            cnt_bombs_flagged++;

        if (cell.ask_is_bomb())
            cnt_bombs++;

        if (cell.ask_is_opened())
            cnt_open++;
    }
}

void Minefield::init() {
    init_variables();
    value_3bv = value_max_reveals = 0;

    for (int row = 0; row < nrow; row++)
    for (int col = 0; col < ncol; col++) {
        MinefieldCell &cell = cell_matrix.at(row).at(col);
        if (cell.ask_is_opened())
            continue;
        if (cell.get_number_under() != 0)
            continue;
        open_cell(row, col);
        value_3bv++;
        value_max_reveals++;
    }

    for (int row = 0; row < nrow; row++)
    for (int col = 0; col < ncol; col++) {
        MinefieldCell &cell = cell_matrix.at(row).at(col);
        if (cell.get_number_under() > 0)
            value_max_reveals++;
        if (cell.ask_is_opened())
            continue;
        if (cell.get_number_under() > 0)
            value_3bv++;
    }

//    std::cerr << "value_3bv = " << value_3bv << std::endl;

    for (int row = 0; row < nrow; row++)
    for (int col = 0; col < ncol; col++) {
        MinefieldCell &cell = cell_matrix.at(row).at(col);
        cell.set_open(false);
    }

    init_variables();
}

int Minefield::get_nrow() const { return nrow; }
int Minefield::get_ncol() const { return ncol; }
float Minefield::get_cell_width() const {
    return (context.WINDOW_SIZE.height - 2.f * context.BOARD_MARGIN) / nrow;
}

sf::FloatRect Minefield::get_cell_rect(int row, int col) const {
    float width = get_cell_width();
    return sf::FloatRect(
        context.BOARD_MARGIN + col * width,
        context.BOARD_MARGIN + row * width,
        width,
        width
    );
}

float Minefield::get_board_horizontal_occupation() const {
    return 2 * context.BOARD_MARGIN + ncol * get_cell_width();
}

float Minefield::get_cell_width(int nrow) {
    return (context.WINDOW_SIZE.height - 2.f * context.BOARD_MARGIN) / nrow;
}

float Minefield::get_board_horizontal_occupation(int nrow, int ncol) {
    return 2 * context.BOARD_MARGIN + ncol * Minefield::get_cell_width(nrow);
}

void Minefield::for_neighbours(int row, int col, std::function<void(int, int)> fn) {
    for (int dx = -1; dx <= +1; dx++)
    for (int dy = -1; dy <= +1; dy++) {
        if (dx == 0 and dy == 0)
            continue;
        if (row + dx < 0 or row + dx >= nrow)
            continue;
        if (col + dy < 0 or col + dy >= ncol)
            continue;
        fn(row + dx, col + dy);
    }
}

void Minefield::update_graphics() {
    for (int row = 0; row < nrow; row++)
    for (int col = 0; col < ncol; col++)
        cell_matrix.at(row).at(col).update_graphics();
}

void Minefield::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (int row = 0; row < nrow; row++)
    for (int col = 0; col < ncol; col++)
        target.draw(cell_matrix.at(row).at(col));
}

void Minefield::update_on_event(sf::Event event) {
    // Apply event to each cell
    for (int row = 0; row < nrow; row++)
    for (int col = 0; col < ncol; col++) {
        MinefieldCell &cell = cell_matrix.at(row).at(col);

        if (event.type == sf::Event::MouseMoved) {
            bool is_hovering = get_cell_rect(row, col).contains(event.mouseMove.x, event.mouseMove.y);
            cell.set_hover(is_hovering);
            continue;
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            bool is_in_cell = get_cell_rect(row, col).contains(event.mouseButton.x, event.mouseButton.y);
            if (not is_in_cell)
                continue;

            if (event.mouseButton.button == sf::Mouse::Right) {
                flag_cell(row, col);
                continue;
            }

            if (event.mouseButton.button == sf::Mouse::Left) {
                if (cell.ask_is_flagged()) {
                    flag_cell(row, col);
                    continue;
                }

                if (cell.ask_is_opened()) {
                    for_neighbours(row, col, [&](int i, int j) {
                        if (cell_matrix.at(i).at(j).ask_is_flagged())
                            return;

                        if (not cell_matrix.at(i).at(j).ask_is_opened())
                            cnt_reveals++;
                        open_cell(i, j);
                    });

                    continue;
                }

                open_cell(row, col);
                cnt_reveals++;
                continue;
            }

            continue;
        }
    }
}

void Minefield::set_white_board(int _nrow, int _ncol) {
    nrow = _nrow;
    ncol = _ncol;
    cell_matrix.resize(nrow);
    for (int row = 0; row < nrow; row++) {
        std::vector<MinefieldCell> cell_row;
        for (int col = 0; col < ncol; col++)
            cell_row.push_back(MinefieldCell(row, col, get_cell_rect(row, col), false));
        swap(cell_row, cell_matrix.at(row));
    }
}

void Minefield::set_bomb(int row, int col) {
    if (cell_matrix.at(row).at(col).ask_is_bomb())
        return;

    cell_matrix.at(row).at(col).set_bomb();
    for_neighbours(row, col, [&](int i, int j) {
        if (cell_matrix.at(i).at(j).ask_is_bomb())
            return;

        cell_matrix.at(i).at(j).inc_number();
    });
}

void Minefield::open_cell(int row, int col) {
    MinefieldCell &cell = cell_matrix.at(row).at(col);
    if (cell.ask_is_opened())
        return;

    cell.set_open();
    cnt_open++;

    if (cell.ask_is_bomb()) {
        is_bombed = true;
        return;
    }

    if (cell.get_number_under() != 0)
        return;

    for_neighbours(row, col, [&](int i, int j) {
        MinefieldCell &next_cell = cell_matrix.at(i).at(j);
        if (next_cell.ask_is_opened())
            return;
        if (next_cell.ask_is_flagged())
            return;
        if (next_cell.ask_is_bomb())
            return;

        open_cell(i, j);
    });
}

void Minefield::flag_cell(int row, int col) {
    MinefieldCell &cell = cell_matrix.at(row).at(col);
    bool flag = not cell.ask_is_flagged();

    if (not flag) {
        cnt_flagged--;
        if (cell.ask_is_bomb())
            cnt_bombs_flagged--;
    }

    cell.toggle_flag();

    if (flag) {
        cnt_flagged++;
        if (cell.ask_is_bomb())
            cnt_bombs_flagged++;
    }
}

void Minefield::set_end_game_lost() {
    for (int row = 0; row < nrow; row++)
    for (int col = 0; col < ncol; col++) {
        MinefieldCell &cell = cell_matrix.at(row).at(col);
        cell.set_hover(false);
        if (cell.ask_is_bomb())
            cell.set_open();
    }
}

bool Minefield::ask_has_lost() const { return is_bombed; }
bool Minefield::ask_has_won() const {
	return not is_bombed                                // Not bombed; and
	       and cnt_open == nrow * ncol - cnt_bombs      // Only bombs open; and
	       and cnt_bombs_flagged == cnt_bombs;          // All bombs flagged
}

int Minefield::ask_count_reveals() const { return cnt_reveals; }
int Minefield::ask_count_bombs() const { return cnt_bombs; }
int Minefield::ask_count_bombs_flagged() const { return cnt_bombs_flagged; }
int Minefield::ask_count_opened_cells() const { return cnt_open; }
int Minefield::ask_count_closed_cells() const { return nrow * ncol - cnt_bombs - cnt_open; }
int Minefield::ask_count_flagged_cells() const { return cnt_flagged; }
int Minefield::ask_3bv() const { return value_3bv; }
int Minefield::ask_max_reveals() const { return value_max_reveals; }
