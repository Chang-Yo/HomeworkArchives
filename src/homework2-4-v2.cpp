#include <algorithm>
#include <chrono>
// #include <cstdlib>
#include <iostream>
#include <random>

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

int main() {
    int times = 0;
    int count = 0;
    int poke[54];
    // 将牌堆平铺
    for (int i = 0, j = 0; i < 52; i++, j++) {
        poke[i] = j / 4 + 1;
    }
    poke[52] = 14;
    poke[53] = 15;

    int randNum[54];
    for (int i = 0; i < 54; i++) randNum[i] = i;

    int** player = new int*[4];
    for (int i = 0; i < 4; i++) player[i] = new int[15];

    int pos = 0;
    while (times < 1000) {
        // 用乱序数组来模拟随机发牌
        std::shuffle(randNum, randNum + 53, std::default_random_engine(seed));

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 15; j++) {
                player[i][j] = 0;
            }
        }
        for (int i = 0; i < 54; i++) {
            int poke_pos = randNum[i];
            player[pos][poke[poke_pos] - 1]++;
            pos = (pos + 1) % 4;
        }

        bool result = player[0][13] && player[0][14];

        if (result) count++;

        times++;
    }

    for (int i = 0; i < 4; i++) delete[] player[i];
    delete[] player;
    double P = count / 1000.0;
    std::cout << P << "\n";
    return 0;
}