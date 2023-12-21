//
// Created by root on 12/7/23.
//

#ifndef ALGO_HASHTABLEOPERATIONS_H
#define ALGO_HASHTABLEOPERATIONS_H

#include "Solution.h"


namespace hashtable_operations {

    class Solution {
    public:
        /**
         * @problem: LC 242: valid anagram
         * @site: https://leetcode.cn/problems/valid-anagram/
         * @methods: hashtable;
         * **/
        bool isAnagram(const string& s, const string& t) {
            vector<int> letter_s(26, 0);
            for (auto ch : s) {
                ++letter_s[ch - 'a'];
            }
            for (auto ch : t) {
                --letter_s[ch - 'a'];
            }
            return all_of(letter_s.begin(), letter_s.end(), [](int x){ return x == 0;});
        }

        /**
         * @problem: LC 383: ransom note
         * @site: https://leetcode.cn/problems/ransom-note/
         * @methods: hashtable; simulation;
         * **/
        bool canConstruct(const string& ransomNote, const string& magazine) {
            vector<int> letter_s(26, 0);
            for (auto ch : magazine) {
                ++letter_s[ch - 'a'];
            }
            for (auto ch : ransomNote) {
                --letter_s[ch - 'a'];
            }

            return all_of(letter_s.begin(), letter_s.end(), [](int x){ return x >= 0;});
        }

        /**
         * @problem: LC 349: intersection of 2 arrays
         * @site: https://leetcode.cn/problems/intersection-of-two-arrays/
         * @methods: hashtable; simulation;
         * **/
        vector<int> intersection(const vector<int>& nums1, const vector<int>& nums2) {
            unordered_set<int> record1(nums1.begin(), nums1.end()), record2;
            for (auto i: nums2) {
                if (record1.find(i) != record1.end()) {
                    record2.insert(i);
                }
            }
            // return an initializer list
            return {record2.begin(), record2.end()};
        }

        /**
         * @problem: LC 202: happy number
         * @site: https://leetcode.cn/problems/happy-number/
         * @methods: hashtable; simulation;
         * **/
        bool isHappy(int n) {
            unordered_set<int> sum;

            auto getNumber = [](int x) {
                string s(to_string(x));
                auto sum = 0;
                for_each(s.begin(), s.end(), [&](char i){sum += (i - '0') * (i - '0');});
                return sum;
            };

            while (sum.find(n) == sum.end()) {
                sum.insert(n);
                n = getNumber(n);
                if (n == 1) {
                    return true;
                }
            }
            return false;
        }

        /**
         * @problem: LC 1: two sum
         * @site: https://leetcode.cn/problems/two-sum/
         * @methods: hashtable; simulation;
         * **/
        vector<int> twoSum(vector<int>& nums, int target) {
            unordered_map<int, int> record;
            auto len = nums.size();
            for(int i = 0; i < len; ++i) {
                if (record.find(target - nums[i]) != record.end()
                    && record[target - nums[i]] != i) {
                    return {i, record[target - nums[i]]};
                }
                record[nums[i]] = i;
            }
            return {};
        }

        /**
         * @problem: LC 454: 4 sum II
         * @site: https://leetcode.cn/problems/4sum-ii/
         * @methods: hashtable; simulation;
         * **/
        int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
            auto len = nums1.size();
            int result = 0;
            unordered_map<int, int> sum_count;
            for (int i = 0; i < len; ++i) {
                for (int j = 0; j < len; ++j) {
                    sum_count[nums1[i] + nums2[j]]++;
                }
            }

            for (int i = 0; i < len; ++i) {
                for (int j = 0; j < len; ++j) {
                    result += sum_count[-(nums3[i] + nums4[j])];
                }
            }

            return result;
        }

        /**
         * @problem: LC 15: 3 sum
         * @site: https://leetcode.cn/problems/3sum/
         * @methods: hashtable(hard); double pointers(easy); simulation;
         * **/
        vector<vector<int>> threeSum(vector<int>& nums) {
            vector<vector<int>> result;
            sort(nums.begin(), nums.end());
            auto len = nums.size();
            for (int i = 0; i < len; ++i) {
                if (nums[i] > 0) break;
                if (i > 0 && nums[i] == nums[i - 1]) continue;

                int left = i + 1, right = len - 1;
                while (left < right) {
                    if (left > i + 1 && nums[left] == nums[left - 1]) {
                        ++left;
                    } else if (right < len - 1 && nums[right] == nums[right + 1]) {
                        --right;
                    } else {
                        if (nums[i] + nums[left] + nums[right] > 0) {
                            --right;
                        } else if (nums[i] + nums[left] + nums[right] < 0) {
                            ++left;
                        } else {
                            result.push_back({nums[i], nums[right], nums[left]});
                            --right;
                            ++left;
                        }
                    }
                }
            }
            return result;
        }

        /**
         * @problem: LC 18: 4 sum
         * @site: https://leetcode.cn/problems/4sum/
         * @methods: hashtable(hard); double pointers(easy); simulation;
         * **/
        vector<vector<int>> fourSum(vector<int>& nums, int target) {
            vector<vector<int>> result;
            sort(nums.begin(), nums.end());
            auto len = nums.size();

            for (int i = 0; i < len; ++i) {
                if (nums[i] > target && nums[i] > 0) break;
                if (i > 0 && nums[i] == nums[i - 1]) continue;
                for (int j = i + 1; j < len; ++j) {
                    if (nums[j] + nums[i] > target && nums[i] + nums[j] > 0) break;
                    if (j > i + 1 && nums[j] == nums[j - 1]) continue;
                    int left = j + 1, right = len - 1;
                    while (left < right) {
                        if (left > j + 1 && nums[left] == nums[left - 1]) {
                            ++left;
                        } else if (right < len - 1 && nums[right] == nums[right + 1]) {
                            --right;
                        } else {
                            long long cur_sum = (long long)nums[i] + nums[left] + nums[right] + nums[j];
                            if (cur_sum > target) {
                                --right;
                            } else if ( cur_sum < target) {
                                ++left;
                            } else {
                                result.push_back({nums[i], nums[j], nums[right], nums[left]});
                                --right;
                                ++left;
                            }
                        }
                    }
                }
            }

            return result;
        }
    };


}


#endif //ALGO_HASHTABLEOPERATIONS_H
