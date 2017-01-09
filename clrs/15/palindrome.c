#include <stdio.h>
#include <string.h>

int
is_palindrome(char *s, int start, int end)
{
    while (s + start < s + end) {
        if (*(s + start) != *(s + end))
            return 0;
        start++;
        end--;
    }

    return 1;
}

/* θ(n^3) */
void
longest_palindrome(char *s)
{
    int i, j, length;

    for (length = strlen(s); length > 0; length--)
        for (i = 0; i + length <= strlen(s); i++)
            /* 判断有重复，浪费时间了 */
            if (is_palindrome(s, i, i + length - 1)) {
                char temp[length + 1];
                strncpy(temp, s + i, length);
                temp[length] = '\0';
                printf("%s\n", temp);
                return;
            }

    printf("no palindrome\n");
}

enum { FALSE, TRUE };

void
dp_longest_palindrome(char *s)
{
    int length = strlen(s);
    int palindrome[length][length];
    int i, j;
    int max_len, start;
    
    memset(palindrome, 0, sizeof(int) * length * length);
    start = 0;
    max_len = 1;
    for (i = 0; i < length; i++)
        palindrome[i][i] = TRUE;

    for (i = 0; i < length - 1; i++)
        if (s[i] == s[i + 1]) {
            palindrome[i][i + 1] = TRUE;
            start = i;
            max_len = 2;
        }

    for (i = 3; i <= length; i++)
        for (j = 0; j < length - i + 1; j++) {
            int end = j + i - 1;
            if (s[j] == s[end] && palindrome[j + 1][end - 1] == TRUE) {
                palindrome[j][end] = TRUE;
                start = j;
                max_len = i;
            }
        }

    char temp[max_len + 1];
    strncpy(temp, s + start, max_len);
    temp[max_len] = '\0';
    printf("%s\n", temp);
}

int
main(void)
{
    char *s = "character";
    longest_palindrome(s);
    dp_longest_palindrome(s);
}
               
