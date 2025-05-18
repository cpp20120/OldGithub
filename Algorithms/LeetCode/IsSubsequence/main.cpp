class Solution {
public:
bool isSubsequence(const std::string_view& s, const std::string_view& t) {
    int i = 0, j = 0;

    while (i < s.length() && j < t.length()) {
        if (s[i] == t[j]) {
            i++;
        }
        j++;
    }

    return i == s.length();
};
};
