
if (BISON_EXECUTABLE)
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/zend_ini_parser.c ${CMAKE_CURRENT_SOURCE_DIR}/zend_ini_parser.h
        COMMAND ${BISON_EXECUTABLE} -v -d zend_ini_parser.y -o zend_ini_parser.c
        DEPENDS zend_ini_parser.y
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        VERBATIM
    )

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/zend_language_parser.c ${CMAKE_CURRENT_SOURCE_DIR}/zend_language_parser.h
        COMMAND ${BISON_EXECUTABLE} -v -d zend_language_parser.y -o zend_language_parser.c
        DEPENDS zend_language_parser.y
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        VERBATIM
    )
endif (BISON_EXECUTABLE)

if (RE2C_EXECUTABLE)
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/zend_ini_scanner.c
        COMMAND ${RE2C_EXECUTABLE} --no-generation-date --case-inverted -cbdFt zend_ini_scanner_defs.h -o zend_ini_scanner.c zend_ini_scanner.l
        DEPENDS zend_ini_scanner.l zend_ini_scanner_defs.h
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        VERBATIM
    )

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/zend_language_scanner.c
        COMMAND ${RE2C_EXECUTABLE} --no-generation-date --case-inverted -cbdFt zend_language_scanner_defs.h -o zend_language_scanner.c zend_language_scanner.l
        DEPENDS zend_language_scanner.l zend_language_scanner_defs.h
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        VERBATIM
    )
endif (RE2C_EXECUTABLE)

add_library(Zend SHARED zend.c
    zend_alloc.c
    zend_API.c
    zend_ast.c
    zend_attributes.c
    zend_builtin_functions.c
    zend_closures.c
    zend_compile.c
    zend_constants.c
    zend_cpuinfo.c
    zend_default_classes.c
    zend_dtrace.c
    zend_exceptions.c
    zend_execute_API.c
    zend_execute.c
    zend_extensions.c
    zend_float.c
    zend_gc.c
    zend_gdb.c
    zend_generators.c
    zend_hash.c
    zend_highlight.c
    zend_inheritance.c
    zend_ini.c
    zend_ini_parser.c
    zend_ini_scanner.c
    zend_interfaces.c
    zend_iterators.c
    zend_language_parser.c
    zend_language_scanner.c
    zend_list.c
    zend_llist.c
    zend_multibyte.c
    zend_object_handlers.c
    zend_objects_API.c
    zend_objects.c
    zend_observer.c
    zend_opcode.c
    zend_operators.c
    zend_ptr_stack.c
    zend_signal.c
    zend_smart_str.c
    zend_sort.c
    zend_stack.c
    zend_stream.c
    zend_string.c
    zend_strtod.c
    zend_ts_hash.c
    zend_variables.c
    zend_virtual_cwd.c
    zend_vm_opcodes.c
    zend_weakrefs.c
)

#[[ todo: this feels hacky
    Part of it is because PHP source files expect to include foo.h even if it
    is in Zend/foo.h, and so on with all the subdirectories. This is a practice
    that we should consider changing.

    But aside from this, there is also the fact that I am adding directories
    instead of linking targets; which of the following should use targets?
]]
target_include_directories(Zend
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<INSTALL_INTERFACE:include/main>
        $<INSTALL_INTERFACE:include/TSRM>
        $<INSTALL_INTERFACE:include/Zend>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../main>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../TSRM>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_compile_definitions(Zend INTERFACE -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
