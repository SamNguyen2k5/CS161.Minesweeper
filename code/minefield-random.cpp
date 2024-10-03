#include "minefield.hpp"
#include "context.hpp"
#include <algorithm>
#include <utility>
#include <tuple>
#include <iostream>

MinefieldRandom::MinefieldRandom(int nrow, int ncol, int nbomb) {
    set_white_board(nrow, ncol);

    std::vector<std::pair<int, int>> cells_id;
    for (int row = 0; row < nrow; row++)
    for (int col = 0; col < ncol; col++)
        cells_id.emplace_back(row, col);
    shuffle(cells_id.begin(), cells_id.end(), context.RNG);

    for (int i = 0; i < nbomb; i++) {
        int row, col;
        std::tie(row, col) = cells_id.at(i);
        set_bomb(row, col);
    }

    init();
}
