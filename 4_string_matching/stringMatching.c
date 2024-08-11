#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int count, index;
} match_result;

match_result stringMatching(const char *text, const char *pattern, int patternLength, int textLength)
{
    match_result result = {0, -1};
    for (int i = 0; i <= textLength - patternLength; i++)
    {
        int j = 0;
        while (j < patternLength)
        {
            result.count++;
            if (pattern[j] != text[i + j])
                break;
            j++;
        }

        if (j == patternLength)
        {
            result.index = i;
            return result;
        }
    }
    return result;
}

void test()
{
    int patternLength, textLength;

    printf("Enter the length of the pattern : ");
    scanf("%d", &patternLength);

    char pattern[patternLength + 1];
    printf("Enter the pattern: ");
    getchar();
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0';

    printf("Enter the length of the text : ");
    scanf("%d", &textLength);

    char text[textLength + 1];
    printf("Enter the text: ");
    getchar();
    fgets(text, sizeof(text), stdin);
    pattern[strcspn(text, "\n")] = '\0';

    match_result result = stringMatching(text, pattern, patternLength, textLength);
    if (result.index == -1)
        printf("Pattern didn't get matched.\n");
    else
        printf("Pattern got matched from index %d to %d.\n", result.index, result.index + patternLength);
}

void plotter()
{
    srand(time(NULL));
    FILE *data = fopen("stringMatching_results.dat", "w");
    fprintf(data, "#size best avg worst\n");

    int n = 1000;
    char *text = (char *)malloc(sizeof(char) * n);
    for (int i = 0; i < n; i++)
        text[i] = 'a';

    for (int m = 10; m <= 1000; m < 100 ? (m = m + 10) : (m += 100))
    {
        char *pattern = (char *)malloc(sizeof(char) * m);

        for (int i = 0; i < m; i++)
            pattern[i] = 'a';

        match_result bestCase = stringMatching(text, pattern, m, n);

        pattern[m - 1] = 'b';
        match_result worstCase = stringMatching(text, pattern, m, n);

        for (int i = 0; i < m; i++)
            pattern[i] = 97 + rand() % 3;
        match_result avgCase = stringMatching(text, pattern, m, n);

        fprintf(data, "%d %d %d %d\n", m, bestCase.count, avgCase.count, worstCase.count);
        free(pattern);
    }
    free(text);
    fclose(data);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <plot|test>\n", argv[0]);
        exit(1);
    }

    if (strcmp(argv[1], "test") == 0)
        test();

    if (strcmp(argv[1], "plot") == 0)
        plotter();
    return 0;
}