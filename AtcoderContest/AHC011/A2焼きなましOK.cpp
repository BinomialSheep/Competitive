#include <bits/stdc++.h>
using namespace std;
using namespace chrono;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vb = vector<bool>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
using vvb = vector<vector<bool>>;
using vvvi = vector<vector<vector<int>>>;
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 25)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

template <typename T>
inline bool chmax(T &a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T &a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

int N;
int T;
const int TOP = 0;
const int RIGHT = 1;
const int UNDER = 2;
const int LEFT = 3;

// 0以上UINT_MAX(0xffffffff)以下の整数をとる乱数 xorshift
// https://ja.wikipedia.org/wiki/Xorshift
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

int dfs(int c, int r, vvi &t, vvi &color) {
  int ret = 0;
  color[c][r] = 1;
  if ((t[c][r] & 1) && r != 0) {
    if (color[c][r - 1] == 0 && t[c][r - 1] & 4) {
      ret += dfs(c, r - 1, t, color);
    }
  }
  if ((t[c][r] & 2) && c != 0) {
    if (color[c - 1][r] == 0 && t[c - 1][r] & 8) {
      ret += dfs(c - 1, r, t, color);
    }
  }
  if ((t[c][r] & 4) && r != N - 1) {
    if (color[c][r + 1] == 0 && t[c][r + 1] & 1) {
      ret += dfs(c, r + 1, t, color);
    }
  }
  if ((t[c][r] & 8) && c != N - 1) {
    if (color[c + 1][r] == 0 && t[c + 1][r] & 2) {
      ret += dfs(c + 1, r, t, color);
    }
  }
  color[c][r] = 2;
  ret++;

  // デバッグ出力
  // printf("%d %d %d %d\n", c, r, t[c][r], ret);

  return ret;
}

int calcSizeNaive(vvi &t) {
  // 未探索は0、探索中は1、探索済みは2
  vvi color(N, vi(N, 0));

  int size = 0;
  // 各スタート地点からdfsする
  rep(i, N) {
    rep(j, N) {
      if (color[i][j]) continue;
      int temp = dfs(i, j, t, color);
      chmax(size, temp);
    }
  }
  return size;
}

vc randomInit(vi blank) {
  vc ret(T);
  rep(i, T) {
    const int t = randXor() % 4;
    if (t == 0 && blank[0] != 0) {
      ret[i] = 'U';
      blank[0]--;
    } else if (t == 1 && blank[1] != N - 1) {
      ret[i] = 'R';
      blank[1]++;
    } else if (t == 2 && blank[0] != N - 1) {
      ret[i] = 'D';
      blank[0]++;
    } else if (t == 3 && blank[1] != 0) {
      ret[i] = 'L';
      blank[1]--;
    } else {
      i--;
    }
  }
  return ret;
}

int dfs2(int c, int r, vvi &t, vvi &color, vvvi &score, int parent) {
  if (color[c][r] == 2) return score[c][r][4];
  int sum = 0;
  color[c][r] = 1;

  if ((t[c][r] & 1) && r != 0) {
    if (t[c][r - 1] & 4) {
      // 未計算か計算済み
      if (color[c][r - 1] != 1) {
        score[c][r][LEFT] = dfs2(c, r - 1, t, color, score, RIGHT);
      } else {
        // 閉路ができている
        if (parent != LEFT) score[c][r][LEFT] = -INFTY;
      }
      sum += score[c][r][LEFT];
    }
  }
  if ((t[c][r] & 2) && c != 0) {
    if (t[c - 1][r] & 8) {
      if (color[c - 1][r] != 1) {
        score[c][r][TOP] = dfs2(c - 1, r, t, color, score, UNDER);
        sum += score[c][r][TOP];
      } else {
        if (parent != TOP) score[c][r][TOP] = -INFTY;
      }
    }
  }
  if ((t[c][r] & 4) && r != N - 1) {
    if (t[c][r + 1] & 1) {
      if (color[c][r + 1] != 1) {
        score[c][r][RIGHT] = dfs2(c, r + 1, t, color, score, LEFT);
        sum += score[c][r][RIGHT];
      } else {
        if (parent != RIGHT) score[c][r][RIGHT] = -INFTY;
      }
    }
  }
  if ((t[c][r] & 8) && c != N - 1) {
    if (t[c + 1][r] & 2) {
      if (color[c + 1][r] != 1) {
        score[c][r][UNDER] = dfs2(c + 1, r, t, color, score, TOP);
        sum += score[c][r][UNDER];
      } else {
        if (parent != UNDER) score[c][r][UNDER] = -INFTY;
      }
    }
  }

  score[c][r][4] = sum + 1;
  if (score[c][r][4] < 0) score[c][r][4] = -INFTY;
  color[c][r] = 2;

  // デバッグ出力
  // printf("%d %d %d %d %d %d\n", c, r, score[c][r][0], score[c][r][1],
  //       score[c][r][2], score[c][r][3]);

  return score[c][r][4];
}

// 差分計算を行えるように改良したスコア計算
vvvi calcSize2(vvi &t) {
  vvvi score(N, vvi(N, vi(5)));

  // 未探索は0、探索中は1、探索済みは2
  vvi color(N, vi(N, 0));

  // 各スタート地点からdfsする
  rep(i, N) {
    rep(j, N) {
      if (color[i][j]) continue;
      dfs2(i, j, t, color, score, -1);
    }
  }
  return score;
}

void scoreCalcTest(vvi t) {
  int score1 = calcSizeNaive(t);

  int score2 = 0;
  vvvi scorelist = calcSize2(t);
  rep(i, N) rep(j, N) { chmax(score2, scorelist[i][j][4]); }

  // cout << score1 << " " << score2 << endl;

  assert(score1 == score2);
}

int main() {
  // 時間計測
  auto startClock = system_clock::now();

  /* input */
  cin >> N >> T;

  vvi t(N, vi(N));
  vi blank(2);
  rep(i, N) rep(j, N) {
    char c;
    cin >> c;
    if ('0' <= c && c <= '9') {
      t[i][j] = c - '0';
      if (c == '0') {
        blank = {i, j};
      }
    } else {
      t[i][j] = c - 'a' + 10;
    }
  }

  /* solve */
  // 初期盤面のサイズ計算
  int nowSize = calcSizeNaive(t);
  // cout << nowSize << " " << round(500000 * nowSize / (N * N - 1)) << endl;
  //
  // scoreCalcTest(t);

  // 初期解
  // vc initAns = randomInit(blank);

  //
  vc ans;
  int maxSize = -1;
  int maxIndex = -1;

  const static double START_TEMP = 1500;  // 開始時の温度
  const static double END_TEMP = 100;     // 終了時の温度
  const static double END_TIME = 2.5;     // 終了時間（秒）
  double time = 0.0;                      // 経過時間（秒）

  do {
    // 進捗。開始時が0.0で、終了時が1.0
    const double progressRatio = time / END_TIME;
    const double temp = START_TEMP + (END_TEMP - START_TEMP) * progressRatio;

    // blankを移動させてみる
    const int rnd = randXor() % 4;
    // 盤面の外には移動できない
    if (rnd == TOP && blank[0] == 0) continue;
    if (rnd == RIGHT && blank[1] == N - 1) continue;
    if (rnd == UNDER && blank[0] == N - 1) continue;
    if (rnd == LEFT && blank[1] == 0) continue;

    // 変えてみる
    if (rnd == TOP) {
      swap(t[blank[0]][blank[1]], t[blank[0] - 1][blank[1]]);
      blank[0]--;
    } else if (rnd == RIGHT) {
      swap(t[blank[0]][blank[1]], t[blank[0]][blank[1] + 1]);
      blank[1]++;
    } else if (rnd == UNDER) {
      swap(t[blank[0]][blank[1]], t[blank[0] + 1][blank[1]]);
      blank[0]++;
    } else if (rnd == LEFT) {
      swap(t[blank[0]][blank[1]], t[blank[0]][blank[1] - 1]);
      blank[1]--;
    }
    // 変えた盤面でスコア計算
    int afterSize = calcSizeNaive(t);

    double deltaScore = (double)(afterSize - nowSize);
    // 焼きなまし法の遷移確率
    const double probability = exp(deltaScore / temp);

    if (probability >= rand01()) {
      nowSize = afterSize;
      if (rnd == 0)
        ans.push_back('U');
      else if (rnd == 1)
        ans.push_back('R');
      else if (rnd == 2)
        ans.push_back('D');
      else
        ans.push_back('L');
      if ((int)ans.size() == T) break;
    } else {
      // 不採用なら戻す
      if (rnd == TOP) {
        blank[0]++;
        swap(t[blank[0]][blank[1]], t[blank[0] - 1][blank[1]]);
      } else if (rnd == RIGHT) {
        blank[1]--;
        swap(t[blank[0]][blank[1]], t[blank[0]][blank[1] + 1]);
      } else if (rnd == UNDER) {
        blank[0]--;
        swap(t[blank[0]][blank[1]], t[blank[0] + 1][blank[1]]);
      } else if (rnd == LEFT) {
        blank[1]++;
        swap(t[blank[0]][blank[1]], t[blank[0]][blank[1] - 1]);
      }
    }

    // 部分最適なところを覚えておく
    if (maxSize < afterSize) {
      maxSize = afterSize;
      maxIndex = (int)ans.size();
    }

    // 時間更新
    time =
        ((double)duration_cast<microseconds>(system_clock::now() - startClock)
             .count() *
         1e-6);
  } while (time < END_TIME);

  /* output */
  rep(i, maxIndex) cout << ans[i];
  cout << endl;

  return 0;
}