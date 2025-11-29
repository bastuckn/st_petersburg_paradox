#include "st_petersburg_paradox.hpp"
#include <iostream>

int play_game(std::mt19937& gen, std::uniform_int_distribution<>& dist){
    int wins = 0;
    while (dist(gen)) {
        wins++;
    }
    return 1 << wins; // use bit shift for 2^wins
};

int simulation(int N_PLAYERS) {
    // variables to store results
    std::vector<int> results(N_PLAYERS);

    // run the simulation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1);
    progressbar bar(N_PLAYERS);
    for (int i=0; i < N_PLAYERS; i++) {
        bar.update();
        int winnings = play_game(gen, dist);    
        results[i] = winnings;
    }

    // calculate average at each step
    std::vector<int> sums(N_PLAYERS);
    std::vector<float> averages(N_PLAYERS);
    int sum = 0;
    for (int i = 0; i < N_PLAYERS; i++) {
        sum += results[i];
        averages[i] = static_cast<float>(sum) / (i + 1);
    }

    // graph results
    std::vector<double> x(N_PLAYERS), y(N_PLAYERS);
    for (int i = 0; i < N_PLAYERS; i++) {
        x[i] = i + 1;           // Number of games on x-axis
        y[i] = averages[i];     // Average payout on y-axis
    }
    matplot::plot(x, y);
    matplot::xlabel("Number of games");
    matplot::ylabel("Average payout");
    matplot::title("Running average - St. Petersburg Simulation");
    matplot::show();

    std::cout << "Press Enter to exit...";
    std::cin.get();
    
    return 0;
}

int main() {
    std::cout << "Enter number of games to be played for simulaiton: \n";
    int N_PLAYERS;
    std::cin >> N_PLAYERS;
    simulation(N_PLAYERS);
    return 0;
}
