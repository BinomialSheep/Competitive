#include <bits/stdc++.h>
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
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 30)
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
  printf("%d %d %d %d\n", c, r, t[c][r], ret);

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

int main() {
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
  // スコア計算
  int nowSize = calcSizeNaive(t);
  cout << nowSize << " " << round(500000 * nowSize / (N * N - 1)) << endl;

  // 初期解
  vc initAns = randomInit(blank);

  /* output */
  rep(i, T) cout << initAns[i];
  cout << endl;

  return 0;
}