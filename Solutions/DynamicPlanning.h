//
// Created by root on 12/21/23.
//

#ifndef ALGO_DYNAMICPLANNING_H
#define ALGO_DYNAMICPLANNING_H

#include "Solution.h"

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
        int minCostClimbingStairs(vector<int>& cost) {
            int len = cost.size();
            if (len == 1) {
                return cost[0];
            }
            else if (len == 2) {
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
        int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
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
        bool canPartition(vector<int>& nums) {
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
        int lastStoneWeightII(vector<int>& stones) {
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
        int findTargetSumWays(vector<int>& nums, int target) {
            int len = nums.size(), sum = 0;
            for (auto num: nums) sum += num;

            if (abs(target) > sum) return 0;
            if ((target + sum) % 2 == 1) return 0;

            int bpSize = (target + sum) >> 1;
            vector<int> dp(bpSize + 1, 0);

            for(int i = 0; i < len; ++i) {
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
        int findMaxForm(vector<string>& strs, int m, int n) {
            auto cnt = [](const string& str)->pair<int, int> {
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
        int change(int amount, vector<int>& coins) {
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
        int combinationSum4(vector<int>& nums, int target) {
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
        int coinChange(vector<int>& coins, int amount) {
            vector<int> dp(amount + 1, INT_MAX);
            dp[0] = 0;
            for (int coin : coins) {
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
        bool wordBreak(string s, vector<string>& wordDict) {
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
    };
}

#endif //ALGO_DYNAMICPLANNING_H
