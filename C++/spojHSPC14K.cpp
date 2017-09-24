
#include <bits/stdc++.h>
#define MAXN 1005
using namespace std;

int n, m;
long long st[4][MAXN][MAXN];

void update(int k, int i, int j, long long v){
    int tmp = j;
    for (; i <= n; i += i & -i)
        for (j = tmp; j <= m; j += j & -j)
            st[k][i][j] += v;
}
long long get(int k, int i, int j){
    long long sum = 0;
    int tmp = j;
    for (; i > 0; i -= i & -i)
        for (j = tmp; j > 0; j -= j & -j)
            sum += st[k][i][j];
    return sum;
}

void updateSquare(int k, int x, int y, int u, int v, long long w){
    update(k, x, y, w);
    update(k, x, v+1, -w);
    update(k, u+1, y, -w);
    update(k, u+1, v+1, w);
}

void query1(int i, int j, int u, int v, long long w){
    int ii = i-1, jj = j-1;
    updateSquare(0, i, j, u, v, w);
    updateSquare(1, i, j, u, v, -w*jj);
    updateSquare(2, i, j, u, v, -w*ii);
    updateSquare(3, i, j, u, v, w*ii*jj);

    updateSquare(1, i, v+1, u, m, w*(v-jj));
    updateSquare(3, i, v+1, u, m, w*ii*(jj-v));

    updateSquare(2, u+1, j, n, v, w*(u-ii));
    updateSquare(3, u+1, j, n, v, w*jj*(ii-u));

    updateSquare(3, u+1, v+1, n, m, w*(u-ii)*(v-jj));
}

long long getsum(int i, int j){
    return get(0, i, j)*i*j + get(1, i, j)*i + get(2, i, j)*j + get(3, i, j);
}

void query2(int i, int j, int u, int v){
    cout << getsum(u, v) - getsum(u, j-1) - getsum(i-1, v) + getsum(i-1, j-1) << endl;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int q, c, x, y, u, v, w;

    cin >> n >> m >> q;
    while (q--){
        cin >> c >> x >> y >> u >> v;
        //swap(x, u);
        if (c == 1){
            cin >> w;
            query1(x, y, u, v, w);
        } else query2(x, y, u, v);
    }

    return 0;
}
