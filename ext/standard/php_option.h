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

#ifndef PHP_OPTION_H
#define PHP_OPTION_H

extern zend_class_entry *ce_Option, *ce_OptionIterator;

PHP_MINIT_FUNCTION(option);
PHP_MSHUTDOWN_FUNCTION(option);

#endif /* PHP_OPTION_H */
