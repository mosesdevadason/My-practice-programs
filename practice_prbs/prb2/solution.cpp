/******************************************************************************
 * Given an array of integers, return a new array such that each element at
 * index i of the new array is the product of all the numbers in the original
 * array except the one at i.
 *
 * For example, if our input was [1, 2, 3, 4, 5], the expected output would be
 * [120, 60, 40, 30, 24]. If our input was [3, 2, 1], the expected output would
 * be [2, 3, 6].
 *
 * Do it without using division operator.
 *****************************************************************************/

#include <cstdio>
#include <vector>

static inline void print_vector (std::vector<int> &nums)
{
    for (auto it = nums.begin() ; it != nums.end() ; ++it) {
        std::printf("%d ", *it);
    }
    std::printf("\n");
}

std::vector<int> product_without_self_find (std::vector<int> &nums)
{
    std::vector<int> result;
    int prod = 0;

    if (0 == nums.size()) {
        std::printf("nums param is of length 0\n");
        return result;
    }
    
    // result[ix] will contain product of all numbers to the left of ix.
    for (int ix = 0 ; ix < nums.size() ; ++ix) {
        if (ix == 0) {
            prod = 1;
        } else {
            prod = prod * nums[ix - 1];
        }
        result.push_back(prod);
    }

    // Now traversing from right, multiply result[ix] with the product of
    // elements to the right of ix.
    for (int ix = nums.size() - 1 ; ix >= 0 ; --ix) {
        if (ix == (nums.size() - 1)) {
            prod = 1;
        } else {
            prod = prod * nums[ix + 1];
        }
        result[ix] = prod * result[ix];
    }
    
    print_vector(result);

    return result;
}

int main(int argc, char *argv[])
{
    int retval = 0;
    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::vector<int> expected_result = {120, 60, 40, 30, 24};
    
    print_vector(nums);

    std::vector<int> result = product_without_self_find(nums);

    std::printf("Expected result: ");
    print_vector(expected_result);
    if (result == expected_result) {
        std::printf("Expected result is equal to actual.\n");
    } else {
        std::printf("Expected result is not equal to actual.\n");
        retval = 1;
    }

    return retval;
}
