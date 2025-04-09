可以考虑双指针，也可以用辅助数组记录一下下标。


```cpp 
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

template <class T>
struct BitTrie {
    int id = 0, N;
    std::vector<std::array<int, 2>> trie {std::array<int, 2>()};
    std::vector<int> cnt {1000000000};
    BitTrie() {}
    BitTrie(int _) {
        init(_);
    }
    void init(int _) {
        N = _;
        id = 0;
        cnt.assign(1, 1E9);
        trie.assign(1, std::array<int, 2>());
    }
    void insert(int x, int v) {
        int p = 0;
        for (int i = N - 1; i >= 0; --i) {
            int it = x >> i & 1;
            if (!trie[p][it]) {
                trie[p][it] = ++id;
                trie.push_back(std::array<int, 2>());
                cnt.push_back(1E9);
            }
            p = trie[p][it];
            cnt[p] = std::min(cnt[p], v);
        }
    }
    int find(int u, int x) {
        int p = 0, res = 1E9;
        for (int i = N - 1; i >= 0; --i) {
            int it = u >> i & 1, bx = x >> i & 1;
            if (!bx) {
                if (trie[p][it ^ 1]) {
                    res = std::min(res, cnt[trie[p][it ^ 1]]);
                }
                p = trie[p][it];
            } else {
                p = trie[p][it ^ 1];
            }
            if (!i) {
                res = std::min(res, cnt[p]);
            }
            if (!p) {
                break;
            }
        }
        return res;
    }
};

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    if (!k) {
        std::cout << "1\n";
        return;
    }

    int range = *max_element(a.begin(), a.end());
    BitTrie<int> bit(std::bit_width(1U * std::max(k, range)));

    int tans = 1E9;
    for (int i = n - 1; i >= 0; --i) {
        bit.insert(a[i], i);
        int res = bit.find(a[i], k);
        if (res == 1E9) {
            continue;
        }
        // std::cerr << i << " " << res << "\n";
        tans = std::min(tans, res - i + 1);
    }

    int ans = tans == 1E9 ? -1 : tans;
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

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

template <class T>
struct BitTrie {
    int id = 0, N;
    std::vector<std::array<int, 2>> trie {std::array<int, 2>()};
    std::vector<int> cnt {0};
    BitTrie() {}
    BitTrie(int _) {
        init(_);
    }
    void init(int _) {
        N = _;
        id = 0;
        cnt.assign(1, 0);
        trie.assign(1, std::array<int, 2>());
    }
    void insert(int x, int v) {
        int p = 0;
        for (int i = N - 1; i >= 0; --i) {
            int it = x >> i & 1;
            if (!trie[p][it]) {
                trie[p][it] = ++id;
                trie.push_back(std::array<int, 2>());
                cnt.push_back(0);
            }
            p = trie[p][it];
            cnt[p] += v;
        }
    }
    int find(int u, int x) {
        int p = 0, res = 0;
        for (int i = N - 1; i >= 0; --i) {
            int it = u >> i & 1, bx = x >> i & 1;
            if (!bx) {
                if (trie[p][it ^ 1]) {
                    res |= cnt[trie[p][it ^ 1]];
                }
                p = trie[p][it];
            } else {
                p = trie[p][it ^ 1];
            }
            if (!i) {
                res |= cnt[p];
            }
            if (!p) {
                break;
            }
        }
        return res;
    }
};

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    if (!k) {
        std::cout << "1\n";
        return;
    }

    int range = *max_element(a.begin(), a.end());
    BitTrie<int> bit(std::bit_width(1U * std::max(k, range)));

    int tans = 1E9;
    for (int i = n - 1, j = n - 1; i >= 0; --i) {
        bit.insert(a[i], 1);
        while (j >= i && bit.find(a[i], k) > 0) {
            tans = std::min(tans, j - i + 1);
            bit.insert(a[j], -1);
            j--;
        }
    }

    // bit.insert(3, 1);
    // std::cerr << bit.find(3, 3) << "\n";

    int ans = tans == 1E9 ? -1 : tans;
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
```

