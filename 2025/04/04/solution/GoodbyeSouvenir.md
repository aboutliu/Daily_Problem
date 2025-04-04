先不考虑修改。

令 $pre_i$ 表示左边最近的同色的位置，那么可以转化为 $\displaystyle \sum_{l\leq pre_i,i\leq r}i-pre_i$ 。由于 $i > pre_i$ ，所以可以转化为 $(pre_i \ge l)$ 且 $(i \leq r)$ 。

那么将 $(pre_i, i)$ 看做一个点，权值为 $i-pre_i$ 。此时就变成一个二维偏序问题。

但是本题需要修改，修改也很简单，无非就是考虑前后影响（不过多解释），删除的话，可以直接添加一个负权值的点抵消就行。因为修改在时间上天然有序，所以不用变成三维偏序。


```cpp 
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

template <class T>
struct Fenwick {
    int N;
    std::vector<T> f;
    Fenwick() {}
    Fenwick(int _) {
        init(_);
    }
    void init(int _) {
        N = _;
        f.resize(_ + 1);
    }
    void add(int x, T v) {
        for (int i = x; i <= N; i += (i bitand -i)) {
            f[i] += v;
        }
    }
    T query(int x) {
        if (x > N or x <= 0) {
            return T(0);
        }
        T res = 0;
        for (int i = x; i; i -= (i bitand -i)) {
            res += f[i];
        }
        return res;
    }
    T rangesum(int l, int r) {
        if (l > r) {
            return T(0);
        }
        return query(r) - query(l - 1);
    }
    int select(const T &k) {
        int x = 0;
        T cur{};
        for (int i = 1 << std::bit_width(1U * N) - 1; i; i /= 2) {
            if (x + i <= N && cur + f[x + i] <= k) {
                x += i;
                cur = cur + f[x];
            }
        }
        return x;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::array<int, 4>> a;
    std::vector<std::set<int>> set(n + 1);
    std::vector<int> c(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> c[i];

        if (!set[c[i]].empty()) {
            auto pre = std::prev(set[c[i]].end());
            a.emplace_back(std::array {1, *pre, i, 0});
        }
        set[c[i]].emplace(i);
    }

    std::vector<i64> ans(m);
    for (int i = 0; i < m; ++i) {
        int x, y, z;
        std::cin >> x >> y >> z;

        if (x == 1) {
            auto it = set[c[y]].find(y);
            if (std::next(it) != set[c[y]].end()) {
                auto nxt = std::next(it);
                a.emplace_back(std::array {-1, y, *nxt, 0});
                if (it != set[c[y]].begin()) {
                    a.emplace_back(std::array {1, *std::prev(it), *nxt, 0});
                }
            }
            if (it != set[c[y]].begin()) {
                a.emplace_back(std::array {-1, *std::prev(it), y, 0});
            }
            set[c[y]].erase(y);

            c[y] = z;
            set[c[y]].emplace(y);

            it = set[c[y]].find(y);
            if (it != set[c[y]].begin()) {
                a.emplace_back(std::array {1, *std::prev(it), y, 0});
            }
            if (std::next(it) != set[c[y]].end()) {
                a.emplace_back(std::array {1, y, *std::next(it), 0});
                if (it != set[c[y]].begin()) {
                    a.emplace_back(std::array {-1, *std::prev(it), *std::next(it), 0});
                }
            }
            ans[i] = -1;
        } else {
            a.emplace_back(std::array {0, y, z, i});
        }
    }

    Fenwick<i64> fen(n);
    std::vector<std::array<int, 4>> t(a.size());

    auto merge = [&](int l, int r) -> void {
        int i = l, mid = (l + r) / 2, j = mid + 1, k = l;
        while (i <= mid && j <= r) {
            if (a[i][1] >= a[j][1]) {
                if (a[i][0]) {
                    fen.add(a[i][2], a[i][0] * (a[i][2] - a[i][1]));
                }
                t[k++] = a[i++];
            } else {
                if (!a[j][0]) {
                    ans[a[j][3]] += fen.rangesum(1, a[j][2]);
                }
                t[k++] = a[j++];
            }
        }
        while (i <= mid) {
            if (a[i][0]) {
                fen.add(a[i][2], a[i][0] * (a[i][2] - a[i][1]));
            }
            t[k++] = a[i++];
        }
        while (j <= r) {
            if (!a[j][0]) {
                ans[a[j][3]] += fen.rangesum(1, a[j][2]);
            }
            t[k++] = a[j++];
        }
        for (int h = l; h <= mid; ++h) {
            if (a[h][0]) {
                fen.add(a[h][2], -a[h][0] * (a[h][2] - a[h][1]));
            }
        }
        for (int h = l; h <= r; ++h) {
            a[h] = t[h];
        }
    };
    auto split = [&](auto &&self, int l, int r) -> void {
        if (l >= r) {
            return;
        }
        int mid = (l + r) / 2;
        self(self, l, mid);
        self(self, mid + 1, r);
        merge(l, r);
    };

    split(split, 0, a.size() - 1);

    for (int i = 0; i < m; ++i) {
        if (ans[i] == -1) {
            continue;
        }
        std::cout << ans[i] << "\n";
    }

    return 0;
}
```
