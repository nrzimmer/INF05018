#ifndef __NW_H__
#define __NW_H__

struct nw_matrix {
    int rows;
    int columns;
    int **data;
    char **origin;
};

struct nw_matrix *nw_allocmatrix(const int rows, const int columns);
void nw_freematrix(struct nw_matrix *matrix);

struct nw_matrix *nw_create_matrix(const char *sa, const char *sb, int match, int mismatch, int gap);
void nw_fill_matrix(struct nw_matrix *matrix, const char *sa, const char *sb, int match, int mismatch, int gap);

void nw_trackback_matrix(struct nw_matrix *matrix, const char *sa, const char *sb, char *new_a, char *new_b, char *sdiff);

void nw_print_matrix(struct nw_matrix *matrix, const char *sa, const char *sb);
void nw_print_matrix_row(struct nw_matrix *matrix, int row, const char *sa);

#endif
