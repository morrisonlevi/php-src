/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 2aed21ef6d1f76bd72b9c3f7dac0bada6df3f7af */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Option___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Option_None, 0, 0, Option, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Option_Some, 0, 1, Option, 0)
	ZEND_ARG_TYPE_INFO(0, val, IS_MIXED, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Option_is_none, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Option_is_some arginfo_class_Option_is_none

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Option_and, 0, 1, Option, 0)
	ZEND_ARG_OBJ_INFO(0, that, Option, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Option_or arginfo_class_Option_and

#define arginfo_class_Option_xor arginfo_class_Option_and

#define arginfo_class_Option_replace arginfo_class_Option_Some

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Option_take, 0, 0, IS_MIXED, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Option_unwrap arginfo_class_Option_take

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Option_getIterator, 0, 0, OptionIterator, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_OptionIterator___construct, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, option, Option, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OptionIterator_rewind, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_OptionIterator_valid arginfo_class_Option_is_none

#define arginfo_class_OptionIterator_current arginfo_class_Option_take

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_OptionIterator_key, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_OptionIterator_next arginfo_class_OptionIterator_rewind

ZEND_METHOD(Option, __construct);
ZEND_METHOD(Option, None);
ZEND_METHOD(Option, Some);
ZEND_METHOD(Option, is_none);
ZEND_METHOD(Option, is_some);
ZEND_METHOD(Option, and);
ZEND_METHOD(Option, or);
ZEND_METHOD(Option, xor);
ZEND_METHOD(Option, replace);
ZEND_METHOD(Option, take);
ZEND_METHOD(Option, unwrap);
ZEND_METHOD(Option, getIterator);
ZEND_METHOD(OptionIterator, __construct);
ZEND_METHOD(OptionIterator, rewind);
ZEND_METHOD(OptionIterator, valid);
ZEND_METHOD(OptionIterator, current);
ZEND_METHOD(OptionIterator, key);
ZEND_METHOD(OptionIterator, next);

static const zend_function_entry class_Option_methods[] = {
	ZEND_ME(Option, __construct, arginfo_class_Option___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(Option, None, arginfo_class_Option_None, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Option, Some, arginfo_class_Option_Some, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Option, is_none, arginfo_class_Option_is_none, ZEND_ACC_PUBLIC)
	ZEND_ME(Option, is_some, arginfo_class_Option_is_some, ZEND_ACC_PUBLIC)
	ZEND_ME(Option, and, arginfo_class_Option_and, ZEND_ACC_PUBLIC)
	ZEND_ME(Option, or, arginfo_class_Option_or, ZEND_ACC_PUBLIC)
	ZEND_ME(Option, xor, arginfo_class_Option_xor, ZEND_ACC_PUBLIC)
	ZEND_ME(Option, replace, arginfo_class_Option_replace, ZEND_ACC_PUBLIC)
	ZEND_ME(Option, take, arginfo_class_Option_take, ZEND_ACC_PUBLIC)
	ZEND_ME(Option, unwrap, arginfo_class_Option_unwrap, ZEND_ACC_PUBLIC)
	ZEND_ME(Option, getIterator, arginfo_class_Option_getIterator, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static const zend_function_entry class_OptionIterator_methods[] = {
	ZEND_ME(OptionIterator, __construct, arginfo_class_OptionIterator___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(OptionIterator, rewind, arginfo_class_OptionIterator_rewind, ZEND_ACC_PUBLIC)
	ZEND_ME(OptionIterator, valid, arginfo_class_OptionIterator_valid, ZEND_ACC_PUBLIC)
	ZEND_ME(OptionIterator, current, arginfo_class_OptionIterator_current, ZEND_ACC_PUBLIC)
	ZEND_ME(OptionIterator, key, arginfo_class_OptionIterator_key, ZEND_ACC_PUBLIC)
	ZEND_ME(OptionIterator, next, arginfo_class_OptionIterator_next, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_Option(zend_class_entry *class_entry_IteratorAggregate)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "Option", class_Option_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	class_entry->ce_flags |= ZEND_ACC_FINAL;
	zend_class_implements(class_entry, 1, class_entry_IteratorAggregate);

	zval property_val_default_value;
	ZVAL_UNDEF(&property_val_default_value);
	zend_string *property_val_name = zend_string_init("val", sizeof("val") - 1, 1);
	zend_declare_typed_property(class_entry, property_val_name, &property_val_default_value, ZEND_ACC_PRIVATE, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ANY));
	zend_string_release(property_val_name);

	return class_entry;
}

static zend_class_entry *register_class_OptionIterator(zend_class_entry *class_entry_Iterator)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "OptionIterator", class_OptionIterator_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	class_entry->ce_flags |= ZEND_ACC_FINAL;
	zend_class_implements(class_entry, 1, class_entry_Iterator);

	zval property_is_rewound_default_value;
	ZVAL_UNDEF(&property_is_rewound_default_value);
	zend_string *property_is_rewound_name = zend_string_init("is_rewound", sizeof("is_rewound") - 1, 1);
	zend_declare_typed_property(class_entry, property_is_rewound_name, &property_is_rewound_default_value, ZEND_ACC_PRIVATE, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_BOOL));
	zend_string_release(property_is_rewound_name);

	zval property_val_default_value;
	ZVAL_UNDEF(&property_val_default_value);
	zend_string *property_val_name = zend_string_init("val", sizeof("val") - 1, 1);
	zend_declare_typed_property(class_entry, property_val_name, &property_val_default_value, ZEND_ACC_PRIVATE, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ANY));
	zend_string_release(property_val_name);

	return class_entry;
}
