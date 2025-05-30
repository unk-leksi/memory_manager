#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "os_mem.h"
#pragma warning(disable:4996)

typedef struct frame_obj
{
    char* name_obj;
    frame_obj** out_obj_reference;
    int count_out_references;
    int count_enter_ref;
}frame_obj;

int size_obj = 0;
int tmp_size = 0;
int number_object = -1;
frame_obj** array_of_names_obj = NULL;

int my_create(int size, int num_pages) 
{
    if (size < 0 || number_object >= 0) 
    {
        return 0;
    }
    array_of_names_obj = (frame_obj**)malloc(sizeof(frame_obj*) * size);
    size_obj = size;
    number_object = 0;
    return 1;
}

int my_destroy() 
{
    if (size_obj == 0 || number_object == -1) {
        return 0;
    }
    for (int i = 0; i < number_object; i++) {
        if (array_of_names_obj[i]->count_out_references > 0) {
            free(array_of_names_obj[i]->out_obj_reference);
        }
        free(array_of_names_obj[i]->name_obj);
        free(array_of_names_obj[i]);
    }
    free(array_of_names_obj);
    array_of_names_obj = NULL;
    number_object = -1;
    size_obj = 0;
    return 1;
}

int my_create_object(const char* name) 
{
    if (number_object == size_obj)
    {
        return 0;
    }
    if (strlen(name) > 32)
    {
        return 0;
    }
    for (int i = 0; i < number_object; i++)
    {
        if (strcmp(name, array_of_names_obj[i]->name_obj) == 0) 
        {
            return 0;
        }
    }

    frame_obj* new_obj = (frame_obj*)malloc(sizeof(frame_obj));
    if (new_obj)
    {
        new_obj->name_obj = (char*)malloc(sizeof(char) * 33);
        strcpy(new_obj->name_obj, name);
        new_obj->out_obj_reference = NULL;
        new_obj->count_out_references = 0;
        new_obj->count_enter_ref = 0;
        number_object++;
        if (tmp_size < number_object) {
            tmp_size = number_object * 2;
            frame_obj** check_array = (frame_obj**)realloc(array_of_names_obj, sizeof(frame_obj*) * tmp_size);
            if (check_array) {
                array_of_names_obj = check_array;
            }
            else {
                return 0;
            }
        } 
        array_of_names_obj[number_object - 1] = new_obj;
        return 1;
    }
    return 0;
}

int my_destroy_object(const char* name)
{
    if (number_object <= 0) {
        return 0;
    }

    for (int i = 0; i < number_object; i++) {
        if (strcmp(name, array_of_names_obj[i]->name_obj) == 0) {
            for (int j = 0; j < array_of_names_obj[i]->count_out_references; j++) {
                for (int m = 0; m < array_of_names_obj[i]->out_obj_reference[j]->count_out_references; m++) {
                    if (strcmp(array_of_names_obj[i]->out_obj_reference[j]->out_obj_reference[m]->name_obj, name) == 0) {
                        if (m == array_of_names_obj[i]->out_obj_reference[j]->count_out_references - 1) {
                            array_of_names_obj[i]->out_obj_reference[j]->count_out_references--;
                        }
                        else {
                            frame_obj* time_tmp = NULL;
                            time_tmp = array_of_names_obj[i]->out_obj_reference[j]->out_obj_reference[m];
                            array_of_names_obj[i]->out_obj_reference[j]->out_obj_reference[m] = array_of_names_obj[i]->out_obj_reference[j]->out_obj_reference[array_of_names_obj[i]->out_obj_reference[j]->count_out_references - 1];
                            array_of_names_obj[i]->out_obj_reference[j]->out_obj_reference[array_of_names_obj[i]->out_obj_reference[j]->count_out_references - 1] = time_tmp;
                            array_of_names_obj[i]->out_obj_reference[j]->count_out_references--;
                        }
                    }
                }
    
            }
        }
    }

    for (int l = 0; l < number_object; l++) {
        if (strcmp(name, array_of_names_obj[l]->name_obj) == 0) {
            if (array_of_names_obj[l]->count_out_references > 0) {
                for (int i = 0; i < array_of_names_obj[l]->count_out_references; i++) {
                    if (array_of_names_obj[l]->out_obj_reference[i]->count_enter_ref > 0) {
                        array_of_names_obj[l]->out_obj_reference[i]->count_enter_ref--;
                    }
                }
            }
            free(array_of_names_obj[l]->out_obj_reference);
            array_of_names_obj[l]->count_out_references = 0;
            free(array_of_names_obj[l]->name_obj);
            if (l == number_object - 1) {
                free(array_of_names_obj[l]);
                number_object--;
            }
            else {
                frame_obj* time_tmp = NULL;
                time_tmp = array_of_names_obj[l];
                array_of_names_obj[l] = array_of_names_obj[number_object - 1];
                array_of_names_obj[number_object - 1] = time_tmp;
                free(array_of_names_obj[number_object - 1]);
                number_object--;
            }
            return 1;
        }
        if (l == number_object - 1) {
            return 0;
        }
    }
    return 0;
}

void my_print_objects() 
{
    if (number_object <= 0) {
        return;
    }
    frame_obj* tmp = NULL;
    for (int i = 0; i < number_object; i++) {
        for (int j = 0; j < number_object - i - 1; j++) {
            if (strcmp(array_of_names_obj[j]->name_obj, array_of_names_obj[j + 1]->name_obj) > 0) {
                tmp = array_of_names_obj[j];
                array_of_names_obj[j] = array_of_names_obj[j + 1];
                array_of_names_obj[j + 1] = tmp;
            }
        }
    }

    for (int i = 0; i < number_object; i++) {
        printf("%s\n", array_of_names_obj[i]->name_obj);
    }
}

int my_link(const char* object1_name, const char* object2_name)
{
    frame_obj* cur_obj1 = NULL;
    frame_obj* cur_obj2 = NULL;
    if (number_object <= 0) {
        return 0;
    }
    for (int i = 0; i < number_object; i++)
    {
        if (strcmp(object1_name, array_of_names_obj[i]->name_obj) == 0)
        {
            cur_obj1 = array_of_names_obj[i];
            break;
        }
        else if (i == number_object - 1) {
            return 0;
        }
    }
    for (int i = 0; i < number_object; i++)
    {
        if (strcmp(object2_name, array_of_names_obj[i]->name_obj) == 0)
        {
            cur_obj2 = array_of_names_obj[i];
            break;
        }
        else if (i == number_object - 1) {
            return 0;
        }
    }

    if (cur_obj1->count_out_references >= 16)
    {
        return 0;
    }
    for (int i = 0; i < cur_obj1->count_out_references; i++) {
        if (strcmp(cur_obj1->out_obj_reference[i]->name_obj, cur_obj2->name_obj) == 0) {
            return 0;
        }
    }
    cur_obj1->count_out_references++;
    if (cur_obj1->count_out_references == 1) {
        cur_obj1->out_obj_reference = (frame_obj**)malloc(sizeof(frame_obj*) * 16);
    }
    cur_obj1->out_obj_reference[cur_obj1->count_out_references - 1] = cur_obj2;
    cur_obj2->count_enter_ref++;

    return 1;
}

void my_print_link_counts()
{
    if (number_object <= 0) {
        return;
    }
    frame_obj* tmp = NULL;
    for (int i = 0; i < number_object; i++) {
        for (int j = 0; j < number_object - i - 1; j++) {
            if (strcmp(array_of_names_obj[j]->name_obj, array_of_names_obj[j + 1]->name_obj) > 0) {
                tmp = array_of_names_obj[j];
                array_of_names_obj[j] = array_of_names_obj[j + 1];
                array_of_names_obj[j + 1] = tmp;
            }
        }
    }

    for (int i = 0; i < number_object; ++i) {
        printf("%s %d\n", array_of_names_obj[i]->name_obj, array_of_names_obj[i]->count_enter_ref);
    }
}

void setup_memory_manager(memory_manager_t* mm)
{
    mm->create = my_create;
    mm->destroy = my_destroy;
    mm->create_object = my_create_object;
    mm->destroy_object = my_destroy_object;
    mm->print_objects = my_print_objects;
    mm->link = my_link;
    mm->print_link_counts = my_print_link_counts;
}
