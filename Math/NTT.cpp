#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;

const int MOD = 998244353, g = 3, ginv = 332748118;

inline int muln(int x, int y) { return 1LL * x * y % MOD; }
inline int mo(int x) { while(x >= MOD) x -= MOD; while(x < 0) x += MOD; return x; }
inline int qpow(int x, int y) {
    int ret = 1;
    for(; y; y >>= 1, x = muln(x, x))
        if(y & 1) ret = muln(ret, x);
    return ret;
}
inline int inv(int x) { return qpow(x, MOD - 2); }

const int FFT_MAXN = 4004000;
int l, r[FFT_MAXN], a[FFT_MAXN], b[FFT_MAXN], n, m, lim, liminv;
void ntt(int* a, int dft) {
    for(int i = 0; i < lim; ++i)
        if(i < r[i]) swap(a[i], a[r[i]]);
    for(int mid = 1; mid < lim; mid <<= 1) {
        int wn = qpow(dft==1 ? g : ginv, (MOD-1) / (mid << 1));
        for(int len = mid << 1, j = 0; j < lim; j += len) {
            int w = 1;
            for(int k = 0; k < mid; ++k, w = muln(w, wn)) {
                int x = a[j + k], y = muln(w, a[j + k + mid]);
                a[j + k] = mo(x + y);
                a[j + k + mid] = mo(x - y);
            }
        }
    }
    if(dft == -1) for(int i = 0; i < lim; ++i) a[i] = muln(a[i], liminv);
}
void ntt_init(int degA, int degB) {
    lim = 1, l = 0;
    while(lim <= degA + degB) lim <<= 1, l++;
    liminv = inv(lim);
    for(int i = 0; i < lim; ++i)
        r[i] = ( r[i>>1] >> 1 ) | ( (i&1) << (l-1) );
}
void ntt_pmul(int *A, int degA, int *B, int degB) {
    ntt_init(degA, degB);
    ntt(A, 1);
    ntt(B, 1);
    for(int i = 0; i < lim; ++i) A[i] = muln(A[i], B[i]);
    ntt(A, -1);
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i <= n; ++i) scanf("%d", &a[i]);
    for(int i = 0; i <= m; ++i) scanf("%d", &b[i]);
    ntt_pmul(a, n, b, m);
    for(int i = 0; i <= n + m; ++i)
        printf("%d ", a[i]);
    
    return 0;
}
