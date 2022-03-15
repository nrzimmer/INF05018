#ifndef __NW_H__
#define __NW_H__

typedef struct __nw_matrix nw_matrix;

nw_matrix *nw_allocmatrix(const int rows, const int columns);
void nw_freematrix(nw_matrix * matrix);

nw_matrix *nw_create_matrix(const char *sa, const char *sb, int match, int mismatch, int gap);
void nw_fill_matrix(nw_matrix * matrix, const char *sa, const char *sb, int match, int mismatch, int gap);

int *nw_trackback_matrix(nw_matrix * matrix, const char *sa, const char *sb, char *new_a, char *new_b, char *sdiff);

void nw_print_matrix(nw_matrix * matrix, const char *sa, const char *sb);
void nw_print_matrix_row(nw_matrix * matrix, int row, const char *sa);

void nw_print_path(int *path, int new_len);
int nw_get_identity(char *sdiff, int new_len);

#endif
