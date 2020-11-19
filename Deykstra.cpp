//
//  main.cpp
//  Algorithm_Deykstra
//
//  Created by Михаил Остапчук on 26.10.2018.
//  Copyright © 2018 Михаил Остапчук. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>

const int inf = 1000000;

class OrientedGraph {
private:
//    mutable std::vector<std::vector<int>> graph_;
    int size_;
public:
    std::vector<std::vector<int>> graph_;
    OrientedGraph(int n_vertixes) : graph_(n_vertixes) {} // ??
    
    void add_edge(int v, int u, int w) {
        graph_[v].push_back(u);
        graph_[v][u] = w;
    }
    
    int size() {
        return this->size_;
    }
    
};

std::vector<int> FindShortestPaths(OrientedGraph& g, int start) {
    std::vector<int> dist(g.size(), inf);
    std::vector<bool> used(g.size());
    dist[start] = 0;
    std::priority_queue<std::pair<int, int>> q;
    q.push({0,start});
    while (!q.empty()) {
        int v = q.top().second;
        q.pop();
        while (used[v] && !q.empty()) {
            v = q.top().second;
            q.pop();
        }
        if (used[v]) break;
        used[v] = true;
        // ??
        for (auto to : g.graph_[v]) {
            if (dist[to] > dist[v] + g.graph_[v][to]) {
                dist[to] = dist[v] + g.graph_[v][to];
                q.push({-dist[to], to});
                // p[to] = v
            }
        }
    }
    return dist;
}
int main() {
    int n, m;
    std::cin >> n >> m;
    OrientedGraph ograph(n);
    for (int i = 0; i < m; ++i) {
        int v, u, w;
        std::cin >> v >> u >> w;
        v--;
        u--;
        ograph.add_edge(v, u, w);
    }
    for (auto i : FindShortestPaths(ograph, 0)) {
        std::cout << (i + 1) << '\n';
    }
    return 0;
}
