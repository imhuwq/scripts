#include <stdio.h>
#include <stdlib.h>
#include "helper.h"

inline
int diff(void *a, void *b) { return ((char *) a - (char *) b); }

class Thing {
public:
    int id;

    static void DisplayLayout(Thing *obj) {
        PRINT_START(Thing);
        PRINT_OFFSET("Thing", obj, &obj->id);
        PRINT_END();
    }
};

class Material : public Thing {
public:
    float quality;

    static void DisplayLayout(Material *obj) {
        PRINT_START(Material);
        PRINT_OFFSET("Thing", obj, &obj->id);
        PRINT_OFFSET("Material", obj, &obj->quality);
        PRINT_END();
    }
};

class Animal : public Thing {
public:
    float life;

    static void DisplayLayout(Animal *obj) {
        PRINT_START(Animal);
        PRINT_OFFSET("Thing", obj, &obj->id);
        PRINT_OFFSET("Animal", obj, &obj->life);
        PRINT_END();
    }
};

class Cat : public Animal {
public:
    int cute;

    virtual void Climb() { printf("calling Cat::Climb\n"); }

    virtual void Dance() { printf("calling Cat::Dance\n"); }

    static void DisplayLayout(Cat *obj) {
        PRINT_START(Cat);
        PRINT_OFFSET_VPTR("Cat", obj, obj);
        PRINT_OFFSET("Thing", obj, &obj->id);
        PRINT_OFFSET("Animal", obj, &obj->life);
        PRINT_OFFSET("Cat", obj, &obj->cute);
        PRINT_SEPARATOR();

        long *cat_vtable = (long *) *(long *) obj;
        PRINT_VTABLE_START("Cat", cat_vtable);
        PRINT_VTABLE_FUNC("Cat", cat_vtable, 0, "Climb");
        PRINT_VTABLE_FUNC("Cat", cat_vtable, 1, "Dance");
        PRINT_VTABLE_DATA("Cat", cat_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Cat", cat_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Cat", cat_vtable, -3, "VbaseOffset")
        PRINT_END();
    }
};

class Bear : public Animal {
public:
    int horror;

    virtual void Hug() { printf("calling Bear::Hug\n"); }

    virtual void Dance() { printf("calling Bear::Dance\n"); }

    static void DisplayLayout(Bear *obj) {
        PRINT_START(Bear);
        PRINT_OFFSET_VPTR("Bear", obj, obj);
        PRINT_OFFSET("Thing", obj, &obj->id);
        PRINT_OFFSET("Animal", obj, &obj->life);
        PRINT_OFFSET("Bear", obj, &obj->horror);
        PRINT_SEPARATOR();

        long *bear_vtable = (long *) *(long *) obj;
        PRINT_VTABLE_START("Bear", bear_vtable);
        PRINT_VTABLE_FUNC("Bear", bear_vtable, 0, "Hug");
        PRINT_VTABLE_FUNC("Bear", bear_vtable, 1, "Dance");
        PRINT_VTABLE_DATA("Bear", bear_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Bear", bear_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Bear", bear_vtable, -3, "VbaseOffset")
        PRINT_END();
    }
};

class Leopard : public Cat {
public:
    float speed;

    virtual void Climb() { printf("calling Leopard::Climb\n"); }

    virtual void Run() { printf("calling Leopard::Run\n"); }

    static void DisplayLayout(Leopard *obj) {
        PRINT_START(Leopard);
        PRINT_OFFSET_VPTR("Leopard", obj, obj);
        PRINT_OFFSET("Thing", obj, &obj->id);
        PRINT_OFFSET("Animal", obj, &obj->life);
        PRINT_OFFSET("Cat", obj, &obj->cute);
        PRINT_OFFSET("Leopard", obj, &obj->speed);
        PRINT_SEPARATOR();

        long *leopard_vtable = (long *) *(long *) obj;
        PRINT_VTABLE_START("Leopard", leopard_vtable);
        PRINT_VTABLE_FUNC("Leopard", leopard_vtable, 0, "Climb");
        PRINT_VTABLE_FUNC("Leopard", leopard_vtable, 1, "Dance");
        PRINT_VTABLE_FUNC("Leopard", leopard_vtable, 2, "Run");
        PRINT_VTABLE_DATA("Leopard", leopard_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Leopard", leopard_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Leopard", leopard_vtable, -3, "VbaseOffset")
        PRINT_END();
    }

};

class Panda : public Cat, public Bear {
public:
    float fat;

    virtual void Dance() { printf("calling Panda::Dance\n"); }

    virtual void Play() { printf("calling Panda::Play\n"); }

    static void DisplayLayout(Panda *obj) {
        Cat *cat_obj = obj;
        Bear *bear_obj = obj;

        PRINT_START(Panda);
        PRINT_OFFSET_VPTR("Panda", obj, obj);
        PRINT_OFFSET_VPTR("Cat", obj, cat_obj);
        PRINT_OFFSET("Cat", obj, &cat_obj->id);
        PRINT_OFFSET("Cat", obj, &cat_obj->life);
        PRINT_OFFSET("Cat", obj, &obj->cute);
        PRINT_OFFSET_VPTR("Bear", obj, bear_obj);
        PRINT_OFFSET("Bear", obj, &bear_obj->id);
        PRINT_OFFSET("Bear", obj, &bear_obj->life);
        PRINT_OFFSET("Bear", obj, &obj->horror);
        PRINT_OFFSET("Panda", obj, &obj->fat);

        PRINT_SEPARATOR();

        long *panda_vtable = (long *) *(long *) obj;
        PRINT_VTABLE_START("Panda", panda_vtable);
        PRINT_VTABLE_FUNC("Panda", panda_vtable, 0, "Climb");
        PRINT_VTABLE_FUNC("Panda", panda_vtable, 1, "Dance");
        PRINT_VTABLE_FUNC("Panda", panda_vtable, 2, "Play");
        PRINT_VTABLE_DATA("Panda", panda_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Panda", panda_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Panda", panda_vtable, -3, "VbaseOffset")

        long *bear_vtable = (long *) *(long *) bear_obj;
        PRINT_VTABLE_START("Panda::Bear", bear_vtable);
        PRINT_VTABLE_FUNC("Panda::Bear", bear_vtable, 0, "Hug");
        PRINT_VTABLE_FUNC("Panda::Bear", bear_vtable, 1, "Dance");
        PRINT_VTABLE_DATA("Panda::Bear", bear_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Panda::Bear", bear_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Panda::Bear", bear_vtable, -3, "VbaseOffset")
        PRINT_END();

    }
};

int main() {
    Thing thing;
    Thing::DisplayLayout(&thing);

    Material material;
    Material::DisplayLayout(&material);

    Animal animal;
    Animal::DisplayLayout(&animal);

    Cat cat;
    Cat::DisplayLayout(&cat);

    Bear bear;
    Bear::DisplayLayout(&bear);

    Leopard leopard;
    Leopard::DisplayLayout(&leopard);

    Panda panda;
    Panda::DisplayLayout(&panda);
}