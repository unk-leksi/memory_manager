#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "os_mem.h"

int main()
{
    memory_manager_t mm;
    setup_memory_manager(&mm);

    int result = mm.create(5, 1);
    result = mm.create_object("obj1"); //1
    result = mm.create_object("obj2"); //1
    result = mm.create_object("obj3"); //1
    result = mm.create_object("ob234"); //1
    result = mm.destroy_object("obj56"); //0
    result = mm.destroy_object("obj2"); //1
    result = mm.create_object("obj2"); //1
    result = mm.link("obj2", "obj1"); //1
    result = mm.link("obj2", "obj3"); //1
    result = mm.link("obj45", "obj1"); //0
    mm.print_objects(); // 4
    mm.print_link_counts();
    result = mm.destroy(); //1

    return 0;
}
