#include <vector>
#include <unordered_set>
#include <stack>
#include <iostream>
#include <algorithm>

// 举个例子，当然还可以用邻接矩阵来表示
struct vertex{
    int val;
    std::vector<vertex> linkedVertexs;
};
void dfs(vertex startPoint) {
    // 通常会对第一个startPoint有个判断


    std::unordered_set<vertex> visited;
    // 栈是dfs实现的主要手段
    std::stack<vertex> s;

    s.push(startPoint);
    while(!s.empty()) {
        vertex tmp = s.top();
        s.pop();

        // 剪枝，这里的visited是通常的条件
        if(visited.find(tmp) != visited.end()) {
            continue;
        }

        // 访问，自行修改访问会发生什么
        visited.insert(tmp);
        std::cout << tmp.val <<std::endl;

        // 加入相邻节点（可以加判断条件）
        for(auto v : tmp.linkedVertexs) {
            s.push(v);
        }

    }

}

// Leetcode面试题 16.19. 水域大小
// https://leetcode-cn.com/problems/pond-sizes-lcci
using namespace std;
class Solution {
public:
    vector<int> poolSize;
    vector<vector<int>> visited;
    vector<int> pondSizes(vector<vector<int>>& land) {
        visited.resize(land.size(), vector<int>(land[0].size(), 0));
        for(int i = 0; i < land.size(); i++) {
            for(int j = 0; j < land[i].size(); j++) {
                dfs(i, j, land);
            }
        }
        std::sort(poolSize.begin(), poolSize.end());
        return poolSize;
    }
    void dfs(int row, int col, vector<vector<int>>& land) {
        if(visited[row][col] == 1) {
            return;
        }
        if(land[row][col] != 0) {
            visited[row][col] = 1;
            return;
        }
        std::vector<std::pair<int, int> > direction = {
            {0, 1},
            {0, -1},
            {1, 0},
            {-1, 0},
            {1, 1},
            {1, -1},
            {-1, 1},
            {-1, -1}
        };
        std::stack<std::pair<int, int>> s;
        int count = 0;

        s.push({row, col});
        while(!s.empty()) {
            auto tmp = s.top();
            s.pop();

            // 剪枝，这里的visited是通常的条件
            if(visited[tmp.first][tmp.second] == 1) {
                continue;
            }

            // 访问，自行修改访问会发生什么
            visited[tmp.first][tmp.second] = 1;
            count++;

            // 加入相邻节点（可以加判断条件）
            for(auto direct : direction) {
                int nrow = tmp.first + direct.first;
                int ncol = tmp.second + direct.second;
                if(nrow < land.size() && nrow >= 0 && ncol < land[nrow].size() && ncol >= 0 && land[nrow][ncol] == 0) {
                    s.push({nrow, ncol});
                } 
            }
        }
        poolSize.push_back(count);
    }
};

// Leetcode695. Max Area of Island
// https://leetcode-cn.com/problems/max-area-of-island/
class Solution {
public:
    vector<vector<int>> visited;
    int maxArea;
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        maxArea = 0;
        visited.resize(grid.size(), vector<int>(grid[0].size(), 0));
        for(int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid[i].size(); j++) {
                if(visited[i][j] == 0 && grid[i][j] == 1) {
                    dfs(i, j, grid);
                }
            }
        }
        return maxArea;
    }
    void dfs(int row, int col, vector<vector<int>>& land) {
        std::vector<std::pair<int, int> > direction = {
            {0, 1},
            {0, -1},
            {1, 0},
            {-1, 0}
        };
        std::stack<std::pair<int, int>> s;
        int count = 0;

        s.push({row, col});
        while(!s.empty()) {
            auto tmp = s.top();
            s.pop();

            // 剪枝，这里的visited是通常的条件
            if(visited[tmp.first][tmp.second] == 1) {
                continue;
            }

            // 访问，自行修改访问会发生什么
            visited[tmp.first][tmp.second] = 1;
            count++;

            // 加入相邻节点（可以加判断条件）
            for(auto direct : direction) {
                int nrow = tmp.first + direct.first;
                int ncol = tmp.second + direct.second;
                if(nrow < land.size() && nrow >= 0 && ncol < land[nrow].size() && ncol >= 0 && land[nrow][ncol] == 1) {
                    s.push({nrow, ncol});
                } 
            }
        }
        if(count > maxArea) {
            maxArea = count;
        }
    }
};

// Leetcode200.  Number of Islands
// https://leetcode-cn.com/problems/number-of-islands/
class Solution {
public:
    vector<vector<int>> visited;
    int count;
    int numIslands(vector<vector<char>>& grid) {
        if(grid.size() == 0 || grid[0].size() == 0) {
            return 0;
        }
        count = 0;
        visited.resize(grid.size(), vector<int>(grid[0].size(), 0));
        for(int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid[i].size(); j++) {
                if(visited[i][j] == 0 && grid[i][j] == '1') {
                    dfs(i, j, grid);
                }
            }
        }
        return count;
    }
    void dfs(int row, int col, vector<vector<char>>& land) {
        std::vector<std::pair<int, int> > direction = {
            {0, 1},
            {0, -1},
            {1, 0},
            {-1, 0}
        };
        std::stack<std::pair<int, int>> s;

        s.push({row, col});
        while(!s.empty()) {
            auto tmp = s.top();
            s.pop();

            // 剪枝，这里的visited是通常的条件
            if(visited[tmp.first][tmp.second] == 1) {
                continue;
            }

            // 访问，自行修改访问会发生什么
            visited[tmp.first][tmp.second] = 1;

            // 加入相邻节点（可以加判断条件）
            for(auto direct : direction) {
                int nrow = tmp.first + direct.first;
                int ncol = tmp.second + direct.second;
                if(nrow < land.size() && nrow >= 0 && ncol < land[nrow].size() && ncol >= 0 && land[nrow][ncol] == '1') {
                    s.push({nrow, ncol});
                } 
            }
        }
        count++;
    }
};

// Leetcode547. Friend Circles
// https://leetcode-cn.com/problems/friend-circles/
class Solution
{
public:
    vector<int> visited;
    int count;
    int findCircleNum(vector<vector<int>> &M)
    {
        if (M.size() == 0)
            return 0;
        count = 0;
        visited.resize(M.size(), 0);
        for (int i = 0; i < M.size(); i++)
        {
            if (visited[i] == 0)
            {
                dfs(i, M);
            }
        }
        return count;
    }
    void dfs(int startPoint, vector<vector<int>> &M)
    {
        // 栈是dfs实现的主要手段
        std::stack<int> s;

        s.push(startPoint);
        while (!s.empty())
        {
            int tmp = s.top();
            s.pop();

            // 剪枝，这里的visited是通常的条件
            if (visited[tmp] == 1)
            {
                continue;
            }

            // 访问，自行修改访问会发生什么
            visited[tmp] = 1;

            // 加入相邻节点（可以加判断条件）
            for (int i = 0; i < M[tmp].size(); i++)
                if (M[tmp][i] == 1)
                {
                    s.push(i);
                }
        }
        count++;
    }
};

// Leetcode207. 课程表
// https://leetcode-cn.com/problems/course-schedule/

// Leetcode130. Surrounded Regions