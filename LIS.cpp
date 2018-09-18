// Binary search approach to get Longest Increasing Subsequence in O(nlogn) complexity
// Input format: test case + n + n numbers
// dp[i]: LIS which ends at position i
// low[i]: lowest last number of LIS of length i
// As we can show: low[1] <= low[2] <= ... <= low[n]

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
const int maxn = 40050;
int low[maxn], dp[maxn], a[maxn], n;
int main(){
    int T; scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        rep(i, n) scanf("%d", &a[i]);
        memset(low, 0x3f, sizeof low);
        int ans = 0;
        for(int i = 1; i <= n; ++i){
            int k = lower_bound(low + 1, low + 1 + n, a[i]) - low;
            dp[i] = k, low[k] = a[i];
            ans = max(ans, dp[i]);
        }
        printf("%d\n", ans);
    }
    return 0;
}
