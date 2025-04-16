#include <bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;
const int inf = 1000000007;
const ll longinf = 1ll << 60;

struct Timer {
  chrono::system_clock::time_point start, last_updated;

  Timer() {
    start = chrono::system_clock::now();
    last_updated = chrono::system_clock::now();
  }

  void reset() { start = chrono::system_clock::now(); }

  void update() { last_updated = chrono::system_clock::now(); }

  double getTime() {
    auto now = chrono::system_clock::now();
    return chrono::duration<double>(now - start).count();
  }
};

Timer timer;
struct Xor128 {
  unsigned x, y, z, w;

  Xor128() : x(123456789), y(362436069), z(521288629), w(88675123) {};

  inline unsigned xor128() {
    unsigned t;
    t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
  }

  int nextInt(int x, int y) { return xor128() % (y - x) + x; }

  double nextDouble(double a, double b) {
    return (double)(xor128() & 0xffff) / 0xffff * (b - a) + a;
  }
};
auto rnd = Xor128();

const int N = 1000, H = 10;
int M;
vector<vector<int>> G(N);
int A[N], X[N], Y[N];

void input() {
  int _;
  cin >> _ >> M >> _;
  rep(i, N) cin >> A[i];
  rep(i, M) {
    int x, y;
    cin >> x >> y;
    G[x].push_back(y);
    G[y].push_back(x);
  }
  rep(i, N) cin >> X[i] >> Y[i];
  rep(i, N) {
    sort(G[i].begin(), G[i].end(), [&](int x, int y) { return A[x] < A[y]; });
  }
}

void output(array<int, N> &h) {
  vector<int> p(N, -1);
  vector<int> cnt(12);
  rep(i, N) {
    cnt[h[i]]++;
    if (h[i] == 1) {
      p[i] = -1;
    } else {
      for (auto to : G[i]) {
        if (h[to] + 1 == h[i]) {
          p[i] = to;
        }
      }
    }
  }
  // rep(i, 11) cerr << cnt[i + 1] << " \n"[i + 1 == 11];
  rep(i, N) cout << p[i] << " \n"[i + 1 == N];
}

using BS = bitset<N>;

BS bfs(int _x, int md, BS &used) {
  BS bs;
  queue<pair<int, int>> q;
  q.push({0, _x});
  while (q.size()) {
    auto [d, x] = q.front();
    q.pop();
    if (bs[x] || d == md) {
      continue;
    }
    bs.set(x);
    for (auto to : G[x]) {
      if (!used[to] && !bs[to]) {
        q.push({d + 1, to});
      }
    }
  }
  return bs;
}
using u64 = unsigned long long;

struct State {
  int score;
  u64 hash;
  BS all;
  vector<BS> bss;
  State(int score = 0) : score(score) {}
  bool operator<(const State &other) const { return score < other.score; }
  bool operator>(const State &other) const { return score > other.score; }
};

struct DiffState {
  int target;
  int score;
  u64 hash;
  BS bs;
  bool operator<(const DiffState &other) const { return score < other.score; }
  bool operator>(const DiffState &other) const { return score > other.score; }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  input();
  vector<int> ord(N);
  rep(i, N) ord[i] = i;
  sort(ord.begin(), ord.end(), [&](int x, int y) { return A[x] < A[y]; });
  vector<u64> used_hash(N);
  vector<u64> using_hash(N);
  rep(i, N) {
    used_hash[i] = u64(rnd.xor128()) << 32 | rnd.xor128();
    using_hash[i] = u64(rnd.xor128()) << 32 | rnd.xor128();
  }
  vector<State> states;
  {
    int score = 0;
    rep(i, N) score += 11 * A[i];
    states.push_back(State(score));
  }
  double bfstime = 0, looptime = 0;
  vector<double> times(H);
  rep(l, H) {
    vector<State> ns;
    vector<DiffState> diffs;
    times[l] -= timer.getTime();
    rep(t, states.size()) {
      auto &state = states[t];
      if (timer.getTime() > 0.195 * (l + 1)) {
        break;
      }
      vector<int> vs;
      BS bs;
      u64 hash;
      for (auto i : ord) {
        if (state.all[i] != 0) {
          bs.set(i);
          hash ^= used_hash[i];
          continue;
        }
        for (auto to : G[i]) {
          if (l == 0 || state.bss[l - 1][to]) {
            vs.push_back(i);
            break;
          }
        }
      }
      int m = vs.size();
      vector<pair<int, BS>> vbs(m);
      bfstime -= timer.getTime();
      rep(i, m) { vbs[i] = {vs[i], bfs(vs[i], H + 1 - l, state.all)}; }
      bfstime += timer.getTime();
      looptime -= timer.getTime();
      vector<int> random_value(N);

      rep(_, l == 0 ? 2000 : 30) {
        // State nstate = state;
        // nstate.hash = nhash;
        int nscore = state.score;
        u64 nhash = hash;
        BS use;
        vector<BS> acc(m + 1);
        int last = m - 1;
        rep(i, m) {
          acc[i + 1] = acc[i] | vbs[i].second;
          if (acc[i + 1].all()) {
            last = i;
            break;
          }
        }
        BS cur = bs;
        for (int i = last; i >= 0; i--) {
          if ((acc[i] | cur).all()) {
            continue;
          }
          cur |= vbs[i].second;
          use.set(vbs[i].first);
          nscore -= (10 - l) * A[vbs[i].first];
          nhash ^= using_hash[vbs[i].first];
        }
        diffs.push_back(DiffState{t, nscore, nhash, use});
        rep(i, m) {
          random_value[vbs[i].first] = A[vbs[i].first] + rnd.nextInt(0, 50);
        }
        sort(vbs.begin(), vbs.end(), [&](auto &x, auto &y) {
          return random_value[x.first] < random_value[y.first];
        });
      }
      looptime += timer.getTime();
    }
    sort(diffs.rbegin(), diffs.rend());
    unordered_set<ull> hashes;
    for (auto &&d : diffs) {
      if (hashes.insert(d.hash).second) {
        auto ps = states[d.target];
        ps.score = d.score;
        ps.hash = d.hash;
        ps.all |= d.bs;
        ps.bss.push_back(d.bs);
        ns.push_back(ps);
        if (ns.size() == 500) {
          break;
        }
      }
    }
    ns.swap(states);
    times[l] += timer.getTime();
    // rep(i, N) cout << h[i] << " \n"[i + 1 == N];
  }
  auto best_state = states[0];
  cerr << best_state.score << endl;
  cerr << bfstime << " " << looptime << endl;
  rep(i, H) { cerr << times[i] << " \n"[i + 1 == H]; }
  array<int, N> h;
  rep(i, N) {
    h[i] = 11;
    rep(l, 10) {
      if (best_state.bss[l][i]) {
        h[i] = l + 1;
      }
    }
  }
  output(h);
}