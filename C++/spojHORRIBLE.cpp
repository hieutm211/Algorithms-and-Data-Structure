
#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

int n;
long long sta[MAXN], stb[MAXN];

void reset_all(){
    memset(sta, 0, sizeof(sta));
    memset(stb, 0, sizeof(stb));
}

void updatea(int i, int v){
    while (i <= n){
        sta[i] += v;
        i += i & -i;
    }
}

long long geta(int i){
    long long sum = 0;
    while (i > 0){
        sum += sta[i];
        i -= i & -i;
    }
    return sum;
}

void updateb(int i, long long v){
    while (i <= n){
        stb[i] += v;
        i += i & -i;
    }
}

long long getb(int i){
    long long sum = 0;
    while (i > 0){
        sum += stb[i];
        i -= i & -i;
    }
    return sum;
}

void query1(int u, int v, int w){
    updatea(u, w);
    updatea(v+1, -w);
    updateb(u, (long long)(1-u)*w);
    updateb(v+1, -(long long)(1-u)*w);
    updateb(v+1, (long long)(v-u+1)*w);
}

long long getsum(int i){
    return (geta(i)) * i + getb(i);
}

void query2(int u, int v){
    cout << getsum(v)-getsum(u-1) << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int testcase, q, c, u, v, w;

    cin >> testcase;
    while (testcase--){
        cin >> n >> q;
        reset_all();
        while (q--){
            cin >> c >> u >> v;
            if (c == 0){
                cin >> w;
                query1(u, v, w);
            } else query2(u, v);
        }
    }
    return 0;
}
