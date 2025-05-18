class Solution {
public:
    int numSquares(int n) {
      bool seen[10001] = {false};
      std::queue<std::pair<int,int>> q;
      q.emplace(0, 0);
      while (!q.empty()) {
        auto [sum, gen] = q.front();
        ++gen;
        for (int i = 1; (sum + i * i) <= n; ++i) {
          int next_sum = sum + i * i;
          if (next_sum == n) {
            return gen;
          }
          if (!seen[next_sum]) {
            q.emplace(next_sum, gen);
            seen[next_sum] = true;
          }
        }
        q.pop();
      }
      return - 1;  
    }
};
