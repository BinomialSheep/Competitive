
#pragma region header
#include <bits/stdc++.h>
// デバッグ用マクロ：https://naskya.net/post/0002/
#ifdef LOCAL
#include <debug_print.hpp>
#define debug(...) debug_print::multi_print(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (static_cast<void>(0))
#endif
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)

template <typename T>
inline bool chmax(T& a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T& a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

#pragma endregion header
// #include <atcoder/all>
// using namespace atcoder;
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
// 0以上1未満の小数をとる乱数
static double rand01() { return (randXor() + 0.5) * (1.0 / UINT_MAX); }

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

int si, sj, ti, tj;
double p;
vector<vector<int>> G(400);
vector<vector<int>> Gdir(400);
vector<vector<int>> shortest(400);
vector<vector<int>> dist(20, vector<int>(20, 400));

string dirstr = "UDRL";
const int UP = 0, DOWN = 1, RIGHT = 2, LEFT = 3;
vector dy = {-1, 1, 0, 0};
vector dx = {0, 0, 1, -1};

// (1-p)^残りの距離
vector<double> p_pow_dist(400);
void calc_p_pow_dist() {
  p_pow_dist[0] = 1;
  rep(i, 399) { p_pow_dist[i + 1] = p_pow_dist[i] * (1 - p); }
}

void exec_input() {
  cin >> si >> sj >> ti >> tj >> p;
  rep(i, 20) {
    string h;
    cin >> h;
    rep(j, 19) {
      if (h[j] == '0') {
        G[i * 20 + j].push_back(i * 20 + j + 1);
        G[i * 20 + j + 1].push_back(i * 20 + j);
        Gdir[i * 20 + j].push_back(RIGHT);
        Gdir[i * 20 + j + 1].push_back(LEFT);
      }
    }
  }
  rep(i, 19) {
    string v;
    cin >> v;
    rep(j, 20) {
      if (v[j] == '0') {
        G[i * 20 + j].push_back((i + 1) * 20 + j);
        G[(i + 1) * 20 + j].push_back(i * 20 + j);
        Gdir[i * 20 + j].push_back(DOWN);
        Gdir[(i + 1) * 20 + j].push_back(UP);
      }
    }
  }
}

// ゴールから各地点にBFSして復元する
void calc_shortest() {
  dist[ti][tj] = 0;
  queue<pair<int, int>> q;
  q.emplace(ti, tj);
  while (q.size()) {
    auto [y, x] = q.front();
    q.pop();

    for (auto u : G[y * 20 + x]) {
      int ny = u / 20, nx = u % 20;
      if (chmin(dist[ny][nx], dist[y][x] + 1)) {
        q.emplace(ny, nx);
      }
    }
  }

  rep(y, 20) rep(x, 20) {
    for (auto u : G[y * 20 + x]) {
      int ny = u / 20, nx = u % 20;
      if (dist[ny][nx] == dist[y][x] - 1) {
        if (ny == y - 1) shortest[y * 20 + x].push_back(UP);
        if (ny == y + 1) shortest[y * 20 + x].push_back(DOWN);
        if (nx == x - 1) shortest[y * 20 + x].push_back(LEFT);
        if (nx == x + 1) shortest[y * 20 + x].push_back(RIGHT);
      }
    }
  }
}

// probから方向cに一手進めた時の確率分布を更新する
void update_probs(vector<vector<double>>& prob, char c) {
  vector<vector<double>> next_prob(20, vector<double>(20));

  rep(y, 20) rep(x, 20) {
    bool canmove = false;
    for (auto u : Gdir[y * 20 + x]) {
      if (c == 'U' && u == UP) {
        next_prob[y - 1][x] += (1. - p) * prob[y][x];
        canmove = true;
        break;
      }
      if (c == 'D' && u == DOWN) {
        next_prob[y + 1][x] += (1. - p) * prob[y][x];
        canmove = true;
        break;
      }
      if (c == 'R' && u == RIGHT) {
        next_prob[y][x + 1] += (1. - p) * prob[y][x];
        canmove = true;
        break;
      }
      if (c == 'L' && u == LEFT) {
        next_prob[y][x - 1] += (1. - p) * prob[y][x];
        canmove = true;
        break;
      }
    }
    if (canmove) {
      // 確率pで留まる
      next_prob[y][x] += p * prob[y][x];
    } else {
      next_prob[y][x] += prob[y][x];
    }
  }

  swap(next_prob, prob);
}

int calc_score(string path) {
  double ret = 0;
  // 各マスにいる確率
  vector<vector<double>> prob(20, vector<double>(20));
  prob[si][sj] = 1;

  rep(turn, path.size()) {
    update_probs(prob, path[turn]);

    ret += (400 - turn) * prob[ti][tj];
    prob[ti][tj] = 0;
  }

  return (int)round(ret * 250000);
}

// 最短距離に進む
string naive(int ny = -1, int nx = -1) {
  string ret = "";
  if (ny == -1) ny = si, nx = sj;
  while (ny != ti || nx != tj) {
    assert(min(ny, nx) >= 0);
    assert(max(ny, nx) < 20);
    assert(shortest[ny * 20 + nx].size());
    int dir = shortest[ny * 20 + nx][0];
    if (dir == UP) {
      ny--;
      ret.push_back('U');
    } else if (dir == DOWN) {
      ny++;
      ret.push_back('D');
    } else if (dir == RIGHT) {
      nx++;
      ret.push_back('R');
    } else if (dir == LEFT) {
      nx--;
      ret.push_back('L');
    }
  }

  return ret;
}
// 壁にぶつかったらもう1回進む
string naive_2(int ny = -1, int nx = -1) {
  string ret = "";
  if (ny == -1) ny = si, nx = sj;
  while (true) {
    assert(min(ny, nx) >= 0);
    assert(max(ny, nx) < 20);
    assert(shortest[ny * 20 + nx].size());
    int dir = shortest[ny * 20 + nx][0];
    if (dir == UP) {
      ny--;
      ret.push_back('U');
    } else if (dir == DOWN) {
      ny++;
      ret.push_back('D');
    } else if (dir == RIGHT) {
      nx++;
      ret.push_back('R');
    } else if (dir == LEFT) {
      nx--;
      ret.push_back('L');
    }
    if (ny == ti && nx == tj) break;
    bool kabe = 1;
    for (auto d : Gdir[ny * 20 + nx])
      if (d == dir) kabe = 0;
    if (kabe) ret.push_back(ret.back());
  }

  return ret;
}

// not use（最短方向が複数ある場合が少なすぎる）
string rand_naive(int ny = -1, int nx = -1) {
  string ret = "";
  if (ny == -1) ny = si, nx = sj;
  while (ny != ti || nx != tj) {
    assert(min(ny, nx) >= 0);
    assert(max(ny, nx) < 20);
    assert(shortest[ny * 20 + nx].size());
    int idx = randXor() % (int)shortest[ny * 20 + nx].size();
    int dir = shortest[ny * 20 + nx][idx];
    if (dir == UP) {
      ny--;
      ret.push_back('U');
    } else if (dir == DOWN) {
      ny++;
      ret.push_back('D');
    } else if (dir == RIGHT) {
      nx++;
      ret.push_back('R');
    } else if (dir == LEFT) {
      nx--;
      ret.push_back('L');
    }
  }

  return ret;
}

// pathの長さが200になるまでnaiveを続ける
string repeat_naive(string prev_path = "") {
  string path = prev_path;

  vector<vector<double>> prob(20, vector<double>(20));
  prob[si][sj] = 1;
  for (auto c : prev_path) {
    update_probs(prob, c);
    prob[ti][tj] = 0;
  }

  while ((int)path.size() < 200) {
    int my = 0, mx = 0;
    double mxp = 0;
    auto f = [&](int y, int x) {
      if (200 - (int)path.size() <= dist[y][x]) {
        return p_pow_dist[dist[y][x]] * prob[y][x] *
               (401 - (int)path.size() - dist[y][x]);
      } else {
        return prob[y][x] * 1e-100;
      }
    };

    rep(y, 20) rep(x, 20) {
      if (chmax(mxp, f(y, x))) my = y, mx = x;
    }

    string last = naive(my, mx);
    path = (path + last).substr(0, 200);
    for (auto c : last) {
      update_probs(prob, c);
      prob[ti][tj] = 0;
    }
  }

  return path;
}

// 貪欲プレイアウト
string greedy() {
  // 4方向試して、naiveを繋げたあと、ベストのやつにする
  int best_score = 0;
  string best_path;

  string now_path = "";
  while (now_path.size() < 20) {
    int maxdir = -1;
    int now_max_score = 0;
    rep(di, 4) {
      now_path.push_back(dirstr[di]);

      string path = repeat_naive(now_path);

      if (chmax(now_max_score, calc_score(path))) {
        maxdir = di;
        if (chmax(best_score, now_max_score)) best_path = path;
      }

      // 戻す
      now_path.pop_back();
    }
    // debug(best_score, now_max_score);
    now_path.push_back(dirstr[maxdir]);
  }
  return best_path;
}

// -sum(確率*距離) + α * ゴール確率 の昇順で選ぶ貪欲
string greedy_3() {
  string now_path = "";
  vector<vector<double>> prob(20, vector<double>(20));
  prob[si][sj] = 1;

  // -sum(確率*距離)
  auto calc_sum_value = [&](vector<vector<double>>& now_prob) {
    double ret = 0;
    rep(y, 20) rep(x, 20) { ret += now_prob[y][x] * dist[y][x]; }
    return -ret;
  };

  while (now_path.size() < 200) {
    char max_c = '0';
    double max_val = -1e18;
    for (auto c : dirstr) {
      vector<vector<double>> prob_clone = prob;
      update_probs(prob_clone, c);

      double now_val = prob_clone[ti][tj] * 10;
      now_val += calc_sum_value(prob_clone);
      // debug(c, now_val);
      if (chmax(max_val, now_val)) max_c = c;
    }
    // debug(max_val);
    update_probs(prob, max_c);
    prob[ti][tj] = 0;
    now_path.push_back(max_c);
    // break;
  }

  return now_path;
}

// 今はgreedy3と同じ評価関数を採用
class State {
 public:
  double evaluated_score_ = 0;
  string now_path_ = "";
  vector<vector<double>> prob_;

  State() : prob_(20, vector<double>(20)) {}

  void evaluateScore() {
    rep(y, 20) rep(x, 20) this->evaluated_score_ -= prob_[y][x] * dist[y][x];

    ;
  }

  void advance(const char action) {
    this->now_path_.push_back(action);
    update_probs(prob_, action);
    evaluated_score_ = prob_[ti][tj] * 10;
    prob_[ti][tj] = 0;
  }
};

bool operator<(const State& state_1, const State& state_2) {
  return state_1.evaluated_score_ < state_2.evaluated_score_;
}

string chokudai_search(const int beam_width = 50, const int beam_depth = 50,
                       const int64_t time_threshold = 1650) {
  auto time_keeper = TimeKeeper(time_threshold);
  auto beam = vector<priority_queue<State>>(beam_depth + 1);
  rep(t, beam_depth + 1) beam[t] = priority_queue<State>();
  State init_state;
  init_state.evaluated_score_ = 0;
  init_state.now_path_ = "";
  init_state.prob_[si][sj] = 1;
  beam[0].push(init_state);

  int turn_count = 0;
  for (; !time_keeper.isTimeOver(); turn_count++) {
    rep(t, beam_depth) {
      if (time_keeper.isTimeOver()) break;
      auto& now_beam = beam[t];
      auto& next_beam = beam[t + 1];

      for (int i = 0; i < beam_width; i++) {
        if (time_keeper.isTimeOver()) break;
        if (now_beam.empty()) break;
        State now_state = now_beam.top();
        now_beam.pop();

        for (const auto& action : dirstr) {
          State next_state = now_state;
          next_state.advance(action);
          next_state.evaluateScore();
          next_beam.push(next_state);
        }
      }
    }
  }
  for (int t = beam_depth; t >= 0; t--) {
    const auto& now_beam = beam[t];
    if (!now_beam.empty()) {
      string path = now_beam.top().now_path_;
      debug(path.size());
      path = repeat_naive(path);
      return path;
    }
  }
  return "";
}

string annealing() {
  const int time_threshold = 1980;
  auto time_keeper = TimeKeeper(time_threshold);

  string path = naive_2();
  // string path = naive();
  int now_score = calc_score(path);

  double start_temp = 5e3;  // 開始時の温度
  double end_temp = 1e2;    // 終了時の温度
  double progress_ratio =
      (double)time_keeper.getTime() / (double)time_threshold;
  double temp = start_temp + (end_temp - start_temp) * progress_ratio;
  double probability = 0;
  double time_threshold_inv = 1 / (double)time_threshold;

  int loop_count = 0;
  while (true) {
    loop_count++;

    if (loop_count % 64 == 0) {
      if (time_keeper.isTimeOver()) break;
      progress_ratio = (double)time_keeper.getTime() * time_threshold_inv;
      temp = start_temp + (end_temp - start_temp) * progress_ratio;
    }

    int pat = randXor() % 3;
    string next_path = path;

    if (pat == 0) {
      if (path.size() == 200) {
        debug("追加不可");
        continue;
      }
      // 追加近傍
      char c = dirstr[randXor() % 4];
      int idx = randXor() % (int)path.size();
      next_path.insert(next_path.begin() + idx, c);
    } else if (pat == 1) {
      // 変更近傍
      int idx = randXor() % (int)path.size();
      char c = dirstr[randXor() % 4];
      while (c != next_path[idx]) c = dirstr[randXor() % 4];
      next_path[idx] = c;
    } else {
      // 削除近傍
      if (path.size() == 0) {
        debug("削除不可");
        continue;
      }
      int idx = randXor() % (int)path.size();
      next_path.erase(next_path.begin() + idx);
    }

    int next_score = calc_score(next_path);

    probability = exp((double)(next_score - now_score) / temp);
    // debug(next_score - now_score);
    if (probability >= rand01()) {
      // if (next_score >= now_score) {
      // debug(next_score, path.size());
      now_score = next_score;
      path = next_path;
    }
  }
  cerr << "loop_count: " << loop_count << endl;
  cerr << "now_score: " << now_score << endl;
  // 200まで伸ばす
  path = repeat_naive(path);
  cerr << "final_score: " << calc_score(path) << endl;

  return path;
}

int main() {
  exec_input();
  calc_shortest();
  calc_p_pow_dist();

  // string ans_path = annealing();

  // string ans_naive = naive();
  // debug(calc_score(ans_naive));
  // debug(calc_score(naive_2()));

  // string ans_repeat_naive = repeat_naive();
  // debug(calc_score(ans_repeat_naive));

  // string ans_greedy = greedy();
  // debug(calc_score(ans_greedy));

  // string ans_greedy_2 = greedy_2();
  // debug(calc_score(ans_greedy_2));

  // string ans_naive_3 = greedy_3();
  // debug(calc_score(ans_naive_3));

  string ans_chokudai_search = chokudai_search(100, 200);
  debug(calc_score(ans_chokudai_search));

  cout << ans_chokudai_search << endl;
}