#ifndef ZEND_ENUM_H
#define ZEND_ENUM_H

typedef struct _zend_enum zend_enum;

zend_object *zend_enum_new(zend_class_entry *ce);
void zend_enum_init(zend_enum *e, int ordinal, zend_string *name);
zend_enum *zend_enum_fetch_object(const zend_object*);

void zend_enum_inherit_methods(zend_class_entry *ce);

#endif
