#include<stdio.h>
#include<stdlib.h>
#include "nw.h"

// const char * sa = "AATCFG";
// const char * sb = "AXACG";

// const char * sa = "WHAT";
// const char * sb = "WHY";

const char *sa = "AQSVPWGISRVQAPAAHNRGLTGSGVKVAVLDTGISTHPDLNIRGGASFVPGEPSTQDGNGHGTHVAGTIAALNNSIGVLGVAPSAELYAVKVLGASGSGSVSSIAQGLEWAGNNGMHVA"
    "NLSLGSPSPSATLEQAVNSATSRGVLVVAASGNSGAGSISYPARYANAMAVGATDQNNNRASFSQYGAGLDIVAPGVNVQSTYPGSTYASLNGTSMATPHVAGAAALVKQKNPSWSNVQIRNHLKNTATSLGS"
    "TNLYGSGLVNAEAATR";
const char *sb = "MRQSLKVMVLSTVALLFMANPAAASEEKKEYLIVVEPEEVSAQSVEESYDVDVIHEFEEIPVIHAELTKKELKKLKKDPNVKAIEKNAEVTISQTVPWGISFINTQQAHNRGIFGNGARV"
    "AVLDTGIASHPDLRIAGGASFISSEPSYHDNNGHGTHVAGTIAALNNSIGVLGVAPSADLYAVKVLDRNGSGSLASVAQGIEWAINNNMHIINMSLGSTSGSSTLELAVNRANNAGILLVGAAGNTGRQGVNY"
    "PARYSGVMAVAAVDQNGQRASFSTYGPEIEISAPGVNVNSTYTGNRYVSLSGTSMATPHVAGVAALVKSRYPSYTNNQIRQRINQTATYLGSPSLYGNGLVHAGRATQ";

const int match = 2;
const int mismatch = -2;
const int gap = -4;

int main(void)
{
    nwMatrix *matrix = nwGenerateMatrix(sa, sb, match, mismatch, gap);

    nwFillMatrix(matrix, sa, sb, match, mismatch, gap);
    nwPrintMatrix(matrix, sa, sb);

    int newSeqSize = nwGetMaxSeqLen(sa, sb) + 1;
    char *newSeqA = (char *)malloc(newSeqSize * sizeof(char));
    char *newSeqB = (char *)malloc(newSeqSize * sizeof(char));
    char *seqDiff = (char *)malloc(newSeqSize * sizeof(char));

    newSeqA[newSeqSize] = 0;
    newSeqB[newSeqSize] = 0;
    seqDiff[newSeqSize] = 0;

    nwSeqTrackback(matrix, sa, sb, newSeqA, newSeqB, seqDiff);

    printf("%s\n%s\n%s\n", newSeqA, seqDiff, newSeqB);

    free(newSeqA);
    free(newSeqB);
    free(seqDiff);
    nwFreeMatrix(matrix);

    return 0;
}
