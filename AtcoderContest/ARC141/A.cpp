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

vi getDivisorList(int n) {
  vi divisorList;
  int fin = (int)sqrt(n);
  for (int i = 1; i <= fin; i++) {
    if (n % i == 0) {
      divisorList.push_back(i);
      divisorList.push_back(n / i);
    }
  }
  return divisorList;
}

int main() {
  int T;
  cin >> T;
  rep(ti, T) {
    /* input */
    ll N;
    cin >> N;

    /* solve */
    //
    string strN = to_string(N);
    int keta = (int)strN.size();
    vi divisorList = getDivisorList(keta);
    //
    set<ll> mayAns;
    for (auto value : divisorList) {
      if (value == keta) continue;

      ll m = stoll(strN.substr(0, value));
      for (int i = value; i < keta; i += value) {
        ll mi = stoll(strN.substr(i, value));
        if (mi < m) {
          m--;
          break;
        } else if (mi > m) {
          break;
        }
      }

      string strM = to_string(m);
      string temp = "";
      rep(i, (int)keta / value) { temp += strM; }
      mayAns.insert(stoll(temp));
    }

    // なんの成果も得られない場合に備えて
    // 1桁下の9999...を追加する
    string temp = "";
    rep(i, (int)keta - 1) temp += "9";
    mayAns.insert(stoll(temp));

    /* output */
    cout << *(mayAns.rbegin()) << endl;
  }

  return 0;
}