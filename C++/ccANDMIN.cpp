
#include <bits/stdc++.h>
using namespace std;

const int maxN = 100001;
const int oo = 1000000001;
int n, q, a[maxN], t[4*maxN], f[4*maxN];

void build(int k, int l, int r){
    if (l == r){
        t[r] = a[r];
        return;
    }
    int mid = (l+r)/2;
    build(2*k, l, mid);
    build(2*k+1, mid+1, r);
}

void down(int k){
    if (f[k] == 0) return;
    t[2*k] &= f[k];
    f[2*k] &= f[k];
    t[2*k+1] &= f[k];
    f[2*k+1] &= f[k];
    f[k] = 0;
}

void update(int k, int l, int r, int u, int v, int x){
    if (v < l || r < u) return;
    if (u <= l && r <= v){
        t[k] &= x;
        f[k] &= x;
        return;
    }
    down(k);
    int mid = (l+r)/2;
    update(2*k, l, mid, u, v, x);
    update(2*k+1, mid+1, r, u, v, x);
    t[k] = min(t[2*k], t[2*k+1]);
}

int get(int k, int l, int r, int u, int v){
    if (v < l || r < u) return +oo;
    if (u <= l && r <= v) return t[k];
    down(k);
    int mid = (l+r)/2;
    return min(get(2*k, l, mid, u, v),
        get(2*k+1, mid+1, r, u, v));
}

int main(){
    freopen("input.txt", "r", stdin);

    int c, L, R, x;

    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build(1, 1, n);

    for (int i = 1; i <= n; ++i) cout << get(1, 1, n, i, i) << " ";
    cout << endl;
    while (q--){
        cin >> c >> L >> R;
        if (c == 0) cout << get(1, 1, n, L, R) << endl;
        else{
            cin >> x;
            update(1, 1, n, L, R, x);
        }
    }
    return 0;
}
