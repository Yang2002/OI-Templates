// Note that after 7 sqrt operations, the number must have become 1.
// We use Flag[] to determine whether we need to update the interval
// If we need, we just bruteforce and update the leaves

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
const int maxn = 100200;

ll a[maxn];
int n, q, kase = 0;

template<typename T> void read(T &x){
    x = 0; int f = 1; char ch = getchar();
    while(!isdigit(ch) ) { if(ch == '-') f *= -1; ch = getchar();}
    while( isdigit(ch) ) {x = x * 10 + ch - 48; ch = getchar();}
    x *= f;
}

struct SegmentTree {
    #define lson (o << 1)
    #define rson (o << 1 | 1)

    private:
    ll sum[maxn << 2];
    bool Flag[maxn << 2];
    inline void pushup(int o) {
        sum[o] = sum[lson] + sum[rson];
        Flag[o] = Flag[lson] && Flag[rson];
    }

    public:
    inline void Build(ll* arr, int o, int l, int r) {
        if(l == r) {sum[o] = arr[l]; Flag[o] = (arr[l] <= 1); return;}
        int mid = (l + r) >> 1;
        Build(arr, lson, l, mid);
        Build(arr, rson, mid + 1, r);
        pushup(o);
    }
    void InterSqrt(int o, int l, int r, int ql, int qr) {
        int mid = (l + r) >> 1;
        if(l == r) {sum[o] = sqrt(sum[o] + 0.500); Flag[o] = (sum[o] <= 1); return;}
        if(ql <= l && r <= qr) {
            if(Flag[o]) return;
            InterSqrt(lson, l, mid, ql, qr);
            InterSqrt(rson, mid + 1, r, ql, qr);
            pushup(o);
            return;
        }
        if(ql <= mid) InterSqrt(lson, l, mid, ql, qr);
        if(qr > mid) InterSqrt(rson, mid + 1, r, ql, qr);
        pushup(o);
    }
    ll Query(int o, int l, int r, int ql, int qr) {
        if(ql <= l && r <= qr) return sum[o];
        int mid = (l + r) >> 1; ll ans = 0;
        if(ql <= mid) ans += Query(lson, l, mid, ql, qr);
        if(qr > mid) ans += Query(rson, mid + 1, r, ql, qr);
        return ans;
    }
} seg;

int main(){
    while(~scanf("%d", &n)) {
        printf("Case #%d:\n", ++kase);
        rep(i, n) read(a[i]);
        seg.Build(a, 1, 1, n);
        read(q);
        while(q--) {
            int opt, x, y;
            read(opt), read(x), read(y);\
            if(x > y) swap(x, y);
            if(opt == 0) seg.InterSqrt(1, 1, n, x, y);
            else printf("%lld\n", seg.Query(1, 1, n, x, y));
        }
        putchar('\n');    
    }
    return 0;
}
