#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ブースのアルゴリズムを用いて最小回転の開始インデックスを見つける関数
int min_rotation(const vector<int>& s) {
  int n = s.size();
  int i = 0, j = 1, k = 0;
  while (i < n && j < n && k < n) {
    int a = s[(i + k) % n];
    int b = s[(j + k) % n];
    if (a == b) {
      k++;
    } else {
      if (a > b) {
        i = i + k + 1;
      } else {
        j = j + k + 1;
      }
      if (i == j) {
        i++;
      }
      k = 0;
    }
  }
  return min(i, j);
}

// 最小周期を見つける関数
int minimal_period(const vector<int>& s) {
  int n = s.size();
  vector<int> failure(n, 0);
  for (int i = 1; i < n; i++) {
    int j = failure[i - 1];
    while (j > 0 && s[i] != s[j]) {
      j = failure[j - 1];
    }
    if (s[i] == s[j]) {
      j++;
    }
    failure[i] = j;
  }
  int p = n - failure[n - 1];
  if (n % p == 0)
    return p;
  else
    return n;
}

// 拡張ユークリッドの互除法
ll extended_gcd_func(ll a, ll b, ll& x, ll& y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  ll x1, y1;
  ll g = extended_gcd_func(b, a % b, x1, y1);
  x = y1;
  y = x1 - (a / b) * y1;
  return g;
}

// 中国剰余定理を用いて2つの合同式を統合する関数
bool extended_crt(ll a1, ll m1, ll a2, ll m2, ll& a3, ll& m3) {
  ll x, y;
  ll g = extended_gcd_func(m1, m2, x, y);
  if ((a2 - a1) % g != 0) {
    return false;
  }
  ll lcm = m1 / g * m2;
  ll tmp = (a2 - a1) / g;
  tmp = (x * tmp) % (m2 / g);
  if (tmp < 0) tmp += (m2 / g);
  a3 = a1 + tmp * m1;
  a3 %= lcm;
  if (a3 < 0) a3 += lcm;
  m3 = lcm;
  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int N;
  cin >> N;
  vector<int> P(N);
  for (int& x : P) {
    cin >> x;
    x--;  // 0-based
  }
  vector<int> A(N);
  for (int& x : A) cin >> x;

  // 順列Pをサイクルに分解
  vector<vector<int>> cycles;
  vector<bool> visited(N, false);
  for (int i = 0; i < N; i++) {
    if (!visited[i]) {
      vector<int> cycle;
      int current = i;
      while (!visited[current]) {
        visited[current] = true;
        cycle.push_back(current);
        current = P[current];
      }
      cycles.push_back(cycle);
    }
  }

  // 各サイクルの最小インデックス順にソート
  sort(cycles.begin(), cycles.end(),
       [&](const vector<int>& a, const vector<int>& b) -> bool {
         return *min_element(a.begin(), a.end()) <
                *min_element(b.begin(), b.end());
       });

  ll k = 0;  // 現在の操作回数
  ll m = 1;  // 現在のモジュロ

  for (auto& cycle : cycles) {
    int L = cycle.size();
    // サイクル内のAの値を収集
    vector<int> cycle_A;
    for (auto idx : cycle) cycle_A.push_back(A[idx]);

    // 最小回転のシフトを見つける
    int min_shift = min_rotation(cycle_A);

    // 最小回転のシフトに対応する最小回転シーケンスを構築
    vector<int> min_rot(L);
    for (int i = 0; i < L; i++) min_rot[i] = cycle_A[(min_shift + i) % L];

    // 最小回転の周期を見つける
    int p = minimal_period(min_rot);

    // 最小回転を生成するシフトのリストを作成
    vector<int> candidate_shifts;
    for (int t = 0; t * p + min_shift < L; t++) {
      int s = min_shift + t * p;
      if (s < L) {
        // 確認のためにシフト後が最小回転と一致するかチェック
        bool match = true;
        for (int i = 0; i < L; i++) {
          if (cycle_A[(s + i) % L] != min_rot[i]) {
            match = false;
            break;
          }
        }
        if (match) {
          candidate_shifts.push_back(s);
        }
      }
    }

    // シフトのリストを昇順にソート
    sort(candidate_shifts.begin(), candidate_shifts.end());

    // シフト候補の中から最小のkを選ぶ
    bool found = false;
    ll new_k, new_m;
    for (auto s_i : candidate_shifts) {
      ll temp_k, temp_m;
      if (extended_crt(k, m, s_i, L, temp_k, temp_m)) {
        k = temp_k;
        m = temp_m;
        found = true;
        break;
      }
    }
  // 問題の制約により、必ず解が存在すると仮定
