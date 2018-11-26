/*
  Link: https://cn.vjudge.net/problem/POJ-2104
  Source: 算法竞赛进阶指南
  “对于原序列的每一个前缀[1···i]建立出一棵线段树维护值域上每个数出现的次数，则其树是可减的”
  也有整体分治（离线）、树套树（动态、在线）与归并树的方法（在线）
*/

#include<cstdio>
#include<cctype>
#include<map>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;

template<typename T> void read(T &x){
    x = 0; int f = 1; char ch = getchar();
    while(!isdigit(ch) ) { if(ch == '-') f = -1; ch = getchar();}
    while( isdigit(ch) ) {x = x * 10 + ch - 48; ch = getchar();}
    x *= f;
}
template<typename T, typename... Args> void read(T& x, Args&... args)
{ read(x), read(args...); }

const int maxn = 200200;
int n, m, roots[maxn], a[maxn], tot = 0, mcnt = 0;
map<int, int> mp;
int raw[maxn];

struct node {
    int lc, rc, cnt;
    node(int x = 0, int y = 0, int z = 0): 
        lc(x), rc(y), cnt(z) { }
} tr[maxn * 50];
inline void pushup(int nd) {
    tr[nd].cnt = tr[ tr[nd].lc ].cnt + tr[ tr[nd].rc ].cnt;
}

int Insert(int v, int now, int l, int r) {
    int p = ++tot; tr[p] = tr[now];
    if(l == r) { tr[p].cnt++; return p; }
    int mid = (l + r) >> 1;
    if(v <= mid) tr[p].lc = Insert(v, tr[now].lc, l, mid);
    else tr[p].rc = Insert(v, tr[p].rc, mid + 1, r);
    pushup(p);
    return p;
}

// p: from root[l-1], q: from root[r]
int Query(int p, int q, int l, int r, int kth) {
    if(l == r) return l;
    int mid = (l + r) >> 1, lcnt = tr[ tr[q].lc ].cnt - tr[ tr[p].lc ].cnt;
    if(kth <= lcnt) return Query(tr[p].lc, tr[q].lc, l, mid, kth);
    else return Query(tr[p].rc, tr[q].rc, mid + 1, r, kth - lcnt);
}

int main() {
    read(n, m);
    rep(i, n) read(a[i]), mp[a[i]] = 1;
    for(map<int,int>::iterator it = mp.begin(); it != mp.end(); ++it) {
        raw[++mcnt] = it->first;
        it->second = mcnt;
    }
    roots[0] = ++tot;
    rep(i, n) roots[i] = Insert(mp[a[i]], roots[i-1], 1, mcnt);
   
    rep(i, m) {
        int li, ri, kth;
        read(li, ri, kth);
        printf("%d\n", raw[Query(roots[li - 1], roots[ri], 1, mcnt, kth)]);
    }
    return 0;
}
