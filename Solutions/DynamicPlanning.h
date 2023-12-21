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
    };
}

#endif //ALGO_DYNAMICPLANNING_H
