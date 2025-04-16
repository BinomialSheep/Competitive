#pragma region header
#include <bits/stdc++.h>
using namespace std;

// デバッグ用マクロ：https://naskya.net/post/0002/
#ifdef LOCAL
#include <debug_print.hpp>
#define debug(...) debug_print::multi_print(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (static_cast<void>(0))
#endif

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(x) (x).begin(), (x).end()

template <typename T>
inline bool chmax(T& a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T& a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}
#pragma endregion header

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

static uint32_t randXor() {
  static uint32_t x = 123456789;
  static uint32_t y = 362436069;
  static uint32_t z = 521288629;
  static uint32_t w = 88675123;
  uint32_t t;

  t = x ^ (x << 11);
  x = y;
  y = z;
  z = w;
  return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

class TimeKeeper {
 private:
  chrono::high_resolution_clock::time_point start_time_;
  int64_t time_threshold_;

 public:
  // 時間制限をミリ秒単位で指定してインスタンスをつくる。
  TimeKeeper(const int64_t& time_threshold)
      : start_time_(chrono::high_resolution_clock::now()),
        time_threshold_(time_threshold) {}

  // インスタンス生成した時から指定した時間制限を超過したか判定する。
  bool isTimeOver() const {
    auto diff = chrono::high_resolution_clock::now() - this->start_time_;
    return chrono::duration_cast<chrono::milliseconds>(diff).count() >=
           time_threshold_;
  }

  int64_t getTime() const {
    auto diff = chrono::high_resolution_clock::now() - this->start_time_;
    return chrono::duration_cast<chrono::milliseconds>(diff).count();
  }
};

int input_N;
vector<int> input_saba_X(5000), input_saba_Y(5000);
vector<int> input_iwashi_X(5000), input_iwashi_Y(5000);

void process_input() {
  cin >> input_N;
  for (int i = 0; i < input_N; i++) {
    cin >> input_saba_X[i] >> input_saba_Y[i];
  }
  for (int i = 0; i < input_N; i++) {
    cin >> input_iwashi_X[i] >> input_iwashi_Y[i];
  }
}

void sort_xy() {
  vector<pair<int, int>> input_saba_XY;
  vector<pair<int, int>> input_iwashi_XY;
  input_saba_XY.reserve(input_N);
  input_iwashi_XY.reserve(input_N);
  rep(i, input_N) input_saba_XY.emplace_back(input_saba_X[i], input_saba_Y[i]);
  rep(i, input_N)
      input_iwashi_XY.emplace_back(input_iwashi_X[i], input_iwashi_Y[i]);

  sort(all(input_saba_XY));
  sort(all(input_iwashi_XY));
  rep(i, input_N) {
    input_saba_X[i] = input_saba_XY[i].first;
    input_saba_Y[i] = input_saba_XY[i].second;
  }
  rep(i, input_N) {
    input_iwashi_X[i] = input_iwashi_XY[i].first;
    input_iwashi_Y[i] = input_iwashi_XY[i].second;
  }
}

int main() {
  // 時間管理
  auto time_keeper = TimeKeeper(500);

  /* preprocessing */
  process_input();
  sort_xy();

  /* solve */

  // 乱択パート
  int loop_count = 0;
  int best_score = 0;
  int best_x1 = 0, best_x2 = 0, best_y1 = 0, best_y2 = 0;

  while (!time_keeper.isTimeOver()) {
    loop_count++;

    // サバがいる範囲で長方形を作る
    int x1 = randXor() % (int)1e5;
    int x2 = randXor() % (int)1e5;
    int y1 = randXor() % (int)1e5;
    int y2 = randXor() % (int)1e5;
    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);

    // スコア計算
    int score = 1;
    auto it = lower_bound(all(input_saba_X), x1);
    int start = (int)distance(input_saba_X.begin(), it);
    for (int i = start; i < input_N; i++) {
      if (input_saba_X[i] > x2) break;
      if (x1 <= input_saba_X[i] && y1 <= input_saba_Y[i] &&
          input_saba_Y[i] <= y2) {
        score++;
      }
    }
    it = lower_bound(all(input_iwashi_X), x1);
    start = (int)distance(input_iwashi_X.begin(), it);
    for (int i = start; i < input_N; i++) {
      if (input_iwashi_X[i] > x2) break;
      if (x1 <= input_iwashi_X[i] && y1 <= input_iwashi_Y[i] &&
          input_iwashi_Y[i] <= y2) {
        score--;
      }
    }

    // これまでのベストスコアを超えていたらx, y座標を更新
    if (best_score < score) {
      best_score = score;
      best_x1 = x1, best_x2 = x2, best_y1 = y1, best_y2 = y2;
    }
  }
  // デバッグ用出力
  cerr << "best_score: " << best_score << endl;
  cerr << "loop_count: " << loop_count << endl;

  auto time_keeper_2 = TimeKeeper(1490);
  int loop_count_2 = 0;
  while (!time_keeper_2.isTimeOver()) {
    loop_count_2++;
    //
    int x1 = best_x1;
    int x2 = best_x2;
    int y1 = best_y1;
    int y2 = best_y2;

    int ty = randXor() % 4;
    int len = randXor() % 100 - 50;
    if (ty == 0) {
      x1 += len;
    } else if (ty == 1) {
      x2 += len;
    } else if (ty == 2) {
      y1 += len;
    } else if (ty == 3) {
      y2 += len;
    }
    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);

    // スコア計算
    int score = 1;
    auto it = lower_bound(all(input_saba_X), x1);
    int start = (int)distance(input_saba_X.begin(), it);
    for (int i = start; i < input_N; i++) {
      if (input_saba_X[i] > x2) break;
      if (x1 <= input_saba_X[i] && y1 <= input_saba_Y[i] &&
          input_saba_Y[i] <= y2) {
        score++;
      }
    }
    it = lower_bound(all(input_iwashi_X), x1);
    start = (int)distance(input_iwashi_X.begin(), it);
    for (int i = start; i < input_N; i++) {
      if (input_iwashi_X[i] > x2) break;
      if (x1 <= input_iwashi_X[i] && y1 <= input_iwashi_Y[i] &&
          input_iwashi_Y[i] <= y2) {
        score--;
      }
    }

    if (best_score < score) {
      best_score = score;
      best_x1 = x1, best_x2 = x2, best_y1 = y1, best_y2 = y2;
    }
  }
  cerr << "best_score: " << best_score << endl;
  cerr << "loop_count_2: " << loop_count_2 << endl;

  /* output */
  cout << 4 << endl;
  cout << best_x1 << " " << best_y1 << endl;
  cout << best_x2 << " " << best_y1 << endl;
  cout << best_x2 << " " << best_y2 << endl;
  cout << best_x1 << " " << best_y2 << endl;
}