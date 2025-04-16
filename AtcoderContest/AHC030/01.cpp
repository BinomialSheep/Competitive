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

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(x) (x).begin(), (x).end()

// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

template <typename T>
inline bool chmax(T& a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T& a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

// #include <atcoder/all>
// using namespace atcoder;

int N, M;
double epsilon;
vector<vector<pair<int, int>>> input_shape;

void exec_input() {
  cin >> N >> M >> epsilon;
  input_shape.resize(M);
  rep(i, M) {
    int d;
    cin >> d;
    input_shape[i].resize(d);
    rep(j, d) { cin >> input_shape[i][j].first >> input_shape[i][j].second; }
  }
}

class Action {
 public:
  char type;
  int d = 0;
  vector<pair<int, int>> vec;

  Action() {}

  int print() {
    cout << type << " " << d << " ";
    rep(i, d) {
      cout << vec[i].first << " " << vec[i].second;
      if (i == d - 1) {
        cout << endl;
      } else {
        cout << " ";
      }
    }
    int ret;
    cin >> ret;
    return ret;
  }
};

void naive() {
  Action ans;
  ans.type = 'a';

  rep(i, N) rep(j, N) {
    Action action;
    action.type = 'q';
    action.d = 1;
    action.vec.emplace_back(i, j);

    int v = action.print();
    if (v) {
      ans.d++;
      ans.vec.emplace_back(i, j);
    }
  }
  int v = ans.print();
  assert(v);
}

int main() {
  exec_input();

  naive();
}