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
};

void DisplayAnimalLayout(Animal *obj) {
    PRINT_START(Animal);
    PRINT_OFFSET("Animal", obj, &obj->id);
    PRINT_OFFSET("Animal", obj, &obj->life);
    PRINT_OFFSET("Animal", obj, &obj->name);
    PRINT_END();
}

int main() {
    Animal animal;
    DisplayAnimalLayout(&animal);
}
