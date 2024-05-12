#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MAX 100000

int parent(int x){
  return x / 2;
}
int left(int x) {
  return 2 * x;
}
int right(int x) {
  return 2 * x + 1;
}

int main() {
  int n, A[MAX+1]; // 1オリジンなので+1している
  cin >> n;
  for (int i = 1; i <= n; i++ ) cin >> A[i];

  // [1, n]におさまってない時、その要素は存在しないので出力しない
  for(int i = 1; i <= n; i++ ) {
    cout << "node " << i << ": key = " << A[i] << ", ";
    if( parent (i) >= 1 ) cout << "parent key = " << A[parent(i)] << ", ";
    if( left(i) <= n ) cout << "left key = " << A[left(i)] << ", ";
    if( right(i) <= n ) cout << "right key = " << A[right(i)] << ", ";
    cout << endl;
  }


  


  return 0;
}