#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <locale.h>
#include "smith-waterman/sw.h"

//#define DEBUG

const char *sa = "MLTAEDKKLIQQAWEKAASHQEEFGAEALTRMFTTYPQTKTYFPHFDLSPGSDQVRGHGKKVLGALGNAVKNVDNLSQAM"
    "AELSNLHAYNLRVDPVNFKLLSQCIQVVLAVHMGKDYTPEVHAAFDKFLSAVSAVLAEKYR";
const char *sb = "XSLTAKDKSVVKAFWGKISGKADVVGAEALGRMLTAYPQTKTYFSHWADLSPGSGPVKKHGGIIMGAIGKAVGLMDDLVG"
    "GMSALSDLHAFKLRVDPGNFKILSHNILVTLAIHFPSDFTPEVHIAVDKFLAAVSAALADKYR";

const int match = 1;
const int mismatch = -1;
const int gap = -2;

int main(void)
{
    setlocale(LC_ALL, "");
    sw_matrix *matrix = sw_create_matrix(sa, sb, match, mismatch, gap);

    sw_fill_matrix(matrix, sa, sb, match, mismatch, gap);
    sw_print_matrix(matrix, sa, sb);

    char *new_a;
    char *new_b;
    char *sdiff;

    int *path = sw_trackback_matrix(matrix, sa, sb, &new_a, &new_b, &sdiff);
    int new_len = strlen(sdiff);
    int identity = sw_get_identity(sdiff, new_len);
    float identity_percent = (identity * 100.0) / new_len;

    printf("Path: ");
    sw_print_path(path, new_len);

    printf("\n%s\n%s\n%s\n\nScore: %d\nIdentity: %d/%d (%.2f%%)\n", new_a, sdiff, new_b, path[0], identity, new_len, identity_percent);

    free(new_a);
    free(new_b);
    free(sdiff);
    free(path);
    sw_freematrix(matrix);

    return 0;
}
