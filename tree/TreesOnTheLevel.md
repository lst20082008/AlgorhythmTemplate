# 讲解和模板
其实就是bfs，通过queue来实现

## 模板
```
#include <queue>
void bfs(Node *root) {
    if(root == NULL)
        return NULL;
    // 这里的int可以用来记录层序，很常用
    queue<pair<Node*, int>> q;
    q.push({root, 0});
    while(!q.empty()) {
        auto tmp = q.front();
        q.pop();
        // 加入左右节点（有个判断，之后可以加条件）
        if(tmp.first->left != NULL)
            q.push({tmp.first->left, tmp.second+1});
        if(tmp.first->right != NULL)    
            q.push({tmp.first->right, tmp.second+1});
            
        // 这里下面写访问代码
    }
}
```

---
# 例题
## [Leetcode117. 填充每个节点的下一个右侧节点指针 II](https://leetcode-cn.com/problems/populating-next-right-pointers-in-each-node-ii/)
```
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

#include <queue>
using namespace std;
class Solution {
public:
    Node* connect(Node* root) {
        if(root == NULL)
            return NULL;
        Node *realRoot = root;
        queue<pair<Node*, int>> q;
        q.push({root, 0});
        while(!q.empty()) {
            auto tmp = q.front();
            q.pop();
            if(tmp.first->left != NULL)
                q.push({tmp.first->left, tmp.second+1});
            if(tmp.first->right != NULL)    
                q.push({tmp.first->right, tmp.second+1});
            if(q.front().second == tmp.second)
                tmp.first->next = q.front().first;
            else
                tmp.first->next = NULL;
        }
        return realRoot;
    }
};
```