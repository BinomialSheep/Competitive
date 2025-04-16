#include <bits/stdc++.h>

#include <atcoder/all>
using namespace std;
using namespace atcoder;
#define rep(i, n) for (long long i = 0; i < (long long)(n); i++)
template <typename T>
inline bool chmax(T& a, T b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}
template <typename T>
inline bool chmin(T& a, T b) {
  if (a > b) {
    a = b;
    return true;
  }
  return false;
}
const long long MOD = 998244353;
const long long INF = 1LL << 60;
using mint = modint998244353;
using ll = long long;

void solve(int N, vector<int>& A) {
  multiset<int> st;

  int res = -1;
  int counter = 0;

  rep(i, N) {
    cin >> A[i];
    st.insert(A[i]);
  }

  rep(i, N) {
    if (st.count(A[i]) == 1) {
      if (counter < A[i]) {
        res = i + 1;
        counter = A[i];
      }
    }
  }

  cout << res << "\n";
}

signed main() {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dist(1, 10000000);
  int N = 3e5;
  vector<int> A(N);
  rep(i, N) A[i] = dist(gen);

  solve(N, A);
}