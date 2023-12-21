//
// Created by root on 12/7/23.
//

#ifndef ALGO_ARRAYSOLUTIONS_H
#define ALGO_ARRAYSOLUTIONS_H

#include "Solution.h"

// array_operations namespace
namespace array_operations {
    class Solution {
    public:
        /**
         * @problem: LC 704: binary search;
         * @site: https://leetcode.cn/problems/binary-search/
         * @methods: binary search [left, right] mode;
         * **/
        int search(vector<int>& nums, int target) {
            size_t left = 0, right = nums.size() - 1;

            while(left <= right) {
                size_t mid = (left + right) >> 1;

                if (nums[mid] == target) {
                    return (int)mid;
                } else if (nums[mid] < target){
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            return -1;
        }

        /**
         * @problem: LC 27: remove element
         * @site: https://leetcode.cn/problems/remove-element/
         * @methods: array; double pointer;
         * **/
        int removeElement(vector<int>& nums, int target) {
            int fast, slow = 0, len = nums.size();

            for (fast = 0; fast < len; ++fast) {
                if (nums[fast] != target) {
                    nums[slow] = nums[fast];
                    ++slow;
                }
            }
            // slow is the size of the new vector.
            return slow;
        }

        /**
         * @problem: LC 977: square of a sorted array
         * @site: https://leetcode.cn/problems/squares-of-a-sorted-array/
         * @methods: array; double pointers;
         * **/
        vector<int> sortedSquares(vector<int>& nums) {
            size_t len = nums.size();
            vector<int> result(len, 0);

            size_t left = 0, right = len - 1, cur_index = len - 1;

            while (left <= right) {
                int left_sq = nums[left] * nums[left];
                int right_sq = nums[right] * nums[right];

                if (right_sq > left_sq) {
                    result[cur_index--] = right_sq;
                    --right;
                } else {
                    result[cur_index--] = left_sq;
                    ++left;
                }
            }

            return result;
        }

        /**
         * @problem: LC 209: minimum size subarray sum
         * @site: https://leetcode.cn/problems/minimum-size-subarray-sum/
         * @methods: sliding windows; double pointers;
         * **/
        int minSubArrayLen(int target, vector<int>& nums) {
            // empty array return
            if (nums.empty()) {
                return 0;
            }

            int result = 0, cur_sum = 0;
            int left = 0, right, len = nums.size();

            for(right = 0; right < len; ++right) {
                cur_sum += nums[right];
                if (cur_sum >= target) {
                    while(cur_sum - nums[left] >= target){
                        cur_sum -= nums[left];
                        ++left;
                    }
                    if (result != 0) {
                        result = min(result, right - left + 1);
                    } else{
                        result = right - left + 1;
                    }
                }
            }
            return result;
        }

        /**
         * @problem: LC 59: spiral matrix II
         * @site: https://leetcode.cn/problems/spiral-matrix-ii/
         * @methods: simulation;
         * **/
        vector<vector<int>> generateMatrix(int n) {
            vector<vector<int>> result(n, vector<int>(n, 0));

            int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            int bounds[4] = {n - 1, n - 1, 0, 0};
            int bounds_change[4] = {-1, -1, 1, 1};
            int cur_num = 1, i = 0, j = 0, cur_direction = 0;

            while (cur_num <= n * n)  {
                result[i][j] = cur_num;
                if (
                        cur_direction == 0 && j == bounds[cur_direction]
                        || cur_direction == 1 && i == bounds[cur_direction]
                        || cur_direction == 2 && j == bounds[cur_direction]
                        || cur_direction == 3 && i == bounds[cur_direction]
                        ) {
                    bounds[(cur_direction + 3) % 4] += bounds_change[(cur_direction + 3) % 4];
                    cur_direction = (cur_direction + 1) % 4;
                }
                i += directions[cur_direction][0];
                j += directions[cur_direction][1];
                ++cur_num;
            }

            return result;
        }

        /**
         * @problem: LC 54: spiral matrix
         * @site: https://leetcode.cn/problems/spiral-matrix/
         * @methods: simulation;
         * **/
        vector<int> spiralOrder(vector<vector<int>>& matrix) {
            vector<int> result;

            int n = matrix.size(), m = matrix[0].size();

            int cur_num = 1, i = 0, j = 0, cur_direction = 0;
            int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            int bounds[4] = {m - 1, n - 1, 0, 0};
            int bounds_change[4] = {-1, -1, 1, 1};

            while (cur_num <= n * m)  {
                result.emplace_back(matrix[i][j]);
                cout << i << " " << j << endl;
                if (
                        cur_direction == 0 && j == bounds[cur_direction]
                        || cur_direction == 1 && i == bounds[cur_direction]
                        || cur_direction == 2 && j == bounds[cur_direction]
                        || cur_direction == 3 && i == bounds[cur_direction]
                        ) {
                    bounds[(cur_direction + 3) % 4] += bounds_change[(cur_direction + 3) % 4];
                    cur_direction = (cur_direction + 1) % 4;
                }
                i += directions[cur_direction][0];
                j += directions[cur_direction][1];
                ++cur_num;
            }

            return result;
        }

        /**
         * @problem: LC 2300: successful pairs of spells and potions
         * @site: https://leetcode.cn/problems/successful-pairs-of-spells-and-potions/
         * @methods: binary search;
         * **/
        vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
            size_t len1 = spells.size(), len2 = potions.size();
            if (len1 == 0) return {};
            vector<int> result(len1, 0);

            sort(potions.begin(), potions.end());
            for (size_t i = 0; i < len1; ++i) {
                size_t left = 0, right = len2 - 1;
                while (left <= right) {
                    size_t mid = (left + right) >> 1;
                    if ((long long) potions[mid] * spells[i] >= success) {
                        right = mid - 1;
                    } else {
                        left = mid + 1;
                    }
                }
                result[i] = static_cast<int>(len2) - left;
            }

            return result;
        }

        /**
         * @problem: LC 2342: max sum of a pair with equal sum og digits
         * @site: https://leetcode.cn/problems/max-sum-of-a-pair-with-equal-sum-of-digits/
         * @methods: simulation; hashtable;
         * **/
        int maximumSum(vector<int>& nums) {
            unordered_map<int, int> map_sums;
            auto getSum = [](int num) {
                int result = num % 10;
                while (num / 10 != 0) {
                    num /= 10;
                    result += num % 10;
                }
                return result;
            };

            int result = -1;
            for (auto i : nums) {
                int bitSum = getSum(i);
                if (map_sums.find(bitSum) == map_sums.end()) {
                    map_sums[bitSum] = i;
                } else {
                    result = max(result, i + map_sums[bitSum]);
                    map_sums[bitSum] = max(map_sums[bitSum], i);
                }
            }

            return result;
        }

        /**
         * @problem: LC 2661: find the overlap element
         * @site: https://leetcode.cn/problems/first-completely-painted-row-or-column/
         * @methods: simulation; array;
         * **/
        int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
            unordered_map<int, pair<int, int>> corrd_map;
            int rows = mat.size(), cols = mat[0].size();
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    corrd_map[mat[i][j]] = {i, j};
                }
            }
            vector<int> row_cnt(rows, 0), col_cnt(cols, 0);
            int len = arr.size(), result = - 1;
            for (int id = 0; id < len; id++) {
                int elem = arr[id];
                int i = corrd_map[elem].first;
                int j = corrd_map[elem].second;
                row_cnt[i] += 1;
                col_cnt[j] += 1;
                if (row_cnt[i] == cols || col_cnt[j] == rows) {
                    result = id;
                    break;
                }
            }
            return result;
        }
    };
};

#endif //ALGO_ARRAYSOLUTIONS_H
