#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nw.h"

#define NW_ORIGIN_NONE 0
#define NW_ORIGIN_TOP  1
#define NW_ORIGIN_LEFT 2
#define NW_ORIGIN_DIAG 4

void nwFreeMatrix(nwMatrix * matrix)
{
    for (int i = 0; i < matrix->Rows; i++) {
        free(matrix->Data[i]);
        free(matrix->Origin[i]);
    }
    free(matrix->Data);
    free(matrix->Origin);
    free(matrix);
}

nwMatrix *nwAllocMatrix(const int rows, const int columns)
{
    nwMatrix *matrix = (nwMatrix *) malloc(sizeof(nwMatrix));

    matrix->Rows = rows;
    matrix->Columns = columns;
    matrix->Data = (int **)malloc(rows * sizeof(int *));
    matrix->Origin = (char **)malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        matrix->Data[i] = (int *)malloc(columns * sizeof(int));
        matrix->Origin[i] = (char *)malloc(columns * sizeof(char));
        for (int j = 0; j < columns; j++) {
            matrix->Origin[i][j] = NW_ORIGIN_NONE;
        }
    }

    return matrix;
}

nwMatrix *nwGenerateMatrix(const char *seqA, const char *seqB, int match, int mismatch, int gap)
{
    int rows = strlen(seqA) + 1;
    int cols = strlen(seqB) + 1;
    nwMatrix *matrix = nwAllocMatrix(rows, cols);

    matrix->Data[0][0] = 0;
    for (int x = 1; x < cols; x++) {
        matrix->Data[0][x] = x * gap;
        matrix->Origin[0][x] = NW_ORIGIN_LEFT;
    }
    for (int y = 1; y < rows; y++) {
        matrix->Data[y][0] = y * gap;
        matrix->Origin[y][0] = NW_ORIGIN_TOP;
    }
    return matrix;
}

void nwFillMatrix(nwMatrix * matrix, const char *seqA, const char *seqB, int match, int mismatch, int gap)
{
    int MatchMismatch;

    for (int row = 1; row < matrix->Rows; row++) {
        for (int col = 1; col < matrix->Columns; col++) {
            if (seqA[row - 1] == seqB[col - 1]) {
                MatchMismatch = match;
            } else {
                MatchMismatch = mismatch;
            }
            MatchMismatch = matrix->Data[row - 1][col - 1] + MatchMismatch;
            int gapA = matrix->Data[row][col - 1] + gap;
            int gapB = matrix->Data[row - 1][col] + gap;
            int maxGap = gapA > gapB ? gapA : gapB;

            matrix->Data[row][col] = MatchMismatch > maxGap ? MatchMismatch : maxGap;
            if (matrix->Data[row][col] == gapB) {
                matrix->Origin[row][col] |= NW_ORIGIN_TOP;
            }
            if (matrix->Data[row][col] == gapA) {
                matrix->Origin[row][col] |= NW_ORIGIN_LEFT;
            }
            if (matrix->Data[row][col] == MatchMismatch) {
                matrix->Origin[row][col] |= NW_ORIGIN_DIAG;
            }
            // nwPrintMatrix(matrix, seqA, seqB);
        }
    }
}

void nwPrintMatrixRow(nwMatrix * matrix, int row, const char *seqA)
{
    // Print Column Header
    if (row) {
        printf("%c ", seqA[row - 1]);
    } else {
        printf("  ");
    }

    for (int col = 0; col < matrix->Columns; col++) {
        printf("%4d", matrix->Data[row][col]);
    }

    printf("\n");
}

void nwPrintMatrix(nwMatrix * matrix, const char *seqA, const char *seqB)
{
    // Print Header
    printf("%6c", ' ');
    for (int col = 0; col < matrix->Columns; col++) {
        printf("%4c", seqB[col]);
    }
    printf("\n");

    for (int row = 0; row < matrix->Rows; row++) {
        nwPrintMatrixRow(matrix, row, seqA);
    }

    printf("\n");
}

void nwSeqTrackback(nwMatrix * matrix, const char *seqA, const char *seqB, char *newSeqA, char *newSeqB, char *seqDiff)
{
    const char __CHR_MATCH = '*';
    const char __CHR_MISMATCH = '|';
    const char __CHR_INSERT = ' ';
    const char __CHR_INSERTED = '-';
    int curY = matrix->Rows - 1;
    int curX = matrix->Columns - 1;
    int max = curX > curY ? curX : curY;
    int curPos = max;

    for (int i = 0; i < max; i++) {
        printf("%3d", matrix->Data[curY][curX]);
        if (matrix->Origin[curY][curX] & NW_ORIGIN_DIAG) {
            // Diagonal (Match / Mismatch)
            curX--;
            curY--;
            curPos--;
            newSeqA[curPos] = seqA[curY];
            newSeqB[curPos] = seqB[curX];
            if (seqA[curY] == seqB[curX]) {
                seqDiff[curPos] = __CHR_MATCH;
            } else {
                seqDiff[curPos] = __CHR_MISMATCH;
            }
        } else if (matrix->Origin[curY][curX] & NW_ORIGIN_LEFT) {
            // Left (Insert in newSeqA)
            curX--;
            curPos--;
            newSeqA[curPos] = __CHR_INSERTED;
            newSeqB[curPos] = seqB[curX];
            seqDiff[curPos] = __CHR_INSERT;
        } else if (matrix->Origin[curY][curX] & NW_ORIGIN_TOP) {
            // Up (Insert in newSeqB)
            curY--;
            curPos--;
            newSeqA[curPos] = seqA[curY];
            newSeqB[curPos] = __CHR_INSERTED;
            seqDiff[curPos] = __CHR_INSERT;
        }
    }
    printf("%3d\n", matrix->Data[0][0]);
}

int nwGetMaxSeqLen(const char *seqA, const char *seqB)
{
    int a = strlen(seqA);
    int b = strlen(seqB);

    return a > b ? a : b;
}
