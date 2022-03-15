#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nw.h"

#define NW_ORIGIN_NONE 0
#define NW_ORIGIN_TOP  1
#define NW_ORIGIN_LEFT 2
#define NW_ORIGIN_DIAG 4

void nw_freematrix(struct nw_matrix *matrix)
{
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
        free(matrix->origin[i]);
    }
    free(matrix->data);
    free(matrix->origin);
    free(matrix);
}

struct nw_matrix *nw_allocmatrix(const int rows, const int columns)
{
    struct nw_matrix *matrix = (struct nw_matrix *) malloc(sizeof(struct nw_matrix));

    matrix->rows = rows;
    matrix->columns = columns;
    matrix->data = (int **) malloc(rows * sizeof(int *));
    matrix->origin = (char **) malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        matrix->data[i] = (int *) malloc(columns * sizeof(int));
        matrix->origin[i] = (char *) malloc(columns * sizeof(char));
        for (int j = 0; j < columns; j++) {
            matrix->origin[i][j] = NW_ORIGIN_NONE;
        }
    }

    return matrix;
}

struct nw_matrix *nw_create_matrix(const char *sa, const char *sb, int match, int mismatch, int gap)
{
    int rows = strlen(sa) + 1;
    int cols = strlen(sb) + 1;
    struct nw_matrix *matrix = nw_allocmatrix(rows, cols);

    matrix->data[0][0] = 0;
    for (int x = 1; x < cols; x++) {
        matrix->data[0][x] = x * gap;
        matrix->origin[0][x] = NW_ORIGIN_LEFT;
    }
    for (int y = 1; y < rows; y++) {
        matrix->data[y][0] = y * gap;
        matrix->origin[y][0] = NW_ORIGIN_TOP;
    }
    return matrix;
}

void nw_fill_matrix(struct nw_matrix *matrix, const char *sa, const char *sb, int match, int mismatch, int gap)
{
    int MatchMismatch;

    for (int row = 1; row < matrix->rows; row++) {
        for (int col = 1; col < matrix->columns; col++) {
            if (sa[row - 1] == sb[col - 1]) {
                MatchMismatch = match;
            } else {
                MatchMismatch = mismatch;
            }
            MatchMismatch = matrix->data[row - 1][col - 1] + MatchMismatch;
            int gapA = matrix->data[row][col - 1] + gap;
            int gapB = matrix->data[row - 1][col] + gap;
            int maxGap = gapA > gapB ? gapA : gapB;

            matrix->data[row][col] = MatchMismatch > maxGap ? MatchMismatch : maxGap;
            if (matrix->data[row][col] == gapB) {
                matrix->origin[row][col] |= NW_ORIGIN_TOP;
            }
            if (matrix->data[row][col] == gapA) {
                matrix->origin[row][col] |= NW_ORIGIN_LEFT;
            }
            if (matrix->data[row][col] == MatchMismatch) {
                matrix->origin[row][col] |= NW_ORIGIN_DIAG;
            }
            // nw_print_matrix(matrix, sa, sb);
        }
    }
}

void nw_print_matrix_row(struct nw_matrix *matrix, int row, const char *sa)
{
    // Print Column Header
    if (row) {
        printf("%c ", sa[row - 1]);
    } else {
        printf("  ");
    }

    for (int col = 0; col < matrix->columns; col++) {
        printf("%4d", matrix->data[row][col]);
    }

    printf("\n");
}

void nw_print_matrix(struct nw_matrix *matrix, const char *sa, const char *sb)
{
    // Print Header
    printf("%6c", ' ');
    for (int col = 0; col < matrix->columns; col++) {
        printf("%4c", sb[col]);
    }
    printf("\n");

    for (int row = 0; row < matrix->rows; row++) {
        nw_print_matrix_row(matrix, row, sa);
    }

    printf("\n");
}

void nw_trackback_matrix(struct nw_matrix *matrix, const char *sa, const char *sb, char *new_a, char *new_b, char *sdiff)
{
    const char CHR_MATCH = '*';
    const char CHR_MISMATCH = '|';
    const char CHR_INSERT = ' ';
    const char CHR_INSERTED = '-';
    int curY = matrix->rows - 1;
    int curX = matrix->columns - 1;
    int max = curX > curY ? curX : curY;
    int curPos = max;

    for (int i = 0; i < max; i++) {
        printf("%3d", matrix->data[curY][curX]);
        if (matrix->origin[curY][curX] & NW_ORIGIN_DIAG) {
            // Diagonal (Match / Mismatch)
            curX--;
            curY--;
            curPos--;
            new_a[curPos] = sa[curY];
            new_b[curPos] = sb[curX];
            if (sa[curY] == sb[curX]) {
                sdiff[curPos] = CHR_MATCH;
            } else {
                sdiff[curPos] = CHR_MISMATCH;
            }
        } else if (matrix->origin[curY][curX] & NW_ORIGIN_LEFT) {
            // Left (Insert in new_a)
            curX--;
            curPos--;
            new_a[curPos] = CHR_INSERTED;
            new_b[curPos] = sb[curX];
            sdiff[curPos] = CHR_INSERT;
        } else if (matrix->origin[curY][curX] & NW_ORIGIN_TOP) {
            // Up (Insert in new_b)
            curY--;
            curPos--;
            new_a[curPos] = sa[curY];
            new_b[curPos] = CHR_INSERTED;
            sdiff[curPos] = CHR_INSERT;
        }
    }
    printf("%3d\n", matrix->data[0][0]);
}
