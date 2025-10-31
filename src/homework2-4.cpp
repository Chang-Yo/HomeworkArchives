#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>
bool GamePlay(void);

std::mt19937 engine(static_cast<unsigned>(
    std::chrono::high_resolution_clock::now().time_since_epoch().count()));
std::uniform_int_distribution<> dist(1, 15);
int main() {
    int times = 0;
    int count = 0;

    int* poke = new int[15];
    int** player = new int*[4];
    for (int i = 0; i < 4; i++) player[i] = new int[15];
    while (times < 1) {
        // initialize the pokes
        for (int i = 0; i < 15; i++) {
            if (i < 13)
                poke[i] = 4;
            else
                poke[i] = 1;
        }
        // initialize the player
        for (int i = 0; i < 4; i++) {
            // player[i] = new int[15];
            for (int j = 0; j < 15; j++) {
                player[i][j] = 0;
            }
        }

        // disttribute the pokes
        int poke_num = 0;
        int pos = 0;
        while (poke_num <= 10) {
            int poke_pos = dist(engine);
            if (poke[poke_pos] > 0) {
                player[pos][poke_pos]++;
                pos = (pos + 1) % 4;
                poke_num++;
                poke[poke_pos]--;  // update the number of certain poke
            } else {
                while (poke[poke_pos] = 0) poke_pos=(poke_pos+1)%15;
                player[pos][poke_pos]++;
                pos = (pos + 1) % 4;
                poke_num++;
                poke[poke_pos]--;
            }
        }

        bool result = player[0][13] && player[0][14];

        if (result) count++;

        times++;
    }

    delete[] poke;
    for (int i = 0; i < 4; i++) delete[] player[i];
    delete[] player;

    double P = count / 1000.0;
    std::cout << P << "\n";
    return 0;
}


/*
bool GamePlay(void) {
    // to initialize the poker
    int* poke = new int[15];
    for (int i = 0; i < 15; i++) {
        if (i < 13)
            poke[i] = 4;
        else
            poke[i] = 1;
    }
    // initialize the player
    int** player = new int*[4];
    for (int i = 0; i < 4; i++) {
        player[i] = new int[15];
        for (int j = 0; j < 15; j++) {
            player[i][j] = 0;
        }
    }

    // disttribute the pokes
    int poke_num = 0;
    int pos = 0;
    while (poke_num <= 54) {
        int poke_pos = dist(engine);
        if (poke[poke_pos] > 0) {
            player[pos][poke_pos]++;
            pos = (pos + 1) % 4;
            poke_num++;
            poke[poke_pos]--;  // update the number of certain poke
        } else
            continue;
    }

    bool result = player[0][13] && player[0][14];

    delete[] poke;
    for (int i = 0; i < 4; i++) delete[] player[i];
    delete[] player;

    return result;
}*/