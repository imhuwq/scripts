#include <stdio.h>
#include <stdlib.h>

inline
int diff(void *a, void *b) { return ((char *) a - (char *) b); }

class Thing {
public:
    float id;

    static void DisplayLayout(Thing &thing) {
        printf("Layout of Thing:\n");
        printf("%-20s: %03d\n", "Size", sizeof(Thing));
        printf("%-20s: %03d\n", "Offset", 0);
        printf("%-20s: %03d\n", " Thing id", &Thing::id);
        printf("%-20s: %p\n", "Address", &thing);
        printf("%-20s: %p(+%02d)\n", " Thing id", &thing.id, diff(&thing.id, &thing));
        printf("\n==========\n\n");
    }
};

class Material: public Thing {
public:
    float color;

    static void DisplayLayout(Material &material) {
        printf("Layout of Material:\n");
        printf("%-20s: %03d\n", "Size", sizeof(Material));
        printf("%-20s: %03d\n", "Offset", 0);
        printf("%-20s: %03d\n", " Thing id", &Material::id);
        printf("%-20s: %03d\n", " Material Color", &Material::color);
        printf("%-20s: %p\n", "Address", &material);
        printf("%-20s: %p(+%02d)\n", " Thing id", &material.id, diff(&material.id, &material));
        printf("%-20s: %p(+%02d)\n", " Material color", &material.color, diff(&material.color, &material));
        printf("\n==========\n\n");
    }
};

class Paper : public virtual Thing {
public:
    float size;

    static void DisplayLayout(Paper &paper) {
        printf("Layout of Paper:\n");
        printf("%-20s: %03d\n", "Size", sizeof(Paper));
        printf("%-20s: %03d\n", "Offset", 0);
        printf("%-20s: %03d\n", " Paper size", &Paper::size);
        printf("%-20s: %03d(Runtime), %03d(Static)\n", " Thing id", diff(&paper.id, &paper), &Paper::id);
        printf("%-20s: %p\n", "Address", &paper);
        printf("%-20s: %p(+%02d)\n", " Paper vptr", &paper, diff(&paper, &paper));
        printf("%-20s: %p(+%02d)\n", " Paper size", &paper.size, diff(&paper.size, &paper));
        printf("%-20s: %p(+%02d)\n", " Thing id", &paper.id, diff(&paper.id, &paper));

        printf("%-20s: %03d\n", "Paper Virtual Table", 0);
        long *vptr = (long *) &paper;
        long *vtbl = (long *) *vptr;
        printf("%-20s: %p\n", " type info", *(vtbl - 1));
        printf("%-20s: %02d\n", " top offset", *(vtbl - 2));
        printf("%-20s: %02d\n", " vbase offset", *(vtbl - 3));

        printf("\n==========\n\n");
    }
};

class Good : public virtual Thing {
public:
    float price;

    static void DisplayLayout(Good &good) {
        printf("Layout of Good:\n");
        printf("%-20s: %03d\n", "Size", sizeof(Good));
        printf("%-20s: %03d\n", "Offset", 0);
        printf("%-20s: %03d\n", " Good price", &Good::price);
        printf("%-20s: %03d(Runtime), %03d(Static)\n", " Thing id", diff(&good.id, &good), &Good::id);
        printf("%-20s: %p\n", "Address", &good);
        printf("%-20s: %p(+%02d)\n", " Good vptr", &good, diff(&good, &good));
        printf("%-20s: %p(+%02d)\n", " Good price", &good.price, diff(&good.price, &good));
        printf("%-20s: %p(+%02d)\n", " Thing id", &good.id, diff(&good.id, &good));

        printf("%-20s: %03d\n", "Good Virtual Table", 0);
        long *vptr = (long *) &good;
        long *vtbl = (long *) *vptr;
        printf("%-20s: %p\n", " type info", *(vtbl - 1));
        printf("%-20s: %02d\n", " top offset", *(vtbl - 2));
        printf("%-20s: %02d\n", " vbase offset", *(vtbl - 3));

        printf("\n==========\n\n");
    }
};

class Book : public virtual Paper, public virtual Good {
public:
    int count;

    static void DisplayLayout(Book &book) {
        printf("Layout of Book:\n");
        printf("%-20s: %03d\n", "Size", sizeof(Book));
        printf("%-20s: %03d\n", "Offset", 0);
        printf("%-20s: %03d\n", " Book count", &Book::count);
        printf("%-20s: %03d(Runtime), %03d(Static)\n", " Paper size", diff(&book.size, &book), &Book::id);
        printf("%-20s: %03d(Runtime), %03d(Static)\n", " Thing id", diff(&book.id, &book), &Book::id);
        printf("%-20s: %03d(Runtime), %03d(Static)\n", " Good price", diff(&book.price, &book), &Book::id);
        printf("%-20s: %p\n", "Address", &book);
        printf("%-20s: %p(+%02d)\n", " Book vptr", &book, diff(&book, &book));
        printf("%-20s: %p(+%02d)\n", " Book count", &book.count, diff(&book.count, &book));
        printf("%-20s: %p(+%02d)\n", " Paper vptr", (long *) (Paper *) &book, diff((long *) (Paper *) &book, &book));
        printf("%-20s: %p(+%02d)\n", " Paper size", &book.size, diff(&book.size, &book));
        printf("%-20s: %p(+%02d)\n", " Thing id", &book.id, diff(&book.id, &book));
        printf("%-20s: %p(+%02d)\n", " Good vptr", (long *) (Good *) &book, diff((long *) (Good *) &book, &book));
        printf("%-20s: %p(+%02d)\n", " Good price", &book.price, diff(&book.price, &book));

        printf("%-20s: %03d\n", "Book Virtual Table", 0);
        long *vptr = (long *) &book;
        long *vtbl = (long *) *vptr;
        printf("%-20s: %p\n", " type info", *(vtbl - 1));
        printf("%-20s: %02d\n", " top offset", *(vtbl - 2));
        printf("%-20s: %02d\n", " vbase offset", *(vtbl - 3));

        printf("%-20s: %03d\n", "Paper Virtual Table", 0);
        vptr = (long *) (Paper *) &book;
        vtbl = (long *) *vptr;
        printf("%-20s: %p\n", " type info", *(vtbl - 1));
        printf("%-20s: %02d\n", " top offset", *(vtbl - 2));
        printf("%-20s: %02d\n", " vbase offset", *(vtbl - 3));

        printf("%-20s: %03d\n", "Good Virtual Table", 0);
        vptr = (long *) (Good *) &book;
        vtbl = (long *) *vptr;
        printf("%-20s: %p\n", " type info", *(vtbl - 1));
        printf("%-20s: %02d\n", " top offset", *(vtbl - 2));
        printf("%-20s: %02d\n", " vbase offset", *(vtbl - 3));

        printf("\n==========\n\n");
    }
};

int main() {
    Thing thing;
    Thing::DisplayLayout(thing);

    Material material;
    Material::DisplayLayout(material);

    Paper paper;
    Paper::DisplayLayout(paper);

    Good good;
    Good::DisplayLayout(good);

    Book book;
    Book::DisplayLayout(book);
}