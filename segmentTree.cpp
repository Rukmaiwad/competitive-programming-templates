#include<bits/stdc++.h>
using namespace std;

#define ll long long

class SegmentTree {
public:
    vector<ll> seg;

    SegmentTree(ll n) {
        seg.resize(4 * n + 1);
    }

    void build(ll ind, ll low, ll high, ll arr[]) {
        if (low == high) {
            seg[ind] = arr[low];
            return;
        }
        ll mid = (low + high) / 2;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);
        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    ll query(ll ind, ll low, ll high, ll l, ll r) {
        // no overlap
        if (r < low || high < l) return LLONG_MAX;

        // complete overlap
        if (low >= l && high <= r) return seg[ind];

        // partial overlap
        ll mid = (low + high) >> 1;
        ll left = query(2 * ind + 1, low, mid, l, r);
        ll right = query(2 * ind + 2, mid + 1, high, l, r);
        return min(left, right);
    }

    void update(ll ind, ll low, ll high, ll i, ll val) {
        if (low == high) {
            seg[ind] = val;
            return;
        }
        ll mid = (low + high) >> 1;
        if (i <= mid) update(2 * ind + 1, low, mid, i, val);
        else update(2 * ind + 2, mid + 1, high, i, val);
        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
};

void solve2() {
    // if(two arrays are given as input create 2 instance of class)
    ll n1;
    cin >> n1;
    ll arr1[n1];
    for (ll i = 0; i < n1; i++) cin >> arr1[i];
    SegmentTree sg1(n1);
    sg1.build(0, 0, n1 - 1, arr1);

    ll n2;
    cin >> n2;
    ll arr2[n2];
    for (ll i = 0; i < n2; i++) cin >> arr2[i];
    SegmentTree sg2(n2);
    sg2.build(0, 0, n2 - 1, arr2);

    ll q;
    cin >> q;
    while (q--) {
        ll type;
        cin >> type;
        if (type == 1) {
            ll l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;
            ll min1 = sg1.query(0, 0, n1 - 1, l1, r1);
            ll min2 = sg2.query(0, 0, n2 - 1, l2, r2);
            cout << min(min1, min2) << endl;
        } else {
            ll arrNo, i, val;
            cin >> arrNo >> i >> val;
            if (arrNo == 1) {
                sg1.update(0, 0, n1 - 1, i, val);
                arr1[i] = val;
            } else {
                sg2.update(0, 0, n2 - 1, i, val);
                arr2[i] = val;
            }
        }
    }
}

int main() {
    solve2();
    return 0;
}
