#include "zend.h"
#include "zend_globals.h"
#include "zend_variables.h"
#include "zend_API.h"
#include "zend_objects.h"
#include "zend_objects_API.h"
#include "zend_object_handlers.h"
#include "zend_hash.h"
#include "zend_enum.h"


#define Z_ENUM_P(o)	zend_enum_fetch_object(Z_OBJ_P(o))


struct _zend_enum {
	zend_long ordinal;
	zend_string *name;
	zend_object std;
};


zend_enum *zend_enum_fetch_object(const zend_object *obj)
{
	return (zend_enum*)((char*)(obj) - XtOffsetOf(zend_enum, std));
}
/* }}} */


void zend_enum_init(zend_enum *e, int ordinal, zend_string *name) /* {{{ */
{
	e->ordinal = ordinal;
	e->name = zend_string_copy(name);
}
/* }}} */


zend_object *_enum_clone(zval *object) /* {{{ */
{
	Z_ADDREF_P(object);
	return Z_OBJ_P(object);
}
/* }}} */


zval *_enum_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv) /* {{{ */
{
	return std_object_handlers.read_property(object, member, type, cache_slot, rv);
}
/* }}} */


void _enum_write_property(zval *object, zval *member, zval *value, void **cache_slot) /* {{{ */
{
	zend_class_entry *ce = Z_OBJCE_P(object);
	zend_error(E_EXCEPTION | E_ERROR, "Enums cannot have dynamic properties", ce->name->val);
}
/* }}} */


zval *_enum_read_dimension(zval *object, zval *offset, int type, zval *rv) /* {{{ */
{
	zend_error(E_EXCEPTION | E_ERROR, "Cannot use enum %s as array", Z_OBJCE_P(object)->name->val);
	return &EG(uninitialized_zval);
}
/* }}} */


void _enum_write_dimension(zval *object, zval *offset, zval *value) /* {{{ */
{
	zend_class_entry *ce = Z_OBJCE_P(object);
	zend_error(E_EXCEPTION | E_ERROR, "Cannot use enum %s as array", ce->name->val);
}
/* }}} */


zval *_enum_get_property_ptr_ptr(zval *object, zval *member, int type, void **cache_slot) /* {{{ */
{
	zend_error(E_EXCEPTION | E_ERROR, "Cannot refer to enum properties by reference");
	return &EG(uninitialized_zval);
}
/* }}} */


int _enum_has_property(zval *object, zval *member, int has_set_exists, void **cache_slot) /** {{{ */
{
	return 0;
}
/* }}} */


void _enum_unset_property(zval *object, zval *member, void **cache_slot) /** {{{ */
{
	zend_error(E_EXCEPTION | E_ERROR, "Cannot unset enum properties");
}
/* }}} */


int _enum_has_dimension(zval *object, zval *offset, int check_empty) /* {{{ */
{
	return 0;
}
/* }}} */


void _enum_unset_dimension(zval *object, zval *offset) /** {{{ */
{
	zend_class_entry *ce = Z_OBJCE_P(object);
	zend_error(E_EXCEPTION | E_ERROR, "Cannot use enum %s as array", ce->name->val);
}
/* }}} */


HashTable *_enum_get_properties(zval *object) /** {{{ */
{
	return Z_OBJ_P(object)->properties;
}
/* }}} */


static union _zend_function *_enum_get_method(zend_object **obj_ptr, zend_string *method_name, const zval *key) /* {{{ */
{
	return std_object_handlers.get_method(obj_ptr, method_name, key);
}
/* }}} */


union _zend_function *_enum_get_constructor(zend_object *zobj) /** {{{ */
{
	zend_error(E_EXCEPTION | E_ERROR, "Enum constructors cannot be called");
	return NULL;
}
/* }}} */


zend_string *_enum_get_class_name(const zend_object *zobj) /** {{{ */
{
	return zend_string_copy(zobj->ce->name);
}
/* }}} */


int _enum_compare_objects(zval *o1, zval *o2) /** {{{ */
{
	if (Z_OBJCE_P(o1) != Z_OBJCE_P(o2)) {
		return 1;
	}

	return Z_ENUM_P(o1)->ordinal == Z_ENUM_P(o2)->ordinal ? 0 : 1;
}
/* }}} */


ZEND_RESULT_CODE _enum_compare(zval *result, zval *zv1, zval *zv2) /* {{{ */
{
	int cmp;
	if (Z_TYPE_P(zv1) == Z_TYPE_P(zv2) && Z_TYPE_P(zv1) == IS_OBJECT) {
		cmp = _enum_compare_objects(zv1, zv2);
		ZVAL_LONG(result, cmp);
		return cmp ? FAILURE : SUCCESS;
	} else {
		ZVAL_LONG(result, 1);
		return FAILURE;
	}
}
/* }}} */


int _enum_cast_object(zval *readobj, zval *writeobj, int type) /** {{{ */
{
	ZEND_ASSERT(Z_TYPE_P(readobj) == IS_OBJECT);
	switch (type) {
		case _IS_BOOL:
			ZVAL_BOOL(writeobj, 1);
			break;
		default:
			return FAILURE;
	}
	return SUCCESS;
}
/* }}} */


HashTable *_enum_get_debug_info(zval *object, int *is_temp) /** {{{ */
{
	zend_enum *enum_obj = Z_ENUM_P(object);
	zval ordinal_zv, name_zv;
	HashTable *ht;
	ALLOC_HASHTABLE(ht);
	zend_hash_init(ht, 2, NULL, ZVAL_PTR_DTOR, 0);

	ZVAL_LONG(&ordinal_zv, enum_obj->ordinal);
	ZVAL_STR_COPY(&name_zv, enum_obj->name);

	zend_hash_str_add(ht, "ordinal", strlen("ordinal"), &ordinal_zv);
	zend_hash_str_add(ht, "name", strlen("name"), &name_zv);

	*is_temp = 1;
	return ht;
}
/* }}} */


static void _enum_free(zend_object *object) /* {{{ */
{
	zend_enum *obj = zend_enum_fetch_object(object);
	zend_string_release(obj->name);
	obj->name = NULL;
}
/* }}} */


static void _enum_dtor(zend_object *object) /* {{{ */
{
}
/* }}} */


const zend_object_handlers zend_enum_object_handlers = {
	XtOffsetOf(zend_enum, std),		/* offset */

	_enum_free,						/* free_obj */
	_enum_dtor,						/* dtor_obj */
	_enum_clone,					/* clone_obj */

	_enum_read_property,			/* read_property */
	_enum_write_property,			/* write_property */
	_enum_read_dimension,			/* read_dimension */
	_enum_write_dimension,			/* write_dimension */
	_enum_get_property_ptr_ptr,		/* get_property_ptr_ptr */
	NULL,							/* get */
	NULL,							/* set */
	_enum_has_property,				/* has_property */
	_enum_unset_property,			/* unset_property */
	_enum_has_dimension,			/* has_dimension */
	_enum_unset_dimension,			/* unset_dimension */
	_enum_get_properties,			/* get_properties */
	_enum_get_method,				/* get_method */
	NULL,							/* call_method */
	_enum_get_constructor,			/* get_constructor */
	_enum_get_class_name,			/* get_class_name */
	_enum_compare_objects,			/* compare_objects */
	_enum_cast_object,				/* cast_object */
	NULL,							/* count_elements */
	_enum_get_debug_info,			/* get_debug_info */
	NULL,							/* get_closure */
	NULL,							/* get_gc */
	NULL,							/* do_operation */
	_enum_compare,					/* compare */
};


zend_object *zend_enum_new(zend_class_entry *ce) /* {{{ */
{
	zend_enum *enum_object = (zend_enum*) emalloc(sizeof(zend_enum));
	zend_object_std_init(&enum_object->std, ce);
	enum_object->std.handlers = &zend_enum_object_handlers;
	return &enum_object->std;
}
/* }}} */


ZEND_NAMED_FUNCTION(_enum_ordinal) /* {{{ */
{
	zval *obj_zv;

	ZEND_PARSE_PARAMETERS_START(0, 0)
	ZEND_PARSE_PARAMETERS_END();

	obj_zv = getThis();

	RETURN_LONG(Z_ENUM_P(obj_zv)->ordinal);
}
/* }}} */


ZEND_NAMED_FUNCTION(_enum_name) /* {{{ */
{
	zval *obj_zv;

	ZEND_PARSE_PARAMETERS_START(0, 0)
	ZEND_PARSE_PARAMETERS_END();

	obj_zv = getThis();

	RETURN_STR_COPY(Z_ENUM_P(obj_zv)->name);
}
/* }}} */


ZEND_NAMED_FUNCTION(_enum_values) /* {{{ */
{
	zval *entry;
	zend_class_entry *ce;

	ZEND_PARSE_PARAMETERS_START(0, 0)
	ZEND_PARSE_PARAMETERS_END();

	ce = EG(current_execute_data)->called_scope;

	array_init_size(return_value, zend_hash_num_elements(&ce->constants_table));
	zend_hash_real_init(Z_ARRVAL_P(return_value), 1);

	ZEND_HASH_FILL_PACKED(Z_ARRVAL_P(return_value)) {
		ZEND_HASH_FOREACH_VAL(&ce->constants_table, entry) {
			Z_ADDREF_P(entry);
			ZEND_HASH_FILL_ADD(entry);
		} ZEND_HASH_FOREACH_END();
	} ZEND_HASH_FILL_END();
}
/* }}} */


ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_name, IS_STRING, NULL, 0)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_ordinal, IS_LONG, NULL, 0)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_values, IS_ARRAY, NULL, 0)
ZEND_END_ARG_INFO()


const zend_internal_function _internal_function_values = {
	ZEND_INTERNAL_FUNCTION,
	ZEND_ACC_STATIC | ZEND_ACC_PUBLIC,
	NULL,		/* function_name */
	NULL,		/* scope */
	NULL,		/* prototype */
	0,		/* num_args */
	0,		/* required_num_args */
	NULL,		/* arg_info */
	&_enum_values,	/* handler */
	NULL,		/* module */
};


const zend_internal_function _internal_function_ordinal = {
	ZEND_INTERNAL_FUNCTION,
	ZEND_ACC_PUBLIC,
	NULL,		/* function_name */
	NULL,		/* scope */
	NULL,		/* prototype */
	0,		/* num_args */
	0,		/* required_num_args */
	NULL,		/* arg_info */
	&_enum_ordinal,	/* handler */
	NULL,		/* module */
};


const zend_internal_function _internal_function_name = {
	ZEND_INTERNAL_FUNCTION,
	ZEND_ACC_PUBLIC,
	NULL,		/* function_name */
	NULL,		/* scope */
	NULL,		/* prototype */
	0,		/* num_args */
	0,		/* required_num_args */
	NULL,		/* arg_info */
	&_enum_name,	/* handler */
	NULL,		/* module */
};


static void _enum_copy_arg_info(zend_internal_arg_info *to, const zend_internal_arg_info *from, const char *class_name)
{
	memcpy(to, from, sizeof(zend_internal_arg_info));
	to->class_name = class_name;
}


static void _enum_inherit_function(zend_function *to, const zend_internal_function *from, zend_class_entry *ce, const char *name_cstr) /* {{{ */
{
	zend_string *name = zend_string_init(name_cstr, strlen(name_cstr), 0);
	zend_string *key = zend_string_tolower(name);
	memcpy(to, from, sizeof(zend_internal_function));
	to->common.fn_flags |= ZEND_ACC_ARENA_ALLOCATED;
	to->common.function_name = name;
	to->common.scope = ce;
	zend_hash_add_new_ptr(&ce->function_table, key, to);
	zend_string_release(key);
}
/* }}} */


void zend_enum_inherit_methods(zend_class_entry *ce) /* {{{ */
{
	zend_function *storage = zend_arena_alloc(&CG(arena), sizeof(zend_function[3]));
	zend_internal_arg_info *arg_infos = zend_arena_alloc(&CG(arena), sizeof(zend_internal_arg_info[3]));
	const char *class_name = ce->name->val;
	int i;

	_enum_inherit_function(&storage[0], &_internal_function_name, ce, "name");
	_enum_inherit_function(&storage[1], &_internal_function_ordinal, ce, "ordinal");
	_enum_inherit_function(&storage[2], &_internal_function_values, ce, "values" );

	_enum_copy_arg_info(&arg_infos[0], arginfo_name, class_name);
	_enum_copy_arg_info(&arg_infos[1], arginfo_ordinal, class_name);
	_enum_copy_arg_info(&arg_infos[2], arginfo_values, class_name);

	for (i = 0; i < 3; ++i) {
		storage[i].internal_function.arg_info = &arg_infos[i];
	}
}
/* }}} */


