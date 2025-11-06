class Solution {
public:
    class UnionFind {
public:
    vector<int> parent;
    UnionFind(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px != py)
            parent[px] = py;
    }
};


    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
        UnionFind uf(c + 1);

        // Step 1: Build the power grids (connected components)
        for (auto& e : connections)
            uf.unite(e[0], e[1]);

        // Step 2: Group stations by their root (component)
        unordered_map<int, deque<int>> groups;
        for (int i = 1; i <= c; i++)
            groups[uf.find(i)].push_back(i);

        // Step 3: Process queries
        vector<bool> online(c + 1, true);
        vector<int> ans;

        for (auto& q : queries) {
            int type = q[0], x = q[1];

            if (type == 2) { // go offline
                online[x] = false;
            } 
            else { // type == 1 : maintenance check
                if (online[x]) {
                    ans.push_back(x);
                    continue;
                }
                int g = uf.find(x);
                auto& dq = groups[g];
                while (!dq.empty() && !online[dq.front()])
                    dq.pop_front();

                if (!dq.empty()) ans.push_back(dq.front());
                else ans.push_back(-1);
            }
        }

        return ans;
    }
};