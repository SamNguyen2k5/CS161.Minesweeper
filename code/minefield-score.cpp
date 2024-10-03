#include "minefield.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

MinefieldScore::MinefieldScore(Minefield *minefield) {
    // Imported values
    cells_closed = minefield->ask_count_closed_cells();
    cnt_reveals = minefield->ask_count_reveals();
    value_3bv = minefield->ask_3bv();
    int value_max_reveals = minefield->ask_max_reveals();

    // Derived values
    double rate = double(cnt_reveals - 1) / double(value_3bv);
    if (rate < 1) {
        double inv_rate = 1.0 / rate;
        eff = 1.0 / (1.0 + (inv_rate - 1.0) * (inv_rate - 1.0));
    }
    else
        eff = 0.75 / (1.0 - value_max_reveals) * (rate - 1.0) + 1.0;

    eff /= log(1 + cells_closed);
    std::cerr << "Score = " << eff << std::endl;

    const auto now = std::chrono::system_clock::now();
    const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
    id_date_time = std::ctime(&t_c);
    id_date_time.pop_back();            // Remove '\n' at the end
}

void MinefieldScore::add_to_leaderboard() {
    std::ofstream ofs("data/leaderboard.csv", std::ios::app);
    ofs << id_date_time     << ','
        << std::setprecision(6)
        << std::fixed
        << eff              << ','
        << value_3bv        << ','
        << cnt_reveals      << ','
        << cells_closed     << '\n';
    ofs.close();
}
