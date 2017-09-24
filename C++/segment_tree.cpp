
#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

int n, t[4*MAXN];

void update(int k, int l, int r, int i, int v){
    if (i < l || r < i) return;
    if (l == r) {
        t[k] = v;
        return;
    }
    int mid = (l+r)/2;
    update(2*k, l, mid, i, v);
    update(2*k+1, mid+1, r, i, v);
    t[k] = max(t[2*k], t[2*k+1]);
}

int get(int k, int l, int r, int u, int v){
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return t[k];
    int mid = (l+r)/2;
    return max(get(2*k, l, mid, u, v), get(2*k+1, mid+1, r, u, v));
}


int main(){
    int x, u, v, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i){
        cin >> x;
        update(1, 1, n, i, x);
    }
    for (int i = 1; i <= q; ++i){
        cin >> u >> v;
        cout << get(1, 1, n, u, v) << endl;
    }
    return 0;
}
