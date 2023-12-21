//
// Created by root on 12/7/23.
//

#ifndef ALGO_BINARYTREE_H
#define ALGO_BINARYTREE_H

#include "Solution.h"

namespace binary_tree {

    typedef TTreeNode<int> TreeNode;

    class Solution {
    public:

        /**
         * @problem: Tree traversal collection
         * @site:
         * @methods: binary tree;
         * **/
        typedef enum TMode{PRE, IN, POST} TraversalMode;
        vector<int> treeTraversal(TreeNode* root, const TraversalMode& mode=PRE, bool recursive=false) {
            vector<int> result;
            if (mode == PRE) {
                if (!root) return result;
                stack<TreeNode*> nodeStack;
                nodeStack.emplace(root);

                while (!nodeStack.empty()) {
                    auto tempNode = nodeStack.top();
                    result.push_back(tempNode->val);
                    nodeStack.pop();

                    if (tempNode->right) {
                        nodeStack.push(tempNode->right);
                    }
                    if (tempNode->left) {
                        nodeStack.push(tempNode->left);
                    }
                }
            } else if (mode == IN) {
                if (!root) return result;
                stack<TreeNode*> nodeStack;
                TreeNode* curNode = root;

                while (curNode != nullptr || !nodeStack.empty()) {
                    if (curNode != nullptr) {
                        nodeStack.push(curNode);
                        curNode = curNode->left;
                    } else {
                        curNode = nodeStack.top();
                        result.push_back(curNode->val);
                        nodeStack.pop();
                        curNode = curNode->right;
                    }
                }
            } else if (mode == POST) {
                if (!root) return result;
                stack<TreeNode*> nodeStack;
                nodeStack.emplace(root);

                while (!nodeStack.empty()) {
                    auto tempNode = nodeStack.top();
                    result.push_back(tempNode->val);
                    nodeStack.pop();
                    if (tempNode->left) {
                        nodeStack.push(tempNode->left);
                    }
                    if (tempNode->right) {
                        nodeStack.push(tempNode->right);
                    }
                }
                reverse(result.begin(), result.end());
            }
            return result;
        }


        /**
         * @problem: LC 144: preorder traversal
         * @site: https://leetcode.cn/problems/binary-tree-preorder-traversal/
         * @methods: binary tree;
         * **/
        vector<int> preorderTraversal(TreeNode* root) {
            const auto& innerPreorder = [](TreeNode* root, vector<int>& result) {
                std::function<void(TreeNode*, vector<int>&)> dummyFunc;
                dummyFunc = [&] (TreeNode* root, vector<int>& result) {
                    if (!root) return ;
                    result.push_back(root->val);
                    dummyFunc(root->left, result);
                    dummyFunc(root->right, result);
                };
                dummyFunc(root, result);
            };

            vector<int> result;
            innerPreorder(root, result);
            return result;
        }

        /**
         * @problem: LC 94: inorder traversal
         * @site: https://leetcode.cn/problems/binary-tree-inorder-traversal/
         * @methods: binary tree;
         * **/
        vector<int> inorderTraversal(TreeNode* root) {
            const auto& innerInorder = [](TreeNode* root, vector<int>& result) {
                std::function<void(TreeNode*, vector<int>&)> dummyFunc;
                dummyFunc = [&] (TreeNode* root, vector<int>& result) {
                    if (!root) return ;
                    dummyFunc(root->left, result);
                    result.push_back(root->val);
                    dummyFunc(root->right, result);
                };
                dummyFunc(root, result);
            };

            vector<int> result;
            innerInorder(root, result);
            return result;
        }

        /**
         * @problem: LC 145: postorder traversal
         * @site: https://leetcode.cn/problems/binary-tree-postorder-traversal/
         * @methods: binary tree;
         * **/
        vector<int> postorderTraversal(TreeNode* root) {
            const auto& innerPostorder = [](TreeNode* root, vector<int>& result) {
                std::function<void(TreeNode*, vector<int>&)> dummyFunc;
                dummyFunc = [&] (TreeNode* root, vector<int>& result) {
                    if (!root) return ;
                    dummyFunc(root->left, result);
                    dummyFunc(root->right, result);
                    result.push_back(root->val);
                };
                dummyFunc(root, result);
            };

            vector<int> result;
            innerPostorder(root, result);
            return result;
        }

        /**
         * @problem: LC 102: binary tree level order
         * @site: https://leetcode.cn/problems/binary-tree-level-order-traversal/
         * @methods: binary tree;
         * **/
        vector<vector<int>> levelOrder(TreeNode* root) {
            if (root == nullptr) return {};

            vector<vector<int>> result;

            queue<pair<TreeNode*, int>> levelBuffer;
            levelBuffer.emplace(root, 1);
            while (!levelBuffer.empty()) {
                auto temp = levelBuffer.front();
                levelBuffer.pop();
                if (temp.second > result.size()) {
                    result.push_back({temp.first->val});
                } else {
                    result[temp.second - 1].push_back(temp.first->val);
                }
                if (temp.first->left != nullptr) {
                    levelBuffer.emplace(temp.first->left, temp.second + 1);
                }
                if (temp.first->right != nullptr) {
                    levelBuffer.emplace(temp.first->right, temp.second + 1);
                }
            }

            return result;
        }

        /**
         * @problem: LC 226: reverse binary tree
         * @site: https://leetcode.cn/problems/invert-binary-tree/
         * @methods: binary tree;
         * **/
        TreeNode* invertTree(TreeNode* root) {
            const auto& innerPreorder = [](TreeNode* root) {
                std::function<void(TreeNode*)> dummyFunc;
                dummyFunc = [&] (TreeNode* root) {
                    if (!root) return ;
                    swap(root->left, root->right);
                    dummyFunc(root->left);
                    dummyFunc(root->right);
                };
                dummyFunc(root);
            };

            innerPreorder(root);
            return root;
        }

        /**
         * @problem: LC 101: symmetic tree
         * @site: https://leetcode.cn/problems/symmetric-tree/
         * @methods: binary tree;
         * **/
        bool isSymmetric(TreeNode* root) {
            const auto& innerPreorder = [](TreeNode* leftNode, TreeNode* rightNode) ->bool{
                std::function<bool(TreeNode*, TreeNode*)> dummyFunc;
                dummyFunc = [&] (TreeNode* leftNode, TreeNode* rightNode) -> bool{
                    if (leftNode == nullptr && rightNode == nullptr) return true;
                    else if (leftNode == nullptr && rightNode != nullptr) return false;
                    else if (leftNode != nullptr && rightNode == nullptr) return false;
                    else if (leftNode->val != rightNode->val) return false;

                    bool outside = dummyFunc(leftNode->left, rightNode->right);
                    bool inside = dummyFunc(leftNode->right, rightNode->left);
                    return outside && inside;
                };
                return dummyFunc(leftNode, rightNode);
            };
            if (root == nullptr) return true;
            return innerPreorder(root->left, root->right);
        }

        /**
         * @problem: LC 104: max depth of binary tree
         * @site: https://leetcode.cn/problems/maximum-depth-of-binary-tree/
         * @methods: binary tree;
         * **/
        int maxDepth(TreeNode* root) {
            const auto& innerFunc = [](TreeNode* root)->int{
                std::function<int(TreeNode*)> dummyFunc;
                dummyFunc = [&](TreeNode* root)->int{
                    if (!root) return 0;
                    int leftDepth = dummyFunc(root->left);
                    int rightDepth = dummyFunc(root->right);

                    return max(leftDepth, rightDepth) + 1;

                };
                return dummyFunc(root);
            };

            return innerFunc(root);
        }

        /**
         * @problem: LC 111: min depth of binary tree
         * @site: https://leetcode.cn/problems/minimum-depth-of-binary-tree/
         * @methods: binary tree;
         * **/
        int minDepth(TreeNode* root) {
            const auto& innerFunc = [](TreeNode* root)->int{
                std::function<int(TreeNode*)> dummyFunc;
                dummyFunc = [&](TreeNode* root)->int{
                    if (!root) return 0;

                    int leftDepth = dummyFunc(root->left);
                    int rightDepth = dummyFunc(root->right);

                    if (root->left && !root->right) {
                        return leftDepth + 1;
                    } else if (!root->left && root->right) {
                        return rightDepth + 1;
                    }

                    return min(leftDepth, rightDepth) + 1;

                };
                return dummyFunc(root);
            };
            if (!root) return 0;
            return innerFunc(root);
        }

        /**
         * @problem: LC 222: count complete tree nodes
         * @site: https://leetcode.cn/problems/count-complete-tree-nodes/
         * @methods: binary tree;
         * **/
        int countNodes(TreeNode* root) {
            const auto& innerFunc = [](TreeNode* root) ->int {
                std::function<int(TreeNode*)> dummyFunc;
                dummyFunc = [&](TreeNode* root) ->int{
                    if (!root) return 0;
                    auto leftNode = root->left, rightNode = root->right;
                    int leftDepth = 1, rightDepth = 1;
                    while (leftNode) {
                        leftNode = leftNode->left;
                        ++leftDepth;
                    }
                    while (rightNode) {
                        rightNode = rightNode->right;
                        ++rightDepth;
                    }

                    if (leftDepth == rightDepth) {
                        return (1 << leftDepth) - 1;
                    }
                    return dummyFunc(root->left) + dummyFunc(root->right) + 1;
                };
                return dummyFunc(root);
            };
            return innerFunc(root);
        }

        /**
         * @problem: LC 110: balanced binary tree
         * @site: https://leetcode.cn/problems/balanced-binary-tree/
         * @methods: binary tree;
         * **/
        bool isBalanced(TreeNode* root) {
            const auto& innerFunc = [](TreeNode* root) ->pair<int, bool> {
                std::function<pair<int, bool>(TreeNode*)> dummyFunc;
                dummyFunc = [&](TreeNode* root)->pair<int, bool> {
                    auto resultCheck = true;

                    if (!root) return {0, resultCheck};
                    auto leftDepth = dummyFunc(root->left);
                    auto rightDepth = dummyFunc(root->right);
                    resultCheck = (leftDepth.second && rightDepth.second);

                    if (abs(rightDepth.first - leftDepth.first) > 1) {
                        resultCheck = false;
                    }

                    return {max(leftDepth.first, rightDepth.first) + 1, resultCheck};
                };
                return dummyFunc(root);
            };
            return innerFunc(root).second;
        }

        /**
         * @problem: LC 257: binary tree paths
         * @site: https://leetcode.cn/problems/binary-tree-paths/
         * @methods: binary tree;
         * **/
        vector<string> binaryTreePaths(TreeNode* root) {
            vector<string> result;

            const auto& innerFunc = [](TreeNode* root, vector<string>& result, const string& temp) {
                std::function<void(TreeNode*, vector<string>&, string)> dummyFunc;
                dummyFunc = [&](TreeNode* root, vector<string>& result, string temp) {
                    if (!root) return ;
                    if (temp.empty()) {
                        temp = to_string(root->val);
                    } else {
                        temp += ("->" + to_string(root->val));
                    }
                    if (!root->left && !root->right) {
                        result.push_back(temp);
                    }
                    if (root->left) {
                        dummyFunc(root->left, result, temp);
                    }
                    if (root->right) {
                        dummyFunc(root->right, result, temp);
                    }
                };
                return dummyFunc(root, result, "");
            };

            innerFunc(root, result, "");
            return result;
        }

        /**
         * @problem: LC 404: left leaves sum
         * @site: https://leetcode.cn/problems/sum-of-left-leaves/
         * @methods: binary tree;
         * **/
        int sumOfLeftLeaves(TreeNode* root) {
            auto innerFunc = [](TreeNode *root)->int{
                std::function<int(TreeNode*)> dummyFunc;
                dummyFunc = [&](TreeNode* root)->int{
                    if (!root) return 0;
                    int result = 0;
                    if (root->left && !root->left->left && !root->left->right) result += root->left->val;
                    result += dummyFunc(root->left) + dummyFunc(root->right);
                    return result;
                };
                return dummyFunc(root);
            };

            if (!root) return 0;

            return innerFunc(root);
        }

        /**
         * @problem: LC 513: find bottom left tree value
         * @site: https://leetcode.cn/problems/find-bottom-left-tree-value/
         * @methods: binary tree;
         * **/
        int findBottomLeftValue(TreeNode* root) {
            int result = 0;
            queue<TreeNode*> levelBuffer;
            if (root != nullptr) levelBuffer.push(root);
            while (!levelBuffer.empty()) {
                int len = levelBuffer.size();
                for (int i = 0; i < len; i++) {
                    TreeNode* node = levelBuffer.front();
                    levelBuffer.pop();
                    if (i == 0) result = node->val;
                    if (node->left) levelBuffer.push(node->left);
                    if (node->right) levelBuffer.push(node->right);
                }
            }
            return result;
        }

        /**
         * @problem: LC 112: path sum
         * @site: https://leetcode.cn/problems/path-sum/
         * @methods: binary tree; recursion;
         * **/
        bool hasPathSum(TreeNode* root, int targetSum) {
            if (!root) return false;
            if (!root->left && !root->right) {
                return root->val == targetSum;
            }
            bool result = false;
            if (root->left) {
                result |= hasPathSum(root->left, targetSum - root->val);
            }
            if (root->right) {
                result |= hasPathSum(root->right, targetSum - root->val);
            }
            return result;
        }

        /**
         * @problem: LC 106: construct binary tree
         * @site: https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
         * @methods: binary tree; recursion;
         * **/
        TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
            int len = postorder.size();
            if (len == 0) return nullptr;

            auto curVal = *postorder.rbegin();
            auto root = new TreeNode(curVal);

            int sep = 0;
            for (sep = 0; sep < len - 1; sep++) {
                if (inorder[sep] == curVal) {
                    break;
                }
            }
            int leftNodes = sep, rightNodes = len - sep - 1;
            if (leftNodes > 0) {
                auto leftInorder = vector<int>(inorder.begin(), inorder.begin() + leftNodes);
                auto leftPostorder = vector<int>(postorder.begin(), postorder.begin() + leftNodes);
                root->left = buildTree(leftInorder, leftPostorder);
            }

            if (rightNodes > 0) {
                auto rightInorder = vector<int>(inorder.begin() + leftNodes + 1, inorder.begin() + leftNodes + rightNodes + 1);
                auto rightPostorder = vector<int>(postorder.begin() + leftNodes, postorder.begin() + leftNodes + rightNodes);
                root->right = buildTree(rightInorder, rightPostorder);
            }

            return root;
        }


        /**
         * @problem: LC 106: max binary tree
         * @site: https://leetcode.cn/problems/maximum-binary-tree/
         * @methods: binary tree; recursion;
         * **/
        TreeNode* constructMaximumBinaryTree(vector<int> nums) {
            int maxIndex = 0, maxVal = INT_MIN, len = nums.size();
            TreeNode *root = nullptr;
            for (int i = 0; i < len; ++i) {
                if (nums[i] > maxVal) {
                    maxVal = nums[i];
                    maxIndex = i;
                }
            }
            if (len > 0) {
                root = new TreeNode(maxVal);
                int leftNodes = maxIndex, rightNodes = len - maxIndex - 1;
                if (leftNodes > 0) {
                    root->left = constructMaximumBinaryTree(vector<int>(nums.begin(), nums.begin() + leftNodes));
                }
                if (rightNodes > 0) {
                    root->right = constructMaximumBinaryTree(vector<int>(nums.begin() + leftNodes + 1, nums.begin() + leftNodes + rightNodes + 1));
                }
            }
            return root;
        }

        /**
         * @problem: LC 617: merge binary tree
         * @site: https://leetcode.cn/problems/merge-two-binary-trees/
         * @methods: binary tree; recursion;
         * **/
        TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
            auto traversal = [](TreeNode* root1, TreeNode* root2)->TreeNode*{
                std::function<TreeNode*(TreeNode* , TreeNode*)> dummyFunc;
                dummyFunc = [&](TreeNode* root1, TreeNode* root2)->TreeNode*{
                    TreeNode* result = root1;
                    if (root1 != nullptr && root2!= nullptr) {
                        result->val += root2->val;
                        result->left = dummyFunc(root1->left, root2->left);
                        result->right = dummyFunc(root1->right, root2->right);
                    } else {
                        if (root1 == nullptr) {
                            result = root2;
                        }
                        if (root2 == nullptr) {
                            result = root1;
                        }
                    }
                    return result;
                };
                return dummyFunc(root1, root2);
            };
            return traversal(root1, root2);
        }

        /**
         * @problem: LC 98: validate BST
         * @site: https://leetcode.cn/problems/validate-binary-search-tree/
         * @methods: binary tree; BST;
         * **/
        bool isValidBST(TreeNode* root) {
            auto traversal = [](TreeNode* root, long long minVal, long long maxVal) -> bool{
                std::function<bool(TreeNode*, long long, long long)> dummyFunc;
                dummyFunc = [&](TreeNode* root, long long minVal, long long maxVal)->bool {
                    bool result = true;
                    if (root == nullptr) return result;
                    if (root->val > minVal && root->val < maxVal) {
                        result &= dummyFunc(root->left, minVal, root->val);
                        result &= dummyFunc(root->right, root->val, maxVal);
                    } else {
                        result = false;
                    }
                    return result;
                };
                return dummyFunc(root, minVal, maxVal);
            };
            return traversal(root, LLONG_MIN, LLONG_MAX);
        }

        /**
         * @problem: LC 530: min diff in BST
         * @site: https://leetcode.cn/problems/minimum-absolute-difference-in-bst/
         * @methods: binary tree; BST;
         * **/
        int getMinimumDifference(TreeNode* root) {
            auto traversal = [](TreeNode* root)->int {
                std::function<int(TreeNode*)> dummyFunc;
                dummyFunc = [&](TreeNode* root)->int{
                    int result = INT_MAX;
                    if (!root->left && !root->right) return result;
                    if (root->left) {
                        result = min(result, min(abs(root->val - root->left->val), dummyFunc(root->left)));
                    }
                    if (root->right) {
                        result = min(result, min(abs(root->val - root->right->val), dummyFunc(root->right)));
                    }
                    return result;
                };
                return dummyFunc(root);
            };
            if (!root) return 0;
            return traversal(root);
        }

        /**
         * @problem: LC 501: mode in BST
         * @site: https://leetcode.cn/problems/minimum-absolute-difference-in-bst/
         * @methods: binary tree; BST;
         * **/
        vector<int> findMode(TreeNode* root) {
            auto traversal = [](TreeNode* cur)->vector<int>{
                TreeNode *pre = nullptr;
                int count = 0, maxCount = 0;
                vector<int> result;
                std::function<void(TreeNode*)> dummyFunc;
                dummyFunc = [&](TreeNode* cur){
                    if (cur == nullptr) return ;

                    dummyFunc(cur->left);
                    if (pre == nullptr) count = 1;
                    else if (pre->val == cur->val) {
                        count ++;
                    } else {
                        count = 1;
                    }
                    pre = cur;

                    if (count == maxCount) {
                        result.push_back(cur->val);
                    }
                    if (count > maxCount) {
                        maxCount = count;
                        result.clear();
                        result.push_back(cur->val);
                    }

                    dummyFunc(cur->right);
                };
                dummyFunc(cur);
                return result;
            };
            return traversal(root);
        }

        /**
         * @problem: LC 236: public ancestor
         * @site: https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/description/
         * @methods: binary tree;
         * **/
        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
            TreeNode *result = nullptr, *lr = nullptr, *rr = nullptr;
            if (root == q || root == p || root == nullptr) {
                return root;
            }

            if (root->left) {
                lr = lowestCommonAncestor(root->left, p, q);
            }
            if (root->right) {
                rr = lowestCommonAncestor(root->right, p, q);
            }

            if (lr && rr) {
                result = root;
            } else if (lr) {
                return lr;
            } else if (rr) {
                return rr;
            }
            return result;
        }

        /**
         * @problem: LC 235: public ancestor in BST
         * @site: https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree/description/
         * @methods: binary tree;
         * **/
        TreeNode* lowestCommonAncestorBST(TreeNode* root, TreeNode* p, TreeNode* q) {
            if (!root) return nullptr;
            if (p->val > q->val) swap(p, q);
            if (root->val >= p->val && root->val <= q->val) {
                return root;
            }
            if (root->left && root->val > q->val) {
                return lowestCommonAncestorBST(root->left, p, q);
            }

            if (root->right && root->val < p->val) {
                return lowestCommonAncestorBST(root->right, p, q);
            }
            return nullptr;
        }

        /**
         * @problem: LC 701: insert in BST
         * @site: https://leetcode.cn/problems/insert-into-a-binary-search-tree/
         * @methods: binary tree; BST;
         * **/
        TreeNode* insertIntoBST(TreeNode* root, int val) {
            if (!root) {
                root = new TreeNode(val);
            }
            else {
                if (root->val > val) {
                    root->left = insertIntoBST(root->left, val);
                }
                if (root->val < val) {
                    root->right = insertIntoBST(root->right, val);
                }
            }
            return root;
        }

        /**
         * @problem: LC 701: delete in BST
         * @site: https://leetcode.cn/problems/delete-node-in-a-bst/
         * @methods: binary tree; BST;
         * **/
        TreeNode* deleteNode(TreeNode* root, int key) {
            if (!root) return nullptr;
            TreeNode * result = nullptr;
            if (root->val == key) {
                if (!root->left) {
                    return root->right;
                } else if (!root->right) {
                    return root->left;
                } else {
                    TreeNode *temp = root->right;
                    while (temp->left) {
                        temp = temp->left;
                    }
                    temp->left = root->left;
                    return root->right;
                }
            } else if (root->val < key) {
                root->right = deleteNode(root->right, key);
            } else {
                root->left = deleteNode(root->left, key);
            }
            return root;
        }

        /**
         * @problem: LC 701: delete in BST
         * @site: https://leetcode.cn/problems/delete-node-in-a-bst/
         * @methods: binary tree; BST;
         * **/
        TreeNode* trimBST(TreeNode* root, int low, int high) {
            if (!root) return nullptr;

            if (root->val < low) {
                root->right = trimBST(root->right, low, high);
                return root->right;
            } else if(root->val > high) {
                root->left = trimBST(root->left, low, high);
                return root->left;
            } else {
                root->left = trimBST(root->left, low, high);
                root->right = trimBST(root->right, low, high);
            }
            return root;
        }

        /**
         * @problem: LC 108: convert sorted array to binary search tree
         * @site: https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/
         * @methods: binary tree; BST;
         * **/
        TreeNode* sortedArrayToBST(vector<int>& nums) {
            int len = nums.size();
            std::function<TreeNode*(vector<int>&, int, int)> binarySplit;
            binarySplit = [&](vector<int>& nums, int left, int right)->TreeNode*{
                if (left > right) return nullptr;
                int mid = (left + right + 1) >> 1;
                auto *root = new TreeNode(nums[mid]);
                root->left = binarySplit(nums, left, mid - 1);
                root->right = binarySplit(nums, mid + 1, right);
                return root;
            };

            if (len == 0) {
                return nullptr;
            }
            return binarySplit(nums, 0, len - 1);
        }

        /**
         * @problem: LC 538: convert binary search tree to grater sum tree;
         * @site: https://leetcode.cn/problems/convert-bst-to-greater-tree/
         * @methods: binary tree; BST;
         * **/
        TreeNode* convertBST(TreeNode *root) {
            auto traversal = [](TreeNode *root){
                int preSum = 0;
                std::function<void(TreeNode*)> dummyFunc;
                dummyFunc = [&](TreeNode *root){
                    if (!root) return ;
                    dummyFunc(root->right);
                    root->val += preSum;
                    preSum  = root->val;
                    dummyFunc(root->left);
                };
                dummyFunc(root);
            };
            traversal(root);
            return root;
        }
    };

}

#endif //ALGO_BINARYTREE_H
