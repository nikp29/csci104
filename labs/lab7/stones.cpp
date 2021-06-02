#include "stones.h"
#include <queue> // to use std::priority_queue
using namespace std;

int lastStoneWeight(vector<int> &stones)
{
    // base case empty
    if (stones.size() == 0)
    {
        return 0;
    }
    // base case 1
    if (stones.size() == 1)
    {
        return stones.front();
    }
    make_heap(stones.begin(), stones.end());
    while (stones.size() != 1)
    {
        int weight_1 = stones.front();
        pop_heap(stones.begin(), stones.end());
        stones.pop_back();
        int weight_2 = stones.front();
        pop_heap(stones.begin(), stones.end());
        stones.pop_back();
        if (weight_1 != weight_2)
        {
            stones.push_back(weight_1 - weight_2);
            push_heap(stones.begin(), stones.end());
        }
        else if (stones.size() == 2)
        {
            return 0;
        }
    }
    return stones.front();
}
