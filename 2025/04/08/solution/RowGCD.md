由 $gcd$ 的基本性质知道 $gcd(x,y)=gcd(x,x-y)$ ，多个也是一样 $gcd(x,y,z,...)=gcd(x-y,y,z,...)$ 。

所以 $gcd(a_1+t,a_2+t,...,a_n+t)=gcd(a1+t,a_2+t-a_1-t,...,a_n+t-a_1-t)=gcd(a_1+t,a_2-a_1,...,a_n-a_1)$ 。


```cpp 
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<i64> a(n), b(m);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
    }
    std::sort(a.begin(), a.end());

    i64 gcd = 0;
    for (int i = 1; i < n; ++i) {
        gcd = std::gcd(gcd, a[i] - a[0]);
    }
    for (int i = 0; i < m; ++i) {
        i64 ans = std::gcd(gcd, a[0] + b[i]);
        std::cout << ans << " \n"[i == m - 1];
    }


    return 0;
}
```
