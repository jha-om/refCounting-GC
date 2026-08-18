#include <assert.h>
#include <stdio.h>
#include "ref.h"

void ref_counted_init(ref_counted_t *ref_counted, ref_free_f_t free_f) {
  assert(ref_counted != NULL);
  assert(free_f != NULL);

  ref_counted->count = 1;
  ref_counted->free_f = free_f;
}

void ref_counted_inc(ref_counted_t *ref_counted) {
  assert(ref_counted != NULL);
  assert(ref_counted->count > 0);

  ref_counted->count++;
}

void ref_counted_dec(void **obj_vp, ref_counted_t *ref_counted) {
  assert(obj_vp != NULL);
  assert(*obj_vp != NULL);
  assert(ref_counted != NULL);
  assert(ref_counted->count > 0);

  ref_counted->count--;

  if (ref_counted->count == 0) {
    void *to_free = *obj_vp;
    *obj_vp = NULL;
    ref_counted->free_f(to_free);
  }
}
