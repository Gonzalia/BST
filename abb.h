#ifndef _ABB_H
#define _ABB_H

#include <stdbool.h>

typedef struct _s_abb * abb;

typedef int abb_elem;

abb abb_empty(void);

abb abb_add(abb tree, abb_elem e);

bool abb_is_empty(abb tree);

bool abb_exists(abb tree, abb_elem e);

unsigned int abb_length(abb tree);

abb abb_remove(abb tree, abb_elem e);

abb_elem abb_root(abb tree);

abb_elem abb_max(abb tree);

abb_elem abb_min(abb tree);

void abb_dump(abb tree);

abb abb_destroy(abb tree);


#endif
