#ifndef SCRIPTS_C_HELPER_H
#define SCRIPTS_C_HELPER_H

inline
int diff(void *a, void *b) { return ((char *) a - (char *) b); }

#define FUNC_T void(*)()

#define PRINT_START(cls) printf("%s Layout (Total Size %03ld):\n%-20s::%-20s: %s\n", \
                                #cls, sizeof(cls), "SubObject","Attribute","Offset(~Size) 0xAddress")
#define PRINT_OFFSET(cls, obj, attr) printf("%-20s::%-20s: %06d(~%04ld) %p\n",\
                                            cls, #attr, diff(attr, obj),sizeof(*attr), (void *)attr)
#define PRINT_OFFSET_VPTR(cls, obj, sub_obj) printf("%-20s::%-20s: %06d(~%04ld) %p\n",\
                                            cls, "vptr", diff(sub_obj, obj),sizeof(void*), (void *)sub_obj)
#define PRINT_SEPARATOR() printf("----------\n")
#define PRINT_VTABLE_START(cls, obj_vtable) printf("%s VTable (%p)\n%-20s::%-20s: %s\n", \
                                                    cls, obj_vtable, "SubObject", "VirtualFunc", "0xAddress")
#define PRINT_VTABLE_FUNC(cls, obj_vtable, idx, func_name) printf("%-20s::%-20s: %p    ", cls, func_name, obj_vtable[idx]);\
                                                         ((FUNC_T)obj_vtable[idx])();
#define PRINT_VTABLE_DATA(cls, obj_vtable, idx, data_name) printf("%-20s::%-20s: %d    \n", cls, data_name, obj_vtable[idx]);
#define PRINT_END() printf("==========\n\n")

#endif //SCRIPTS_C_HELPER_H
