#include <vector>
#include <iostream>
using namespace std;

#define ll long long

class SegmentTree
{
public:
    vector<ll> tree;
    int n;

    SegmentTree(int size)
    {
        n = size;
        tree.resize(4 * n, 0);
    }

    void build(vector<ll> &arr, int v, int tl, int tr)
    {
        if (tl == tr)
        {
            tree[v] = arr[tl];
        }
        else
        {
            int tm = (tl + tr) / 2;
            build(arr, v * 2, tl, tm);
            build(arr, v * 2 + 1, tm + 1, tr);
            tree[v] = tree[v * 2] + tree[v * 2 + 1];
        }
    }

    ll sum(int v, int tl, int tr, int l, int r)
    {
        if (l > r)
            return 0;
        if (l == tl && r == tr)
            return tree[v];
        int tm = (tl + tr) / 2;
        return sum(v * 2, tl, tm, l, min(r, tm)) + sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
    }

    void update(int v, int tl, int tr, int pos, ll new_val)
    {
        if (tl == tr)
        {
            tree[v] = new_val;
        }
        else
        {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
            {
                update(v * 2, tl, tm, pos, new_val);
            }
            else
            {
                update(v * 2 + 1, tm + 1, tr, pos, new_val);
            }
            tree[v] = tree[v * 2] + tree[v * 2 + 1];
        }
    }
};

int main()
{
    int n;
    cin >> n;
    vector<ll> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    SegmentTree st(n);
    st.build(arr, 1, 0, n - 1);

    // Example usage
    int q;
    cin >> q;
    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int l, r;
            cin >> l >> r;
            cout << st.sum(1, 0, n - 1, l, r) << endl;
        }
        else if (type == 2)
        {
            int pos;
            ll new_val;
            cin >> pos >> new_val;
            st.update(1, 0, n - 1, pos, new_val);
        }
    }
    return 0;
}
