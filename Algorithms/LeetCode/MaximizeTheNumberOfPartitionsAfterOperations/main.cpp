class Solution {
public:
    int maxPartitionsAfterOperations(string s, int k) {
        if (k == 26) return 1;
        
        int n = s.size();
        vector<int> dp(n + 1), pos_k_last(n);
        int cnt[26];
        memset(cnt, 0, sizeof(cnt));
        for (int i = n - 1, j = n, distinct = 0; i >= 0; --i) {
            if (++cnt[s[i] - 'a'] == 1) ++distinct;
            while (distinct > k) {
                if (--cnt[s[--j] - 'a'] == 0) --distinct;
            }
            dp[i] = 1 + dp[j];
            pos_k_last[i] = j;
        }
        
        memset(cnt, 0, sizeof(cnt));
        vector<int> pos_k_first(n), mask(n);
        vector<bool> has_k(n);
        for (int i = 0, j = 0, distinct = 0, m = 0; i < n; ++i) {
            if (i > 0) {
                if (--cnt[s[i - 1] - 'a'] == 0) {
                    --distinct;
                    m ^= 1 << (s[i - 1] - 'a');
                }
            }
            while (j < n && distinct < k) {
                if (++cnt[s[j++] - 'a'] == 1) {
                    ++distinct;
                    m ^= 1 << (s[j - 1] - 'a');
                }
            }
            pos_k_first[i] = j;
            has_k[i] = distinct == k;
            mask[i] = m;
        }
        
        auto find_rep = [&s, &n, &k, &cnt, &pos_k_first](int i) -> pair<int, bool> {
            memset(cnt, 0, sizeof(cnt));
            int distinct = 0, start = i;
            bool has_rep = false;
            while (i < n && !(distinct == k - 1 && has_rep)) {
                if (++cnt[s[i++] - 'a'] == 1) ++distinct;
                else has_rep = true;
            }
            pair<int, bool> ret{i - 1, cnt[s[i - 1] - 'a'] > 1 || i + 1 == pos_k_first[start]};
            return ret;
        };
        
        int ans = dp[0], start = 0, num_partition = 1;
        int full_mask = (1 << 26) - 1;
        while (start < n) {
            if (has_k[start]) {
                int k_first = pos_k_first[start], k_last = pos_k_last[start];
                int stop;
                if (k_first - start > k) {
                    auto rep = find_rep(start); // guaranteed to take less than (k_last - start)
                    // ooperations, which is important to understand the O(n) complexity of this algorithm
                    stop = rep.second ? rep.first : (rep.first + 1);
                    while (stop < k_first) {
                        ans = max(ans, num_partition + dp[stop + 1]);
                        ++stop;
                    }
                } else {
                    ans = max(ans, num_partition + dp[k_first]);
                }
                stop = k_first - 1;
                while (stop < k_last - 1) {
                    if (stop + 2 >= n) {
                        ans = max(ans, num_partition + (stop + 1 < n ? 1 : 0));
                    } else {
                        if ((mask[start] | mask[stop + 2]) == full_mask) {
                            ans = max(ans, num_partition + dp[stop + 1]);
                        } else {
                            ans = max(ans, num_partition + 1 + (has_k[stop + 2] ? dp[pos_k_first[stop + 2] - 1] : 0));
                            if ((mask[start] & mask[stop + 2]) != mask[stop + 2]) {
                                ans = max(ans, num_partition + dp[stop + 1]);
                            }
                        }
                    }
                    ++stop;
                }
            }
            
            ++num_partition;
            start = pos_k_last[start];
        }
        return ans;
    }
};
