#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Function to compute 2^K mod mod using fast exponentiation
ll two_pow_mod(ll K, ll mod) {
  if (mod == 1) return 0;
  ll res = 1;
  ll a = 2 % mod;
  while (K > 0) {
    if (K & 1) {
      res = (res * a) % mod;
    }
    a = (a * a) % mod;
    K >>= 1;
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll N, K;
  cin >> N >> K;

  // Read the permutation, 1-based indexing
  vector<ll> P(N + 1);
  for (int i = 1; i <= N; i++) cin >> P[i];

  // Initialize the final permutation
  vector<ll> P_final(N + 1, 0);

  // To keep track of visited elements for cycle decomposition
  vector<bool> visited(N + 1, false);

  for (int i = 1; i <= N; i++) {
    if (!visited[i]) {
      vector<ll> cycle;
      ll x = i;
      // Traverse the cycle starting from element i
      while (!visited[x]) {
        visited[x] = true;
        cycle.push_back(x);
        x = P[x];
      }
      ll c = cycle.size();
      // Compute m = 2^K mod c
      ll m = two_pow_mod(K, c);
      // Assign the new positions after shifting by m steps
      for (int j = 0; j < c; j++) {
        ll new_j = (j + m) % c;
        P_final[cycle[j]] = cycle[new_j];
      }
    }
  }

  // Output the final permutation
  for (int i = 1; i <= N; i++) {
    cout << P_final[i] << (i < N ? ' ' : '\n');
  }
}
