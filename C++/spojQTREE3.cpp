
#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

int n, q, cnt, head[MAXN], adj[2*MAXN+1], nxt[2*MAXN+1], col[MAXN], num[MAXN], child[MAXN], par[MAXN], p[MAXN][20], t[MAXN];

void add(int i, int u, int v){
    nxt[i] = head[u];
    head[u] = i;
    adj[i] = v;
}

void buildgraph(){
    cin >> n >> q;
    for (int i = 2; i <= 2*(n - 1)+1; i+=2){
        int u, v;
        cin >> u >> v;
        add(i, u, v);
        add(i+1, v, u);
    }
}

void dfs(int u, int parent){
    num[u] = ++cnt; child[u] = 1;
    int j = head[u];
    while (j != 0){
        int v = adj[j];
        if (v != parent) {
            par[v] = u;
            dfs(v, u);
            child[u] += child[v];
        }
        j = nxt[j];
    }
}

void InitP(){
    int log2n = log(n) / log(2);
    for (int i = 1; i <= n; ++i){
        p[i][0] = par[i];
        for (int j = 1; j <= log2n; ++j) p[i][j] = -1;
    }

    for (int j = 1; j <= log2n; ++j)
        for (int i = 1; i <= n; ++i)
            if (p[i][j-1] != -1) p[i][j] = p[p[i][j-1]][j-1];
}

void update(int i, int x){
    while (i <= n) {
        t[i] += x;
        i += i & -i;
    }
}

int get(int i){
    int ans = 0;
    while (i > 0){
        ans += t[i];
        i -= i & -i;
    }
    return ans;
}

int main(){
    freopen("input.txt", "r", stdin);
    buildgraph();
    dfs(1, -1);
    InitP();

    for (; q > 0; --q){
        int c, v, ans = -1;
        cin >> c >> v;
        if (c == 0) {
            if (col[v] == 0) {
                update(num[v], 1);
                update(num[v] + child[v], -1);
            } else {
                update(num[v], -1);
                update(num[v] + child[v], 1);
            }
            col[v] = 1 - col[v];
        } else{
            if (get(num[v]) == 0) cout << -1 << endl;
            else {
                int log2n = log(n) / log(2);
                for (int i = log2n; i >= 0; --i)
                    if (p[v][i] != -1 && get(num[p[v][i]]) > 0) v = p[v][i];
                cout << v << endl;
            }
        }
    }
    return 0;
}
