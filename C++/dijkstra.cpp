
#include <bits/stdc++.h>
#define MAXN 1005
#define oo 1000000007
using namespace std;

int n, m, s, f, c[MAXN][MAXN], d[MAXN];
bool a[MAXN][MAXN], Free[MAXN];

void dijkstra(){
    int dmin, j, u, v;

    memset(Free, 1, sizeof(Free));
    for (int i = 1; i <= n; ++i) d[i] = +oo;
    d[s] = 0;
    while (0 == 0){
        u = 0; dmin = +oo;
        for (int i = 1; i <= n; ++i)
        if (Free[i] && d[i] < dmin){
            dmin = d[i];
            u = i;
        }
        if (u == 0 || u == f) return;
        Free[u] = 0;

        for (int v = 1; v <= n; ++v)
        if (a[u][v] && Free[v]) d[v] = min(d[v], d[u] + c[u][v]);
    }
}

int main(){
    int u, v, w;

    cin >> n >> m >> s >> f;
    for (int i = 1; i <= m; ++i){
        cin >> u >> v >> w;
        a[u][v] = 1;
        c[u][v] = w;
        a[v][u] = 1;
        c[v][u] = w;
    }
    dijkstra();
    cout << d[f] << endl;
    return 0;
}
