#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;

const int FFT_MAXN = 4002000; // multiply by 4!!
const double Pi = 3.1415926535897932384626;
struct comp {
    double re, im;
    comp(double x = 0.0, double y = 0.0): re(x), im(y) { }
    comp operator + (const comp& c) { return comp(re+c.re, im+c.im); }
    comp operator - (const comp& c) { return comp(re-c.re, im-c.im); }
    comp operator * (const comp& c) { return comp(re*c.re-im*c.im, re*c.im+im*c.re); }
    comp operator / (double dev) { return comp(re / dev, im / dev); }
} a[FFT_MAXN], b[FFT_MAXN];
int n, m, lim = 1, l = 0, r[FFT_MAXN];
void fft(comp* a, int dft) { // -1 for idft, 1 for dft
    for(int i = 0; i < lim; ++i)
        if(i < r[i]) swap(a[i], a[r[i]]);
    for(int mid = 1; mid < lim; mid <<= 1) {
        comp wn = comp( cos(Pi / mid), sin(Pi / mid) * dft );
        for(int len = mid << 1, s = 0; s < lim; s += len) {
            comp w(1, 0);
            for(int k = 0; k < mid; ++k, w = w * wn) {
                comp x = a[s + k], y = w * a[s + k + mid];
                a[s + k] = x + y;
                a[s + k + mid] = x - y;
            }
        }
    }
    if(dft == -1) for(int i = 0; i < lim; ++i) a[i] = a[i] / lim;
}
void fft_init(int degA, int degB) {
    lim = 1, l = 0;
    while(lim <= degA + degB) lim <<= 1, l++;
    for(int i = 0; i < lim; ++i)
        r[i] = ( r[i >> 1] >> 1 ) | ( (i & 1) << (l - 1) );
}

void fft_pmul(comp *A, int degA, comp *B, int degB) { // A will be modified to get answer
    fft_init(degA, degB);
    fft(A, 1);
    fft(B, 1);
    for(int i = 0; i < lim; ++i) A[i] = A[i] * B[i];
    fft(A, -1);
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i <= n; ++i) scanf("%lf", &a[i].re);
    for(int i = 0; i <= m; ++i) scanf("%lf", &b[i].re);
    fft_pmul(a, n, b, m);
    for(int i = 0; i <= n + m; ++i)
        printf("%d%c", int(a[i].re + 0.5), " \n"[i == n+m]);
    
    return 0;
}
