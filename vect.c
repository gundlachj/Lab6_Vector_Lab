/**
 * @file vect.c
 * @author Jacob Gundlach
 * @date 10/10/2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vect.h"

static vect_t vectors[NUM_VECTORS] = {0};
static int current_vect_idx = 0;

void add_vect(vect_t vect) {
  vect_t *found_vect = find_vect(vect.ident);
  if (found_vect == NULL) {
    strcpy(vectors[current_vect_idx].ident, vect.ident);
    for (int i = 0; i < NUM_COMPONENTS; i++) {
      vectors[current_vect_idx].comp[i] = vect.comp[i];
    }
    current_vect_idx++;
  } else {
    *found_vect = vect;
  }
}

int assign_vect(char *a_ident, char *b_ident) {
  vect_t *a_vect_ptr = find_vect(a_ident);
  vect_t new_vect = {0};
  if (a_vect_ptr != NULL) {
    new_vect = *a_vect_ptr;
    strcpy(new_vect.ident, "");
    current_vect_idx--;
  } else {
    if (current_vect_idx >= NUM_VECTORS) {
      return -1;
    }
  }

  vect_t *b_vect = find_vect(b_ident);
  if (b_vect == NULL) {
    return -2;
  }

  strncpy(new_vect.ident, a_ident, LEN_IDENT);
  for (int i = 0; i < NUM_COMPONENTS; i++) {
    new_vect.comp[i] = b_vect->comp[i];
  }

  vectors[current_vect_idx] = new_vect;
  current_vect_idx++;
  print_vect(new_vect);

  return 0;
}

int make_vect(char *tokens[]) {
  vect_t *vect_ptr = find_vect(tokens[0]);
  vect_t vect = {0};
  if (vect_ptr != NULL) {
    vect = *vect_ptr;
    strcpy(vect.ident, "");
    current_vect_idx--;
  } else {
    if (current_vect_idx >= NUM_VECTORS) {
      return -1;
    }
  }

  strncpy(vect.ident, tokens[0], LEN_IDENT);
  for (int i = 0; i < NUM_COMPONENTS; i++) {
    if (tokens[i + 2] == NULL) {
      vect.comp[i] = 0;
    } else {
      vect.comp[i] = strtof(tokens[i + 2], NULL);
    }
  }
  vectors[current_vect_idx] = vect;

  current_vect_idx++;
  print_vect(vect);

  return 0;
}

vect_t *find_vect(char *ident) {
  for (int i = 0; i < NUM_VECTORS; i++) {
    if (!strcmp(ident, vectors[i].ident)) {
      return &vectors[i];
    }
  }

  return NULL;
}

void print_vect(vect_t vect) {
  printf("%-5s=>\t", vect.ident);
  for (int j = 0; j < NUM_COMPONENTS; j++) {
    printf("%f\t", vect.comp[j]);
  }
  printf("\n");
}

void print_vects() {
  if (current_vect_idx == 0) {
    printf("Vector list empty.\n");
    return;
  }

  int highest_idx = current_vect_idx;
  if (current_vect_idx >= NUM_VECTORS) {
    highest_idx = NUM_VECTORS;
  }

  for (int i = 0; i < highest_idx; i++) {
    print_vect(vectors[i]);
  }
  printf("\n");
}

void clear_vects() {
  for (int i = 0; i < NUM_VECTORS; i++) {
    strcpy(vectors[i].ident, "");
    for (int k = 0; k < NUM_COMPONENTS; k++) {
      vectors[i].comp[k] = 0;
    }
  }
  current_vect_idx = 0;
}

vect_t add(char *a_ident, char *b_ident) {
  vect_t *a_vect = find_vect(a_ident);
  vect_t *b_vect = find_vect(b_ident);

  vect_t result = {0};
  strcpy(result.ident, "ans");
  for (int i = 0; i < NUM_COMPONENTS; i++) {
    result.comp[i] = a_vect->comp[i] + b_vect->comp[i];
  }

  return result;
}

vect_t subtract(char *a_ident, char *b_ident) {
  vect_t *a_vect = find_vect(a_ident);
  vect_t *b_vect = find_vect(b_ident);

  vect_t result = {0};
  strcpy(result.ident, "ans");
  for (int i = 0; i < NUM_COMPONENTS; i++) {
    result.comp[i] = a_vect->comp[i] - b_vect->comp[i];
  }

  return result;
}

vect_t multiply(char *vect_ident, int num) {
  vect_t *vect = find_vect(vect_ident);

  vect_t result = {0};
  strcpy(result.ident, "ans");
  for (int i = 0; i < NUM_COMPONENTS; i++) {
    result.comp[i] = vect->comp[i] * num;
  }

  return result;
}

double dot(char *a_ident, char *b_ident) {
  vect_t *a_vect = find_vect(a_ident);
  vect_t *b_vect = find_vect(b_ident);

  double result = 0;
  for (int i = 0; i < NUM_COMPONENTS; i++) {
    result += a_vect->comp[i] * b_vect->comp[i];
  }

  return result;
}

vect_t cross(char *a_ident, char *b_ident) {
  vect_t *a_vect = find_vect(a_ident);
  vect_t *b_vect = find_vect(b_ident);

  vect_t result = {0};
  strcpy(result.ident, "ans");
  for (int i = 0; i < NUM_COMPONENTS; i++) {
    result.comp[i] = a_vect->comp[(i + 1) % NUM_COMPONENTS] *
                         b_vect->comp[(i + 2) % NUM_COMPONENTS] -
                     a_vect->comp[(i + 2) % NUM_COMPONENTS] *
                         b_vect->comp[(i + 1) % NUM_COMPONENTS];
  }

  return result;
}
