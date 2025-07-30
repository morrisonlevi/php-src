/*
   +----------------------------------------------------------------------+
   | Copyright (c) The PHP Group                                          |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | https://www.php.net/license/3_01.txt                                 |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Levi Morrison <levim@php.net>                               |
   +----------------------------------------------------------------------+
*/

#include <php.h>
#include <zend_interfaces.h>

#include "option_arginfo.h"

zend_class_entry *ce_Option = NULL, *ce_OptionIterator = NULL;

static zend_object *zend_option_new_copy(zval *val)
{
	ZEND_ASSERT(val != NULL);
        zend_object *object = zend_objects_new(ce_Option);
	object_properties_init(object, ce_Option);
	zval *prop = OBJ_PROP_NUM(object, 0);
	ZVAL_COPY(prop, val);
	return object;
}

static zend_object *zend_option_new_move(zval *val)
{
	ZEND_ASSERT(val != NULL);
        zend_object *object = zend_objects_new(ce_Option);
	object_properties_init(object, ce_Option);
	zval *prop = OBJ_PROP_NUM(object, 0);
	ZVAL_COPY_VALUE(prop, val);
	return object;
}

static zend_object *zend_option_none(void)
{
        zend_object *object = zend_objects_new(ce_Option);
	object_properties_init(object, ce_Option);
	return object;
}

static zend_object *zend_option_some(zval *val)
{
	ZEND_ASSERT(val != NULL);
	ZEND_ASSERT(Z_TYPE_P(val) != IS_UNDEF);

	return zend_option_new_copy(val);
}

/**
 * Transfers the value from the option to the return value. If there isn't a
 * value, *rv will be IS_UNDEF. After this operation, option is a None.
 *
 * * `option` must be non-null and be an Option.
 * * `rv` must be non-null and must not need dtor'd before being written to.
 */
static void zend_option_take(zend_object *option, zval *rv)
{
	ZEND_ASSERT(option != NULL);
	ZEND_ASSERT(option->ce == ce_Option);
	ZEND_ASSERT(rv != NULL);

	zval *prop = OBJ_PROP_NUM(option, 0);

	/* Transfer ownership without fussing with refcounts. */
	// todo: is this the correct way to do this?
	ZVAL_COPY_VALUE(rv, prop);
	ZVAL_UNDEF(prop);
}

/**
 * If there is a value, copies it to `rv` and returns SUCCESS; if not, sets the
 * `rv` to IS_UNDEF and returns FAILURE.
 *
 * * `option` must be non-null and be an Option.
 * * `rv` must be non-null and must not need dtor'd before being written to.
 */
static zend_result zend_option_unwrap(zend_object *option, zval **rv)
{
	ZEND_ASSERT(option != NULL);
	ZEND_ASSERT(option->ce == ce_Option);
	ZEND_ASSERT(rv != NULL);

	zval undef;
	ZVAL_UNDEF(&undef);
	zval *prop = OBJ_PROP_NUM(option, 0);

	bool is_some = Z_TYPE_P(prop) != IS_UNDEF;
        ZVAL_COPY(*rv, is_some ? prop : &undef);
	return is_some ? SUCCESS : FAILURE;
}

static bool zend_option_is_some(zend_object *option)
{
	ZEND_ASSERT(option != NULL);
	ZEND_ASSERT(option->ce == ce_Option);

	zval *prop = OBJ_PROP_NUM(option, 0);
	return Z_TYPE_P(prop) != IS_UNDEF;
}

static void zend_optioniter_construct(zend_object *iter, zend_object *option)
{
	ZEND_ASSERT(iter != NULL);
	ZEND_ASSERT(iter->ce == ce_OptionIterator);
	ZEND_ASSERT(option != NULL);
	ZEND_ASSERT(option->ce == ce_Option);

	ZVAL_BOOL(OBJ_PROP_NUM(iter, 0), true);
	ZVAL_COPY(OBJ_PROP_NUM(iter, 1), OBJ_PROP_NUM(option, 0));
}

static zend_object *zend_option_get_iterator(zend_object *option)
{
	ZEND_ASSERT(option != NULL);
	ZEND_ASSERT(option->ce == ce_Option);

        zend_object *iter = zend_objects_new(ce_OptionIterator);
	object_properties_init(iter, ce_OptionIterator);

	zend_optioniter_construct(iter, option);

	return iter;
}

static zval *zend_optioniter_prop_rewound(zend_object *iter)
{
	ZEND_ASSERT(iter != NULL);
	ZEND_ASSERT(iter->ce == ce_OptionIterator);

	zval *prop = OBJ_PROP_NUM(iter, 0);
	ZEND_ASSERT(Z_TYPE_P(prop) == IS_TRUE || Z_TYPE_P(prop) == IS_FALSE);
	return prop;
}

static bool zend_optioniter_is_valid(zend_object *iter)
{
	zval *prop_rewound = zend_optioniter_prop_rewound(iter);
	return Z_TYPE_P(prop_rewound) == IS_TRUE && Z_TYPE_P(OBJ_PROP_NUM(iter, 1));
}

PHP_METHOD(Option, None)
{
	if (UNEXPECTED(zend_parse_parameters_none() != SUCCESS)) {
		return;
	}

	RETURN_OBJ(zend_option_none());
}

PHP_METHOD(Option, Some)
{
	zval *val;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(val)
	ZEND_PARSE_PARAMETERS_END();

	zend_object *object = zend_option_some(val);
	RETURN_OBJ(object);
}

PHP_METHOD(Option, is_none)
{
	if (UNEXPECTED(zend_parse_parameters_none() != SUCCESS)) {
		return;
	}

	zend_object *option = Z_OBJ_P(ZEND_THIS);
	bool is_some = zend_option_is_some(option);
	RETURN_BOOL(!is_some);
}

PHP_METHOD(Option, is_some)
{
	if (UNEXPECTED(zend_parse_parameters_none() != SUCCESS)) {
		return;
	}

	zend_object *option = Z_OBJ_P(ZEND_THIS);
	bool is_some = zend_option_is_some(option);
	RETURN_BOOL(is_some);
}

PHP_METHOD(Option, and)
{
	zend_object *B;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(B, ce_Option)
	ZEND_PARSE_PARAMETERS_END();

	zend_object *A = Z_OBJ_P(ZEND_THIS);
	zval *prop_a = OBJ_PROP_NUM(A, 1);

	RETURN_OBJ(Z_TYPE_P(prop_a) == IS_UNDEF ? A : B);
}

PHP_METHOD(Option, or)
{
	zend_object *B;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(B, ce_Option)
	ZEND_PARSE_PARAMETERS_END();

	zend_object *A = Z_OBJ_P(ZEND_THIS);
	zval *prop_a = OBJ_PROP_NUM(A, 1);

	RETURN_OBJ(Z_TYPE_P(prop_a) != IS_UNDEF ? A : B);
}

PHP_METHOD(Option, xor)
{
	zend_object *B;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(B, ce_Option)
	ZEND_PARSE_PARAMETERS_END();

	zend_object *A = Z_OBJ_P(ZEND_THIS);
	zval *prop_a = OBJ_PROP_NUM(A, 1);
	zval *prop_b = OBJ_PROP_NUM(B, 1);

	if (Z_TYPE_P(prop_a) == IS_UNDEF) {
		/* If A is None, then B can always be returned, because it
		 * doesn't matter if B is Some or None, either way it upholds
		 * the return conditions.
		 */
		RETURN_OBJ(B);
	} else {
		RETURN_OBJ(Z_TYPE_P(prop_b) == IS_UNDEF ? A : B);
	}
}

//PHP_METHOD(Option, map)
//{
//	zend_fcall_info fci = empty_fcall_info;
//	zend_fcall_info_cache fcc = empty_fcall_info_cache;
//
//	ZEND_PARSE_PARAMETERS_START(1, 1)
//		Z_PARAM_FUNC(fci, fcc)
//	ZEND_PARSE_PARAMETERS_END();
//
//	zend_object *option = Z_OBJ_P(ZEND_THIS);
//	if (zend_option_is_none(option)) {
//		RETURN_OBJ(zend_option_none());
//	}
//
//	zval *prop = OBJ_PROP_NUM(option, 1);
//
//	zval arg, rv;
//	// todo: why are the copies to temporaries needed?
//	ZVAL_COPY(&arg, prop);
//	ZVAL_UNDEF(&rv);
//
//	fci.retval = &rv;
//	fci.param_count = 1;
//	fci.params = &arg;
//
//	zend_result result = zend_call_function(&fci, &fci_cache);
//	zval_ptr_dtor(&arg);
//
//	if (UNEXPECTED(result != SUCCESS)) {
//		RETURN_NU
//	}
//
//	ZVAL_COPY_VALUE(return_value, &rv);
//	// todo: should return-by-reference even be allowed for this?
//	if (UNEXPECTED(Z_ISREF_P(return_value))) {
//		zend_unwrap_reference(return_value);
//	}
//}

PHP_METHOD(Option, replace)
{
	zval *val;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(val)
	ZEND_PARSE_PARAMETERS_END();

	zend_object *option = Z_OBJ_P(ZEND_THIS);

	zval prop;
	zend_option_take(option, &prop);

	// todo: can a value from ZPP be IS_UNDEF?
	ZVAL_COPY(OBJ_PROP_NUM(option, 0), val);
	RETURN_OBJ(zend_option_new_move(&prop));
}

PHP_METHOD(Option, take)
{
	if (UNEXPECTED(zend_parse_parameters_none() != SUCCESS)) {
		return;
	}

	zend_object *option = Z_OBJ_P(ZEND_THIS);
	zend_option_take(option, return_value);

	if (EXPECTED(Z_TYPE_P(return_value) != IS_UNDEF)) {
		return;
	}

	/* The retval shouldn't be IS_UNDEF, set to NULL before throwing. */
	RETVAL_NULL();
	// todo: throw specific error/exception?
	zend_value_error("take called on empty Option");
	RETURN_THROWS();
}

PHP_METHOD(Option, unwrap)
{
	if (UNEXPECTED(zend_parse_parameters_none() != SUCCESS)) {
		return;
	}

	zend_object *option = Z_OBJ_P(ZEND_THIS);
	if (UNEXPECTED(zend_option_unwrap(option, &return_value) != SUCCESS)) {
		// todo: throw specific error/exception?
		zend_value_error("unwrap called on empty Option");
		RETURN_THROWS();
	}
}

PHP_METHOD(Option, __construct)
{
	if (UNEXPECTED(zend_parse_parameters_none() != SUCCESS)) {
		return;
	}

	zend_error_noreturn(E_ERROR, "Option cannot be directly constructed");
}

PHP_METHOD(Option, getIterator)
{
	if (UNEXPECTED(zend_parse_parameters_none() != SUCCESS)) {
		return;
	}

	zend_object *option = Z_OBJ_P(ZEND_THIS);
	RETURN_OBJ(zend_option_get_iterator(option));
}

PHP_METHOD(OptionIterator, __construct)
{
	zend_object *option;
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(option, ce_Option)
	ZEND_PARSE_PARAMETERS_END();

	zend_object *iter = Z_OBJ_P(ZEND_THIS);
	zend_optioniter_construct(iter, option);
}

PHP_METHOD(OptionIterator, rewind)
{
	if (UNEXPECTED(zend_parse_parameters_none() != SUCCESS)) {
		return;
	}

	zend_object *iter = Z_OBJ_P(ZEND_THIS);
	ZVAL_BOOL(OBJ_PROP_NUM(iter, 0), true);
	RETURN_NULL();
}

PHP_METHOD(OptionIterator, valid)
{
	if (UNEXPECTED(zend_parse_parameters_none() != SUCCESS)) {
		return;
	}

	zend_object *iter = Z_OBJ_P(ZEND_THIS);
	RETURN_BOOL(zend_optioniter_is_valid(iter));
}

PHP_METHOD(OptionIterator, current)
{
	if (UNEXPECTED(zend_parse_parameters_none() != SUCCESS)) {
		return;
	}

	zend_object *iter = Z_OBJ_P(ZEND_THIS);
	if (EXPECTED(zend_optioniter_is_valid(iter))) {
		zval *prop = OBJ_PROP_NUM(iter, 1);
		RETURN_COPY(prop);
	}
	
	// todo: what error/exception to throw?
	zend_throw_error(NULL, "OptionIterator::current() called on invalid iterator");
	RETURN_THROWS();
}

PHP_METHOD(OptionIterator, key)
{
	if (UNEXPECTED(zend_parse_parameters_none() != SUCCESS)) {
		return;
	}

	zend_object *iter = Z_OBJ_P(ZEND_THIS);
	if (EXPECTED(zend_optioniter_is_valid(iter))) {
		RETURN_LONG(0);
	}
	
	// todo: what error/exception to throw?
	zend_throw_error(NULL, "OptionIterator::key() called on invalid iterator");
	RETURN_THROWS();
}

PHP_METHOD(OptionIterator, next)
{
	if (UNEXPECTED(zend_parse_parameters_none() != SUCCESS)) {
		return;
	}

	zend_object *iter = Z_OBJ_P(ZEND_THIS);
	zval *is_rewound = zend_optioniter_prop_rewound(iter);
	ZVAL_BOOL(is_rewound, false);
	RETURN_NULL();
}

PHP_MINIT_FUNCTION(option)
{
        ce_OptionIterator = register_class_OptionIterator(zend_ce_iterator);
        ce_Option = register_class_Option(zend_ce_aggregate);

	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(option)
{
	return SUCCESS;
}

