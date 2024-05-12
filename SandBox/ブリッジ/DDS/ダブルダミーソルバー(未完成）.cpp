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
// #include <atcoder/all>
// using namespace atcoder;
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

struct Solver {
  void solve() {
    /* input */
    // North[0] := Northのスペードのリスト
    vvi NorthHand(4);
    vvi SouthHand(4);
    vvi EastHand(4);
    vvi WestHand(4);

    // ハンドの入力（2NT by West -1）
    {
      const int A = 14;
      const int K = 13;
      const int Q = 12;
      const int J = 11;
      const int T = 10;
      NorthHand = {{8, 5, 3, 2}, {A, T, 5}, {A, 9}, {K, J, T, 5}};
      EastHand = {{A, 7, 6, 4}, {J, 9, 4}, {7, 4}, {6, 4, 3, 2}};
      SouthHand = {{Q, 9}, {Q, 6, 3, 2}, {J, T, 6, 5}, {9, 8, 7}};
      WestHand = {{K, J, T}, {K, 8, 7}, {K, Q, 8, 3, 2}, {A, Q}};
    }
    // ハンドが正しいか
    {
      // カードが13枚ずつあるかチェック
      auto assert13 = [](vvi &hand) {
        int cnt = 0;
        rep(i, 4) cnt += (int)hand[i].size();
        assert(cnt == 13);
      };
      assert13(NorthHand);
      assert13(SouthHand);
      assert13(EastHand);
      assert13(WestHand);
      // カードが漏れなくダブりないかチェック
      vb cards(57);
      auto assert52 = [&](vvi &hand) {
        rep(i, 4) {
          for (auto card : hand[i]) {
            if (cards[i * 14 + card]) {
              assert(false);
            } else {
              cards[i * 14 + card] = true;
            }
          }
        }
      };
      assert52(NorthHand);
      assert52(SouthHand);
      assert52(EastHand);
      assert52(WestHand);
    }
    // ハンドの正規化
    vi North;
    vi East;
    vi South;
    vi West;
    rep(i, 4) for (auto card : NorthHand[i]) North.push_back(13 * i + card);
    rep(i, 4) for (auto card : EastHand[i]) East.push_back(13 * i + card);
    rep(i, 4) for (auto card : SouthHand[i]) South.push_back(13 * i + card);
    rep(i, 4) for (auto card : WestHand[i]) West.push_back(13 * i + card);

    /* solve */
    auto next = [](char now) {
      if (now == 'N') return 'E';
      if (now == 'E') return 'S';
      if (now == 'S') return 'W';
      return 'N';
    };

    vvb used(4, vb(13));

    auto isLegal = [&](int color, int dir, vi &cards, int idx) {
      // リードスートをフォローしているならOK
      if (cards[idx] / 14 == color) return true;
      //フォローできないならOK
      rep(i, 13) {
        if (!used[dir][i] && cards[i] / 14 == color) return false;
      }
      return true;
    };

    auto rec = [&](auto f, int count, int color, char nowTurn, char strongDir,
                   int strongCard, int winner) -> int {
      // 1巡終わり
      if (count % 4 == 1 && strongCard != -1 && count != 1) {
        if (strongDir % 2) winner++;
        if (count == 52) {
          // 13巡終わり
          return winner;
        }
        if (strongDir == 0) nowTurn = 'N';
        if (strongDir == 1) nowTurn = 'E';
        if (strongDir == 2) nowTurn = 'S';
        if (strongDir == 3) nowTurn = 'W';
        f(f, count, -1, nowTurn, 'Z', -1, winner);
      }

      if (count == 52) return 0;
      int ret = 0;
      // 出せるカードを全部試す
      // todo 繋がっているカードを試す必要はない
      // todo メモ化する
      if (next(nowTurn) == 'E') {
        rep(i, 13) {
          if (!used[1][i] && isLegal(color, 1, East, i)) {
            used[1][i] = true;
            int now =
                f(f, count + 1, color, nowTurn, strongDir, strongCard, winner);

            used[1][i] = false;
          }
        }
      } else if (next(nowTurn) == 'S') {
        rep(i, 13) {
          if (!used[2][i]) {
            used[2][i] = true;

            used[2][i] = false;
          }
        }
      } else if (next(nowTurn) == 'W') {
        rep(i, 13) {
          if (!used[3][i]) {
            used[3][i] = true;

            used[3][i] = false;
          }
        }
      } else if (next(nowTurn) == 'N') {
        rep(i, 13) {
          if (!used[4][i]) {
            used[4][i] = true;

            used[4][i] = false;
          }
        }
      }
    };

    int ans = -1;
    /* output */
    cout << ans << endl;
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