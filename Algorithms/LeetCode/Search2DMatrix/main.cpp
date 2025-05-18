class Solution {
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
        for (const auto& sublist : matrix) {
            if (std::find(sublist.begin(), sublist.end(), target) != sublist.end()) {
                return true;
            }
        }
        return false;
    }
};
