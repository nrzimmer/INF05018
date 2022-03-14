typedef struct nwMatrix {
    int Rows;
    int Columns;
    int** Data;
    char** Origin;
} nwMatrix;

void nwRun(const char* seqA, const char* seqB, int match, int mismatch, int gap);
void nwPrintMatrix(nwMatrix* matrix, const char* seqA, const char* seqB);