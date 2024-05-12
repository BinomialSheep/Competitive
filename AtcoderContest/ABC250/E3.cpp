#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vb = vector<bool>;
using vs = vector<string>;
using vc = vector<char>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvb = vector<vector<bool>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
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

int main() {
  /* input */
  int N;
  cin >> N;
  vi a(N);
  vi b(N);
  rep(i, N) cin >> a[i];
  rep(i, N) cin >> b[i];
  // 累積種類数
  vi ca(N), cb(N), mx(N);
  // 前処理
  map<int, int> mp;
  rep(i, N) {
    if (!mp.count(a[i])) {
      mp[a[i]] = mp.size() + 1;
    }
    ca[i] = mp.size();
  }
  int m = 0;
  set<int> st;
  rep(i, N) {
    st.insert(b[i]);
    int x = mp[b[i]];
    if (x == 0) x = INFTY;
    m = max(m, x);
    mx[i] = m;
    cb[i] = st.size();
  }

  /* solve */
  int q;
  cin >> q;
  rep(qi, q) {
    int x, y;
    cin >> x >> y;
    --x;
    --y;
    if (ca[x] == cb[y] && mx[y] == cb[y]) {
      puts("Yes");
    } else {
      puts("No");
    }
  }

  return 0;
}