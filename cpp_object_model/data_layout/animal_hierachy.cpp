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

    static void DisplayLayout(Animal *obj) {
        PRINT_START(Animal);
        PRINT_OFFSET("Animal", obj, &obj->id);
        PRINT_OFFSET("Animal", obj, &obj->life);
        PRINT_OFFSET("Animal", obj, &obj->name);
        PRINT_END();
    }
};

class Cat : public Animal {
public:
    int cute;

    void climb() { printf("Calling Cat::climb...\n"); }

    void dance() { printf("Calling Cat::dance...\n"); }

    static void DisplayLayout(Cat *obj) {
        PRINT_START(Cat);
        PRINT_OFFSET("Animal", obj, &obj->id);
        PRINT_OFFSET("Animal", obj, &obj->life);
        PRINT_OFFSET("Animal", obj, &obj->name);
        PRINT_OFFSET("Cat", obj, &obj->cute);
        PRINT_END();
    }
};

class Bear : public Animal {
public:
    int horror;

    void hug() { printf("Calling Bear::hug...\n"); }

    void dance() { printf("Calling Bear::dance...\n"); }

    static void DisplayLayout(Bear *obj) {
        PRINT_START(Bear);
        PRINT_OFFSET("Animal", obj, &obj->id);
        PRINT_OFFSET("Animal", obj, &obj->life);
        PRINT_OFFSET("Animal", obj, &obj->name);
        PRINT_OFFSET("Bear", obj, &obj->horror);
        PRINT_END();
    }
};

class Panda : public Cat, public Bear {
public:
    float fat;

    void dance() { printf("Calling Panda::dance...\n"); }

    void play() { printf("Calling Panda::play...\n"); }

    static void DisplayLayout(Panda *obj) {
        PRINT_START(Panda);
        Cat *cat_obj = obj;
        Bear *bear_obj = obj;
        PRINT_OFFSET("Cat::Animal", obj, &cat_obj->id);
        PRINT_OFFSET("Cat::Animal", obj, &cat_obj->life);
        PRINT_OFFSET("Cat::Animal", obj, &cat_obj->name);
        PRINT_OFFSET("Cat", obj, &cat_obj->cute);
        PRINT_OFFSET("Bear::Animal", obj, &bear_obj->id);
        PRINT_OFFSET("Bear::Animal", obj, &bear_obj->life);
        PRINT_OFFSET("Bear::Animal", obj, &bear_obj->name);
        PRINT_OFFSET("Bear", obj, &bear_obj->horror);
        PRINT_OFFSET("Panda", obj, &obj->fat);
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
