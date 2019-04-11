#include <stdio.h>
#include <stdlib.h>

inline
int diff(void *a, void *b) { return ((char *) a - (char *) b); }

class Point3D {
public:
    float x;
    float y;
    float z;

    static void DisplayLayout(Point3D &point3D) {
        printf("Layout of Point3D:\n");
        printf("%-20s: %03d\n", "Size", sizeof(Point3D));
        printf("%-20s: %03d\n", "Offset", 0);
        printf("%-20s: %03d\n", "  Point3D x", &Point3D::x);
        printf("%-20s: %03d\n", "  Point3D y", &Point3D::y);
        printf("%-20s: %03d\n", "  Point3D z", &Point3D::z);
        printf("%-20s: %p\n", "Address", &point3D);
        printf("%-20s: %p(+%02d)\n", " float x", &point3D.x, diff(&point3D.x, &point3D));
        printf("%-20s: %p(+%02d)\n", " float y", &point3D.y, diff(&point3D.y, &point3D));
        printf("%-20s: %p(+%02d)\n", " float z", &point3D.z, diff(&point3D.z, &point3D));
        printf("\n==========\n\n");
    }
};

class Point3D_VPTR {
public:
    float x;
    float y;
    float z;

    virtual void v_func0() {
        printf("calling virtual function v_func0\n");
    };

    virtual void v_func1() {
        printf("calling virtual function v_func1\n");
    };

    static void DisplayLayout(Point3D_VPTR &point3D_vptr) {
        printf("Layout of Point3D_VPTR:\n");
        printf("%-20s: %03d\n", "Size", sizeof(Point3D_VPTR));
        printf("%-20s: %03d\n", "Offset", 0);
        printf("%-20s: %03d\n", "  Point3D_VPTR x", &Point3D_VPTR::x);
        printf("%-20s: %03d\n", "  Point3D_VPTR y", &Point3D_VPTR::y);
        printf("%-20s: %03d\n", "  Point3D_VPTR z", &Point3D_VPTR::z);
        printf("%-20s: %p\n", "Address", &point3D_vptr);
        printf("%-20s: %p(+%02d)\n", " Point3D_VPTR vptr", &point3D_vptr, diff(&point3D_vptr, &point3D_vptr));
        printf("%-20s: %p(+%02d)\n", " Point3D_VPTR x", &point3D_vptr.x, diff(&point3D_vptr.x, &point3D_vptr));
        printf("%-20s: %p(+%02d)\n", " Point3D_VPTR y", &point3D_vptr.y, diff(&point3D_vptr.y, &point3D_vptr));
        printf("%-20s: %p(+%02d)\n", " Point3D_VPTR z", &point3D_vptr.z, diff(&point3D_vptr.z, &point3D_vptr));

        long *vptr = (long *) &point3D_vptr;  // 最开始 8 字节是 vptr
        long *vtbl = (long *)*vptr;           // 读取 vptr 获取 vtbl 地址，保存为指针
        long *vtbl_0 = vtbl;                  // vtbl 第 0 项地址
        long *vtbl_1 = vtbl + 1;              // vtbl 第 1 项地址
        auto *v_func0 = (void(*)())*vtbl_0;   // 读取 vtbl 第 0 项获取 v_func0 地址
        auto *v_func1 = (void(*)())*vtbl_1;   // 读取 vtbl 第 1 项获取 v_func1 地址
        printf("%-20s: %p\n", " vtable", vtbl);
        printf("%-20s: %p\n", " vtable[0]", vtbl_0);
        printf("%-20s: %p\n", " vtable[1]", vtbl_1);
        printf("%-20s: %p\n", " v_func0", v_func0);
        printf("%-20s: %p\n", " v_func1", v_func1);
        v_func0();
        v_func1();
        printf("\n==========\n\n");
    }
};

int main() {
    Point3D p;
    Point3D::DisplayLayout(p);

    Point3D_VPTR pv;
    Point3D_VPTR::DisplayLayout(pv);
}