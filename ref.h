#ifndef REF_H
#define REF_H

typedef struct RefCounted ref_counted_t;
typedef void (*ref_free_f_t)(void *);

struct RefCounted {
  unsigned int count;
  ref_free_f_t free_f;
};

void ref_counted_init(ref_counted_t *ref_counted, ref_free_f_t free_f);
void ref_counted_inc(ref_counted_t *ref_counted);
void ref_counted_dec(void **obj_vp, ref_counted_t *ref_counted);

#endif
