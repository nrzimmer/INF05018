#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nw.h"

#define NW_ORIGIN_NONE 0
#define NW_ORIGIN_TOP 1
#define NW_ORIGIN_LEFT 2
#define NW_ORIGIN_DIAG 4
#define CHR_MATCH '*'
#define CHR_MISMATCH '|'
#define CHR_INSERT ' '
#define CHR_INSERTED '-'

struct __nw_matrix {
    int rows;
    int columns;
    int **data;
    char **origin;
};

int nw_get_matrix_value(nw_matrix * matrix, int row, int col);

void nw_freematrix(nw_matrix * matrix)
{
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
        free(matrix->origin[i]);
    }
    free(matrix->data);
    free(matrix->origin);
    free(matrix);
}

nw_matrix *nw_allocmatrix(const int rows, const int columns)
{
    nw_matrix *matrix = (nw_matrix *) malloc(sizeof(nw_matrix));

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

nw_matrix *nw_create_matrix(const char *sa, const char *sb, int match, int mismatch, int gap)
{
    int rows = strlen(sa) + 1;
    int cols = strlen(sb) + 1;

    return nw_allocmatrix(rows, cols);
    nw_matrix *matrix = nw_allocmatrix(rows, cols);

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

int nw_get_matrix_value(nw_matrix * matrix, int row, int col)
{
    if ((row < 0) || (col < 0))
        return 0;

    return matrix->data[row][col];
}

int nw_is_match(const char *sa, const char *sb, int row, int col)
{
    if ((row <= 0) || (col <= 0))
        return 0;
    if (sa[row - 1] == sb[col - 1])
        return 1;
    return 0;
}

int nw_get_best_origin(int mm, int ga, int gb, int *out)
{
    int max = (mm > ga ? mm : ga);

    *out = (max > gb ? max : gb);
    int result = 0;

    if (*out == mm)
        result |= NW_ORIGIN_DIAG;
    if (*out == ga)
        result |= NW_ORIGIN_LEFT;
    if (*out == gb)
        result |= NW_ORIGIN_TOP;
    return result;
}

void nw_fill_matrix(nw_matrix * matrix, const char *sa, const char *sb, int match, int mismatch, int gap)
{
    int mm;
    int ga;
    int gb;

    for (int row = 0; row < matrix->rows; row++) {
        for (int col = 0; col < matrix->columns; col++) {
            if (row == 0 && col == 0) {
                matrix->data[row][col] = 0;
                matrix->origin[row][col] = 0;
            } else if (row == 0) {
                matrix->data[row][col] = nw_get_matrix_value(matrix, row, col - 1) + gap;
                matrix->origin[row][col] = NW_ORIGIN_LEFT;
            } else if (col == 0) {
                matrix->data[row][col] = nw_get_matrix_value(matrix, row - 1, col) + gap;
                matrix->origin[row][col] = NW_ORIGIN_TOP;
            } else {
                mm = nw_get_matrix_value(matrix, row - 1, col - 1) + (nw_is_match(sa, sb, row, col) ? match : mismatch);
                ga = nw_get_matrix_value(matrix, row, col - 1) + gap;
                gb = nw_get_matrix_value(matrix, row - 1, col) + gap;
                matrix->origin[row][col] = nw_get_best_origin(mm, ga, gb, &(matrix->data[row][col]));
            }
#ifdef DEBUG
            nw_print_matrix(matrix, sa, sb);
#endif
        }
    }
}

void nw_print_matrix_row(nw_matrix * matrix, int row, const char *sa)
{
    // Print Column Header
    if (row) {
        printf("%c ", sa[row - 1]);
    } else {
        printf("  ");
    }

    for (int col = 0; col < matrix->columns; col++) {
        printf("%6d", matrix->data[row][col]);
    }

    printf("\n");
}

void nw_print_matrix(nw_matrix * matrix, const char *sa, const char *sb)
{
    // Print Header
    printf("%8c", ' ');
    for (int col = 0; col < matrix->columns; col++) {
        printf("%6c", sb[col]);
    }
    printf("\n");

    for (int row = 0; row < matrix->rows; row++) {
        nw_print_matrix_row(matrix, row, sa);
    }

    printf("\n");
}

int *nw_trackback_matrix(nw_matrix * matrix, const char *sa, const char *sb, char *new_a, char *new_b, char *sdiff)
{
    int row = matrix->rows - 1;
    int col = matrix->columns - 1;
    int max = col > row ? col : row;
    int *path = (int *) malloc((max + 1) * 2 * sizeof(int));
    int index = max;

    for (int i = 0; i < max; i++) {
        path[i * 2] = matrix->data[row][col];
        if (matrix->origin[row][col] & NW_ORIGIN_DIAG) {
            // Diagonal (Match / Mismatch)
            path[i * 2 + 1] = NW_ORIGIN_DIAG;
            col--;
            row--;
            index--;
            new_a[index] = sa[row];
            new_b[index] = sb[col];
            if (sa[row] == sb[col]) {
                sdiff[index] = CHR_MATCH;
            } else {
                sdiff[index] = CHR_MISMATCH;
            }
        } else if (matrix->origin[row][col] & NW_ORIGIN_LEFT) {
            // Left (Insert in new_a)
            path[i * 2 + 1] = NW_ORIGIN_LEFT;
            col--;
            index--;
            new_a[index] = CHR_INSERTED;
            new_b[index] = sb[col];
            sdiff[index] = CHR_INSERT;
        } else if (matrix->origin[row][col] & NW_ORIGIN_TOP) {
            // Up (Insert in new_b)
            path[i * 2 + 1] = NW_ORIGIN_TOP;
            row--;
            index--;
            new_a[index] = sa[row];
            new_b[index] = CHR_INSERTED;
            sdiff[index] = CHR_INSERT;
        }
    }
    path[max * 2] = 0;
    path[max * 2 + 1] = -1;
    return path;
}

int nw_get_identity(char *sdiff, int new_len)
{
    int result = 0;

    for (int i = 0; i < new_len; i++) {
        if (sdiff[i] == CHR_MATCH)
            result++;
    }
    return result;
}

void nw_print_path(int *path, int new_len)
{
    for (int i = 0; i <= new_len; i++) {
        printf("%d", path[i * 2]);
        switch (path[i * 2 + 1]) {
        case NW_ORIGIN_DIAG:
            printf(" \u2196 "); // ↖
            break;
        case NW_ORIGIN_TOP:
            printf(" \u2191 "); // ↑
            break;
        case NW_ORIGIN_LEFT:
            printf(" \u2190 "); // ← 
            break;
        default:
            printf("\n");
        }
    }
}
