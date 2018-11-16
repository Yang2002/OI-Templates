/*
Link: https://cn.vjudge.net/problem/POJ-1151
Algorithm: The joint of areas of rectangles, Scanning line, segment tree
Complexity: O(nlogn)
Note: The segment tree here can't support full queries on interval union.
      As the modifying operations here always come in pairs and with +1 first
      and then -1, we don't need to push down the tags.
*/

#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<map>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;

const int maxn = 2200;
const double eps = 1e-7;
int n;

map<double, int> val;
double raw[maxn];
int mcnt = 0, ecnt = 0;

struct rect {
    double xa, ya, xb, yb;
    inline void init() {
        scanf("%lf %lf %lf %lf", &xa, &ya, &xb, &yb);
        val[ya] = val[yb] = 1;
    }
} re[maxn];

struct Event {
    double xp;
    int yp1, yp2, tp;
    Event(double a = 0, double b = 0, double c = 0, int d = 0) : 
        xp(a), yp1(val[b]), yp2(val[c]), tp(d) { }
    bool operator < (const Event& ev) const {
        return xp < ev.xp;
    }
} e[maxn];

struct SegmentTree {
    #define lson (o << 1)
    #define rson (o << 1 | 1)

    private:
    double len[maxn];
    int cnt[maxn], sz;
    inline void pushup(int o, int l, int r) {
        if(cnt[o]) len[o] = raw[r + 1] - raw[l];
        else len[o] = len[lson] + len[rson];
    }
    void modify(int o, int l, int r, int ql, int qr, int tp) {
        if(ql <= l && r <= qr) {
            cnt[o] += tp;
            pushup(o, l, r);
            return ;
        }
        int mid = (l + r) >> 1;
        if(ql <= mid) modify(lson, l, mid, ql, qr, tp);
        if(qr > mid) modify(rson, mid + 1, r, ql, qr, tp);
        pushup(o, l, r);
    }

    public:
    inline void Build(int size) {
        sz = size;
        memset(len, 0, sizeof len);
        memset(cnt, 0, sizeof cnt);
    }
    double query(int o, int l, int r, int ql, int qr) {
        pushup(o, l, r);
        if(ql <= l && r <= qr) return len[o];
        double ans = 0.0;
        int mid = (l + r) >> 1;
        if( ql <= mid ) ans += query(lson, l, mid, ql, qr);
        if( qr >  mid ) ans += query(rson, mid + 1, r, ql, qr);
        return ans;
    }
    inline void Modify(int l, int r, int tp) { modify(1, 1, sz, l, r, tp); }
    inline double Query(int l, int r) { return query(1, 1, sz, l, r); }
} seg;

int main(){
    #ifdef FREOPEN
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int kase = 0;
    while(~scanf("%d", &n) && n) {
        printf("Test case #%d\n", ++kase);
        val.clear(), mcnt = ecnt = 0;
        for(int i = 1; i <= n; ++i) re[i].init();
        for(map<double, int>::iterator it = val.begin(); it != val.end(); ++it) {
            it->second = ++mcnt;
            raw[mcnt] = it->first;
        }
        for(int i = 1; i <= n; ++i) {
            e[++ecnt] = Event(re[i].xa, re[i].ya, re[i].yb,  1);
            e[++ecnt] = Event(re[i].xb, re[i].ya, re[i].yb, -1);
        }
        sort(e + 1, e + 1 + ecnt);
        seg.Build(mcnt - 1);
        int p = 1; double ans = 0.0;
        while(p <= ecnt) {
            seg.Modify(e[p].yp1, e[p].yp2 - 1, e[p].tp); 
            if(p < ecnt && fabs(e[p+1].xp - e[p].xp) > eps) {
                ans += seg.Query(1, mcnt-1) * (e[p+1].xp - e[p].xp);
            }
            ++p;
        }     
        printf("Total explored area: %.2f\n\n", ans);
    }
    return 0;
}
