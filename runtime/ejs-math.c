/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=4 sw=4 et tw=99 ft=cpp:
 */

#include <math.h>

#include "ejs-ops.h"
#include "ejs-value.h"
#include "ejs-function.h"
#include "ejs-math.h"
#include "ejs-string.h"
#include "ejs-symbol.h"

ejsval _ejs_Math EJSVAL_ALIGNMENT;

// ECMA262: 15.8.2.1
static EJS_NATIVE_FUNC(_ejs_Math_abs) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];

    double x_ = ToDouble(x);
    if (isnan(x_))
        return _ejs_nan;
    
    return NUMBER_TO_EJSVAL(x_ < 0 ? -x_ : x_);
}

// ECMA262: 15.8.2.2
static EJS_NATIVE_FUNC(_ejs_Math_acos) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];

    double x_ = ToDouble(x);
    if (isnan(x_))
        return _ejs_nan;

    return NUMBER_TO_EJSVAL(acos(x_));
}

// ECMA262: 15.8.2.3
static EJS_NATIVE_FUNC(_ejs_Math_asin) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];

    double x_ = ToDouble(x);
    if (isnan(x_))
        return _ejs_nan;

    return NUMBER_TO_EJSVAL(asin(x_));
}

// ECMA262: 15.8.2.4
static EJS_NATIVE_FUNC(_ejs_Math_atan) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];

    double x_ = ToDouble(x);
    if (isnan(x_))
        return _ejs_nan;

    return NUMBER_TO_EJSVAL(atan(x_));
}

// ECMA262: 15.8.2.5
static EJS_NATIVE_FUNC(_ejs_Math_atan2) {
    ejsval y = _ejs_undefined;
    ejsval x = _ejs_undefined;
    if (argc > 0) y = args[0];
    if (argc > 1) x = args[1];

    double x_ = ToDouble(x);
    double y_ = ToDouble(y);

    if (isnan(x_) || isnan(y_))
        return _ejs_nan;

    return NUMBER_TO_EJSVAL(atan2(y_,x_));
}

// ECMA262: 15.8.2.6
static EJS_NATIVE_FUNC(_ejs_Math_ceil) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];

    double x_ = ToDouble(x);
    if (isnan(x_))
        return _ejs_nan;

    return NUMBER_TO_EJSVAL(ceil(x_));
}

// ECMA262: 15.8.2.7
static EJS_NATIVE_FUNC(_ejs_Math_cos) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];

    double x_ = ToDouble(x);
    if (isnan(x_))
        return _ejs_nan;

    return NUMBER_TO_EJSVAL(cos(x_));
}

// ECMA262: 15.8.2.8
static EJS_NATIVE_FUNC(_ejs_Math_exp) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];

    double x_ = ToDouble(x);
    if (isnan(x_))
        return _ejs_nan;

    return NUMBER_TO_EJSVAL(exp(x_));
}

// ECMA262: 15.8.2.9
static EJS_NATIVE_FUNC(_ejs_Math_floor) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];

    double x_ = ToDouble(x);
    if (isnan(x_))
        return _ejs_nan;

    return NUMBER_TO_EJSVAL(floor(x_));
}

// ECMA262: 15.8.2.10
static EJS_NATIVE_FUNC(_ejs_Math_log) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];

    double x_ = ToDouble(x);
    if (isnan(x_))
        return _ejs_nan;

    return NUMBER_TO_EJSVAL(log(x_));
}

// ECMA262: 15.8.2.11
static EJS_NATIVE_FUNC(_ejs_Math_max) {
    double current_max = -INFINITY;
    for (int i = 0; i < argc; i ++) {
        double d = ToDouble(args[i]);
        if (isnan (d))
            return _ejs_nan;

        if (d > current_max)
            current_max = d;
    }

    return NUMBER_TO_EJSVAL(current_max);
}

// ECMA262: 15.8.2.12
static EJS_NATIVE_FUNC(_ejs_Math_min) {
    double current_min = INFINITY;
    for (int i = 0; i < argc; i ++) {
        double d = ToDouble(args[i]);
        if (isnan (d))
            return _ejs_nan;

        if (d < current_min)
            current_min = d;
    }

    return NUMBER_TO_EJSVAL(current_min);
}

// ECMA262: 15.8.2.13
static EJS_NATIVE_FUNC(_ejs_Math_pow) {
    ejsval x = _ejs_undefined;
    ejsval y = _ejs_undefined;
    if (argc > 0) x = args[0];
    if (argc > 1) y = args[1];

    double x_ = ToDouble(x);
    double y_ = ToDouble(y);
    if (isnan(x_) || isnan(y_))
        return _ejs_nan;

    return NUMBER_TO_EJSVAL(pow(x_, y_));
}

// ECMA262: 15.8.2.14
static EJS_NATIVE_FUNC(_ejs_Math_random) {
    return NUMBER_TO_EJSVAL((double)rand() / RAND_MAX);
}

// ECMA262: 15.8.2.15
static EJS_NATIVE_FUNC(_ejs_Math_round) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];

    double x_ = ToDouble(x);
    if (isnan(x_))
        return _ejs_nan;

    return NUMBER_TO_EJSVAL(round (x_));
}

// ECMA262: 15.8.2.16
static EJS_NATIVE_FUNC(_ejs_Math_sin) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];

    double x_ = ToDouble(x);
    if (isnan(x_))
        return _ejs_nan;

    return NUMBER_TO_EJSVAL(sin (x_));
}

// ECMA262: 15.8.2.17
static EJS_NATIVE_FUNC(_ejs_Math_sqrt) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];

    double x_ = ToDouble(x);
    if (isnan(x_))
        return _ejs_nan;

    return NUMBER_TO_EJSVAL(sqrt (x_));
}

// ECMA262: 15.8.2.18
static EJS_NATIVE_FUNC(_ejs_Math_tan) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];

    double x_ = ToDouble(x);
    if (isnan(x_))
        return _ejs_nan;

    return NUMBER_TO_EJSVAL(tan (x_));
}


static EJS_NATIVE_FUNC(_ejs_Math_clz32) {
    ejsval v = _ejs_undefined;
    if (argc > 0) v = args[0];

    uint32_t val = ToUint32(v);

#if __has_builtin(__builtin_clz)
    return NUMBER_TO_EJSVAL(val == 0 ? 32 : __builtin_clz(val));
#else
    // from qemu source:

    /* Binary search for leading zeros.  */

    int cnt = 0;

    if (!(val & 0xFFFF0000U)) {
        cnt += 16;
        val <<= 16;
    }
    if (!(val & 0xFF000000U)) {
        cnt += 8;
        val <<= 8;
    }
    if (!(val & 0xF0000000U)) {
        cnt += 4;
        val <<= 4;
    }
    if (!(val & 0xC0000000U)) {
        cnt += 2;
        val <<= 2;
    }
    if (!(val & 0x80000000U)) {
        cnt++;
        val <<= 1;
    }
    if (!(val & 0x80000000U)) {
        cnt++;
    }
    return NUMBER_TO_EJSVAL(cnt);
#endif
}

static EJS_NATIVE_FUNC(_ejs_Math_imul) {
    if (argc != 2)
        return NUMBER_TO_EJSVAL(0);

    // When the Math.imul is called with arguments x and y the following steps are taken:
    // 1. Let a be ToUint32(x).
    uint32_t a = ToUint32(args[0]);
    // 2. ReturnIfAbrupt(a).
    // 3. Let b be ToUint32(y).
    uint32_t b = ToUint32(args[1]);
    // 4. ReturnIfAbrupt(b).
    // 5. Let product be (a × b) modulo 2^32.
    uint64_t product = ((uint64_t)a * (uint64_t)b) % (2LL<<32);

    // 6. If product ≥ 2^31, return product − 2^32, otherwise return product.
    if (product >= 2LL<<31)
        return NUMBER_TO_EJSVAL(product - (2LL<<32));
    else
        return NUMBER_TO_EJSVAL(product);
}

// Returns the sign of the x, indicating whether x is positive, negative or zero.
static EJS_NATIVE_FUNC(_ejs_Math_sign) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];

    double x_ = ToDouble(x);

    // 1. If x is NaN, the result is NaN.
    if (isnan(x_))
        return _ejs_nan;

    // 2. If x is −0, the result is −0.
    // 3. If x is +0, the result is +0.
    // 4. If x is negative and not −0, the result is −1.
    // 5. If x is positive and not +0, the result is +1.

    if (x_ < 0)
        return NUMBER_TO_EJSVAL(-1);
    else if (x_ > 0)
        return NUMBER_TO_EJSVAL(1);
    else /* x is zero, either positive or negative */
        return x;
}

static EJS_NATIVE_FUNC(_ejs_Math_log10) {
    // Returns an implementation-dependent approximation to the base 10 logarithm of x.
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];

    double x_ = ToDouble(x);

    // 1. If x is NaN, the result is NaN.
    if (isnan(x_))
        return _ejs_nan;

    // 2. If x is less than 0, the result is NaN.
    if (x_ < 0)
        return _ejs_nan;

    // 3. If x is +0, the result is +0.
    // 4. If x is −0, the result is −0.
    if (x_ == 0)
        return x;

    // 5. If x is 1, the result is +0.
    // 6. If x is +∞, the result is +∞.
    return NUMBER_TO_EJSVAL(log10(x_));
}

static EJS_NATIVE_FUNC(_ejs_Math_log2) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];
    return NUMBER_TO_EJSVAL(log2(ToDouble(x)));
}

static EJS_NATIVE_FUNC(_ejs_Math_log1p) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];
    return NUMBER_TO_EJSVAL(log1p(ToDouble(x)));
}

static EJS_NATIVE_FUNC(_ejs_Math_expm1) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];
    return NUMBER_TO_EJSVAL(expm1(ToDouble(x)));
}

static EJS_NATIVE_FUNC(_ejs_Math_cosh) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];
    return NUMBER_TO_EJSVAL(cosh(ToDouble(x)));
}

static EJS_NATIVE_FUNC(_ejs_Math_sinh) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];
    return NUMBER_TO_EJSVAL(sinh(ToDouble(x)));
}

static EJS_NATIVE_FUNC(_ejs_Math_tanh) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];
    return NUMBER_TO_EJSVAL(tanh(ToDouble(x)));
}

static EJS_NATIVE_FUNC(_ejs_Math_acosh) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];
    return NUMBER_TO_EJSVAL(acosh(ToDouble(x)));
}

static EJS_NATIVE_FUNC(_ejs_Math_asinh) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];
    return NUMBER_TO_EJSVAL(asinh(ToDouble(x)));
}

static EJS_NATIVE_FUNC(_ejs_Math_atanh) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];
    return NUMBER_TO_EJSVAL(atanh(ToDouble(x)));
}

static EJS_NATIVE_FUNC(_ejs_Math_hypot) {
    if (argc == 0) return NUMBER_TO_EJSVAL(0);

    double sum = 0;

    EJSBool has_nan = EJS_FALSE;
    EJSBool has_pos_inf = EJS_FALSE;
    EJSBool has_neg_inf = EJS_FALSE;

    for (int i = 0; i < argc; i ++) {
        double arg = ToDouble(args[i]);
        int classified = fpclassify(arg);
        if (classified == FP_INFINITE)
            if (arg > 0)
                has_pos_inf = EJS_TRUE;
            else
                has_neg_inf = EJS_TRUE;
        else if (isnan(arg))
            has_nan = EJS_TRUE;
        else
            sum += arg * arg;
    }
    if (has_pos_inf)
        return NUMBER_TO_EJSVAL(INFINITY);
    if (has_neg_inf)
        return NUMBER_TO_EJSVAL(-INFINITY);
    if (has_nan)
        return NUMBER_TO_EJSVAL(nan("7734")); // XXX this should be in ejs.h or something?

    return NUMBER_TO_EJSVAL(sqrt(sum));
}

static EJS_NATIVE_FUNC(_ejs_Math_trunc) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];
    return NUMBER_TO_EJSVAL(trunc(ToDouble(x)));
}

static EJS_NATIVE_FUNC(_ejs_Math_fround) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];
    return NUMBER_TO_EJSVAL((float)ToDouble(x));
}

static EJS_NATIVE_FUNC(_ejs_Math_cbrt) {
    ejsval x = _ejs_undefined;
    if (argc > 0) x = args[0];
    return NUMBER_TO_EJSVAL(cbrt(ToDouble(x)));
}

void
_ejs_math_init(ejsval global)
{
    _ejs_Math = _ejs_object_new (_ejs_Object_prototype, &_ejs_Object_specops);
    _ejs_object_setprop (global, _ejs_atom_Math, _ejs_Math);

#define OBJ_METHOD(x) EJS_INSTALL_ATOM_FUNCTION(_ejs_Math, x, _ejs_Math_##x)
#define OBJ_METHOD_LEN(x,l) EJS_INSTALL_ATOM_FUNCTION_LEN_FLAGS(_ejs_Math, x, _ejs_Math_##x, l, 0)

    OBJ_METHOD(abs);
    OBJ_METHOD(acos);
    OBJ_METHOD(asin);
    OBJ_METHOD(atan);
    OBJ_METHOD(atan2);
    OBJ_METHOD(ceil);
    OBJ_METHOD(cos);
    OBJ_METHOD(exp);
    OBJ_METHOD(floor);
    OBJ_METHOD(log);
    OBJ_METHOD(max);
    OBJ_METHOD(min);
    OBJ_METHOD(pow);
    OBJ_METHOD(random);
    OBJ_METHOD(round);
    OBJ_METHOD(sin);
    OBJ_METHOD(sqrt);
    OBJ_METHOD(tan);

    // ES6
    OBJ_METHOD(clz32);
    OBJ_METHOD(imul);
    OBJ_METHOD(sign);
    OBJ_METHOD(log10);
    OBJ_METHOD(log2);
    OBJ_METHOD(log1p);
    OBJ_METHOD(expm1);
    OBJ_METHOD(cosh);
    OBJ_METHOD(sinh);
    OBJ_METHOD(tanh);
    OBJ_METHOD(acosh);
    OBJ_METHOD(asinh);
    OBJ_METHOD(atanh);
    OBJ_METHOD_LEN(hypot, 2);
    OBJ_METHOD(trunc);
    OBJ_METHOD(fround);
    OBJ_METHOD(cbrt);

#undef OBJ_METHOD

    _ejs_object_setprop (_ejs_Math, _ejs_atom_PI, NUMBER_TO_EJSVAL(M_PI));
    _ejs_object_setprop (_ejs_Math, _ejs_atom_E, NUMBER_TO_EJSVAL(M_E));

    _ejs_object_define_value_property (_ejs_Math, _ejs_Symbol_toStringTag, _ejs_atom_Math, EJS_PROP_NOT_ENUMERABLE | EJS_PROP_NOT_WRITABLE | EJS_PROP_CONFIGURABLE);
}

