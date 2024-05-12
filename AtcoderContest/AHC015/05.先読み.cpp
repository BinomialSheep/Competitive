#include <bits/stdc++.h>
// デバッグ用マクロ：https://naskya.net/post/0002/
#ifdef LOCAL
#include <debug_print.hpp>
#define debug(...) debug_print::multi_print(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (static_cast<void>(0))
#endif
using namespace std;
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
using pii = pair<int, int>;
#include <atcoder/all>
using namespace atcoder;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(x) (x).begin(), (x).end()
// #define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

template <typename T>
inline bool chmax(T &a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T &a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

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

vi f(100);

struct Solver {
  ll calcScore(vvi &maze) {
    ll ret = 0;

    dsu uf(100);
    rep(i, 10) rep(j, 10) {
      if (j < 9) {
        if (maze[i][j] != 0 && maze[i][j] == maze[i][j + 1])
          uf.merge(i * 10 + j, i * 10 + j + 1);
      }
      if (i < 9) {
        if (maze[i][j] != 0 && maze[i][j] == maze[i + 1][j])
          uf.merge(i * 10 + j, i * 10 + j + 10);
      }
    }

    for (auto g : uf.groups()) {
      if (maze[g[0] / 10][g[0] % 10] == 0) continue;
      ret += g.size() * g.size();
    }
    return ret;
  }

  double calcRating(vvi &maze) {
    double ret = 0;

    dsu uf(100);
    rep(i, 10) rep(j, 10) {
      if (j < 9) {
        if (maze[i][j] != 0 && maze[i][j + 1] != 0) {
          if (maze[i][j] == maze[i][j + 1])
            uf.merge(i * 10 + j, i * 10 + j + 1);
        } else {
          ret -= -0.01;
        }
      }
      if (i < 9) {
        if (maze[i][j] != 0 && maze[i + 1][j] != 0) {
          if (maze[i][j] == maze[i + 1][j])
            uf.merge(i * 10 + j, i * 10 + j + 10);
        } else {
          ret -= 0.01;
        }
      }
    }

    for (auto g : uf.groups()) {
      if (maze[g[0] / 10][g[0] % 10] == 0) continue;
      ret += g.size() * g.size();
    }
    return ret;
  }

  double testF(vvi maze, int idx, int f99 = 0) {
    rep(j, 10) {
      rep(k, 10) {
        rep(i, 9) {
          if (maze[i][j] == 0 && maze[i + 1][j] != 0) {
            maze[i][j] = maze[i + 1][j];
            maze[i + 1][j] = 0;
          }
        }
      }
    }
    if (f99) {
      rep(i, 10) rep(j, 10) if (maze[i][j]) {
        maze[i][j] = f99;
        break;
      }
      return calcRating(maze);
    }
    return rec(maze, 1, idx, false);
  }
  double testB(vvi maze, int f99 = 0) {
    rep(j, 10) {
      rep(k, 10) {
        for (int i = 9; i > 0; i--) {
          if (maze[i][j] == 0 && maze[i - 1][j] != 0) {
            maze[i][j] = maze[i - 1][j];
            maze[i - 1][j] = 0;
          }
        }
      }
    }
    if (f99) {
      rep(i, 10) rep(j, 10) if (maze[i][j]) {
        maze[i][j] = f99;
        break;
      }
    }
    return calcRating(maze);
  }
  double testR(vvi maze, int f99 = 0) {
    rep(i, 10) {
      rep(k, 10) {
        for (int j = 9; j > 0; j--) {
          if (maze[i][j] == 0 && maze[i][j - 1] != 0) {
            maze[i][j] = maze[i][j - 1];
            maze[i][j - 1] = 0;
          }
        }
      }
    }
    if (f99) {
      rep(i, 10) rep(j, 10) if (maze[i][j]) {
        maze[i][j] = f99;
        break;
      }
    }
    return calcRating(maze);
  }
  double testL(vvi maze, int f99 = 0) {
    rep(i, 10) {
      rep(k, 10) {
        rep(j, 9) {
          if (maze[i][j] == 0 && maze[i][j + 1] != 0) {
            maze[i][j] = maze[i][j + 1];
            maze[i][j + 1] = 0;
          }
        }
      }
    }
    if (f99) {
      rep(i, 10) rep(j, 10) if (maze[i][j]) {
        maze[i][j] = f99;
        break;
      }
    }

    return calcRating(maze);
  }

  void tiltF(vvi &maze) {
    rep(j, 10) {
      rep(k, 10) {
        rep(i, 9) {
          if (maze[i][j] == 0 && maze[i + 1][j] != 0) {
            maze[i][j] = maze[i + 1][j];
            maze[i + 1][j] = 0;
          }
        }
      }
    }
  }
  void tiltB(vvi &maze) {
    rep(j, 10) {
      rep(k, 10) {
        for (int i = 9; i > 0; i--) {
          if (maze[i][j] == 0 && maze[i - 1][j] != 0) {
            maze[i][j] = maze[i - 1][j];
            maze[i - 1][j] = 0;
          }
        }
      }
    }
  }
  void tiltR(vvi &maze) {
    rep(i, 10) {
      rep(k, 10) {
        for (int j = 9; j > 0; j--) {
          if (maze[i][j] == 0 && maze[i][j - 1] != 0) {
            maze[i][j] = maze[i][j - 1];
            maze[i][j - 1] = 0;
          }
        }
      }
    }
  }
  void tiltL(vvi &maze) {
    rep(i, 10) {
      rep(k, 10) {
        rep(j, 9) {
          if (maze[i][j] == 0 && maze[i][j + 1] != 0) {
            maze[i][j] = maze[i][j + 1];
            maze[i][j + 1] = 0;
          }
        }
      }
    }
  }
  vvi tiltF2(vvi maze) {
    rep(j, 10) {
      rep(k, 10) {
        rep(i, 9) {
          if (maze[i][j] == 0 && maze[i + 1][j] != 0) {
            maze[i][j] = maze[i + 1][j];
            maze[i + 1][j] = 0;
          }
        }
      }
    }
    return maze;
  }
  vvi tiltB2(vvi maze) {
    rep(j, 10) {
      rep(k, 10) {
        for (int i = 9; i > 0; i--) {
          if (maze[i][j] == 0 && maze[i - 1][j] != 0) {
            maze[i][j] = maze[i - 1][j];
            maze[i - 1][j] = 0;
          }
        }
      }
    }
    return maze;
  }
  vvi tiltR2(vvi maze) {
    rep(i, 10) {
      rep(k, 10) {
        for (int j = 9; j > 0; j--) {
          if (maze[i][j] == 0 && maze[i][j - 1] != 0) {
            maze[i][j] = maze[i][j - 1];
            maze[i][j - 1] = 0;
          }
        }
      }
    }
    return maze;
  }
  vvi tiltL2(vvi maze) {
    rep(i, 10) {
      rep(k, 10) {
        rep(j, 9) {
          if (maze[i][j] == 0 && maze[i][j + 1] != 0) {
            maze[i][j] = maze[i][j + 1];
            maze[i][j + 1] = 0;
          }
        }
      }
    }
    return maze;
  }

  double rec(vvi maze, int cnt, int nowI, bool flag = true) {
    double ret = 0;
    if (cnt == 0 || nowI == 99) {
      ret += testF(maze);
      ret += testB(maze);
      ret += testR(maze);
      ret += testL(maze);
      return ret / 4;
    }
    if (flag) {
      int pos = randXor() % (99 - nowI);
      int idx = -1;
      for (int cnt2 = 0; cnt < pos;) {
        idx++;
        if (maze[idx / 10][idx % 10] == 0) cnt2++;
      }
      maze[idx / 10][idx % 10] = f[nowI + 1];
    }

    ret += rec(tiltF2(maze), --cnt, ++nowI);
    ret += rec(tiltB2(maze), --cnt, ++nowI);
    ret += rec(tiltR2(maze), --cnt, ++nowI);
    ret += rec(tiltL2(maze), --cnt, ++nowI);

    return ret / 4;
  }

  void solve() {
    /* input */
    vvi maze(10, vi(10));
    rep(i, 100) cin >> f[i];

    /* solve */
    rep(i, 100) {
      int pos;
      cin >> pos;
      // debug(pos);
      // debug用
      // while (maze[pos / 10][pos % 10] != 0) {
      //   pos++;
      //   if (pos == 100) pos = 0;
      // }
      int idx = -1;
      for (int cnt = 0; cnt < pos;) {
        idx++;
        if (maze[idx / 10][idx % 10] == 0) cnt++;
      }

      maze[idx / 10][idx % 10] = f[i];
      //

      if (i <= 97) {
        int r = 0;
        // debug(testF(maze), testB(maze), testR(maze), testL(maze));
        // double score = testF(maze);
        // if (chmax(score, testB(maze))) r = 1;
        // if (chmax(score, testR(maze))) r = 2;
        // if (chmax(score, testL(maze))) r = 3;
        double score = testF(maze, i);
        if (chmax(score, testB(maze))) r = 1;
        if (chmax(score, testR(maze))) r = 2;
        if (chmax(score, testL(maze))) r = 3;

        if (r == 0) {
          tiltF(maze);
          cout << "F" << endl;
        } else if (r == 1) {
          tiltB(maze);
          cout << "B" << endl;
        } else if (r == 2) {
          tiltR(maze);
          cout << "R" << endl;
        } else {
          tiltL(maze);
          cout << "L" << endl;
        }
      }
      if (i == 98) {
        int r = 0;
        // debug(testF(maze, f[99]), testB(maze, f[99]), testR(maze, f[99]),
        //       testL(maze, f[99]));
        double score = testF(maze, f[99]);
        if (chmax(score, testB(maze, f[99]))) r = 1;
        if (chmax(score, testR(maze, f[99]))) r = 2;
        if (chmax(score, testL(maze, f[99]))) r = 3;

        if (r == 0) {
          tiltF(maze);
          cout << "F" << endl;
        } else if (r == 1) {
          tiltB(maze);
          cout << "B" << endl;
        } else if (r == 2) {
          tiltR(maze);
          cout << "R" << endl;
        } else {
          tiltL(maze);
          cout << "L" << endl;
        }
      }
      // if (i <= 20) debug(maze);
    }
    // debug(maze);

    // ll tmp = calcScore(maze);
    // ll denominator = 0;
    // vi cnt(3);
    // rep(i, 10) rep(j, 10) {
    //   assert(1 <= maze[i][j] && maze[i][j] <= 3);
    //   cnt[maze[i][j] - 1]++;
    // }
    // rep(i, 3) denominator += cnt[i] * cnt[i];
    // tmp = tmp * 1e6 / denominator;
    // debug(tmp);
  }
};

int main() {
  int ts = 1;
  rep(ti, ts) {
    Solver solver;
    solver.solve();
  }
  return 0;
}