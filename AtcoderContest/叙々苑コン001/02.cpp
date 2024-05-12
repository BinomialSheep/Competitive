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
  int N, M;
  vi a, b;
  // α
  int A = 5;

  vpii stupidInit() {
    vpii ret;
    rep(i, N) ret.emplace_back(1, i + 1);
    ret.emplace_back(1, 1);
    return ret;
  }

  // 惑星を経由しない
  vpii greedyInit() {
    vpii ret;
    vector<vpii> distList(N);

    auto dist = [](int x1, int y1, int x2, int y2) {
      return (ll)((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    };

    rep(i, N) rep(j, i) {
      int x1 = a[i];
      int y1 = b[i];
      int x2 = a[j];
      int y2 = b[j];
      auto d = A * A * dist(x1, y1, x2, y2);
      distList[i].emplace_back(d, j);
      distList[j].emplace_back(d, i);
    }
    rep(i, N) sort(all(distList[i]));

    vi color(N);
    int now = 0;
    color[0] = 1;
    ret.emplace_back(1, 1);
    rep(i, N) {
      for (auto p : distList[now]) {
        if (color[p.second]) continue;
        now = p.second;
        color[p.second] = 1;
        ret.emplace_back(1, now + 1);
        break;
      }
    }
    ret.emplace_back(1, 1);
    return ret;
  }

  // 惑星を経由する
  vpii greedyInit2(vpii &cd) {
    vpii ret;
    vector<vpii> distList(N);
    map<pii, vpii> mp;

    auto dist = [&](int x1, int y1, int x2, int y2, int xi, int yi) {
      vpii value;

      ll dt = A * A * (ll)((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
      rep(i, (int)cd.size()) {
        auto x = cd[i].first;
        auto y = cd[i].second;
        ll tmp = A * (ll)((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));
        tmp += A * (ll)((x - x2) * (x - x2) + (y - y2) * (y - y2));
        if (chmin(dt, tmp)) {
          value.clear();
          value.emplace_back(2, i + 1);
        }
      }
      ll tmp1 = INFTY;
      ll tmp2 = INFTY;
      int idx1, idx2;
      rep(i, (int)cd.size()) {
        auto x = cd[i].first;
        auto y = cd[i].second;
        if (chmin(tmp1, A * (ll)((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y))))
          idx1 = i;
        if (chmin(tmp2, A * (ll)((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y))))
          idx2 = i;
      }
      if (idx1 != idx2) {
        auto xx1 = cd[idx1].first;
        auto yy1 = cd[idx1].first;
        auto xx2 = cd[idx2].first;
        auto yy2 = cd[idx2].first;
        ll tmp3 = (ll)((xx1 - xx2) * (xx1 - xx2) + (yy1 - yy2) * (yy1 - yy2));
        if (chmin(dt, tmp1 + tmp2 + tmp3)) {
          value.clear();
          value.emplace_back(2, idx1 + 1);
          value.emplace_back(2, idx2 + 1);
        }
      }
      mp[make_pair(xi, yi)] = value;
      return dt;
    };

    rep(i, N) rep(j, i) {
      int x1 = a[i];
      int y1 = b[i];
      int x2 = a[j];
      int y2 = b[j];
      auto d = A * A * dist(x1, y1, x2, y2, i, j);
      mp[make_pair(j, i)] = mp[make_pair(i, j)];
      distList[i].emplace_back(d, j);
      distList[j].emplace_back(d, i);
    }
    rep(i, N) sort(all(distList[i]));

    vi color(N);
    int now = 0;
    color[0] = 1;
    ret.emplace_back(1, 1);
    rep(i, N) {
      for (auto p : distList[now]) {
        if (color[p.second]) continue;
        for (auto pp : mp[make_pair(now, p.second)]) {
          ret.push_back(pp);
        }
        ret.emplace_back(1, p.second + 1);
        now = p.second;
        color[p.second] = 1;
        break;
      }
    }
    ret.emplace_back(1, 1);
    return ret;
  }

  // 宇宙ステーションの初期配置
  vpii initStation() {
    vpii ret;
    ret.emplace_back(800, 500);
    ret.emplace_back(200, 500);
    ret.emplace_back(500, 800);
    ret.emplace_back(500, 200);
    ret.emplace_back(600, 600);
    ret.emplace_back(600, 400);
    ret.emplace_back(400, 600);
    ret.emplace_back(400, 400);
    return ret;
  }

  // シンプルなスコア計算
  ll calcScore(vpii &tr) {
    ll ret = 0;
    int len = (int)tr.size();

    auto dist = [](int x1, int y1, int x2, int y2) {
      return (ll)((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    };

    rep(i, len - 1) {
      if (tr[i].first == 1 && tr[i + 1].first == 1) {
        int x1 = a[tr[i].second - 1];
        int y1 = b[tr[i].second - 1];
        int x2 = a[tr[i + 1].second - 1];
        int y2 = b[tr[i + 1].second - 1];
        ret += A * A * dist(x1, y1, x2, y2);
      } else if (tr[i].first == 2 && tr[i + 1].first == 2) {
        // TODO
      } else {
        // TODO
      }
    }
    return ret;
  }

  void solve() {
    /* input */
    cin >> N >> M;
    a.resize(N);
    b.resize(N);
    rep(i, N) cin >> a[i] >> b[i];

    /* solve */
    vpii cd = initStation();
    // vpii tr = stupidInit();
    // vpii tr = greedyInit();
    vpii tr = greedyInit2(cd);

    debug(calcScore(tr));

    /* output */
    int V = (int)tr.size();
    assert(tr[0].second == 1);
    assert(tr[V - 1].second == 1);

    rep(i, M) cout << cd[i].first << " " << cd[i].second << "\n";

    cout << V << endl;
    rep(i, V) cout << tr[i].first << " " << tr[i].second << "\n";
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