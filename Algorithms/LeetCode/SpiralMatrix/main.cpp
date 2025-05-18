class Solution {
public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
        std::vector<int> ans;
        if (matrix.empty() || matrix[0].empty()) {
            return ans; 
        }

        int left = 0, right = matrix[0].size() - 1, top = 0, bottom = matrix.size() - 1;

        while (left <= right && top <= bottom) {
            for (int j = left; j <= right; j++) {
                ans.push_back(matrix[top][j]);
            }
            top++;

            for (int j = top; j <= bottom; j++) {
                ans.push_back(matrix[j][right]);
            }
            right--;

            if (top <= bottom) {
                for (int j = right; j >= left; j--) {
                    ans.push_back(matrix[bottom][j]);
                }
                bottom--;
            }

            if (left <= right) {
                for (int j = bottom; j >=top; j--) {
                    ans.push_back(matrix[j][left]);
                }
                left++;
            }
        }

        return ans;
    }
};
