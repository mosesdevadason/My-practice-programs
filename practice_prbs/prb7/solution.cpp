#include <cstdio>
#include <vector>

int larget_sum_non_adj(std::vector<int> &nums)
{
    int sum_incl = 0;
    int sum_excl = 0;
    int old_sum_incl = 0;

    for (auto it = nums.begin() ; it != nums.end() ; ++it) {
        old_sum_incl = sum_incl;
        sum_incl = sum_excl + *it;
        /* sum_excl the current element will be the maximum among the sum
         * including the previous element and sum excluding the previous
         * element */
        sum_excl = std::max(old_sum_incl, sum_excl);
        std::printf("old_sum_incl : %d, sum_incl : %d, sum_excl : %d\n",
            old_sum_incl, sum_incl, sum_incl);
    }

    return std::max(sum_incl, sum_excl);
}

int main(int argc, char *argv[])
{
    std::vector<int> nums1({2, 4, 6, 2, 5});
    std::printf("Max of nums1 : %d\n", larget_sum_non_adj(nums1));

    std::vector<int> nums2({5, 1, 1, 5});
    std::printf("Max of nums2 : %d\n", larget_sum_non_adj(nums2));

    return 0;
}