//
// Created by root on 10/31/23.
//

#include "Solutions/ArraySolutions.h"
#include "Solutions/LinkedListOperations.h"
#include "Solutions/StringOperations.h"
#include "Solutions/StackAndQueue.h"
#include "Solutions/DoublePointerCollection.h"
#include "Solutions/BinaryTree.h"
#include "Solutions/BackTracking.h"

int main() {
    auto perform_array_operations = []() {
        using namespace array_operations;
        Solution s;

        vector<vector<int>> input_v({{4, 3, 5},
                                     {1, 2, 6}});
        vector<int> arr = {1, 4, 5, 2, 6, 3};
        int target = 3;
        cout << s.firstCompleteIndex(arr, input_v) << endl;
    };

    auto perform_linked_list_operations = []() {
        using namespace linked_list_operations;
        Solution s;
        vector<int> source = {1, 2, 6, 3, 4, 5, 6};
        ListNode *root = create_from_array<int>(source);
        root = s.removeElements(root, 6);

    };
    auto perform_string_operations = []() {
        using namespace string_operations;
        Solution s;
        vector<char> str{'1', '2', '3', '4', '5'};
        string a = "F R  I   E    N     D      S      ";
        cout << s.repeatedSubstringPattern("abcabcabcabc") << endl;
    };
    auto double_pointers = []() {
        using namespace double_pointer_collection;
        Solution s;
        auto inputV = vector<int>({0, 1, 2, 2, 3, 0, 4, 2});
        auto inputStr = string("   abc  iop  paa ");
        cout << s.reverseWords(inputStr) << endl;
    };

    using backtracking::Solution;
    Solution s;
    vector<vector<string>> vec = {{"MUC", "LHR"},
                                  {"JFK", "MUC"},
                                  {"SFO", "SJC"},
                                  {"LHR", "SFO"}};
    auto vec1 = s.findItinerary(vec);
    for (auto i: vec1) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}