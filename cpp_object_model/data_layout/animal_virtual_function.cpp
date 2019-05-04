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

    virtual void eat() { printf("Calling Animal::eat...\n"); }

    static void DisplayLayout(Animal *obj) {
        PRINT_START(Animal);
        PRINT_OFFSET_VPTR("Animal", obj, obj);
        PRINT_OFFSET("Animal", obj, &obj->id);
        PRINT_OFFSET("Animal", obj, &obj->life);
        PRINT_OFFSET("Animal", obj, &obj->name);

        long *animal_vtable = (long *) *(long *) obj;
        PRINT_VTABLE_START("Animal", animal_vtable);
        PRINT_VTABLE_FUNC("Animal", animal_vtable, 0, "dance");
        PRINT_VTABLE_FUNC("Animal", animal_vtable, 1, "eat");
        PRINT_END();
    }
};

class Cat : public Animal {
public:
    int cute;

    virtual void climb() { printf("Calling Cat::climb...\n"); }

    virtual void dance() { printf("Calling Cat::dance...\n"); }

    static void DisplayLayout(Cat *obj) {
        PRINT_START(Cat);
        PRINT_OFFSET_VPTR("Cat", obj, obj);
        PRINT_OFFSET("Animal", obj, &obj->id);
        PRINT_OFFSET("Animal", obj, &obj->life);
        PRINT_OFFSET("Animal", obj, &obj->name);
        PRINT_OFFSET("Cat", obj, &obj->cute);

        long *cat_vtable = (long *) *(long *) obj;
        PRINT_VTABLE_START("Cat", cat_vtable);
        PRINT_VTABLE_FUNC("Cat", cat_vtable, 0, "dance");
        PRINT_VTABLE_FUNC("Animal", cat_vtable, 1, "eat");
        PRINT_VTABLE_FUNC("Cat", cat_vtable, 2, "climb");

        PRINT_END();
    }
};

class Bear : public Animal {
public:
    int horror;

    virtual void hug() { printf("Calling Bear::hug...\n"); }

    virtual void dance() { printf("Calling Bear::dance...\n"); }

    static void DisplayLayout(Bear *obj) {
        PRINT_START(Bear);
        PRINT_OFFSET_VPTR("Bear", obj, obj);
        PRINT_OFFSET("Animal", obj, &obj->id);
        PRINT_OFFSET("Animal", obj, &obj->life);
        PRINT_OFFSET("Animal", obj, &obj->name);
        PRINT_OFFSET("Bear", obj, &obj->horror);

        long *bear_vtable = (long *) *(long *) obj;
        PRINT_VTABLE_START("Bear", bear_vtable);
        PRINT_VTABLE_FUNC("Bear", bear_vtable, 0, "dance");
        PRINT_VTABLE_FUNC("Animal", bear_vtable, 1, "eat");
        PRINT_VTABLE_FUNC("Bear", bear_vtable, 2, "hug");

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
        PRINT_OFFSET_VPTR("Panda", obj, obj);
        PRINT_OFFSET("Cat::Animal", obj, &cat_obj->id);
        PRINT_OFFSET("Cat::Animal", obj, &cat_obj->life);
        PRINT_OFFSET("Cat::Animal", obj, &cat_obj->name);
        PRINT_OFFSET("Cat", obj, &cat_obj->cute);
        PRINT_OFFSET_VPTR("Panda::Bear", obj, bear_obj);
        PRINT_OFFSET("Bear::Animal", obj, &bear_obj->id);
        PRINT_OFFSET("Bear::Animal", obj, &bear_obj->life);
        PRINT_OFFSET("Bear::Animal", obj, &bear_obj->name);
        PRINT_OFFSET("Bear", obj, &bear_obj->horror);
        PRINT_OFFSET("Panda", obj, &obj->fat);

        long *panda_vtable = (long *) *(long *) obj;
        PRINT_VTABLE_START("Panda", panda_vtable);
        PRINT_VTABLE_FUNC("Panda", panda_vtable, 0, "dance");
        PRINT_VTABLE_FUNC("Animal", panda_vtable, 1, "eat");
        PRINT_VTABLE_FUNC("Cat", panda_vtable, 2, "climb");
        PRINT_VTABLE_FUNC("Panda", panda_vtable, 3, "play");

        long *cat_vtable = (long *) *(long *) cat_obj;
        PRINT_VTABLE_START("Panda::Cat", cat_vtable);
        PRINT_VTABLE_FUNC("Bear", cat_vtable, 0, "dance");
        PRINT_VTABLE_FUNC("Animal", cat_vtable, 1, "eat");
        PRINT_VTABLE_FUNC("Cat", cat_vtable, 2, "climb");

        long *bear_vtable = (long *) *(long *) bear_obj;
        PRINT_VTABLE_START("Panda::Bear", bear_vtable);
        PRINT_VTABLE_FUNC("Bear", bear_vtable, 0, "dance");
        PRINT_VTABLE_FUNC("Animal", bear_vtable, 1, "eat");
        PRINT_VTABLE_FUNC("Bear", bear_vtable, 2, "hug");

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
