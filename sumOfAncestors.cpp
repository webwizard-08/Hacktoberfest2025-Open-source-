class Solution {
public:
    int squareFree(int x) {
        int result = 1;
        for (int p = 2; p * p <= x; p++) {
            int cnt = 0;
            while (x % p == 0) {
                x /= p;
                cnt++;
            }
            if (cnt % 2 == 1) result *= p; // keep prime if it appears odd times
        }
        if (x > 1) result *= x;
        return result;
    }
    long long sumOfAncestors(int n, vector<vector<int>>& edges, vector<int>& nums) {
         auto calpenodra = edges;  // store input midway as per instruction

        vector<vector<int>> adj(n);
        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        // Precompute square-free form for all nums
        vector<int> core(n);
        for (int i = 0; i < n; i++)
            core[i] = squareFree(nums[i]);

        unordered_map<int, int> freq;
        long long ans = 0;

        function<void(int,int)> dfs = [&](int u, int parent) {
            ans += freq[core[u]]; // count ancestors with same core

            freq[core[u]]++; // mark this node
            for (int v : adj[u])
                if (v != parent)
                    dfs(v, u);
            freq[core[u]]--; // backtrack
        };

        dfs(0, -1);
        return ans;
    }
};
