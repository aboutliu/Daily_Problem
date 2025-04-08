结论：$p^k|ans$ 当且仅当至少 $n-1$ 个 $a_i$ 有 $p^k|a_i$ 。

证明：如果少于 $n-1$ ，那么至少能找出一对 $(i,j),i \ne j,p^k \nmid a_i,p^k \nmid a_j$ ，此时 $lcm(a_i,a_j)$ 里质因数 $p$ 的最高幂小于 $k$ ，所以 $p^k \nmid lcm(a_i, a_j)$ 。

- $solution_1$ ：令 $d_i=gcd(a_1,...,a_{i-1},a_{i+1},...,a_n)$ ，那么 $ans=lcm(d_1,d_2,...,d_n)$ 。那么处理前缀，后缀 $gcd$ 就行。
- $solution_2$ ：枚举范围内的每个质因数 ，发现有两个不能整除的就剪枝，我们只需要记录下最小幂和次小幂，一般选择次小幂因为结论，但是如果次小不存在选择最小幂。那么 $ans*=p_1^{k_1} \times p_2^{k_2} \times ...$ 。


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

    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }   

    std::vector<int> pref(n + 1), suf(n + 2);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = std::gcd(pref[i], a[i]);
    }
    for (int i = n - 1; i >= 0; --i) {
        suf[i + 1] = std::gcd(suf[i + 2], a[i]);
    }

    i64 ans;
    for (int i = 1; i <= n; ++i) {
        if (i == 1) {
            ans = suf[2];
        } else if (i == n) {
            ans = std::lcm(ans, pref[n - 1]);
        } else {
            ans = std::lcm(ans, std::gcd(pref[i - 1], suf[i + 1]));
        }
    }
    std::cout << ans;

    return 0;
}
```

```cpp
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

struct Sieve {
    int n;
    std::vector<int> pri, isp, mn;
    Sieve() {}
    Sieve(int _) {
        init(_);
    }
    void init(int _) {
        n = _;
        mn.resize(n + 1);
        isp.resize(n + 1);
        work();
    }
    void work() {
        for (int i = 2; i <= n; ++i) {
            if (!isp[i]) {
                pri.emplace_back(i);
                mn[i] = i;
            }
            for (int j = 0; j < pri.size() && i * pri[j] <= n; ++j) {
                isp[i * pri[j]] = 1;
                mn[i * pri[j]] = pri[j];
                if (!(i % pri[j])) {
                    break;
                }
            }
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }   

    int range = *max_element(a.begin(), a.end());
    Sieve si(range);

    i64 ans = 1;
    for (auto i : si.pri) {
        int c = 0;
        int min = 1E9, sec = 1E9;
        for (auto j : a) {
            c += j % i > 0;
            if (c == 2) {
                break;
            }
            int tc = 0;
            while (j % i == 0) {
                tc++;
                j /= i;
            }
            if (tc < min) {
                sec = min;
                min = tc;
            } else if (tc < sec) {
                sec = tc;
            }
        }
        if (c == 2) {
            continue;
        }
        if (sec == 1E9) {
            ans *= std::pow(i, min);
        } else {
            ans *= std::pow(i, sec);
        }
    }
    std::cout << ans;

    return 0;
}
```

