
#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

int n, cnt, head[MAXN], adj[2*MAXN+1], nxt[2*MAXN+1], c[MAXN], child[MAXN], pos[MAXN], start[MAXN], h[MAXN], par[MAXN], p[MAXN][21], edge[2*MAXN+1], e[MAXN], t[4*MAXN], d[MAXN];

void add(int i, int u, int v, int w){
    nxt[i] = head[u];
    head[u] = i;
    adj[i] = v;
    c[i] = w;
}

void dfs1(int u, int parent){
    int j, v;

    child[u] = 1;
    j = head[u];
    while (j != 0){
        v = adj[j];
        if (v != parent){
            edge[j] = v;
            edge[j^1] = v;
            h[v] = h[u] + 1;
            par[v] = u;
            dfs1(v, u);
            child[u] += child[v];
        }
        j = nxt[j];
    }
}

void dfs2(int u, int parent, int mark){
    int j, v, vmax;

    pos[u] = ++cnt;
    if (mark == 0) start[u] = u;
    else start[u] = start[parent];

    j = head[u]; vmax = 0;
    while (j != 0){
        v = adj[j];
        if (v != parent && child[v] > child[vmax]) vmax = v;
        j = nxt[j];
    }

    if (vmax != 0) {
        dfs2(vmax, u, 1);
        d[pos[u]] = pos[vmax];
    }
    j = head[u];
    while (j != 0){
        v = adj[j];
        if (v != parent && v != vmax) dfs2(v, u, 0);
        j = nxt[j];
    }
}

void InitLCA(){
    int log2n = log(n)/log(2);

    for (int i = 1; i <= n; ++i){
        p[i][0] = par[i];
        for (int j = 1; j <= log2n; ++j) p[i][j] = -1;
    }

    for (int j = 1; j <= log2n; ++j)
        for (int i = 1; i <= n; ++i)
            if (p[i][j-1] != -1) p[i][j] = p[p[i][j-1]][j-1];
}

int LCA(int u, int v){
    if (u == v) return u;
    if (u < v) swap(u, v);

    int log2n = log(n) / log(2);

    for (int i = log2n; i >= 0; --i)
        if (h[u] - (1 << i) >= h[v]) u = p[u][i];

    if (u == v) return u;

    for (int i = log2n; i >= 0; --i)
    if (p[u][i] != -1 && p[u][i] != p[v][i]){
        u = p[u][i];
        v = p[v][i];
    }
    return par[u];
}

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
    int testcase, u, v, w;

    freopen("input.txt", "r", stdin);
    cin >> testcase;
    for (; testcase > 0; --testcase){
        memset(t, 0, sizeof(t));
        memset(nxt, 0, sizeof(nxt));
        memset(head, 0, sizeof(head));
        memset(h, 0, sizeof(h));
        memset(par, 0, sizeof(par));
        memset(pos, 0, sizeof(pos));
        memset(child, 0, sizeof(child));
        memset(c, 0 ,sizeof(c));
        cin >> n;
        for (int i = 2; i <= 2*(n-1)+1; i += 2){
            cin >> u >> v >> w;
            add(i, u, v, w);
            add(i+1, v, u, w);
            e[i/2] = w;
        }

        dfs1(1, -1);
        dfs2(1, -1, 0);
        InitLCA();
        for (int i = 1; i <= n-1; ++i) update(1, 1, n, pos[edge[2*i]], e[i]);

        char s[5];
        cin >> s;
        while (s[0] != 'D'){
            cin >> u >> v;
            if (s[0] == 'C') update(1, 1, n, pos[edge[2*u]], v);
            else {
                int lca = LCA(u, v), ans = 0;
                u = pos[u]; v = pos[v]; lca = pos[lca];
                while (u != lca){
                    if (start[u] > lca) {
                        ans = max(ans, get(1, 1, n, u, d[pos[start[u]]]));
                        ans = max(ans, get(1, 1, n, pos[start[u]], pos[start[u]]));
                        u = pos[par[start[u]]];
                    } else {
                        ans = max(ans, get(1, 1, n, u, lca));
                        u = lca;
                    }
                }
                while (v != lca){
                    if (start[v] > lca) {
                        ans = max(ans, get(1, 1, n, v, d[pos[start[v]]]));
                        ans = max(ans, get(1, 1, n, pos[start[v]], pos[start[v]]));
                        v = pos[par[start[v]]];
                    } else {
                        ans = max(ans, get(1, 1, n, v, lca));
                        v = lca;
                    }
                }
                cout << ans << endl;
            }
            cin >> s;
        }
    }
    return 0;
}
