//
// Created by root on 12/21/23.
//

#ifndef ALGO_DYNAMICPLANNING_H
#define ALGO_DYNAMICPLANNING_H

#include "Solution.h"
#include "BasicDataStructure.h"

namespace dynamic_planning {
    class Solution {
    public:
        /**
         * @problem: LC 509: fib number
         * @site: https://leetcode.cn/problems/fibonacci-number/
         * @methods: dp;
         * **/
        int fib(int n) {
            vector<int> fibVector({0, 1});
            if (n < 2) return fibVector[n];
            for (int i = 2; i <= n; ++i) {
                fibVector.emplace_back(fibVector[i - 1] + fibVector[i - 2]);
            }
            return *fibVector.rbegin();
        }

        /**
         * @problem: LC 509: fib number
         * @site: https://leetcode.cn/problems/fibonacci-number/
         * @methods: dp;
         * **/
        int climbStairs(int n) {
            vector<int> methCnt({1, 1});
            if (n < 2) return methCnt[n];
            for (int i = 2; i <= n; ++i) {
                methCnt.push_back(methCnt[i - 1] + methCnt[i - 2]);
            }
            return *methCnt.rbegin();
        }

        /**
         * @problem: LC 746: min cost upstairs
         * @site: https://leetcode.cn/problems/min-cost-climbing-stairs/
         * @methods: dp;
         * **/
        int minCostClimbingStairs(vector<int> &cost) {
            int len = cost.size();
            if (len == 1) {
                return cost[0];
            } else if (len == 2) {
                return min(cost[0], cost[1]);
            }
            vector<int> dp(len + 1, 0);
            for (int i = 2; i <= len; ++i) {
                dp[i] = min(dp[i - 2] + cost[i - 2], dp[i - 1] + cost[i - 1]);
            }

            return *dp.rbegin();
        }

        /**
         * @problem: LC 62: unique paths
         * @site: https://leetcode.cn/problems/unique-paths/description/
         * @methods: dp;
         * **/
        int uniquePaths(int m, int n) {
            vector<int> dp(n, 1);
            // rolling array
            for (int i = 1; i < m; ++i) {
                for (int j = 1; j < n; ++j) {
                    dp[j] += dp[j - 1];
                }
            }

            return dp[n - 1];
        }

        /**
         * @problem: LC 63: unique paths II
         * @site: https://leetcode.cn/problems/unique-paths/description/
         * @methods: dp;
         * **/
        int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
            int m = obstacleGrid.size(), n = obstacleGrid[0].size();
            vector<vector<int>> dp(m, vector<int>(n, 0));
            for (int i = 0; i < m; ++i) {
                if (obstacleGrid[i][0] == 1) break;
                dp[i][0] = 1;
            }
            for (int i = 0; i < n; ++i) {
                if (obstacleGrid[0][i] == 1) break;
                dp[0][i] = 1;
            }

            for (int i = 1; i < m; ++i) {
                for (int j = 1; j < n; ++j) {
                    if (obstacleGrid[i][j] == 1) continue;
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }

            return dp[m - 1][n - 1];
        }

        /**
         * @problem: LC 343: integer break
         * @site: https://leetcode.cn/problems/integer-break/description/
         * @methods: dp;
         * **/
        int integerBreak(int n) {
            if (n <= 2) return 1;
            vector<int> dp(60, 0);
            dp[2] = 1;
            for (int i = 3; i <= n; ++i) {
                for (int j = 1; j <= i / 2; ++j) {
                    dp[i] = max(dp[i - j] * j, max((i - j) * j, dp[i]));
                }
            }
            return dp[n];
        }

        /**
         * @problem: LC 96: num trees
         * @site: https://leetcode.cn/problems/unique-binary-search-trees/
         * @methods: dp;
         * **/
        int numTrees(int n) {
            vector<int> dp(n + 1, 0);
            if (n <= 1) return 1;
            dp[0] = dp[1] = 1;
            for (int i = 2; i <= n; ++i) {
                for (int j = 1; j <= i; j++) {
                    dp[i] += (dp[j - 1] * dp[i - j]);
                }
            }
            return dp[n];
        }

        /**
         * @problem: LC 416: split equal subsets
         * @site: https://leetcode.cn/problems/partition-equal-subset-sum/
         * @methods: dp;
         * **/
        bool canPartition(vector<int> &nums) {
            int len = nums.size();
            int sum = 0;
            for (int i = 0; i < len; ++i) {
                sum += nums[i];
            }
            if (sum % 2 != 0) return false;
            bool result = false;

            vector<int> dp(sum / 2 + 1, 0);
            for (int i = 0; i < len; ++i) {
                for (int j = sum / 2; j >= nums[i]; --j) {
                    dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
                }
            }
            if (dp[sum / 2] == sum / 2) result = true;
            return result;
        }

        /**
         * @problem: LC 1049: last stone weight
         * @site: https://leetcode.cn/problems/last-stone-weight-ii/description/
         * @methods: dp;
         * **/
        int lastStoneWeightII(vector<int> &stones) {
            int sum = 0, len = stones.size();
            for (auto st: stones) sum += st;
            int target = sum >> 1;
            vector<int> dp(target + 1, 0);

            for (int i = 0; i < len; ++i) {
                for (int j = target; j >= stones[i]; --j) {
                    dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
                }
            }
            return (sum - dp[target]) - dp[target];
        }

        /**
         * @problem: LC 494: target sum
         * @site: https://leetcode.cn/problems/target-sum/description/
         * @methods: dp;
         * **/
        int findTargetSumWays(vector<int> &nums, int target) {
            int len = nums.size(), sum = 0;
            for (auto num: nums) sum += num;

            if (abs(target) > sum) return 0;
            if ((target + sum) % 2 == 1) return 0;

            int bpSize = (target + sum) >> 1;
            vector<int> dp(bpSize + 1, 0);

            for (int i = 0; i < len; ++i) {
                for (int j = bpSize; j >= nums[i]; --j) {
                    dp[j] += dp[j - nums[i]];
                }
            }
            return dp[bpSize];
        }

        /**
         * @problem: LC 474: 1 & 0
         * @site: https://leetcode.cn/problems/ones-and-zeroes/
         * @methods: dp;
         * **/
        int findMaxForm(vector<string> &strs, int m, int n) {
            auto cnt = [](const string &str) -> pair<int, int> {
                int _0 = 0, _1 = 0;
                for (auto ch: str) {
                    if (ch == '0') _0++;
                    else if (ch == '1') _1++;
                }
                return {_0, _1};
            };

            vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

            int len = strs.size();
            for (int i = 0; i < len; ++i) {
                auto numCnt = cnt(strs[i]);
                auto cntZero = numCnt.first, cntOne = numCnt.second;
                for (int x = m; x >= cntZero; --x) {
                    for (int y = n; y >= cntOne; --y) {
                        dp[x][y] = max(dp[x][y], dp[x - cntZero][y - cntOne] + 1);
                    }
                }
            }
            return dp[m][n];
        }

        /**
         * @problem: LC 518: exchange coins
         * @site: https://leetcode.cn/problems/ones-and-zeroes/
         * @methods: dp;
         * **/
        int change(int amount, vector<int> &coins) {
            vector<int> dp(amount + 1, 0);
            dp[0] = 1;
            for (int coin: coins) {
                for (int j = coin; j <= amount; ++j) {
                    dp[j] += dp[j - coin];
                }
            }

            return dp[amount];
        }

        /**
         * @problem: LC 377: combination IV
         * @site: https://leetcode.cn/problems/combination-sum-iv/description/
         * @methods: dp; full backpack;
         * **/
        int combinationSum4(vector<int> &nums, int target) {
            vector<int> dp(target + 1, 0);
            dp[0] = 1;

            int len = nums.size();
            for (int j = 0; j <= target; ++j) {
                for (int i = 0; i < len; ++i) {
                    if (j >= nums[i] && dp[j] < INT_MAX - dp[j - nums[i]]) {
                        dp[j] += dp[j - nums[i]];
                    }
                }
            }

            return dp[target];
        }

        /**
         * @problem: KC 57: stairs
         * @site: https://kamacoder.com/problempage.php?pid=1067
         * @methods: dp; full backpack;
         * **/
        int climbStairsII(int n, int m) {
            std::vector<int> dp(n + 1, 0);
            dp[0] = 1;

            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    if (i >= j) {
                        dp[i] += dp[i - j];
                    }
                }
            }
            return dp[n];
        }

        /**
         * @problem: LC 322: exchange coins
         * @site: https://leetcode.cn/problems/coin-change/description/
         * @methods: dp; full backpack;
         * **/
        int coinChange(vector<int> &coins, int amount) {
            vector<int> dp(amount + 1, INT_MAX);
            dp[0] = 0;
            for (int coin: coins) {
                for (int j = coin; j <= amount; ++j) {
                    if (dp[j - coin] != INT_MAX) {
                        dp[j] = min(dp[j], dp[j - coin] + 1);
                    }
                }
            }
            if (dp[amount] == INT_MAX) return -1;
            return dp[amount];
        }

        /**
         * @problem: LC 279: perfect squares
         * @site: https://leetcode.cn/problems/perfect-squares/
         * @methods: dp; full backpack;
         * **/
        int numSquares(int n) {
            vector<int> dp(n + 1, INT_MAX);
            dp[0] = 0;

            int target = sqrt(n);
            for (int i = 1; i <= target; ++i) {
                for (int j = 1; j <= n; ++j) {
                    if (j >= i * i) {
                        dp[j] = min(dp[j], dp[j - i * i] + 1);
                    }
                }
            }

            return dp[n];
        }

        /**
         * @problem: LC 139: word break
         * @site: https://leetcode.cn/problems/word-break/
         * @methods: dp; full backpack;
         * **/
        bool wordBreak(string s, vector<string> &wordDict) {
            unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
            int len = s.size();
            vector<bool> dp(len + 1, false);
            dp[0] = true;
            for (int i = 1; i <= len; ++i) {
                for (int j = 0; j < i; ++j) {
                    string word = s.substr(j, i - j);
                    if (wordSet.find(word) != wordSet.end() && dp[j]) {
                        dp[i] = true;
                    }
                }
            }
            return dp[len];
        }

        /**
         * @problem: LC 198: rob
         * @site: https://leetcode.cn/problems/house-robber/
         * @methods: dp; backpack;
         * **/
        int rob(vector<int> &nums) {
            int len = nums.size();
            vector<int> dp(len + 1, 0);
            dp[0] = 0;
            dp[1] = nums[0];

            for (int i = 2; i <= len; ++i) {
                dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
            }
            return dp[len];
        }

        /**
         * @problem: LC 213: rob II
         * @site: https://leetcode.cn/problems/house-robber-ii/description/
         * @methods: dp; backpack;
         * **/
        int robII(vector<int> &nums) {
            int len = nums.size();

            if (len == 1) return nums[0];

            auto innerRob = [](vector<int> nums, int start, int end) -> int {
                int len = nums.size();
                if (start == end) return nums[start];
                vector<int> dp(len, 0);
                dp[start] = nums[start];
                dp[start + 1] = max(nums[start], nums[start + 1]);
                for (int i = start + 2; i <= end; ++i) {
                    dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
                }
                return dp[end];
            };
            int result = 0;
            result = innerRob(nums, 0, len - 2);
            result = max(result, innerRob(nums, 1, len - 1));
            return result;
        }

        /**
         * @problem: LC 337: rob III
         * @site: https://leetcode.cn/problems/house-robber-iii/description/
         * @methods: dp; backpack; tree dp;
         * **/
        using TreeNode = TTreeNode<int>;

        int robIII(TreeNode *root) {
            unordered_map<TreeNode *, int> nodeMap;
            std::function<vector<int>(TreeNode *)> traversal;
            traversal = [&](TreeNode *root) -> vector<int> {
                if (!root) return {0, 0};
                if (!root->left && !root->right) return {root->val, 0};

                auto leftResult = traversal(root->left);
                auto rightResult = traversal(root->right);

                int wRoot = leftResult[1] + rightResult[1] + root->val;
                int woRoot = max(leftResult[0], leftResult[1]) + max(rightResult[0], rightResult[1]);

                return {wRoot, woRoot};
            };
            auto result = traversal(root);
            return max(result[0], result[1]);
        }

        /**
         * @problem: LC 121: max profit
         * @site: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/description/
         * @methods: dp; greedy;
         * @param: mode, 0 for greedy, 1 for dp;
         * **/
        int maxProfit(vector<int> &prices, int mode = 1) {
            if (mode == 0) {
                int len = prices.size();
                int result = 0;
                int minPrice = prices[0];
                for (int i = 1; i < len; ++i) {
                    minPrice = min(minPrice, prices[i]);
                    result = max(prices[i] - minPrice, result);
                }

                return result;
            } else if (mode == 1) {
                int len = prices.size();
                vector<vector<int>> dp(len, vector<int>(2, 0));
                dp[0][0] = -prices[0];
                dp[0][1] = 0;
                for (int i = 1; i < len; ++i) {
                    dp[i][0] = max(dp[i - 1][0], -prices[i]);
                    dp[i][1] = max(prices[i] + dp[i - 1][0], dp[i - 1][1]);
                }
                return dp[len - 1][1];
            }

            return 0;
        }

        /**
         * @problem: LC 122: max profit II
         * @site: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/description/
         * @methods: dp;
         * **/
        int maxProfitII(vector<int> &prices) {
            int len = prices.size();
            vector<vector<int>> dp(len, vector<int>(2, 0));
            dp[0][0] = -prices[0];
            dp[0][1] = 0;
            for (int i = 1; i < len; ++i) {
                dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
                dp[i][1] = max(prices[i] + dp[i - 1][0], dp[i - 1][1]);
            }
            return dp[len - 1][1];
        }

        /**
         * @problem: LC 123: max profit III
         * @site: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iii/description/
         * @methods: dp;
         * **/
        int maxProfitIII(vector<int> &prices) {
            int len = prices.size();
            vector<vector<int>> dp(len, vector<int>(5, 0));
            dp[0][1] = -prices[0];
            dp[0][3] = -prices[0];
            for (int i = 1; i < len; ++i) {
                dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
                dp[i][2] = max(dp[i - 1][2], prices[i] + dp[i - 1][1]);
                dp[i][3] = max(dp[i - 1][3], dp[i - 1][2] - prices[i]);
                dp[i][4] = max(dp[i - 1][4], prices[i] + dp[i - 1][3]);
            }
            return dp[len - 1][4];
        }

        /**
         * @problem: LC 188: max profit IV
         * @site: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/description/
         * @methods: dp;
         * **/
        int maxProfitIV(int k, vector<int> &prices) {
            int len = prices.size();
            vector<vector<int>> dp(len, vector<int>(2 * k + 1));
            for (int i = 0; i < k; ++i) dp[0][2 * i + 1] = -prices[0];

            for (int i = 1; i < len; ++i) {
                for (int j = 1; j < 2 * k + 1; ++j) {
                    if (j % 2 == 1) {
                        dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] - prices[i]);
                    } else {
                        dp[i][j] = max(dp[i - 1][j], prices[i] + dp[i - 1][j - 1]);
                    }
                }
            }
            return dp[len - 1][2 * k];
        }

        /**
         * @problem: LC 309: max profit with cooldown
         * @site: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-cooldown/description/
         * @methods: dp;
         * **/
        int maxProfitWithCooldown(vector<int> &prices) {
            int len = prices.size();
            vector<vector<int>> dp(len, vector<int>(4));
            dp[0][0] = -prices[0];

            for (int i = 1; i < len; ++i) {
                dp[i][0] = max(dp[i - 1][0], max(dp[i - 1][3], dp[i - 1][1]) - prices[i]);
                dp[i][1] = max(dp[i - 1][1], dp[i - 1][3]);
                dp[i][2] = prices[i] + dp[i - 1][0];
                dp[i][3] = dp[i - 1][2];
            }

            return max(dp[len - 1][1], max(dp[len - 1][2], dp[len - 1][3]));
        }

        /**
         * @problem: LC 714: max profit with fee
         * @site: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
         * @methods: dp;
         * **/
        int maxProfitWithFee(vector<int> &prices, int fee) {
            int len = prices.size();
            vector<vector<int>> dp(len, vector<int>(2, 0));
            dp[0][0] = -prices[0];

            for (int i = 1; i < len; ++i) {
                dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
                dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i] - fee);
            }

            return dp[len - 1][1];
        }


        /**
         * @problem: LC 300: max subsequence
         * @site: https://leetcode.cn/problems/longest-increasing-subsequence/description/
         * @methods: dp;
         * **/
        int lengthOfLIS(const vector<int> &sums) {
            int len = sums.size(), result = INT_MIN;
            vector<int> dp(len, 1);

            for (int i = 0; i < len; ++i) {
                for (int j = 0; j < i; ++j) {
                    if (sums[i] > sums[j]) {
                        dp[i] = max(dp[i], dp[j] + 1);
                    }
                }
                if (dp[i] > result) result = dp[i];
            }

            return result;
        }

        /**
         * @problem: LC 674: max continuous subsequence
         * @site: https://leetcode.cn/problems/longest-continuous-increasing-subsequence/
         * @methods: dp;
         * **/
        int findLengthOfLCIS(const vector<int> &nums) {
            int len = nums.size(), result = 1;
            vector<int> dp(len, 1);

            for (int i = 1; i < len; ++i) {
                if (nums[i] > nums[i - 1]) {
                    dp[i] = max(dp[i], dp[i - 1] + 1);
                }
                result = max(result, dp[i]);
            }
            return result;
        }

        /**
         * @problem: LC 718: max repeated subarray
         * @site: https://leetcode.cn/problems/maximum-length-of-repeated-subarray/
         * @methods: dp;
         * **/
        int findLength(vector<int> &nums1, vector<int> &nums2) {
            int len1 = nums1.size(), len2 = nums2.size(), result = 0;
            vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));

            for (int i = 1; i <= len1; ++i) {
                for (int j = 1; j <= len2; ++j) {
                    if (nums1[i - 1] == nums2[j - 1]) {
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                    }
                    result = max(result, dp[i][j]);
                }
            }
            return result;
        }

        /**
         * @problem: LC 1143: max common subarray
         * @site: https://leetcode.cn/problems/longest-common-subsequence/
         * @methods: dp;
         * **/
        int longestCommonSubsequence(const string &text1, const string &text2) {
            int len1 = text1.size(), len2 = text2.size(), result = 0;
            vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));

            for (int i = 1; i <= len1; ++i) {
                for (int j = 1; j <= len2; ++j) {
                    if (text1[i - 1] == text2[j - 1]) {
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                    } else {
                        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                    }
                    result = max(result, dp[i][j]);
                }
            }

            return result;
        }

        /**
        * @problem: LC 1035: uncrossed lines
        * @site: https://leetcode.cn/problems/uncrossed-lines/
        * @methods: dp;
        * **/
        int maxUncrossedLines(vector<int> &nums1, vector<int> &nums2) {
            int len1 = nums1.size(), len2 = nums2.size(), result = 0;
            vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));

            for (int i = 1; i <= len1; ++i) {
                for (int j = 1; j <= len2; ++j) {
                    if (nums1[i - 1] == nums2[j - 1]) {
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                    } else {
                        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                    }
                    result = max(result, dp[i][j]);
                }
            }

            return result;
        }

        /**
         * @problem: LC 53: max sum subarray
         * @site: https://leetcode.cn/problems/maximum-subarray/description/
         * @methods: dp;
         * **/
        int maxSubarray(const vector<int> &nums) {
            int len = nums.size(), result = INT_MIN;
            vector<int> dp(len, 0);
            dp[0] = nums[0];

            for (int i = 1; i < len; ++i) {
                dp[i] = max(nums[i], dp[i - 1] + nums[i]);
                result = max(result, dp[i]);
            }

            return result;
        }

        /**
         * @problem: LC 392: is subsequence
         * @site: https://leetcode.cn/problems/is-subsequence/
         * @methods: dp;
         * **/
        bool isSubsequence(const string &s, const string &t) {
            int len1 = s.size(), len2 = t.size();
            if (len1 == 0) return true;
            if (len2 == 0 || len1 > len2) return false;
            vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));

            for (int i = 1; i <= len1; ++i) {
                for (int j = 1; j <= len2; ++j) {
                    if (s[i - 1] == t[j - 1]) {
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                    } else {
                        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                    }
                    if (dp[i][j] == len1) return true;
                }
            }

            return false;
        }


        /**
         * @problem: LC 115: distinct subsequence
         * @site: https://leetcode.cn/problems/distinct-subsequences/
         * @methods: dp;
         * **/
        int numDistinct(const string &s, const string &t) {
            const int mod = 1e9 + 7;
            int len1 = s.size(), len2 = t.size();
            vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
            for (int i = 0; i <= len1; ++i) dp[i][0] = 1;
            for (int i = 1; i <= len1; ++i) {
                for (int j = 1; j <= len2; ++j) {
                    if (s[i - 1] == t[j - 1]) {
                        dp[i][j] = ((dp[i - 1][j - 1] % mod) + (dp[i - 1][j] % mod)) % mod;
                    } else {
                        dp[i][j] = dp[i - 1][j] % mod;
                    }
                }
            }
            return dp[len1][len2] % mod;
        }

        /**
         * @problem: LC 583: delete two string
         * @site: https://leetcode.cn/problems/delete-operation-for-two-strings/description/
         * @methods: dp;
         * **/
        int minDistance(const string &word1, const string &word2, const string& type="delete") {
            int m = word1.size(), n = word2.size();
            vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

            for (int i = 0; i <= m; ++i) {
                dp[i][0] = i;
            }
            for (int i = 0; i <= n; ++i) {
                dp[0][i] = i;
            }

            for (int i = 1; i <= m; ++i) {
                for (int j = 1; j <= n; ++j) {
                    if (word1[i - 1] == word2[j - 1]) {
                        dp[i][j] = dp[i - 1][j - 1];
                    } else {
                        dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1);
                    }
                }
            }

            return dp[m][n];
        }

        /**
         * @problem: LC 72: edit distance
         * @site: https://leetcode.cn/problems/edit-distance/description/
         * @methods: dp;
         * **/
        int minDistance(const string& word1, const string& word2) {
            int m = word1.size(), n = word2.size();
            vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
            for (int i = 0; i <= m; ++i) dp[i][0] = i;
            for (int i = 0; i <= n; ++i) dp[0][i] = i;

            for (int i = 1; i <= m; ++i) {
                for (int j = 1; j <= n; ++j) {
                    if (word1[i - 1] == word2[j - 1]) {
                        dp[i][j] = dp[i - 1][j - 1];
                    } else {
                        dp[i][j] = min(dp[i - 1][j - 1] + 1, min(dp[i][j - 1] + 1, dp[i - 1][j] + 1));
                    }
                }
            }

            return dp[m][n];
        }

        /**
         * @problem: LC 647: palindromic substrings
         * @site: https://leetcode.cn/problems/palindromic-substrings/description/
         * @methods: dp;
         * **/
        int countSubstrings(const string& s) {
            int len = s.size(), result = len;
            vector<vector<bool>> dp(len + 1, vector<bool>(len + 1));
            dp[0][0] = true;
            for (int i = 1; i <= len; ++i) dp[i][i] = true;

            for (int end = 1; end <= len; end++) {
                for (int start = end - 1; start >= 1; start--) {
                    if (start == end - 1) {
                        dp[start][end] = (s[start - 1] == s[end - 1]);
                    } else {
                        dp[start][end] = (s[start - 1] == s[end - 1] && dp[start + 1][end - 1]);
                    }
                    if (dp[start][end]) result += 1;
                }
            }
            return result;
        }

        /**
         * @problem: LC 516: longest palindromic subsequence
         * @site: https://leetcode.cn/problems/longest-palindromic-subsequence/description/
         * @methods: dp;
         * **/
        int longestPalindromeSubseq(const string& s) {
            int len = s.size(), result = 1;
            vector<vector<int>> dp(len + 1, vector<int>(len + 1, 1));

            for (int end = 1; end <= len; ++end) {
                for (int start = end - 1; start >= 1; --start) {
                    if (s[start - 1] == s[end - 1]) {
                        if (end - start <= 1) {
                            dp[start][end] = end - start + 1;
                        } else {
                            dp[start][end] = dp[start + 1][end - 1] + 2;
                        }
                    } else {
                        if (end - start > 1) dp[start][end] = max(dp[start + 1][end], dp[start][end - 1]);
                    }
                    result = max(result, dp[start][end]);
                }
            }
            return result;
        }
    };
}

#endif //ALGO_DYNAMICPLANNING_H
