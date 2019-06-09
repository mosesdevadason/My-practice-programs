/******************************************************************************
 * Given a list of numbers and a number k, return whether any two numbers from
 * the list add up to k.
 *
 * For example, given  {10, 15, 3, 7} and k of 17, return true sunce 10 + 7 is
 * 17.
 *****************************************************************************/

#include <vector>
#include <unordered_set>
#include <cstdio>
#include <algorithm>

bool list_adds_up_to_val_check_using_hashtable(std::vector<int> &input, int k)
{
    // Use unordered_map if indices have to be returned.
    std::unordered_set<int> hashmap;

    // Boundary cases.
    if ((0 == input.size()) || (1 == input.size())) {
        std::printf("Input array is of size %lu\n", input.size());
        return false;
    }

    for (std::size_t ix = 0 ; ix < input.size() ; ++ix) {
        // If k - input[ix] is present in the hashmap.
        auto it = hashmap.find(k - input[ix]);
        if (it != hashmap.end()) {
            std::printf("Numbers %d and %d add upto %d\n", input[ix], *it, k);
            return true;
        }
        hashmap.insert(input[ix]);
    }

    return false;
}

bool list_adds_up_to_val_check_using_sorting(std::vector<int> &input, int k)
{
    auto left_it = input.begin(), right_it = input.end() - 1;
    int temp_sum = 0;

    // Boundary cases.
    if ((0 == input.size()) || (1 == input.size())) {
        std::printf("Input array is of size %lu\n", input.size());
        return false;
    }

    std::sort(input.begin(), input.end());

    while(left_it < right_it) {
        temp_sum = *left_it + *right_it;
        if (temp_sum == k) {
            std::printf("Numbers %d and %d add upto %d\n", *left_it, *right_it,
                    k);
            return true;
        }
        if (temp_sum < k) {
            ++left_it;
        }
        else {
            --right_it;
        }
    }

    return false;
}

static inline void print_vector(std::vector<int> &input) {
    for(auto it = input.begin() ; it != input.end() ; ++it) {
        std::printf("%d ", *it);
    }
    std::printf("\n");
}

int main(int argc, char *argv[])
{
    std::vector<int> input = {10, 3, 15, 7};
    int k = 17;
    int retval = 0;

    print_vector(input);

    std::printf("SORTING SOLUTION:\n");
    if (!list_adds_up_to_val_check_using_sorting(input, k)) {
        std::printf("Sorting solution failed.\n");
        retval = 1;
    }
    std::printf("HASHMAP SOLUTION:\n");
    if (!list_adds_up_to_val_check_using_hashtable(input, k)) {
        std::printf("Hashmap solution failed.\n");
        retval = 1;
    }
    
    return retval;
}
