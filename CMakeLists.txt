cmake_minimum_required(VERSION 3.26)
project(Algo)

set(CMAKE_CXX_STANDARD 17)

add_executable(Algo
        Solutions/Solution.h
        main.cpp
        Solutions/ArraySolutions.h
        Solutions/LinkedListOperations.h
        Solutions/HashTableOperations.h
        Solutions/StringOperations.h
        Solutions/DoublePointerCollection.h
        Solutions/StackAndQueue.h
        Solutions/BinaryTree.h
        Solutions/BackTracking.h
        Solutions/BasicDataStructure.h
        Solutions/Greedy.h
        Solutions/DynamicPlanning.h)
