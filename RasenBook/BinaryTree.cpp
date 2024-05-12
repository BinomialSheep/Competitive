#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define MAX 26
#define NIL -1


int n; // 節点の個数
int root = 0;

struct Node {
  int parent, left, right;
};

Node tree[MAX];
int D[MAX], H[MAX];

// 深さの配列を再帰的に求める（深さ：rootから節点までの経路の長さ）
void setDepth(int u, int d) {
  if( u == NIL) return;
  D[u] = d;
  setDepth(tree[u].left, d + 1);
  setDepth(tree[u].right, d + 1);
}

// 高さの配列を再帰的に求める（高さ：節点から葉までの経路の長さの最大値）
int setHeight(int u) {
  int h1 = 0, h2 = 0;
  if( tree[u].left != NIL ) h1 = setHeight(tree[u].left) + 1;
  if( tree[u].right != NIL ) h2 = setHeight(tree[u].right) + 1;
  return H[u] = (h1 > h2 ? h1 : h2);
}

// 節点 u の兄弟を返す
int getSibling(int u) {
  if (tree[u].parent == NIL ) return NIL;
  if (tree[tree[u].parent].left != u && tree[tree[u].parent].left != NIL ) return tree[tree[u].parent].left;
  if (tree[tree[u].parent].right != u && tree[tree[u].parent].right != NIL ) return tree[tree[u].parent].right; 
  return NIL;
}


void print(int u) {
    cout << "node " << u;
    cout << ": parent = " << tree[u].parent;
    cout << ", sibling = " << getSibling(u);
    int deg = 0;
    if(tree[u].left != NIL ) deg++;
    if(tree[u].right != NIL ) deg++;
    cout << ", degree = " << deg;
    cout << ", depth = " << D[u];
    cout << ", height = " << H[u];
    string type;
    if( tree[u].parent == NIL ) type = "root";
    else if( tree[u].left == NIL && tree[u].right == NIL ) type = "leaf";
    else type = "internal node";

    cout << ", " << type << endl;
}


int main() {
  
  cin >> n;

  

  for(int i = 0; i < n; i++ ) {
    tree[i].parent = NIL;
  }

  for(int i = 0; i < n; i++ ) {
    int v, l, r;
    cin >> v >> l >> r;
    tree[v].left = l;
    tree[v].right = r;
    if(l != NIL) tree[l].parent = v;
    if(r != NIL) tree[r].parent = v;
  }

  for(int i = 0; i < n; i++ ){
    if(tree[i].parent == NIL ) root = i;
  }

  setDepth(root, 0);
  setHeight(root);

  for(int i = 0; i < n; i++ ) print(i);



  return 0;
}