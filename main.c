#include "ref.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct suii {
  ref_counted_t ref_counted;
  char *name;
} suii_t;

static void suii_free(void *obj) {
  printf("-- Suii free object...\n");
  suii_t *suii = (suii_t *)obj;
  free(suii->name);
  free(suii);
}

static char *string_duplicate(const char *str) {
  size_t len = strlen(str) + 1;
  char *cp = malloc(len);

  if (cp == NULL) {
    return NULL;
  }

  memcpy(cp, str, len);
  return cp;
}

suii_t *suii_new(const char *name) {
  printf("-> Creating suii_t object...\n");
  suii_t *suii = malloc(sizeof(*suii));

  if (suii == NULL) {
    return NULL;
  }
  // suii->name = strdup(name);
  // This will work if we compile our c program <17 version, because strdup is
  // not c compatible
  // therefore we'll define our own function that copies the string to the
  // buffer;
  suii->name = string_duplicate(name);
  if (suii->name == NULL) {
    free(suii);
    return NULL;
  }

  ref_counted_init(&suii->ref_counted, suii_free);
  return suii;
}

int main(void) {
  suii_t *suii = suii_new("Bade bhaiya");

  if (suii == NULL) {
    fprintf(stderr, "Failed to create suiit_t object.\n");
    return EXIT_FAILURE;
  }
  printf("Reference count: %u\n\n", suii->ref_counted.count);

  ref_counted_inc(&suii->ref_counted);

  printf("Reference count: %u\n\n", suii->ref_counted.count);

  ref_counted_dec((void **)&suii, &suii->ref_counted);

  printf("Reference count after first dec: ");

  if (suii != NULL) {
    printf("%u\n\n", suii->ref_counted.count);
  } else {
    printf("object freed\n\n");
  }

  ref_counted_dec((void **)&suii, &suii->ref_counted);

  printf("Object pointer after final dec: %p\n", (void *)suii);

  return EXIT_SUCCESS;
}
