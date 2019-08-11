#include <cstdio>
#include <vector>
#include <algorithm>

void init_zero (std::vector<int>& v, size_t len)
{
    for (size_t ix = 0 ; ix < len ; ++ix)
        v.push_back(0);
}

int find_possibilities_ext (int N, std::vector<int>& allowed)
{
    std::vector<int> dp;
    init_zero(dp, N + 1);

    // @TODO: Corner cases have not been identified yet.

    for (int ix = 0 ; ix < N + 1 ; ++ix) {
        // Example: if allowed = {1, 3, 5}, then dp[ix] = dp[ix - 1] +
        // dp[ix - 3] + dp[ix - 5].
        for (auto it = allowed.begin() ; it != allowed.end() ; ++it) {
            if ((ix - *it) > 0)
                dp[ix] += dp[ix - *it];
        }
        if (allowed.end() != std::find(allowed.begin(), allowed.end(), ix))
            dp[ix] += 1;

        std::printf("dp[%d] = %d\n", ix, dp[ix]);
    }

    return dp[N];
}

int find_possibilities (int N)
{
    int ix_minus_1_poss = 1; // Init for N = 1
    int ix_minus_2_poss = 2; // Init for N = 2
    int curr = 0;

    if (1 == N) return ix_minus_1_poss;
    if (2 == N) return ix_minus_2_poss;

    int temp = 0;
    for (int ix = 2 ; ix < N ; ++ix) {
        curr = ix_minus_1_poss + ix_minus_2_poss;
        ix_minus_1_poss = ix_minus_2_poss;
        ix_minus_2_poss = curr;
    }

    return curr;
}

int main(int argc, char *argv[])
{
    std::printf("N = 5 : %d\n", find_possibilities(5));

    std::vector<int> allowed = {1, 3, 5};
    std::printf("N = 5, allowed = {1, 3, 5} : %d\n", find_possibilities_ext(5,
                allowed));

    return 0;
}
