//
// Created by root on 12/21/23.
//

#ifndef ALGO_GREEDY_H
#define ALGO_GREEDY_H

#include "Solution.h"

namespace greedy {
    class Solution {
    public:
        /**
         * @problem: LC 455: assign cookies
         * @site: https://leetcode.cn/problems/assign-cookies/
         * @methods: greedy;
         * **/
        int findContentChildren(vector<int>& g, vector<int>& s) {
            sort(g.begin(), g.end());
            sort(s.begin(), s.end());

            int result = 0;
            int index = s.size() - 1;
            for (int i = g.size() - 1; i >= 0 && index >= 0; --i) {
                if (s[index] >= g[i]) {
                    ++result;
                    --index;
                }
            }
            return result;
        }

        /**
         * @problem: LC 376: wiggle subsequence
         * @site: https://leetcode.cn/problems/wiggle-subsequence/description/
         * @methods: greedy;
         * **/
        int wiggleMaxLength(vector<int>& nums) {

        }
    };
}

#endif //ALGO_GREEDY_H
