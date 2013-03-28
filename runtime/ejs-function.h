/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=4 sw=4 et tw=99 ft=cpp:
 */

#ifndef _ejs_function_h_
#define _ejs_function_h_

#include "ejs.h"
#include "ejs-object.h"
#include "ejs-closureenv.h"

typedef ejsval (*EJSClosureFunc) (ejsval env, ejsval _this, uint32_t argc, ejsval* args);

typedef struct {
    /* object header */
    EJSObject obj;

    EJSClosureFunc func;
    ejsval env;

    EJSBool bound;
    ejsval bound_this;
    uint32_t bound_argc;
    ejsval *bound_args;
} EJSFunction;


EJS_BEGIN_DECLS

#define EJS_INSTALL_ATOM_FUNCTION(o,n,f) EJS_MACRO_START               \
    ADD_STACK_ROOT(ejsval, tmpfunc, _ejs_function_new_native (_ejs_null, _ejs_atom_##n, (EJSClosureFunc)f)); \
    _ejs_object_setprop (o, _ejs_atom_##n, tmpfunc);                    \
EJS_MACRO_END

#define EJS_INSTALL_ATOM_FUNCTION_FLAGS(o,n,f,flags) EJS_MACRO_START         \
    ADD_STACK_ROOT(ejsval, tmpfunc, _ejs_function_new_native (_ejs_null, _ejs_atom_##n, (EJSClosureFunc)f)); \
    _ejs_object_define_value_property (o, _ejs_atom_##n, tmpfunc, flags); \
EJS_MACRO_END

#define EJS_INSTALL_FUNCTION(o,n,f) EJS_MACRO_START                    \
    ADD_STACK_ROOT(ejsval, funcname, _ejs_string_new_utf8(n));          \
    ADD_STACK_ROOT(ejsval, tmpfunc, _ejs_function_new_native (_ejs_null, funcname, (EJSClosureFunc)f)); \
    _ejs_object_setprop (o, funcname, tmpfunc);                         \
    EJS_MACRO_END

#define EJS_INSTALL_GETTER(o,n,f) EJS_MACRO_START                     \
    ADD_STACK_ROOT(ejsval, key, _ejs_string_new_utf8(n));          \
    ADD_STACK_ROOT(ejsval, tmpfunc, _ejs_function_new (_ejs_null, key, (EJSClosureFunc)f)); \
    _ejs_object_define_accessor_property (o, key, tmpfunc, _ejs_undefined, EJS_PROP_FLAGS_GETTER_SET); \
    EJS_MACRO_END

ejsval  _ejs_invoke_closure (ejsval closure, ejsval _this, uint32_t argc, ejsval* args);
EJSBool _ejs_decompose_closure (ejsval closure, EJSClosureFunc* func, ejsval* env, ejsval *_this);

extern ejsval _ejs_function_new (ejsval env, ejsval name, EJSClosureFunc func);
extern ejsval _ejs_function_new_native (ejsval env, ejsval name, EJSClosureFunc func);
extern ejsval _ejs_function_new_anon (ejsval env, EJSClosureFunc func);
extern ejsval _ejs_function_new_utf8 (ejsval env, const char* name, EJSClosureFunc func);

extern ejsval _ejs_Function;
extern ejsval _ejs_Function__proto__;
extern EJSSpecOps _ejs_function_specops;

extern void _ejs_function_init(ejsval global);

// used as the __proto__ for a number of builtin objects
ejsval _ejs_Function_empty (ejsval env, ejsval _this, uint32_t argc, ejsval *args);

EJS_END_DECLS

#endif
