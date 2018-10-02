// Segment Tree: supports interval modify and range minimum query / range sum query
// Complexity: O(n) to build the tree, O(logn) to modify and query
// Interface:
// build(ll* array, 1, 1, n) to build array[1...n]
// modify(1, 1, n, ql, qr, v) to let array[ql...qr] += v
// query(1, 1, n, ql, qr) to find sum of array[ql...qr]

#include<cstdio>
#include<cstring>
#include<cctype>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
const int maxn = 100200;
ll a[maxn];
int n, q;
template<typename T> void read(T &x){
    x = 0; int f = 1; char ch = getchar();
    while(!isdigit(ch) ) { if(ch == '-') f *= -1; ch = getchar();}
    while( isdigit(ch) ) {x = x * 10 + ch - 48; ch = getchar();}
    x *= f;
}
struct SegmentTree {
    #define lson (o << 1)
    #define rson (o << 1 | 1)
    ll sum[maxn << 2], lazy[maxn << 2];
    inline void pushup(int o) {sum[o] = sum[lson] + sum[rson];}
    inline void pushdown(int o, int l, int r) {
        if(!lazy[o]) return;
        int mid = (l + r) >> 1;
        sum[lson] += (mid - l + 1) * lazy[o];
        sum[rson] += (r - mid) * lazy[o];
        lazy[lson] += lazy[o], lazy[rson] += lazy[o];
        lazy[o] = 0;
    }
    void build (ll* arr, int o, int l, int r) {
        lazy[o] = 0;
        if(l == r) {sum[o] = arr[l]; return;}
        int mid = (l + r) >> 1;
        build(arr, lson, l, mid);
        build(arr, rson, mid + 1, r);
        pushup(o);
    }
    ll query(int o, int l, int r, int ql, int qr) {
        if(ql <= l && r <= qr) return sum[o];
        int mid = (l + r) >> 1; ll ans = 0;
        pushdown(o, l, r);
        if(ql <= mid) ans += query(lson, l, mid, ql, qr);
        if(qr > mid) ans += query(rson, mid + 1, r, ql, qr);
        return ans;
    }
    void modify(int o, int l, int r, int ql, int qr, ll v) {
        if(ql <= l && r <= qr) {sum[o] += v * (r - l + 1); lazy[o] += v; return;}
        int mid = (l + r) >> 1;
        pushdown(o, l, r);
        if(ql <= mid) modify(lson, l, mid, ql, qr, v);
        if(qr > mid) modify(rson, mid + 1, r, ql, qr, v);
        pushup(o);
    }
} seg;
int main(){
    read(n), read(q);
    rep(i, n) read(a[i]);
    seg.build(a, 1, 1, n);
    while(q--) {
        int x, y, opt; ll v;
        read(opt), read(x), read(y);
        if(opt == 1) read(v), seg.modify(1, 1, n, x, y, v);
        else printf("%lld\n", seg.query(1, 1, n, x, y));
    }
    return 0;
}
