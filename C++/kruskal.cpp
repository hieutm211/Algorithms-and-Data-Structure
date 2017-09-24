
#include <bits/stdc++.h>
#define MAXN 3005
#define MAXM MAXN*MAXN
using namespace std;

int n, m, ans;
int eu[MAXM], ev[MAXM], ec[MAXM], lab[MAXN];

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
            ++i; --j;
        }
    }
    qsort(L, j); qsort(i, H);
}

int getroot(int u){
    if (lab[u] == u) return u;
    lab[u] = getroot(lab[u]);
    return lab[u];
}

int main(){
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int u, v, c;

    cin >> n >> m;
    for (int i = 1; i <= m; ++i){
        cin >> u >> v >> c;
        eu[i] = u;
        ev[i] = v;
        ec[i] = c;
    }

    qsort(1, m);

    for (int i = 1; i <= n; ++i) lab[i] = i;

    ans = 0;
    for (int i = 1; i <= m; ++i){
        u = getroot(eu[i]);
        v = getroot(ev[i]);
        if (u != v){
            lab[v] = u;
            ans += ec[i];
        }
    }
    cout << ans;
    return 0;
}
