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

class Cat : public virtual Animal {
public:
    int cute;

    virtual void Climb() { printf("calling Cat::Climb\n"); }

    virtual void Dance() { printf("calling Cat::Dance\n"); }

    static void DisplayLayout(Cat *obj) {
        PRINT_START(Cat);
        PRINT_OFFSET_VPTR("Cat", obj, obj);
        PRINT_OFFSET("Cat", obj, &obj->cute);
        PRINT_OFFSET("Thing", obj, &obj->id);
        PRINT_OFFSET("Animal", obj, &obj->life);
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

class Bear : public virtual Animal{
public:
    int horror;

    virtual void Hug() { printf("calling Bear::Hug\n"); }

    virtual void Dance() { printf("calling Bear::Dance\n"); }

    static void DisplayLayout(Bear *obj) {
        PRINT_START(Bear);
        PRINT_OFFSET_VPTR("Bear", obj, obj);
        PRINT_OFFSET("Bear", obj, &obj->horror);
        PRINT_OFFSET("Thing", obj, &obj->id);
        PRINT_OFFSET("Animal", obj, &obj->life);
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

class Panda : public Cat, public Bear{
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
        PRINT_OFFSET("Cat", obj, &obj->cute);
        PRINT_OFFSET_VPTR("Bear", obj, bear_obj);
        PRINT_OFFSET("Bear", obj, &obj->horror);
        PRINT_OFFSET("Panda", obj, &obj->fat);
        PRINT_OFFSET("Thing", obj, &obj->id);
        PRINT_OFFSET("Animal", obj, &obj->life);

        PRINT_SEPARATOR();

        long *panda_vtable = (long *) *(long *) obj;
        PRINT_VTABLE_START("Panda", panda_vtable);
        PRINT_VTABLE_FUNC("Panda", panda_vtable, 0, "Climb");
        PRINT_VTABLE_FUNC("Panda", panda_vtable, 1, "Dance");
        PRINT_VTABLE_FUNC("Panda", panda_vtable, 2, "Play");
        PRINT_VTABLE_DATA("Panda", panda_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Panda", panda_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Panda", panda_vtable, -3, "VbaseOffset")

        long *cat_vtable = (long *) *(long *) cat_obj;
        PRINT_VTABLE_START("Panda", panda_vtable);
        PRINT_VTABLE_FUNC("Panda::Cat", cat_vtable, 0, "Climb");
        PRINT_VTABLE_FUNC("Panda::Cat", cat_vtable, 1, "Dance");
        PRINT_VTABLE_FUNC("Panda::Cat", cat_vtable, 2, "Play");
        PRINT_VTABLE_DATA("Panda::Cat", cat_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Panda::Cat", cat_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Panda::Cat", cat_vtable, -3, "VbaseOffset")

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

class Mixin {
public:
    int mixin;
};

class Human : public virtual Mixin {
public:
    int iq;
};


class PandaMan : public Cat, public Bear, public Human{
public:
    float fat;

    virtual void Dance() { printf("calling Panda::Dance\n"); }

    virtual void Play() { printf("calling Panda::Play\n"); }

    static void DisplayLayout(PandaMan *obj) {
        Cat *cat_obj = obj;
        Bear *bear_obj = obj;
        Human *human_obj = obj;

        PRINT_START(PandaMan);
        PRINT_OFFSET_VPTR("PandaMan", obj, obj);
        PRINT_OFFSET_VPTR("Cat", obj, cat_obj);
        PRINT_OFFSET("Cat", obj, &obj->cute);
        PRINT_OFFSET_VPTR("Bear", obj, bear_obj);
        PRINT_OFFSET("Bear", obj, &obj->horror);
        PRINT_OFFSET_VPTR("Human", obj, human_obj);
        PRINT_OFFSET("Human", obj, &obj->iq);
        PRINT_OFFSET("Panda", obj, &obj->fat);
        PRINT_OFFSET("Thing", obj, &obj->id);
        PRINT_OFFSET("Animal", obj, &obj->life);
        PRINT_OFFSET("Mixin", obj, &obj->mixin);

        PRINT_SEPARATOR();

        long *panda_vtable = (long *) *(long *) obj;
        PRINT_VTABLE_START("PandaMan", panda_vtable);
        PRINT_VTABLE_FUNC("PandaMan", panda_vtable, 0, "Climb");
        PRINT_VTABLE_FUNC("PandaMan", panda_vtable, 1, "Dance");
        PRINT_VTABLE_FUNC("PandaMan", panda_vtable, 2, "Play");
        PRINT_VTABLE_DATA("PandaMan", panda_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("PandaMan", panda_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("PandaMan", panda_vtable, -3, "VbaseOffset")
        PRINT_VTABLE_DATA("PandaMan", panda_vtable, -4, "VbaseOffset")

        long *cat_vtable = (long *) *(long *) cat_obj;
        PRINT_VTABLE_START("PandaMan::Cat", panda_vtable);
        PRINT_VTABLE_FUNC("PandaMan::Cat", cat_vtable, 0, "Climb");
        PRINT_VTABLE_FUNC("PandaMan::Cat", cat_vtable, 1, "Dance");
        PRINT_VTABLE_FUNC("PandaMan::Cat", cat_vtable, 2, "Play");
        PRINT_VTABLE_DATA("PandaMan::Cat", cat_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("PandaMan::Cat", cat_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("PandaMan::Cat", cat_vtable, -3, "VbaseOffset")

        long *bear_vtable = (long *) *(long *) bear_obj;
        PRINT_VTABLE_START("Panda::Bear", bear_vtable);
        PRINT_VTABLE_FUNC("Panda::Bear", bear_vtable, 0, "Hug");
        PRINT_VTABLE_FUNC("Panda::Bear", bear_vtable, 1, "Dance");
        PRINT_VTABLE_DATA("Panda::Bear", bear_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Panda::Bear", bear_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Panda::Bear", bear_vtable, -3, "VbaseOffset")

        long *human_vtable = (long *) *(long *) human_obj;
        PRINT_VTABLE_START("Panda::Human", human_vtable);
        PRINT_VTABLE_DATA("Panda::Human", human_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Panda::Human", human_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Panda::Human", human_vtable, -3, "VbaseOffset")
        PRINT_END();
    }
};

int main() {
    Thing thing;
    Thing::DisplayLayout(&thing);

    Animal animal;
    Animal::DisplayLayout(&animal);

    Cat cat;
    Cat::DisplayLayout(&cat);

    Bear bear;
    Bear::DisplayLayout(&bear);

    Panda panda;
    Panda::DisplayLayout(&panda);

    PandaMan pandaMan;
    PandaMan::DisplayLayout(&pandaMan);
}