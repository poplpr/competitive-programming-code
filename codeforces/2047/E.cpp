/*
 * @Author: poplpr
 * @Date: 2024-12-06 23:04:37
 * @Description: competitive programming code
 */
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using db = double;
using ld = long double;
using pii = pair<int, int>;

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) (int)(x).size()
#define dbg(x) cout << #x << " = " << x << ", "
#define dbg2(x) cout << #x << " = " << x << endl

template<typename T> void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    while (!isdigit(c)) { if (c == '-') f = -1; c = getchar(); }
    while (isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
    x *= f;
}

template<typename T, typename... Args> void read(T &x, Args&... args) {
    read(x); read(args...);
}

template<typename T> void write(T x) {
    static int buf[42];
    int p = 0;
    if (x < 0) putchar('-'), x = -x;
    if (x == 0) return putchar('0'), void();
    while(x) {
        buf[p++] = x % 10;
        x /= 10;
    }
    for (int i = p - 1; i >= 0; i--) putchar(buf[i] + '0');
}
namespace atcoder {

namespace internal {

#ifndef _MSC_VER
template <class T>
using is_signed_int128 =
    typename std::conditional<std::is_same<T, __int128_t>::value ||
                                  std::is_same<T, __int128>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using is_unsigned_int128 =
    typename std::conditional<std::is_same<T, __uint128_t>::value ||
                                  std::is_same<T, unsigned __int128>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using make_unsigned_int128 =
    typename std::conditional<std::is_same<T, __int128_t>::value,
                              __uint128_t,
                              unsigned __int128>;

template <class T>
using is_integral = typename std::conditional<std::is_integral<T>::value ||
                                                  is_signed_int128<T>::value ||
                                                  is_unsigned_int128<T>::value,
                                              std::true_type,
                                              std::false_type>::type;

template <class T>
using is_signed_int = typename std::conditional<(is_integral<T>::value &&
                                                 std::is_signed<T>::value) ||
                                                    is_signed_int128<T>::value,
                                                std::true_type,
                                                std::false_type>::type;

template <class T>
using is_unsigned_int =
    typename std::conditional<(is_integral<T>::value &&
                               std::is_unsigned<T>::value) ||
                                  is_unsigned_int128<T>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using to_unsigned = typename std::conditional<
    is_signed_int128<T>::value,
    make_unsigned_int128<T>,
    typename std::conditional<std::is_signed<T>::value,
                              std::make_unsigned<T>,
                              std::common_type<T>>::type>::type;

#else

template <class T> using is_integral = typename std::is_integral<T>;

template <class T>
using is_signed_int =
    typename std::conditional<is_integral<T>::value && std::is_signed<T>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using is_unsigned_int =
    typename std::conditional<is_integral<T>::value &&
                                  std::is_unsigned<T>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using to_unsigned = typename std::conditional<is_signed_int<T>::value,
                                              std::make_unsigned<T>,
                                              std::common_type<T>>::type;

#endif

template <class T>
using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;

template <class T>
using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;

template <class T> using to_unsigned_t = typename to_unsigned<T>::type;

}  // namespace internal

// Reference: https://en.wikipedia.org/wiki/Fenwick_tree
template <class T> struct fenwick_tree {
    using U = internal::to_unsigned_t<T>;

  public:
    fenwick_tree() : _n(0) {}
    explicit fenwick_tree(int n) : _n(n), data(n) {}

    void add(int p, const T& x) {
        assert(0 <= p && p < _n);
        p++;
        while (p <= _n) {
            data[p - 1] += U(x);
            p += p & -p;
        }
    }

    T sum(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        return sum(r) - sum(l);
    }

    /**
     * 返回前缀和 [0, ret) 小于等于 v 的最后一个位置。
     * params::v >= 0
     */
    int max_right(const T& v) {
        int ret = 0;
        U now{};
        for (int i = 1 << std::__lg(_n); i != 0; i >>= 1) {
            if (ret + i <= _n && now + data[ret + i - 1] <= v) {
                ret += i;
                now = now + data[ret - 1];
            }
        }
        return ret;
    }

  private:
    int _n;
    std::vector<U> data;

    U sum(int r) {
        U s = 0;
        while (r > 0) {
            s += data[r - 1];
            r -= r & -r;
        }
        return s;
    }
};

}  // namespace atcoder
void solve() {
    int n; read(n);
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        read(x[i]); read(y[i]);
    }
    auto xd = x, yd = y;
    
    sort(xd.begin(), xd.end());
    sort(yd.begin(), yd.end());

    xd.erase(unique(xd.begin(), xd.end()), xd.end());
    yd.erase(unique(yd.begin(), yd.end()), yd.end());

    for (int i = 0; i < n; i++) {
        x[i] = lower_bound(xd.begin(), xd.end(), x[i]) - xd.begin();
        y[i] = lower_bound(yd.begin(), yd.end(), y[i]) - yd.begin();
    }

    atcoder::fenwick_tree<int> fl(n), fr(n);
    for (int i = 0; i < n; i++) {
        fr.add(y[i], +1);
    }

    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    sort(p.begin(), p.end(), [&](int a, int b) { return x[a] < x[b];});

    int ans = 0;
    int ansx = 0, ansy = 0;

    for (int i = 0; i < n; i++) {
        int pi = p[i];
        fl.add(y[i], +1);
        fr.add(y[i], -1);

        if (i + 1 < n && x[p[i+1]] == x[pi]) continue;

        // 枚举答案
        for (;2 * (ans + 1) <= i + 1 && 2 * (ans + 1) <= n - i - 1;) {
            // 找到 sum( [0, y) ) >= ans + 1 且 sum ( [y, n) ) >= ans + 1
            // sum( [0, yl) ) <= ans
            // sum( [yr, n) ) >= ans + 1
            // 所以 y in [yl + 1, yr] 都满足条件

            int yl = max(fl.max_right(ans), fr.max_right(ans));
            int yr = min(fl.max_right(i + 1 - (ans + 1)), fr.max_right(n - (i + 1) - (ans + 1)));
            if (yl > yr) break;
            ans++;
            ansx = xd[x[pi]] + 1;
            ansy = yd[yr];
        }
    }
    write(ans); putchar(10);
    write(ansx); putchar(32); write(ansy); putchar(10);
}


int main() {
#ifdef LOCAL
    freopen("test.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    read(T);
    while (T--) solve();
    return 0;
}