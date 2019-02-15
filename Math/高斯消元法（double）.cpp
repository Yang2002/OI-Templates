// Luogu P3389

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1, i##_end_ = (n); i <= i##_end_; ++i)
using namespace std;
typedef long long ll;

const int maxn = 120;
double mat[maxn][maxn];
int n;

bool gauss(double mat[maxn][maxn], int n) {
    for(int i = 1; i <= n; ++i) {
        int r = i;
        for(int j = i + 1; j <= n; ++j)
            if(fabs(mat[j][i]) > fabs(mat[r][i])) r = j;
        if(fabs(mat[r][i]) < 1e-9) return false;
        if(r != i) for(int j = i; j <= n + 1; ++j) swap(mat[r][j],mat[i][j]);

        for(int j = i + 1; j <= n; ++j) {
            double f = mat[j][i] / mat[i][i];
            for(int k = i; k <= n + 1; ++k)
                mat[j][k] -= f * mat[i][k];
        }
    }

    for(int i = n; i > 0; --i) {
        for(int j = i + 1; j <= n; ++j)
            mat[i][n + 1] -= mat[j][n + 1] * mat[i][j], mat[i][j] = 0;
        mat[i][n + 1] /= mat[i][i];
        mat[i][i] = 1;
    }
    return true;
}

int main() {
    scanf("%d", &n);
    rep(i, n) rep(j, n + 1) 
        scanf("%lf", &mat[i][j]);
    if(gauss(mat, n)) rep(i, n) printf("%.2f\n", mat[i][n + 1]);
    else puts("No Solution");
    
    return 0;
}
