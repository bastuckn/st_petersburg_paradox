#include <iostream>
#include <random>

int play_game(std::mt19937 gen, std::uniform_int_distribution<> dist){
    int wins = 0;
    bool winning = true;
    while (winning==true) {
        // play game
        if (dist(gen)) {
            wins++;
        } else {
            winning = false;
        }
    }
    return std::pow(2, wins);
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1);
    for (int i=1; i < 1000000; i++){
        int winnings = play_game(gen, dist);
        std::cout << winnings << std::endl;
    }
    return 0;
}
