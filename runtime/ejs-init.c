/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=4 sw=4 et tw=99 ft=cpp:
 */

#include <math.h>

#include "ejs.h"
#include "ejs-gc.h"
#include "ejs-ops.h"
#include "ejs-arguments.h"
#include "ejs-array.h"
#include "ejs-console.h"
#include "ejs-date.h"
#include "ejs-error.h"
#include "ejs-exception.h"
#include "ejs-function.h"
#include "ejs-json.h"
#include "ejs-math.h"
#include "ejs-number.h"
#include "ejs-boolean.h"
#include "ejs-object.h"
#include "ejs-process.h"
#include "ejs-regexp.h"
#include "ejs-require.h"
#include "ejs-string.h"
#include "ejs-typedarrays.h"
#include "ejs-uri.h"
#include "ejs-value.h"

const ejsval _ejs_undefined = STATIC_BUILD_EJSVAL(EJSVAL_TAG_UNDEFINED, 0);
ejsval _ejs_nan;
const ejsval _ejs_null = STATIC_BUILD_EJSVAL(EJSVAL_TAG_NULL, 0);
const ejsval _ejs_true = STATIC_BUILD_BOOLEAN_EJSVAL(EJS_TRUE);
const ejsval _ejs_false = STATIC_BUILD_BOOLEAN_EJSVAL(EJS_FALSE);
const ejsval _ejs_zero = STATIC_BUILD_DOUBLE_EJSVAL(0);
const ejsval _ejs_one = STATIC_BUILD_DOUBLE_EJSVAL(1);

ejsval _ejs_global;


/* useful strings literals */
#include "ejs-atoms-gen.c"

void
_ejs_init(int argc, char** argv)
{
    START_SHADOW_STACK_FRAME;

    // initialize our atoms before anything else
    _ejs_init_static_strings();

    _ejs_gc_init();
    _ejs_exception_init();

    // initialization or ECMA262 builtins
    _ejs_gc_add_named_root (_ejs_global);
    _ejs_global = _ejs_object_new (_ejs_null, &_ejs_object_specops);

    _ejs_nan = NUMBER_TO_EJSVAL(nan("7734"));

    _ejs_object_setprop (_ejs_global, _ejs_atom_undefined, _ejs_undefined);
    _ejs_object_setprop (_ejs_global, _ejs_atom_NaN, _ejs_nan);

    _ejs_object_init_proto();

    _ejs_function_init(_ejs_global);
    _ejs_object_init(_ejs_global);

    _ejs_error_init(_ejs_global);
    _ejs_arguments_init(_ejs_global);
    _ejs_array_init(_ejs_global);
    _ejs_boolean_init (_ejs_global);
    _ejs_string_init(_ejs_global);
    _ejs_number_init(_ejs_global);
    _ejs_regexp_init(_ejs_global);
    _ejs_date_init(_ejs_global);
    _ejs_json_init(_ejs_global);
    _ejs_math_init(_ejs_global);

    _ejs_typedarrays_init(_ejs_global);

#define GLOBAL_METHOD(x) EJS_INSTALL_FUNCTION(_ejs_global, EJS_STRINGIFY(x), _ejs_##x)

    GLOBAL_METHOD(isNaN);
    GLOBAL_METHOD(isFinite);
    GLOBAL_METHOD(parseInt);
    GLOBAL_METHOD(parseFloat);

    GLOBAL_METHOD(decodeURI);
    GLOBAL_METHOD(decodeURIComponent);
    GLOBAL_METHOD(encodeURI);
    GLOBAL_METHOD(encodeURIComponent);

#undef GLOBAL_METHOD

    // the node-like api we support in order for our driver to
    // function.  this should really be a separate opt-in .a/.so.
    _ejs_require_init(_ejs_global);
    _ejs_console_init(_ejs_global);
    _ejs_process_init(_ejs_global, argc, argv);

    // a special global (__ejs) under which we can stuff other
    // semi-useful runtime features, like a call to force a GC.  the
    // compiler also uses the presence of __ejs to disable
    // buggy/nonfunctional code (like those that use regexps)
    ADD_STACK_ROOT(ejsval, _ejs_ejs_global, _ejs_object_new (_ejs_null, &_ejs_object_specops));
    _ejs_object_setprop (_ejs_global, _ejs_atom___ejs, _ejs_ejs_global);

    _ejs_GC_init(_ejs_global);

    END_SHADOW_STACK_FRAME;
}
