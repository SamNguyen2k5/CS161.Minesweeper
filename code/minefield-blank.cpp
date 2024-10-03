#include "minefield.hpp"
#include "context.hpp"
#include <algorithm>
#include <utility>
#include <tuple>
#include <iostream>

MinefieldBlank::MinefieldBlank(int nrow, int ncol) {
    set_white_board(nrow, ncol);
    init();
}
