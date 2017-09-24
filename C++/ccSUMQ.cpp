
#include <bits/stdc++.h>
#define MAXN 100005
#define base 1000000007
using namespace std;

int t, n, m, p, a[MAXN], b[MAXN], c[MAXN];
long long s1[MAXN], s3[MAXN];

int read() {
    int res = 0;
    char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while ('0' <= c && c <= '9') {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res;
}

int main(){
    cin >> t; //t = read();
    for (;t > 0; ++t){
        cin >> n >> m >> p;
        //n = read(); m = read(); p = read();
        for (int i = 1; i <= n; ++i) cin >> a[i]; //a[i] = read();
        for (int i = 1; i <= m; ++i) cin >> b[i]; // = read();
        for (int i = 1; i <= p; ++i) cin >> c[i]; //c[i] = read();
        /*
        sort(a+1, a+n);
        sort(b+1, b+m);
        sort(c+1, c+p);
        for (int i = 1; i <= n; ++i){
            s1[i] = s1[i-1] + a[i];
            s3[i] = s3[i-1] + c[i];
        }
        long long ans = 0;
        int pa = 0, pc = 0;
        for (int i = 1; i <= m; ++i){
            while (pa+1 <= n && a[pa+1] <= b[i]) ++pa;
            while (pc+1 <= p && c[pc+1] <= b[i]) ++pc;
            ans = (((s1[pa]+(b[i] * pa) % base) % base) * ((s3[pc]+(b[i] * pc)%base)%base))%base;
        }
        cout << ans;
        */
    }
    return 0;
}
