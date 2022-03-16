#ifndef __SW_H__
#define __SW_H__

typedef struct __sw_matrix sw_matrix;

sw_matrix *nw_allocmatrix(const int rows, const int columns);
void sw_freematrix(sw_matrix * matrix);

sw_matrix *sw_create_matrix(const char *sa, const char *sb, int match, int mismatch, int gap);
void sw_fill_matrix(sw_matrix * matrix, const char *sa, const char *sb, int match, int mismatch, int gap);

int *sw_trackback_matrix(sw_matrix * matrix, const char *sa, const char *sb, char **new_a, char **new_b, char **sdiff);

void sw_print_matrix(sw_matrix * matrix, const char *sa, const char *sb);
void sw_print_matrix_row(sw_matrix * matrix, int row, const char *sa);

void sw_print_path(int *path, int new_len);
int sw_get_identity(char *sdiff, int new_len);

#endif
