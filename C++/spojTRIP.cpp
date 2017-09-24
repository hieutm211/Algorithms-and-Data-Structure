/*
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

#define maxn 17
#define oo 10000000
int n, minc, minsp, c[maxn][maxn], x[maxn];
bool Free[maxn];

void	init() {
	scanf("%d", &n); minc = +oo;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			scanf("%d", &c[i][j]);
			if (i != j) minc = min(minc, c[i][j]);
		}
	minsp = oo; x[0] = 0;
	for (int i = 1; i <= n; ++i) Free[i] = true;
}

void	Try(int i, int cost){
	for (int j = 1; j <= n; ++j)
		if (Free[j]) {
			x[i] = j;
			Free[j] = false;
			if (i == n) minsp = min(cost + c[x[i-1]][j], minsp);
			else if (cost + (n-i+2)*minc < minsp)
                Try(i+1, cost + c[x[i-1]][j]);
			Free[j] = true;
		}
}

int main() {
	init();
	Try(1, 0);
	printf("%d", minsp);
	return 0;
}
*/
