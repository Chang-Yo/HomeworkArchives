// #include <iostream>

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>
int main() {
  // 前面几次调试发现随机数生成非常离谱，遂询问LLM关于更好的随机数生成方法
  std::mt19937 engine(static_cast<unsigned>(
      std::chrono::high_resolution_clock::now().time_since_epoch().count()));
  std::uniform_int_distribution<> dist(1, 6);

  int times = 0;
  double avg_count = 0.0;

  while (times <= 5000) {
    int count = 0;
    int last_result = 0, result = 0;
    // 模拟掷骰子过程，当连续两次为6时退出重新开始一局
    while (result != 6 || last_result != result) {
      last_result = result;
      // result = dist(engine);
      result = random() % 6 + 1;
      // std::cout << "This time result :" << result << "\n";
      // std::cout << "And last result :" << last_result << "\n\n";
      count++;
    }
    // 统计平均次数
    times++;
    // std::cout << "This is the " << times << " times playing\n";
    // std::cout << "and this count is " << count << "\n";
    avg_count += (double)count / 5000.0;
  }

  std::cout << "The average is : " << (int)avg_count << "\n";
  return 0;
}