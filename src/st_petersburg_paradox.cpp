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
        int winnings = play_game(gen, dist);    
        results[i] = winnings;
        bar.update();
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
    std::vector<double> x(N_PLAYERS);
    for (int i = 0; i < N_PLAYERS; i++) {
        x[i] = i + 1;           // Number of games on x-axis
    }
    matplot::plot(x, averages);
    matplot::xlabel("Number of games");
    matplot::ylabel("Average payout");
    matplot::title("Running average - St. Petersburg Simulation");
    matplot::show();

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    
    return 0;
}

int main() {
    int N_PLAYERS;
    // check input:
    while (true) {
        std::cout << "Enter number of games to be played for simulation: ";
        std::cin >> N_PLAYERS;

        if (!std::cin.fail() && N_PLAYERS > 0) {
            break; // valid input!
        }

        // Bad input -> reset cin
        std::cin.clear();  // clear error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input

        std::cout << "Invalid input. Please enter a positive integer.\n";
    }
    simulation(N_PLAYERS);
    return 0;
}
