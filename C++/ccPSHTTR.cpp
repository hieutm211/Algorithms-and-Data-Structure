
#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

int n, cnt;
int head[MAXN], adj[2*MAXN], nxt[2*MAXN], eu[MAXN], ev[MAXN], ec[MAXN], qu[MAXN], qv[MAXN], qc[MAXN], qid[MAXN], eid[MAXN];
int child[MAXN], edge[MAXN], h[MAXN], par[MAXN], pos[MAXN], start[MAXN], vmax[MAXN], p[MAXN][20], t[4*MAXN], ans[MAXN];

void reset_all(){
    cnt = 0;
    for (int i = 0; i <= n+1; ++i){
        head[i] = 0;
        child[i] = 0;
        edge[i] = 0;
        h[i] = 0;
        par[i] = 0;
        pos[i] = 0;
        start[i] = 0;
        vmax[i] = 0;
    }
    for (int i = 0; i <= 4*n; ++i) t[i] = 0;
}

void add(int i, int u, int v, int w){
    nxt[i] = head[u];
    head[u] = i;
    adj[i] = v;
}

void qsort(int L, int H){
    if (L >= H) return;
    int i = L, j = H, mid = ec[(L+H)/2];
    while (i <= j){
        while (ec[i] < mid) ++i;
        while (ec[j] > mid) --j;
        if (i <= j){
            swap(eu[i], eu[j]);
            swap(ev[i], ev[j]);
            swap(ec[i], ec[j]);
            swap(eid[i], eid[j]);
            ++i; --j;
        }
    }
    qsort(L, j); qsort(i, H);
}

void qsort2(int L, int H){
    if (L >= H) return;
    int i = L, j = H, mid = qc[(L+H)/2];
    while (i <= j){
        while (qc[i] < mid) ++i;
        while (qc[j] > mid) --j;
        if (i <= j){
            swap(qu[i], qu[j]);
            swap(qv[i], qv[j]);
            swap(qc[i], qc[j]);
            swap(qid[i], qid[j]);
            ++i; --j;
        }
    }
    qsort2(L, j); qsort2(i, H);
}

void dfs1(int u, int parent){
    int j, v;

    child[u] = 1;
    j = head[u];
    while (j != 0){
        v = adj[j];
        if (v != parent){
            edge[j/2] = v;
            par[v] = u;
            h[v] = h[u]+1;
            dfs1(v, u);
            child[u] += child[v];
        }
        j = nxt[j];
    }
}

void dfs2(int u, int parent, bool mark){
    int j, v;

    pos[u] = ++cnt;
    if (mark == 0) start[u] = u;
    else start[u] = start[parent];

    j = head[u]; vmax[u] = 0;
    while (j != 0){
        v = adj[j];
        if (v != parent && child[v] > child[vmax[u]]) vmax[u] = v;
        j = nxt[j];
    }
    if (vmax[u] != 0) dfs2(vmax[u], u, 1);
    j = head[u];
    while (j != 0){
        v = adj[j];
        if (v != parent&& v != vmax[u]) dfs2(v, u, 0);
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
    if (h[u] < h[v]) swap(u, v);

    int log2n = log(n)/log(2);

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
    if (r < i || i < l) return;
    if (l == r){
        t[k] = v;
        return;
    }
    int mid = (l + r)/2;
    update(2*k, l, mid, i, v);
    update(2*k+1, mid+1, r, i, v);
    t[k] = t[2*k]^t[2*k+1];
}

int get(int k, int l, int r, int u, int v){
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return t[k];
    int mid = (l+r)/2;
    return get(2*k, l, mid, u, v) ^ get(2*k+1, mid+1, r, u, v);
}

int main(){
    int t, m, u, v, k, i, j, lca;

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d", &t);
    for (; t > 0; --t){
        scanf("%d", &n); reset_all();
        for (int i = 1; i <= n-1; ++i){
            scanf("%d%d%d", &eu[i], &ev[i], &ec[i]);
            add(i*2, eu[i], ev[i], ec[i]);
            add(i*2+1, ev[i], eu[i], ec[i]);
            eid[i] = i;
        }

        dfs1(1, -1);
        dfs2(1, -1, 0);
        InitLCA();

        scanf("%d", &m);
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d%d", &qu[i], &qv[i], &qc[i]);
            qid[i] = i;
        }
        qsort(1, n-1);
        qsort2(1, m);

        j = 0;
        for (int i = 1; i <= m; ++i){
            while (j+1 <= n - 1 && ec[j+1] <= qc[i]){
                update(1, 1, n, pos[edge[eid[j+1]]], ec[j+1]);
                ++j;
            }

            u = qu[i]; v = qv[i];
            ans[qid[i]] = 0;
            lca = LCA(u, v);
            while (u != lca){
                if (pos[start[u]] <= pos[lca]){
                    ans[qid[i]] ^= get(1, 1, n, pos[vmax[lca]], pos[u]);
                    u = lca;
                } else {
                    ans[qid[i]] ^= get(1, 1, n, pos[start[u]], pos[u]);
                    u = par[start[u]];
                }
            }
            while (v != lca){
                if (pos[start[v]] <= pos[lca]){
                    ans[qid[i]] ^= get(1, 1, n, pos[vmax[lca]], pos[v]);
                    v = lca;
                } else {
                    ans[qid[i]] ^= get(1, 1, n, pos[start[v]], pos[v]);
                    v = par[start[v]];
                }
            }
        }
        for (int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
    }

    return 0;
}
