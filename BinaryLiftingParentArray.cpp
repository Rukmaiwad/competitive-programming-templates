#include <bits/stdc++.h>
using namespace std;
#define ll long long

class BinaryLifting
{
public:
    vector<vector<ll>> anc;
    int maxLog;
    vector<int> levelsArray;
    vector<vector<ll>> adj;

    BinaryLifting(int n, vector<int> &parArray)
    {
        maxLog = 21; // Sufficient for n up to 2^21 - 1
        anc.resize(n + 1, vector<ll>(maxLog, -1));
        adj.resize(n + 1, vector<ll>());
        levelsArray = vector<int>(n + 1, 0);

        // Initialize the first ancestor (2^0 = 1 step) from parArray
        for (int i = 2; i <= n; i++)
        {
            // Creating adjacency list
            adj[i].push_back(parArray[i - 2]);
            adj[parArray[i - 2]].push_back(i);
            anc[i][0] = parArray[i - 2];
        }

        // Fill the Binary Lifting table
        for (int j = 1; j < maxLog; j++)
        {
            for (int i = 1; i <= n; i++)
            {
                if (anc[i][j - 1] != -1)
                {
                    anc[i][j] = anc[anc[i][j - 1]][j - 1];
                }
            }
        }
    }

    // Function to find kth ancestor and node u
    ll kanc(ll u, ll k)
    {
        if (u < 1)
            return -1;
        for (int j = maxLog - 1; j >= 0; j--)
        {
            if ((k >> j) & 1)
            {
                u = anc[u][j];
                if (u == -1)
                {
                    return -1;
                }
            }
        }
        return u;
    }

    void levels(int cur, int par)
    {
        levelsArray[cur] = levelsArray[par] + 1;
        for (auto ch : adj[cur])
        {
            if (ch != par)
            {
                levels(ch, cur);
            }
        }
    }

    ll lca(int u, int v)
    {
        if (levelsArray[u] < levelsArray[v])
        {
            swap(u, v);
        }

        ll diff = levelsArray[u] - levelsArray[v];

        for (ll j = 20; j >= 0; j--)
        {
            if ((1 << j) & diff)
            {
                u = anc[u][j];
            }
        }

        if (u == v)
        {
            return u;
        }

        for (ll j = 20; j >= 0; j--)
        {
            if (anc[u][j] != anc[v][j])
            {
                u = anc[u][j];
                v = anc[v][j];
            }
        }
        return anc[u][0];
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t-- > 0)
    {
        int n, q; // Read size of tree and number of queries
        cin >> n >> q;

        // Read input as parent array
        vector<int> parA(n - 1);
        for (int i = 0; i < n - 1; i++)
        {
            cin >> parA[i];
        }

        // Read q number of queries
        vector<vector<int>> queries(q, vector<int>(2));
        for (int i = 0; i < q; i++)
        {
            cin >> queries[i][0] >> queries[i][1];
        }

        BinaryLifting bl(parA.size() + 1, parA); // Adjust size for 1-based indexing

        bl.levels(1, 0); // Initialize levels from root node

        for (auto &query : queries)
        {
            int u = query[0];
            int k = query[1];
            // int res = bl.kanc(u,k);
            int res = bl.lca(u, k);
            cout << res << endl;
        }
    }
    return 0;
}
