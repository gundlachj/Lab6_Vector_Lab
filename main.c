/**
 * @file main.c
 * @brief Vector Math program to perfom vector operations (addition, dot
 *        product, etc.) on in-memory vectors.
 * @author Jacob Gundlach
 * @date 10/10/2026
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vect.h"

int main(int argc, char **argv) {
  const int LEN_INPUT = 50;
  char input[LEN_INPUT];
  const int NUM_MAX_TOKENS = 5;
  char *tokens[NUM_MAX_TOKENS];

  // TODO: implement the -h flag
  if (argc == 2 && !strcmp(argv[1], "-h")) {
    printf("MATHLAB: A vector calculator program that can store and perform "
           "operations on %d dimensional vectors.\n",
           NUM_COMPONENTS);

    printf("-------------------------------------------------------------------"
           "---------------------------------\n");

    printf("Make new vectors with the = operator.\n");
    printf("\tExample: a = 1 2 3\n");
    printf("\tExample: b = 2 2\n");
    printf("Vectors can be assigned to other vectors.\n");
    printf("\tExample: c = a\n");
    printf("Addition, subtraction, scalar multiplication, dot product, and "
           "cross product can be calculated.\n");
    printf("\tExample: a + b (addition)\n");
    printf("\tExample: a - b (subtraction)\n");
    printf("\tExample: a * 4 (scalar multiplication)\n");
    printf("\tExample: a * b (dot product)\n");
    printf("\tExample: a x b (cross product)\n");
    printf("Operations can be performed and then assigned to a new vector.\n");
    printf("\tExample: c = a x b\n");

    printf("\n");
    exit(EXIT_SUCCESS);
  }

  while (1) {
    printf("mathlab> ");

    fgets(input, LEN_INPUT, stdin);

    tokens[0] = strtok(input, " \n=");
    if (strlen(tokens[0]) >= LEN_IDENT) {
      printf("Identifier is too long.\n");
    }

    int num_tokens = NUM_MAX_TOKENS;
    for (int i = 1; i < NUM_MAX_TOKENS; i++) {
      tokens[i] = strtok(NULL, " \n,");
      if (tokens[i] == NULL) {
        num_tokens = i;
        break;
      }
    }
    if (strtok(NULL, " ,") != NULL) {
      printf("Incorrect input.\n");
      continue;
    }

    switch (num_tokens) {
    case 1:
      if (!strcmp(tokens[0], "quit") || !strcmp(tokens[0], "exit")) {
        exit(EXIT_SUCCESS);
      } else if (!strcmp(tokens[0], "list")) {
        print_vects();
        continue;
      } else if (!strcmp(tokens[0], "clear")) {
        clear_vects();
        printf("Cleared vector list.\n");
        continue;
      } else {
        vect_t *vect = find_vect(tokens[0]);
        if (vect == NULL) {
          printf("Invalid identifier.\n");
        } else {
          print_vect(*vect);
        }
        continue;
      }

      break;
    case 3:
      if (strtof(tokens[2], NULL) != 0) {
        vect_t new_vect = {0};
        strcpy(new_vect.ident, tokens[0]);
        new_vect.comp[0] = strtof(tokens[2], NULL);
        add_vect(new_vect);
        print_vect(new_vect);

      } else if (tokens[1][0] == '=') {
        switch (assign_vect(tokens[0], tokens[2])) {
        case -1:
          printf("Vector storage full! Unable to create new vector. Clear the "
                 "vector storage before creating new vectors.\n");

          break;
        case -2:
          printf("The vector '%s' is not in the vector storage. Create it "
                 "first before assigning something to it.\n",
                 tokens[2]);

          break;
        }
      } else {
        switch (tokens[1][0]) {
        case '+':
          print_vect(add(tokens[0], tokens[2]));
          break;
        case '-':
          print_vect(subtract(tokens[0], tokens[2]));
          break;
        case '*':
          double a_float = strtof(tokens[0], NULL);
          double b_float = strtof(tokens[2], NULL);

          if (a_float == 0 && b_float == 0) {
            double result = dot(tokens[0], tokens[2]);
            printf("%-5s=>\t%f\n", "ans", result);

          } else if (a_float != 0 && b_float != 0) {
            printf("%-5s=>\t%f\n", "ans", a_float * b_float);

          } else if (a_float != 0) {
            vect_t result = multiply(tokens[2], a_float);
            printf("%-5s=>", "ans");
            for (int i = 0; i < NUM_COMPONENTS; i++) {
              printf("\t%f", result.comp[i]);
            }
            printf("\n");

          } else if (b_float != 0) {
            vect_t result = multiply(tokens[0], a_float);
            printf("%-5s=>", "ans");
            for (int i = 0; i < NUM_COMPONENTS; i++) {
              printf("\t%f", result.comp[i]);
            }
            printf("\n");
          }

          break;
        case 'x':
          print_vect(cross(tokens[0], tokens[0]));
          break;
        }
      }

      continue;
    case 4:
      if (strtof(tokens[2], NULL) != 0 && strtof(tokens[3], NULL) != 0) {
        vect_t new_vect = {0};
        strcpy(new_vect.ident, tokens[0]);
        new_vect.comp[0] = strtof(tokens[2], NULL);
        new_vect.comp[1] = strtof(tokens[3], NULL);
        add_vect(new_vect);
        print_vect(new_vect);
        continue;
      }

      break;
    case 5:
      if (tokens[1][0] == '=' && !isdigit(tokens[3][0])) {
        vect_t result = {0};
        switch (tokens[3][0]) {
        case '+':
          printf("adding %s and %s\n", tokens[2], tokens[4]);
          result = add(tokens[2], tokens[4]);
          strcpy(result.ident, tokens[0]);
          add_vect(result);
          print_vect(result);
          break;
        case '-':
          result = subtract(tokens[2], tokens[4]);
          strcpy(result.ident, tokens[0]);
          add_vect(result);
          print_vect(result);
          break;
        case '*':
          double a_float = strtof(tokens[2], NULL);
          double b_float = strtof(tokens[4], NULL);

          if (a_float != 0) {
            result = multiply(tokens[2], b_float);
            strcpy(result.ident, tokens[0]);
            add_vect(result);
            print_vect(result);
          } else if (b_float != 0) {
            result = multiply(tokens[2], a_float);
            strcpy(result.ident, tokens[0]);
            add_vect(result);
            print_vect(result);
          } else {
            printf("Cannot assign a scalar to a vector.\n");
          }

          break;
        case 'x':
          result = cross(tokens[2], tokens[4]);
          strcpy(result.ident, tokens[0]);
          add_vect(result);
          print_vect(result);
          break;
        }
      } else if (tokens[1][0] == '=') {
        if (make_vect(tokens) == -1) {
          printf("Vector storage full! Unable to create new vector. Clear the "
                 "vector storage before creating new vectors.\n");
        }
        continue;
      }
    default:
      break;
    }
    printf("Incorrect input.\n");
  }
}
