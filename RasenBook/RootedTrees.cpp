#include <bits/stdc++.h>

using namespace std;
#define MAX 100005
#define NIL -1

typedef long long ll;

// 左子右兄弟表現
struct Node {
  int parent;
  int leftChild;
  int rightSibling;
};

Node T[MAX];
int n, Depth[MAX];

void print(int u) {
  int i, c;
  cout << "node " << u << ": ";
  cout << "parent = " << T[u].parent << ", ";
  cout << "depth = " << Depth[u] << ", ";

  if( T[u].parent == NIL ) cout << "root, ";
  else if ( T[u].leftChild == NIL ) cout << "leaf, ";
  else cout << "internal  node, ";

  cout << "[";

  for( int i = 0, c = T[u].leftChild; c != NIL; i++, c = T[c].rightSibling ) {
    if(i) cout << ", ";
    cout << c;
  }
  cout << "]" << endl;
}

// 再帰的に深さを求める
void rec(int nodeIndex, int depth) {
  Depth[nodeIndex] = depth;
  if ( T[nodeIndex].rightSibling != NIL ) rec(T[nodeIndex].rightSibling, depth); // 右の兄弟に同じ深さを設定
  if ( T[nodeIndex].leftChild != NIL ) rec(T[nodeIndex].leftChild, depth + 1); // 最も左の子に自分の深さ+1を設定
}

int main() {
  int id;
  int childNum;
  int c, l;
  int root;
  // 接点の個数n
  cin >> n;
  // 初期化
  for(int i = 0; i < n; i++ ) T[i].parent = T[i].leftChild = T[i].rightSibling = NIL;

  
  for(int i = 0; i < n; i++ ) {
    cin >> id >> childNum;
    for(int j = 0; j < childNum; j++ ) {
      cin >> c;
      // 1人目の子どもは左子、2人目以降は直前の子の弟とする
      if(j == 0) T[id].leftChild = c;
      else T[l].rightSibling = c;
      l = c;
      T[c].parent = id;
    }
  }
  for(int i = 0; i < n; i++) {
    // 親がいない要素が根
    if (T[i].parent == NIL) root = i;
  }

  rec(root, 0);

  for(int i = 0; i < n; i++ ) print(i);

  return 0;

}