#ifndef __NW_H__
#define __NW_H__

typedef struct nwMatrix {
    int Rows;
    int Columns;
    int **Data;
    char **Origin;
} nwMatrix;

nwMatrix *nwAllocMatrix(const int rows, const int columns);
void nwFreeMatrix(nwMatrix * matrix);

nwMatrix *nwGenerateMatrix(const char *seqA, const char *seqB, int match, int mismatch, int gap);
void nwFillMatrix(nwMatrix * matrix, const char *seqA, const char *seqB, int match, int mismatch, int gap);

void nwSeqTrackback(nwMatrix * matrix, const char *seqA, const char *seqB, char *newSeqA, char *newSeqB, char *seqDiff);

int nwGetMaxSeqLen(const char *seqA, const char *seqB);

void nwPrintMatrix(nwMatrix * matrix, const char *seqA, const char *seqB);
void nwPrintMatrixRow(nwMatrix * matrix, int row, const char *seqA);

#endif
