#include <cstdio>
#include <string>

int find_num_of_decoding_possibilities(std::string &str)
{
    /* No. of possibilities for the substring from start to the previous char
     * in the current iteration. */
    int poss_prev = 1;
    /* No. of possibilities for the substring from start to the char before the
     * previous char to the one in current iteration.  */
    int poss_before_prev = 1;
    int count = 0; // Final count.

    // Nothing can be decoded.
    if (str[0] == '0')
        return 0;

    if (1 == str.size()) {
        if (str[0] == '0')
            return 0;
        else
            return 1;
    }

    // Chars under consideration are ones from start to "ix - 1".
    for (size_t ix = 2; ix <= str.size(); ++ix) {
        count = 0;
        /* 0 cannot be used by itself. So it should always be considered along
         * with the previous element. */
        if (str[ix - 1] > '0')
            count = poss_prev;

        // Check if previous char and this char is a number below 26.
        if ((str[ix - 2] == '1') || (str[ix - 2] == '2' && str[ix - 1] < '7'))
            /* Example: 
             * Conisder the string 111.
             * Possibilities: 1,1,1  11,1  1,11.
             * Now when another 1 is encountered, the existing combinations
             * above can be appended with 1: 1,1,1,1  11,1,1  1,11,1.
             * Now the previous char "1" and current char "1" together form a
             * valid alphabet. So now, the new combinations with number "11"
             * need to be calculated.
             * This would be: 1,1,11 and 11,11.
             * As seen above, the previous two chars already can be decoded in
             * two ways. We have already found this and stored in
             * poss_before_prev.
             * So we add it to count. */
            count = count + poss_before_prev;
        poss_before_prev = poss_prev;
        poss_prev = count;
    }

    return count;
}

int main(int argc, char *argv[])
{
    std::string s1 = "111";
    std::printf("%s : %d\n", s1.c_str(),
                find_num_of_decoding_possibilities(s1));

    std::string s2 = "1111";
    std::printf("%s : %d\n", s2.c_str(),
                find_num_of_decoding_possibilities(s2));

    std::string s3 = "1127";
    std::printf("%s : %d\n", s3.c_str(),
                find_num_of_decoding_possibilities(s3));

    std::string s4 = "0";
    std::printf("%s : %d\n", s4.c_str(),
                find_num_of_decoding_possibilities(s4));

    std::string s5 = "01";
    std::printf("%s : %d\n", s5.c_str(),
                find_num_of_decoding_possibilities(s5));

    std::string s6 = "101";
    std::printf("%s : %d\n", s6.c_str(),
                find_num_of_decoding_possibilities(s6));

    return 0;
}
