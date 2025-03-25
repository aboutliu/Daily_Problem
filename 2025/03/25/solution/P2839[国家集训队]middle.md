中位数可以用二分的办法来查询，假设二分答案 $x$ ，把大于等于 $x$ 的值视为 $1$ ，其余视为 $-1$ 。那么当区间和大于等于 $0$ 即小于等于中位数，当区间和小于等于 $0$ 即大于等于中位数。使用主席树可以优化这个处理。

对于最大中位数，其实就是区间和最大，那么对于 $[b+1,c-1]$ 是必须取的，$[a,b],[c,d]$ 分别应该取最大后缀和，最大前缀和。

说一下主席树处理过程，一开始全部赋值 $1$ ，将序列升序，版本即升序后的 $id$ ，单点更新是按照原序列 $id$ ，因为我们查询的原区间的区间和。

时间复杂度 $O(n \cdot logn + q \cdot log^2n)$ 。

```cpp 
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

template <class Info>
struct PersistentTree {
    int n, tot = 0;
    std::vector<int> rt;
    std::vector<Info> per;
    PersistentTree() {}
    PersistentTree(int _, int m) : n(m), rt(_ + 2), per(_ << 6) {} // _ 是 rt 长度，n 是值域大小
    PersistentTree(int _, std::vector<int> a) : PersistentTree(_, a.size()) {
        auto build = [&](auto &&self, int &p, int l, int r) -> void {
            p = ++tot;
            if (l == r) {
                per[p].apply(a[l - 1]);
                return;
            }
            int mid = (l + r) / 2;
            self(self, per[p].l, l, mid);
            self(self, per[p].r, mid + 1, r);
            pushup(p);
        };

        build(build, rt[1], 1, n);
    }
    void init(int _, int m) {
        n = m;
        rt.resize(_ + 1);
        per.resize(_ << 5);
    }
    void pushup(int i) {
        int l = per[i].l, r = per[i].r;
        per[i] = per[l] + per[r];
        per[i].l = l;
        per[i].r = r;
    }
    int modify(int p, int l, int r, int ind, int v) {
        per[++tot] = per[p];
        p = tot;
        if (l == r) {
            per[p].apply(v);
            return p;
        }
        int mid = (l + r) / 2;
        if (ind <= mid) {
            per[p].l = modify(per[p].l, l, mid, ind, v);
        } else {
            per[p].r = modify(per[p].r, mid + 1, r, ind, v);
        }
        pushup(p);
        return p;
    }
    void modify(int u, int v, int p, int s) {
        rt[u] = modify(rt[v], 1, n, p, s);
    }
    Info rangeInfo(int u, int v, int l, int r, int x, int y) {
        if (x > r || y < l || x > y) {
            return Info().inf();
        }
        if (x <= l && r <= y) {
            return per[v] - per[u];
        }
        int mid = (l + r) / 2;
        return rangeInfo(per[u].l, per[v].l, l, mid, x, y) + rangeInfo(per[u].r, per[v].r, mid + 1, r, x, y);
    }
    Info rangeInfo(int u, int v, int l, int r) {
        return rangeInfo(rt[u], rt[v], 1, n, l, r);
    }
    Info rangeInfo(int v, int l, int r) {
        return rangeInfo(rt[0], rt[v], 1, n, l, r);
    }
    template <class F>
    int findFirst(int u, int v, int l, int r, int x, int y, F &&pred, Info d) {
        if (x > r || y < l || x > y || !pred(per[v] - per[u] + d)) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        int mid = (l + r) / 2;
        int res = findFirst(per[u].l, per[v].l, l, mid, x, y, pred, d);
        if (res == -1) {
            Info ls = per[per[v].l] - per[per[u].l];
            res = findFirst(per[u].r, per[v].r, mid + 1, r, x, y, pred, d + ls);
        }
        return res;
    }
    template <class F>
    int findFirst(int u, int v, int x, int y, F &&pred) {
        return findFirst(u, v, 1, n, x, y, pred, Info());
    }
    template <class F>
    int findFirst(int v, int x, int y, F &&pred) {
        return findFirst(rt[0], rt[v], 1, n, x, y, pred, Info());
    }
    template <class F>
    int findLast(int u, int v, int l, int r, int x, int y, F &&pred, Info d) {
        if (x > r || y < l || x > y || !pred(per[v] - per[u] + d)) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        int mid = (l + r) / 2;
        int res = findLast(per[u].r, per[v].r, mid + 1, r, pred, d);
        if (res == -1) {
            Info rs = per[per[v].r] - per[per[u].r];
            return findLast(per[u].l, per[v].l, l, mid, x, y, pred, d + rs);
        }
        return res;
    }
    template <class F>
    int findLast(int u, int v, int x, int y, F &&pred) {
        return findLast(u, v, 1, n, x, y, pred, Info());
    }
    template <class F>
    int findLast(int v, int x, int y, F &&pred) {
        return findLast(rt[v], 1, n, x, y, pred, Info());
    }
};

struct Info {
    int l, r;
    int sum;
    int pref;
    int suf;
    void apply(int x) {
        pref = suf = sum = x;
    }
    Info inf() { // 阻断值
        Info res {0, 0, 0, int(-1E9), int(-1E9)};
        return res;
    }
};

Info operator + (const Info &u, const Info &v) {
    Info res {};
    res.sum = u.sum + v.sum;
    res.pref = std::max(u.pref, u.sum + v.pref);
    res.suf = std::max(v.suf, v.sum + u.suf);
    return res;
}

Info operator - (const Info &u, const Info &v) {
    Info res {};
    res.sum = u.sum - v.sum;
    res.pref = u.pref - v.pref;
    res.suf = u.suf - v.suf;
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::array<int, 2>> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i][0];
        a[i][1] = i;
    }
    std::sort(a.begin(), a.end());

    std::vector<int> b(n, 1);
    PersistentTree<Info> per(n, b);

    for (int i = 1; i <= n; ++i) {
        per.modify(i + 1, i, a[i - 1][1] + 1, -1);
    }

    int q;
    std::cin >> q;

    auto check = [&](int x, auto tq) -> int {
        auto [l1, r1, l2, r2] = tq;
        int sum = 0;
        if (l2 - 1 >= r1 + 1) {
            sum = per.rangeInfo(x, r1 + 1, l2 - 1).sum;
        }
        sum += per.rangeInfo(x, l1, r1).suf;
        sum += per.rangeInfo(x, l2, r2).pref;
        return sum >= 0;
    };

    int ans = 0;
    while (q--) {
        std::array<int, 4> Q;
        for (int i = 0; i < 4; ++i) {
            std::cin >> Q[i];
            Q[i] = (ans + Q[i]) % n + 1;
        }
        std::sort(Q.begin(), Q.end());

        int lo = 1, hi = n, res = 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (check(mid, Q)) {
                res = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        ans = a[res - 1][0];
        std::cout << ans << "\n";
    }

    return 0;
}
```

