// Range Minimum Query O(nlogn) - O(1)

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
#define ABS(x) ( (x)>0 ? (x) : (-(x)) )
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
using namespace std;
typedef long long ll;
const int maxn = 100020;
int m, q, a[maxn];
namespace ST {
    int d[maxn][30], n;
    inline void RMQ_init(int* arr, int sz) {
        n = sz;
        for(int i = 1; i <= n; ++i) d[i][0] = arr[i];
        for(int j = 1; (1 << j) <= n; ++j)
            for(int i = 1; i + (1 << j) - 1 <= n; ++i)
                d[i][j] = max(d[i][j-1], d[i+(1<<(j-1))][j-1]);
    }
    inline int RMQ(int l, int r) {
        int k = 0;
        while((1 << (k + 1)) < r - l + 1) k++;
        return max(d[l][k], d[r-(1<<k)+1][k]);
    }
}
int main(){
    scanf("%d%d", &m, &q);
    rep(i, m) scanf("%d", &a[i]);
    ST::RMQ_init(a, m);
    while(q--) {
        int x, y; scanf("%d%d", &x, &y);
        printf("%d\n", ST::RMQ(x, y));
    }
    return 0;
}
