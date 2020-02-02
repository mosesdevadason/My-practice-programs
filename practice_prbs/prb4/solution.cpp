#include <cstdio>
#include <cstdlib>
#include <vector>

size_t segregate_negative_to_left(std::vector<int> &nums)
{
    size_t neg_count = 0;

    for (size_t ix = 0; ix < nums.size(); ++ix) {
        if (nums[ix] <= 0) {
            std::swap(nums[ix], nums[neg_count]);
            ++neg_count;
        }
    }

    return neg_count;
}

/*
 * 1. Segregate negative numbers to the left (or right) and get the count.
 * 2. Now for each positive number: Mark the element at index equal to
 *    the number negative, to indicate that the number was processed (if a
 *    number at an index is negative, it means that "index" is present in the
 *    array).
 * 3. Now walk the array and return the first element that is positive.
 */
int find_lowest_missing_positive(std::vector<int> &nums)
{
    if (0 == nums.size()) {
        return 1;
    }
    size_t neg_count = segregate_negative_to_left(nums);

    for (size_t ix = neg_count; ix < nums.size(); ++ix) {
        if ((std::abs(nums[ix]) - 1 + neg_count) < nums.size()) {
            nums[std::abs(nums[ix]) - 1 + neg_count] = -std::abs(
                    nums[std::abs(nums[ix]) - 1 + neg_count]);
        }
    }

    for (size_t ix = neg_count; ix < nums.size(); ++ix) {
        if (nums[ix] > 0) {
            // Since we are considering only the positive side of the array.
            return (ix - neg_count + 1);
        }
    }

    return (nums.size() - neg_count + 1);
}

int main(int argc, char *argv[])
{
    std::vector<int> nums {3, 4, -1, 1, -2, 6, -5, 0, 10, 15};
    std::printf("%d\n", find_lowest_missing_positive(nums));
    std::vector<int> nums1 {1, 2, 0};
    std::printf("%d\n", find_lowest_missing_positive(nums1));
    std::vector<int> nums2 {3, 4, -1, 1};
    std::printf("%d\n", find_lowest_missing_positive(nums2));
    std::vector<int> nums3 {1};
    std::printf("%d\n", find_lowest_missing_positive(nums3));
    return 0;
}
