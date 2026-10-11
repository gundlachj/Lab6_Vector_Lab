/**
 * @file vect.h
 * @author Jacob Gundlach
 * @date 10/10/2026
 */

#ifndef __VECT_H__
#define __VECT_H__

#define NUM_VECTORS 10
#define NUM_COMPONENTS 3
#define LEN_IDENT 10

typedef struct {
  char ident[LEN_IDENT];
  double comp[NUM_COMPONENTS];
} vect_t;

void add_vect(vect_t vect);
int assign_vect(char *a_ident, char *b_ident);
int make_vect(char *tokens[]);
vect_t *find_vect(char *token);
void print_vect(vect_t vect);
void print_vects();
void clear_vects();

vect_t add(char *a_ident, char *b_ident);
vect_t subtract(char *a_ident, char *b_ident);
vect_t multiply(char *vect_ident, int num);
double dot(char *a_ident, char *b_ident);
vect_t cross(char *a_ident, char *b_ident);

#endif
