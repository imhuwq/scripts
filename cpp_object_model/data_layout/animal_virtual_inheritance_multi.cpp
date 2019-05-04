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
        Animal *animal_obj = obj;
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
        PRINT_VTABLE_START("Cat", animal_vtable);
        PRINT_VTABLE_FUNC("Cat", animal_vtable, 0, "Dance");
        PRINT_VTABLE_DATA("Cat", animal_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Cat", animal_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Cat", animal_vtable, -3, "VbaseOffset")

        PRINT_END();
    }
};

class Bear : public virtual Animal {
public:
    int horror;

    virtual void hug() { printf("Calling Bear::hug...\n"); }

    virtual void dance() { printf("Calling Bear::dance...\n"); }

    static void DisplayLayout(Bear *obj) {
        Animal *animal_obj = obj;
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
        PRINT_VTABLE_START("Bear", animal_vtable);
        PRINT_VTABLE_FUNC("Bear", animal_vtable, 0, "Dance");
        PRINT_VTABLE_DATA("Bear", animal_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Bear", animal_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Bear", animal_vtable, -3, "VbaseOffset")

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
        Animal *animal_obj = obj;

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
        PRINT_VTABLE_START("Cat", cat_vtable);
        PRINT_VTABLE_FUNC("Cat", cat_vtable, 0, "climb");
        PRINT_VTABLE_FUNC("Cat", cat_vtable, 1, "dance");
        PRINT_VTABLE_DATA("Cat", cat_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Cat", cat_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Cat", cat_vtable, -3, "VbaseOffset")

        long *bear_vtable = (long *) *(long *) bear_obj;
        PRINT_VTABLE_START("Bear", bear_vtable);
        PRINT_VTABLE_FUNC("Bear", bear_vtable, 0, "hug");
        PRINT_VTABLE_FUNC("Bear", bear_vtable, 1, "dance");
        PRINT_VTABLE_DATA("Bear", bear_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Bear", bear_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Bear", bear_vtable, -3, "VbaseOffset")

        long *animal_vtable = (long *) *(long *) animal_obj;
        PRINT_VTABLE_START("Animal", animal_vtable);
        PRINT_VTABLE_FUNC("Animal", animal_vtable, 0, "dance");
        PRINT_VTABLE_DATA("Animal", animal_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Animal", animal_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Animal", animal_vtable, -3, "VbaseOffset")

        PRINT_END();
    }
};

class MixIn {
public:
    int mixin;
};

class Human : virtual public MixIn {
public:
    int iq;

    virtual void speak() { printf("Calling Human::speak...\n"); }

    virtual void think() { printf("Calling Human::think...\n"); }
};

class PandaMan : public Panda, public Human {
public:
    int level;

    virtual void upgrade() { printf("Calling PandaMan::upgrade...\n"); }

    static void DisplayLayout(PandaMan *obj) {
        Panda * panda_obj = obj;
        Cat *cat_obj = obj;
        Bear *bear_obj = obj;
        Animal *animal_obj = obj;
        Human* human_obj = obj;
        MixIn* mixin_obj = obj;

        PRINT_START(PandaMan);
        PRINT_OFFSET_VPTR("PandaMan", obj, obj);
        PRINT_OFFSET_VPTR("Panda", obj, panda_obj);
        PRINT_OFFSET_VPTR("Cat", obj, cat_obj);
        PRINT_OFFSET("Cat", obj, &cat_obj->cute);
        PRINT_OFFSET_VPTR("Bear", obj, bear_obj);
        PRINT_OFFSET("Bear", obj, &bear_obj->horror);
        PRINT_OFFSET("Panda", obj, &panda_obj->fat);
        PRINT_OFFSET_VPTR("Human", obj, human_obj);
        PRINT_OFFSET("Human", obj, &human_obj->iq);
        PRINT_OFFSET_VPTR("Animal", obj, animal_obj);
        PRINT_OFFSET("Animal", obj, &animal_obj->id);
        PRINT_OFFSET("Animal", obj, &animal_obj->life);
        PRINT_OFFSET("Animal", obj, &animal_obj->name);
        PRINT_OFFSET("MixIn", obj, &mixin_obj->mixin);

        long *panda_man_vtable = (long *) *(long *) obj;
        PRINT_VTABLE_START("PandaMan", panda_man_vtable);
        PRINT_VTABLE_FUNC("PandaMan", panda_man_vtable, 0, "climb");
        PRINT_VTABLE_FUNC("PandaMan", panda_man_vtable, 1, "dance");
        PRINT_VTABLE_FUNC("PandaMan", panda_man_vtable, 2, "play");
        PRINT_VTABLE_FUNC("PandaMan", panda_man_vtable, 3, "upgrade");
        PRINT_VTABLE_DATA("PandaMan", panda_man_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("PandaMan", panda_man_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("PandaMan", panda_man_vtable, -3, "VbaseOffset")
        PRINT_VTABLE_DATA("PandaMan", panda_man_vtable, -4, "VbaseOffset")

        long *panda_vtable = (long *) *(long *) panda_obj;
        PRINT_VTABLE_START("Panda", panda_vtable);
        PRINT_VTABLE_FUNC("Panda", panda_vtable, 0, "climb");
        PRINT_VTABLE_FUNC("Panda", panda_vtable, 1, "dance");
        PRINT_VTABLE_FUNC("Panda", panda_vtable, 2, "play");
        PRINT_VTABLE_DATA("Panda", panda_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Panda", panda_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Panda", panda_vtable, -3, "VbaseOffset")

        long *cat_vtable = (long *) *(long *) cat_obj;
        PRINT_VTABLE_START("Cat", cat_vtable);
        PRINT_VTABLE_FUNC("Cat", cat_vtable, 0, "climb");
        PRINT_VTABLE_FUNC("Panda", cat_vtable, 1, "dance");
        PRINT_VTABLE_DATA("Panda::Cat", cat_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Panda::Cat", cat_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Panda::Cat", cat_vtable, -3, "VbaseOffset")

        long *bear_vtable = (long *) *(long *) bear_obj;
        PRINT_VTABLE_START("Bear", bear_vtable);
        PRINT_VTABLE_FUNC("Bear", bear_vtable, 0, "hug");
        PRINT_VTABLE_FUNC("Panda", bear_vtable, 1, "dance");
        PRINT_VTABLE_DATA("Panda::Bear", bear_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Panda::Bear", bear_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Panda::Bear", bear_vtable, -3, "VbaseOffset")

        long *animal_vtable = (long *) *(long *) animal_obj;
        PRINT_VTABLE_START("Animal", animal_vtable);
        PRINT_VTABLE_FUNC("Animal", animal_vtable, 0, "dance");
        PRINT_VTABLE_DATA("Animal", animal_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Animal", animal_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Animal", animal_vtable, -3, "VbaseOffset")

        long *human_vtable = (long *) *(long *) human_obj;
        PRINT_VTABLE_START("Human", human_vtable);
        PRINT_VTABLE_FUNC("Human", human_vtable, 0, "speak");
        PRINT_VTABLE_FUNC("Human", human_vtable, 1, "think");
        PRINT_VTABLE_DATA("Human", human_vtable, -1, "TypeInfo")
        PRINT_VTABLE_DATA("Human", human_vtable, -2, "TopOffset")
        PRINT_VTABLE_DATA("Human", human_vtable, -3, "VbaseOffset")

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

    PandaMan pandaMan;
    PandaMan::DisplayLayout(&pandaMan);
}
