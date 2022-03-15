#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
    struct nw_matrix *matrix = nw_create_matrix(sa, sb, match, mismatch, gap);

    nw_fill_matrix(matrix, sa, sb, match, mismatch, gap);
    nw_print_matrix(matrix, sa, sb);

    int len_a = strlen(sa);
    int len_b = strlen(sb);
    int len_new = len_a > len_b ? len_a : len_b;

    char *new_a = (char *) malloc(len_new * sizeof(char));
    char *new_b = (char *) malloc(len_new * sizeof(char));
    char *sdiff = (char *) malloc(len_new * sizeof(char));

    new_a[len_new] = 0;
    new_b[len_new] = 0;
    sdiff[len_new] = 0;

    nw_trackback_matrix(matrix, sa, sb, new_a, new_b, sdiff);

    printf("%s\n%s\n%s\n", new_a, sdiff, new_b);

    free(new_a);
    free(new_b);
    free(sdiff);
    nw_freematrix(matrix);

    return 0;
}
