/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=4 sw=4 et tw=99 ft=cpp:
 */

#include "ejs-llvm.h"
#include "ejs-object.h"
#include "ejs-value.h"
#include "ejs-function.h"
#include "ejs-array.h"
#include "ejs-string.h"
#include "constantarray.h"
#include "type.h"
#include "value.h"

namespace ejsllvm {

    static ejsval _ejs_ConstantArray_prototype EJSVAL_ALIGNMENT;
    static ejsval _ejs_ConstantArray EJSVAL_ALIGNMENT;

    static EJS_NATIVE_FUNC(ConstantArray_impl) {
        EJS_NOT_IMPLEMENTED();
    }

    static EJS_NATIVE_FUNC(ConstantArray_get) {
        REQ_LLVM_TYPE_ARG(0, array_type);
        REQ_ARRAY_ARG(1, elements);

        std::vector< llvm::Constant*> element_constants;
        for (int i = 0; i < EJSARRAY_LEN(elements); i ++) {
            element_constants.push_back (static_cast<llvm::Constant*>(Value_GetLLVMObj(EJSDENSEARRAY_ELEMENTS(elements)[i])));
        }

        return Value_new (llvm::ConstantArray::get(static_cast<llvm::ArrayType*>(array_type), element_constants));
    }

    void
    ConstantArray_init (ejsval exports)
    {
        _ejs_gc_add_root (&_ejs_ConstantArray_prototype);
        _ejs_ConstantArray_prototype = _ejs_object_create(_ejs_Object_prototype);

        _ejs_ConstantArray = _ejs_function_new_utf8_with_proto (_ejs_null, "LLVMConstantArray", (EJSClosureFunc)ConstantArray_impl, _ejs_ConstantArray_prototype);

        _ejs_object_setprop_utf8 (exports,              "ConstantArray", _ejs_ConstantArray);

#define OBJ_METHOD(x) EJS_INSTALL_ATOM_FUNCTION(_ejs_ConstantArray, x, ConstantArray_##x)
#define PROTO_METHOD(x) EJS_INSTALL_ATOM_FUNCTION(_ejs_ConstantArray_prototype, x, ConstantArray_prototype_##x)

        OBJ_METHOD(get);

#undef PROTO_METHOD
#undef OBJ_METHOD
    }
};
