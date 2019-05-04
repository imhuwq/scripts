#include <stdio.h>
#include <stdlib.h>
#include "helper.h"

class Animal {
public:
    int id;
    float life;
    char *name;

    int get_id() { return id; }

    void set_id(int id_) { id = id_; }

    virtual void dance() { printf("Calling Animal::dance...\n"); }

    static void DisplayLayout(Animal *obj) {
        PRINT_START(Animal);
        PRINT_OFFSET_VPTR("Animal", obj, obj);
        PRINT_OFFSET("Animal", obj, &obj->id);
        PRINT_OFFSET("Animal", obj, &obj->life);
        PRINT_OFFSET("Animal", obj, &obj->name);

        long *animal_vtable = (long *) *(long *) obj;
        PRINT_VTABLE_START("Animal", animal_vtable);
        PRINT_VTABLE_FUNC("Animal", animal_vtable, 0, "dance");
        PRINT_END();
    }
};

class Cat : public virtual Animal {
public:
    int cute;

    virtual void climb() { printf("Calling Cat::climb...\n"); }

    virtual void dance() { printf("Calling Cat::dance...\n"); }

    static void DisplayLayout(Cat *obj) {
        Animal* animal_obj = obj;
        PRINT_START(Cat);
        PRINT_OFFSET_VPTR("Cat", obj, obj);
        PRINT_OFFSET("Cat", obj, &obj->cute);
        PRINT_OFFSET_VPTR("Animal", obj, animal_obj);
        PRINT_OFFSET("Animal", obj, &obj->id);
        PRINT_OFFSET("Animal", obj, &obj->life);
        PRINT_OFFSET("Animal", obj, &obj->name);

        long *cat_vtable = (long *) *(long *) obj;
        PRINT_VTABLE_START("Cat", cat_vtable);
        PRINT_VTABLE_FUNC("Cat", cat_vtable, 0, "climb");
        PRINT_VTABLE_FUNC("Cat", cat_vtable, 1, "dance");
        PRINT_VTABLE_DATA("Cat", cat_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Cat", cat_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Cat", cat_vtable, -3, "VbaseOffset")

        long *animal_vtable = (long *) *(long *) animal_obj;
        PRINT_VTABLE_START("Cat::Animal", animal_vtable);
        PRINT_VTABLE_FUNC("Cat::Animal", animal_vtable, 0, "Dance");
        PRINT_VTABLE_DATA("Cat::Animal", animal_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Cat::Animal", animal_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Cat::Animal", animal_vtable, -3, "VbaseOffset")

        PRINT_END();
    }
};

class Bear : public virtual Animal {
public:
    int horror;

    virtual void hug() { printf("Calling Bear::hug...\n"); }

    virtual void dance() { printf("Calling Bear::dance...\n"); }

    static void DisplayLayout(Bear *obj) {
        Animal* animal_obj = obj;
        PRINT_START(Bear);
        PRINT_OFFSET_VPTR("Bear", obj, obj);
        PRINT_OFFSET("Bear", obj, &obj->horror);
        PRINT_OFFSET_VPTR("Animal", obj, animal_obj);
        PRINT_OFFSET("Animal", obj, &obj->id);
        PRINT_OFFSET("Animal", obj, &obj->life);
        PRINT_OFFSET("Animal", obj, &obj->name);

        long *bear_vtable = (long *) *(long *) obj;
        PRINT_VTABLE_START("Bear", bear_vtable);
        PRINT_VTABLE_FUNC("Bear", bear_vtable, 0, "hug");
        PRINT_VTABLE_FUNC("Bear", bear_vtable, 1, "dance");
        PRINT_VTABLE_DATA("Bear", bear_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Bear", bear_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Bear", bear_vtable, -3, "VbaseOffset")

        long *animal_vtable = (long *) *(long *) animal_obj;
        PRINT_VTABLE_START("Bear::Animal", animal_vtable);
        PRINT_VTABLE_FUNC("Bear::Animal", animal_vtable, 0, "Dance");
        PRINT_VTABLE_DATA("Bear::Animal", animal_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Bear::Animal", animal_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Bear::Animal", animal_vtable, -3, "VbaseOffset")

        PRINT_END();
    }
};

class Panda : public Cat, public Bear {
public:
    float fat;

    virtual void dance() { printf("Calling Panda::dance...\n"); }

    virtual void play() { printf("Calling Panda::play...\n"); }

    static void DisplayLayout(Panda *obj) {
        PRINT_START(Panda);
        Cat *cat_obj = obj;
        Bear *bear_obj = obj;
        Animal* animal_obj = obj;

        PRINT_OFFSET_VPTR("Panda", obj, obj);
        PRINT_OFFSET("Cat", obj, &cat_obj->cute);
        PRINT_OFFSET_VPTR("Bear", obj, bear_obj);
        PRINT_OFFSET("Bear", obj, &bear_obj->horror);
        PRINT_OFFSET("Panda", obj, &obj->fat);
        PRINT_OFFSET_VPTR("Animal", obj, animal_obj);
        PRINT_OFFSET("Animal", obj, &obj->id);
        PRINT_OFFSET("Animal", obj, &obj->life);
        PRINT_OFFSET("Animal", obj, &obj->name);

        long *panda_vtable = (long *) *(long *) obj;
        PRINT_VTABLE_START("Panda", panda_vtable);
        PRINT_VTABLE_FUNC("Panda", panda_vtable, 0, "climb");
        PRINT_VTABLE_FUNC("Panda", panda_vtable, 1, "dance");
        PRINT_VTABLE_FUNC("Panda", panda_vtable, 2, "play");
        PRINT_VTABLE_DATA("Panda", panda_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Panda", panda_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Panda", panda_vtable, -3, "VbaseOffset")

        long *cat_vtable = (long *) *(long *) cat_obj;
        PRINT_VTABLE_START("Panda::Cat", cat_vtable);
        PRINT_VTABLE_FUNC("Panda::Cat", cat_vtable, 0, "climb");
        PRINT_VTABLE_FUNC("Panda::Cat", cat_vtable, 1, "dance");
        PRINT_VTABLE_DATA("Panda::Cat", cat_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Panda::Cat", cat_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Panda::Cat", cat_vtable, -3, "VbaseOffset")

        long *bear_vtable = (long *) *(long *) bear_obj;
        PRINT_VTABLE_START("Panda::Bea", bear_vtable);
        PRINT_VTABLE_FUNC("Panda::Bea", bear_vtable, 0, "hug");
        PRINT_VTABLE_FUNC("Panda::Bea", bear_vtable, 1, "dance");
        PRINT_VTABLE_DATA("Panda::Bear", bear_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Panda::Bear", bear_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Panda::Bear", bear_vtable, -3, "VbaseOffset")

        long *animal_vtable = (long *) *(long *) animal_obj;
        PRINT_VTABLE_START("Panda::Animal", animal_vtable);
        PRINT_VTABLE_FUNC("Panda::Animal", animal_vtable, 0, "dance");
        PRINT_VTABLE_DATA("Panda::Animal", animal_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Panda::Animal", animal_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Panda::Animal", animal_vtable, -3, "VbaseOffset")

        PRINT_END();
    }
};

int main() {
    Animal animal;
    Animal::DisplayLayout(&animal);

    Cat cat;
    Cat::DisplayLayout(&cat);

    Bear bear;
    Bear::DisplayLayout(&bear);

    Panda panda;
    Panda::DisplayLayout(&panda);
}
