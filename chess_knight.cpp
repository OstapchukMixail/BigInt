//
//  main.cpp
//  Task_Horse_17_09_18
//
//  Created by Михаил Остапчук on 17.09.2018.
//  Copyright © 2018 Михаил Остапчук. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

class Graph {
private:
    std::vector<std::vector<int>> edges;
    std::vector<int> color; // White = 0, Grey = 1, Black = 2
    std::vector<bool> used;
    std::vector<int> cycle;
    std::vector<int> dist;
    std::queue<int> q;
    std::vector<int> way;
    int n_vertices;
public:
    Graph(int n_vertices) : edges(n_vertices), used(n_vertices), n_vertices(n_vertices), color(n_vertices), dist(n_vertices), way(n_vertices) {
        for (auto i : color) {
            i = 0;
        }
        for (int i = 0; i < n_vertices; ++i) {
            dist[i] = -1;
            way[i] = -1;
        }
        
    }
    
    void add_edge(int v, int u) {
        edges[v].push_back(u);
        edges[u].push_back(v);
    }
    
    int comp_count() {
        int count = 0;
        for (int i = 0; i < n_vertices; ++i) {
            if (!used[i]) {
                dfs(i);
                count++;
            }
        }
        return count;
    }
    
    void dfs(int v) {
        used[v] = true;
        for (auto i : edges[v]) {
            if (!used[i]) {
                dfs(i);
            }
        }
    }
    
    void bfs (int A) {
        dist[A] = 0;
        q.push(A);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto u : edges[v]) {
                if (dist[u] == -1) {
                    dist[u] = dist[v] + 1;
                    way[u] = v;
                    q.push(u);
                }
            }
        }
    }
    
    void create_edges(int A) {
        
    }
};

int main() {
    std::vector<int> dx = {1, 2, 2, 1, -1, -2, -2, -1};
    std::vector<int> dy = {2, 1, -1, -2, -2, -1, 1, 2};
    char Ssymb, Fsymb;
    int SSvalue, FSvalue;
    std::map<char, int> mapping;
    std::map<std::pair<char, int>, std::pair<int, int>> map1;
    std::map<std::pair<int, int>, std::pair<char, int>> map2;
    mapping['a'] = 0;
    mapping['b'] = 1;
    mapping['c'] = 2;
    mapping['d'] = 3;
    mapping['e'] = 4;
    mapping['f'] = 5;
    mapping['g'] = 6;
    mapping['h'] = 7;
    std::cin >> Fsymb >> FSvalue >> Ssymb >> SSvalue;
    map1.insert(std::make_pair(Fsymb, FSvalue), std::make_pair<mapping[Fsymb], FSvalue - 1>);
//    map1[std::make_pair(Fsymb, FSvalue)] = std::make_pair<mapping[Fsymb], FSvalue - 1>;
    map2[std::make_pair<mapping[Fsymb], FSvalue - 1>] = std::make_pair(Fsymb, FSvalue);
    Graph FGraph(64);
    FGraph.bfs(8 * mapping[Fsymb] + FSvalue - 1);
    return 0;
}
