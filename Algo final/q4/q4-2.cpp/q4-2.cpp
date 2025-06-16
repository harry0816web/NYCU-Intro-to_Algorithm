#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int findShortestCycle(int n, const vector<vector<int>> &graph)
{
    int shortest_cycle = INT_MAX;

    for (int start = 0; start < n; ++start)
    {
        vector<int> distance(n, -1);
        vector<int> parent(n, -1);
        queue<int> q;

        q.push(start);
        distance[start] = 0;

        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            for (int neighbor : graph[current])
            {
                if (distance[neighbor] == -1)
                {
                    distance[neighbor] = distance[current] + 1;
                    parent[neighbor] = current;
                    q.push(neighbor);
                }
                else if (parent[current] != neighbor)
                {
                    int cycle_length = distance[current] + distance[neighbor] + 1;
                    shortest_cycle = min(shortest_cycle, cycle_length);
                }
            }
        }
    }

    return (shortest_cycle == INT_MAX) ? -1 : shortest_cycle;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n);

    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        --a, --b; // 節點索引從 0 開始
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    cout << findShortestCycle(n, graph) << endl;
    return 0;
}
