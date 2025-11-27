#include <st_petersburg_paradox.hpp>

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
};

int simulation() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1);
    progressbar bar(100000);
    for (int i=1; i < 100000; i++){
        bar.update();
        int winnings = play_game(gen, dist);
    }
    return 0;
}

int main() {
    simulation();
    return 0;
}
