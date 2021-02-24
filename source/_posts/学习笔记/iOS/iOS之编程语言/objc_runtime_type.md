1：objc_object、id
struct objc_object {
    Class _Nonnull isa  OBJC_ISA_AVAILABILITY;
};

typedef struct objc_object *id;

2：objc_class、Class
struct objc_class {
    Class _Nonnull isa  OBJC_ISA_AVAILABILITY;

#if !__OBJC2__
    Class _Nullable super_class                              OBJC2_UNAVAILABLE;
    const char * _Nonnull name                               OBJC2_UNAVAILABLE;
    long version                                             OBJC2_UNAVAILABLE;
    long info                                                OBJC2_UNAVAILABLE;
    long instance_size                                       OBJC2_UNAVAILABLE;
    struct objc_ivar_list * _Nullable ivars                  OBJC2_UNAVAILABLE;
    struct objc_method_list * _Nullable * _Nullable methodLists                    OBJC2_UNAVAILABLE;
    struct objc_cache * _Nonnull cache                       OBJC2_UNAVAILABLE;
    struct objc_protocol_list * _Nullable protocols          OBJC2_UNAVAILABLE;
#endif

}

typedef struct objc_class *Class;

*3：SEL
typedef struct objc_selector *SEL;

4：IMP
typedef void (*IMP)(void /* id, SEL, ... */ );
typedef id _Nullable (*IMP)(id _Nonnull, SEL _Nonnull, ...);

5：objc_objectptr_t
typedef const void* objc_objectptr_t;

6：objc_protocol_list、Protocol
struct objc_protocol_list {
    struct objc_protocol_list * _Nullable next;
    long count;
    __unsafe_unretained Protocol * _Nullable list[1];
};

#ifdef __OBJC__
@class Protocol;
#else
typedef struct objc_object Protocol;
#endif

7：objc_category、Category
struct objc_category {
    char * _Nonnull category_name                            OBJC2_UNAVAILABLE;
    char * _Nonnull class_name                               OBJC2_UNAVAILABLE;
    struct objc_method_list * _Nullable instance_methods     OBJC2_UNAVAILABLE;
    struct objc_method_list * _Nullable class_methods        OBJC2_UNAVAILABLE;
    struct objc_protocol_list * _Nullable protocols          OBJC2_UNAVAILABLE;
}

typedef struct objc_category *Category;


8：objc_ivar
struct objc_ivar {
    char * _Nullable ivar_name                               OBJC2_UNAVAILABLE;
    char * _Nullable ivar_type                               OBJC2_UNAVAILABLE;
    int ivar_offset                                          OBJC2_UNAVAILABLE;
#ifdef __LP64__
    int space                                                OBJC2_UNAVAILABLE;
#endif
}                                                            OBJC2_UNAVAILABLE;

typedef struct objc_ivar *Ivar;

9：objc_ivar_list
struct objc_ivar_list {
    int ivar_count                                           OBJC2_UNAVAILABLE;
#ifdef __LP64__
    int space                                                OBJC2_UNAVAILABLE;
#endif
    /* variable length structure */
    struct objc_ivar ivar_list[1]                            OBJC2_UNAVAILABLE;
}

10：objc_method、objc_method_list、objc_method_description、objc_method_description_list、Method
struct objc_method {
    SEL _Nonnull method_name                                 OBJC2_UNAVAILABLE;
    char * _Nullable method_types                            OBJC2_UNAVAILABLE;
    IMP _Nonnull method_imp                                  OBJC2_UNAVAILABLE;
}                                                            OBJC2_UNAVAILABLE;

struct objc_method_list {
    struct objc_method_list * _Nullable obsolete             OBJC2_UNAVAILABLE;

    int method_count                                         OBJC2_UNAVAILABLE;
#ifdef __LP64__
    int space                                                OBJC2_UNAVAILABLE;
#endif
    /* variable length structure */
    struct objc_method method_list[1]                        OBJC2_UNAVAILABLE;
}

struct objc_method_description {
    SEL _Nullable name;               /**< The name of the method */
    char * _Nullable types;           /**< The types of the method arguments */
};

struct objc_method_description_list {
    int count;
    struct objc_method_description list[1];
};

typedef struct objc_method *Method;

*11：objc_property
typedef struct objc_property *objc_property_t;

typedef struct {
    const char * _Nonnull name;           /**< The name of the attribute */
    const char * _Nonnull value;          /**< The value of the attribute (usually empty) */
} objc_property_attribute_t;

12：objc_symtab、Symtab
struct objc_symtab {
    unsigned long sel_ref_cnt                                OBJC2_UNAVAILABLE;
    SEL _Nonnull * _Nullable refs                            OBJC2_UNAVAILABLE;
    unsigned short cls_def_cnt                               OBJC2_UNAVAILABLE;
    unsigned short cat_def_cnt                               OBJC2_UNAVAILABLE;
    void * _Nullable defs[1] /* variable size */             OBJC2_UNAVAILABLE;
}                                                            OBJC2_UNAVAILABLE;

typedef struct objc_symtab *Symtab                           OBJC2_UNAVAILABLE;

13：objc_cache、Cache
struct objc_cache {
    unsigned int mask /* total = mask + 1 */                 OBJC2_UNAVAILABLE;
    unsigned int occupied                                    OBJC2_UNAVAILABLE;
    Method _Nullable buckets[1]                              OBJC2_UNAVAILABLE;
};

typedef struct objc_cache *Cache                             OBJC2_UNAVAILABLE;


14：objc_module、Module
struct objc_module {
    unsigned long version                                    OBJC2_UNAVAILABLE;
    unsigned long size                                       OBJC2_UNAVAILABLE;
    const char * _Nullable name                              OBJC2_UNAVAILABLE;
    Symtab _Nullable symtab                                  OBJC2_UNAVAILABLE;
}

typedef struct objc_module *Module                           OBJC2_UNAVAILABLE;

15：NSObject、Protocol、SEL、
