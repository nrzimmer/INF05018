#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <locale.h>
#include "needleman-wunsch/nw.h"

const char *sa = "GCATT";
const char *sb = "GTT";

const int match = 7;
const int mismatch = -3;
const int gap = -4;

int main(void)
{
    setlocale(LC_ALL, "");
    nw_matrix *matrix = nw_create_matrix(sa, sb, match, mismatch, gap);

    nw_fill_matrix(matrix, sa, sb, match, mismatch, gap);
    nw_print_matrix(matrix, sa, sb);

    int len_a = strlen(sa);
    int len_b = strlen(sb);
    int new_len = len_a > len_b ? len_a : len_b;

    char *new_a = (char *) malloc(new_len * sizeof(char));
    char *new_b = (char *) malloc(new_len * sizeof(char));
    char *sdiff = (char *) malloc(new_len * sizeof(char));

    new_a[new_len] = 0;
    new_b[new_len] = 0;
    sdiff[new_len] = 0;

    int *path = nw_trackback_matrix(matrix, sa, sb, new_a, new_b, sdiff);
    int identity = nw_get_identity(sdiff, new_len);
    float identity_percent = (identity * 100.0) / new_len;

    printf("Path: ");
    nw_print_path(path, new_len);

    printf("\n%s\n%s\n%s\n\nScore: %d\nIdentity: %d/%d (%.2f%%)\n", new_a, sdiff, new_b, path[0], identity, new_len, identity_percent);

    free(new_a);
    free(new_b);
    free(sdiff);
    free(path);
    nw_freematrix(matrix);

    return 0;
}
