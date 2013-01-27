/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=4 sw=4 et tw=99 ft=cpp:
 */

#ifndef _ejs_object_h_
#define _ejs_object_h_

#include "ejs.h"
#include "ejs-gc.h"
#include "ejs-value.h"

// really terribly performing property maps
typedef struct {
#define EJS_PROP_FLAGS_ENUMERABLE    (1 << 0)
#define EJS_PROP_FLAGS_CONFIGURABLE  (1 << 1)
#define EJS_PROP_FLAGS_WRITABLE      (1 << 2)
#define EJS_PROP_FLAGS_ACCESSORDESC  (1 << 3)

#define EJS_PROP_FLAGS_ENUMERABLE_SET   (1 << 4)
#define EJS_PROP_FLAGS_CONFIGURABLE_SET (1 << 5)
#define EJS_PROP_FLAGS_WRITABLE_SET     (1 << 6)
#define EJS_PROP_FLAGS_VALUE_SET        (1 << 7)
#define EJS_PROP_FLAGS_GETTER_SET       (1 << 8)
#define EJS_PROP_FLAGS_SETTER_SET       (1 << 9)

#define EJS_PROP_FLAGS_SET_MASK (EJS_PROP_FLAGS_ENUMERABLE_SET | EJS_PROP_FLAGS_CONFIGURABLE_SET | EJS_PROP_FLAGS_WRITABLE_SET | EJS_PROP_FLAGS_VALUE_SET | EJS_PROP_FLAGS_GETTER_SET | EJS_PROP_FLAGS_SETTER_SET)

#define EJS_PROP_ENUMERABLE   (EJS_PROP_FLAGS_ENUMERABLE | EJS_PROP_FLAGS_ENUMERABLE_SET)
#define EJS_PROP_CONFIGURABLE (EJS_PROP_FLAGS_CONFIGURABLE | EJS_PROP_FLAGS_CONFIGURABLE_SET)
#define EJS_PROP_WRITABLE     (EJS_PROP_FLAGS_WRITABLE | EJS_PROP_FLAGS_WRITABLE_SET)
#define EJS_PROP_NOT_ENUMERABLE   (EJS_PROP_FLAGS_ENUMERABLE_SET)
#define EJS_PROP_NOT_CONFIGURABLE (EJS_PROP_FLAGS_CONFIGURABLE_SET)
#define EJS_PROP_NOT_WRITABLE     (EJS_PROP_FLAGS_WRITABLE_SET)

    uint32_t flags;
    ejsval value;
    ejsval getter;
    ejsval setter;
} EJSPropertyDesc;

#define _ejs_property_desc_set_flag(p, v, propflag, flagset) EJS_MACRO_START \
    if ((v)) {                                                          \
        (p)->flags |= (propflag);                                       \
    }                                                                   \
    else {                                                              \
        (p)->flags &= ~(propflag);                                      \
    }                                                                   \
    (p)->flags |= (flagset);                                            \
    EJS_MACRO_END

#define _ejs_property_desc_set_value_flag(p, v, vname, flagset) EJS_MACRO_START \
    (p)->vname = v;                                                     \
    (p)->flags |= (flagset);                                            \
    EJS_MACRO_END

#define FLAG_TO_BOOL(x) ((x) != 0 ? EJS_TRUE : EJS_FALSE)

#define _ejs_property_desc_set_enumerable(p, v) _ejs_property_desc_set_flag(p, v, EJS_PROP_FLAGS_ENUMERABLE, EJS_PROP_FLAGS_ENUMERABLE_SET)
#define _ejs_property_desc_set_configurable(p, v) _ejs_property_desc_set_flag(p, v, EJS_PROP_FLAGS_CONFIGURABLE, EJS_PROP_FLAGS_CONFIGURABLE_SET)
#define _ejs_property_desc_set_writable(p, v) _ejs_property_desc_set_flag(p, v, EJS_PROP_FLAGS_WRITABLE, EJS_PROP_FLAGS_WRITABLE_SET)
#define _ejs_property_desc_set_value(p, v) _ejs_property_desc_set_value_flag(p, v, value, EJS_PROP_FLAGS_VALUE_SET)
#define _ejs_property_desc_set_getter(p, v) _ejs_property_desc_set_value_flag(p, v, getter, EJS_PROP_FLAGS_GETTER_SET)
#define _ejs_property_desc_set_setter(p, v) _ejs_property_desc_set_value_flag(p, v, setter, EJS_PROP_FLAGS_SETTER_SET)

#define _ejs_property_desc_has_enumerable(p) FLAG_TO_BOOL((p)->flags & EJS_PROP_FLAGS_ENUMERABLE_SET)
#define _ejs_property_desc_has_configurable(p) FLAG_TO_BOOL((p)->flags & EJS_PROP_FLAGS_CONFIGURABLE_SET)
#define _ejs_property_desc_has_writable(p) FLAG_TO_BOOL((p)->flags & EJS_PROP_FLAGS_WRITABLE_SET)
#define _ejs_property_desc_has_value(p) FLAG_TO_BOOL((p)->flags & EJS_PROP_FLAGS_VALUE_SET)
#define _ejs_property_desc_has_getter(p) FLAG_TO_BOOL((p)->flags & EJS_PROP_FLAGS_GETTER_SET)
#define _ejs_property_desc_has_setter(p) FLAG_TO_BOOL((p)->flags & EJS_PROP_FLAGS_SETTER_SET)

#define _ejs_property_desc_get_flag_default(p,f,fs,def) (((p)->flags & (fs)) != 0 ? FLAG_TO_BOOL((p)->flags & (f)) : (def))
#define _ejs_property_desc_get_value_flag_default(p,v,fs,def) (((p)->flags & (fs)) != 0 ? (p)->v : (def))

#define _ejs_property_desc_is_enumerable(p)   _ejs_property_desc_get_flag_default(p, EJS_PROP_FLAGS_ENUMERABLE, EJS_PROP_FLAGS_ENUMERABLE_SET, EJS_FALSE)
#define _ejs_property_desc_is_configurable(p) _ejs_property_desc_get_flag_default(p, EJS_PROP_FLAGS_CONFIGURABLE, EJS_PROP_FLAGS_CONFIGURABLE_SET, EJS_FALSE)
#define _ejs_property_desc_is_writable(p)     _ejs_property_desc_get_flag_default(p, EJS_PROP_FLAGS_WRITABLE, EJS_PROP_FLAGS_WRITABLE_SET, EJS_FALSE)

#define _ejs_property_desc_get_value(p) _ejs_property_desc_get_value_flag_default(p, value, EJS_PROP_FLAGS_VALUE_SET, _ejs_undefined)
#define _ejs_property_desc_get_getter(p) _ejs_property_desc_get_value_flag_default(p, getter, EJS_PROP_FLAGS_GETTER_SET, _ejs_undefined)
#define _ejs_property_desc_get_setter(p) _ejs_property_desc_get_value_flag_default(p, setter, EJS_PROP_FLAGS_SETTER_SET, _ejs_undefined)
    
struct _EJSPropertyMap {
    jschar **names;
    EJSPropertyDesc *properties;
    int allocated;
    int num;
};

typedef struct _EJSPropertyMap EJSPropertyMap;
typedef struct _EJSPropertyIterator EJSPropertyIterator;

typedef void (*EJSPropertyDescFunc)(EJSPropertyDesc *desc, void* data);

typedef ejsval           (*SpecOpGet) (ejsval obj, ejsval propertyName, EJSBool isCStr);
typedef EJSPropertyDesc* (*SpecOpGetOwnProperty) (ejsval obj, ejsval propertyName);
typedef EJSPropertyDesc* (*SpecOpGetProperty) (ejsval obj, ejsval propertyName);
typedef void             (*SpecOpPut) (ejsval obj, ejsval propertyName, ejsval val, EJSBool flag);
typedef EJSBool          (*SpecOpCanPut) (ejsval obj, ejsval propertyName);
typedef EJSBool          (*SpecOpHasProperty) (ejsval obj, ejsval propertyName);
typedef EJSBool          (*SpecOpDelete) (ejsval obj, ejsval propertyName, EJSBool flag);
typedef ejsval           (*SpecOpDefaultValue) (ejsval obj, const char *hint);
typedef EJSBool          (*SpecOpDefineOwnProperty) (ejsval obj, ejsval propertyName, EJSPropertyDesc* propertyDescriptor, EJSBool _throw);

typedef EJSObject*       (*SpecOpAllocate) ();
typedef void             (*SpecOpFinalize) (EJSObject* obj);
typedef void             (*SpecOpScan) (EJSObject* obj, EJSValueFunc scan_func);

typedef struct {
    // special ops defined in the standard
    const char* class_name;
    SpecOpGet get;
    SpecOpGetOwnProperty get_own_property;
    SpecOpGetProperty get_property;
    SpecOpPut put;
    SpecOpCanPut can_put;
    SpecOpHasProperty has_property;
    SpecOpDelete _delete;
    SpecOpDefaultValue default_value;
    SpecOpDefineOwnProperty define_own_property;

    // ejs-defined ops
    SpecOpAllocate allocate; // allocates space for the new instance (but doesn't initialize it)
    SpecOpFinalize finalize; // called when there are no remaining references to this object
    SpecOpScan     scan;     // used to enumerate object references
} EJSSpecOps;

#define EJS_OBJECT_EXTENSIBLE_FLAG 0x01

#define EJS_OBJECT_EXTENSIBLE_FLAG_SHIFTED (EJS_OBJECT_EXTENSIBLE_FLAG << EJS_GC_USER_FLAGS_SHIFT)

#define EJS_OBJECT_SET_EXTENSIBLE(o) (((EJSObject*)(o))->gc_header |= EJS_OBJECT_EXTENSIBLE_FLAG_SHIFTED)
#define EJS_OBJECT_CLEAR_EXTENSIBLE(o) (((EJSObject*)(o))->gc_header &= ~EJS_OBJECT_EXTENSIBLE_FLAG_SHIFTED)

#define EJS_OBJECT_IS_EXTENSIBLE(o) ((((EJSObject*)(o))->gc_header & EJS_OBJECT_EXTENSIBLE_FLAG_SHIFTED) != 0)

struct _EJSObject {
    GCObjectHeader gc_header;
    EJSSpecOps *ops;
    ejsval proto; // the __proto__ property
    EJSPropertyMap map;
};


#define OP(o,op) (((EJSObject*)o)->ops->op)

#define CLASSNAME(o) OP(o,class_name)

EJS_BEGIN_DECLS

void _ejs_propertymap_init (EJSPropertyMap* map, int initial_allocation);
int _ejs_propertymap_lookup (EJSPropertyMap *map, const jschar *name, EJSBool add_if_not_found);
void _ejs_propertymap_foreach_value (EJSPropertyMap *map, EJSValueFunc foreach_func);
void _ejs_propertymap_foreach_property (EJSPropertyMap *map, EJSPropertyDescFunc foreach_func, void* data);

EJSBool _ejs_object_define_value_property (ejsval obj, ejsval key, ejsval value, uint32_t flags);
EJSBool _ejs_object_define_accessor_property (ejsval obj, ejsval key, ejsval get, ejsval set, uint32_t flags);

ejsval _ejs_object_setprop (ejsval obj, ejsval key, ejsval value);
ejsval _ejs_object_getprop (ejsval obj, ejsval key);

ejsval _ejs_object_setprop_utf8 (ejsval obj, const char *key, ejsval value);
ejsval _ejs_object_getprop_utf8 (ejsval obj, const char *key);

EJSPropertyIterator* _ejs_property_iterator_new (ejsval forObj);
ejsval               _ejs_property_iterator_current (EJSPropertyIterator* iterator);
EJSBool              _ejs_property_iterator_next (EJSPropertyIterator* iterator, EJSBool free_on_end);
void                 _ejs_property_iterator_free (EJSPropertyIterator *iterator);

extern ejsval _ejs_Object;
extern ejsval _ejs_Object__proto__;
extern ejsval _ejs_Object_prototype;
extern EJSSpecOps _ejs_object_specops;

void _ejs_object_init_proto();

ejsval _ejs_object_new (ejsval proto, EJSSpecOps* ops);
ejsval _ejs_object_create (ejsval proto);
void   _ejs_init_object (EJSObject *obj, ejsval proto, EJSSpecOps *ops);

void _ejs_object_finalize(EJSObject *obj);

void _ejs_object_init(ejsval global);

EJS_END_DECLS

#endif // _ejs_object_h_
