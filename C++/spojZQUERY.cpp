
#include <bits/stdc++.h>
#define MAXN 50005
using namespace std;

struct node {
    int L, R, id;
};

int n, m, p, s[MAXN], id1[2*MAXN], id2[2*MAXN], id3[2*MAXN], ans[MAXN];
node q[MAXN];

bool cmp(node a, node b){
    if (a.L/p == b.L/p) return a.R < b.R;
    return a.L/p < b.L/p;
}

void updmax(int &x, int v){
    x = max(x, v);
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int x;

    cin >> n >> m;
    p = sqrt(n+1);

    s[0] = 50000;
    for (int i = 1; i <= n; ++i){
        cin >> x;
        s[i] = s[i-1] + x;
    }

    for (int i = 0; i < m; ++i){
        cin >> q[i].L >> q[i].R;
        --q[i].L;
        q[i].id = i;
    }

    sort(q, q+m, cmp);

    int j = 0;
    for (int i = 0; i <= p; ++i){
        int Rcur = p*i+p-1, tmp = 0;
        memset(id2, -1, sizeof(id2));
        for (int z = 0; z < 2*MAXN; ++z) id3[z] = n+1;
        for (; q[j].L/p == i && j < m; ++j){
            int qid = q[j].id;
            ans[qid] = 0;
            memset(id1, -1, sizeof(id1));

            for (int k = q[j].L; k < min(q[j].R+1, p*i+p); ++k)
            if (id1[s[k]] == -1) id1[s[k]] = k;
            else updmax(ans[qid], k - id1[s[k]]);

            for (int k = Rcur+1; k <= q[j].R; ++k){
                id2[s[k]] = k;
                if(id3[s[k]] == n+1) id3[s[k]] = k;
            }
            for (int k = q[j].L; k < min(q[j].R+1, p*i+p); ++k)
                updmax(ans[qid], id2[s[k]] - k);

            for (int k = Rcur+1; k <= q[j].R; ++k)
                updmax(tmp, k - id3[s[k]]);

            updmax(ans[qid], tmp);
            Rcur = max(Rcur, q[j].R);

        }
    }

    for (int i = 0; i < m; ++i) cout << ans[i] << endl;

    return 0;
}
