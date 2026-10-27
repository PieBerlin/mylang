#ifndef HASHMAP_H
#define HASHMAP_H 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


#define SIZE 20

struct DataItem {
    char *data;
    int key;
};


int hashCode (char key);
struct DataItem *search(int key);
void insert(int key, char *data);
struct DataItem *delete(struct DataItem *item);
void display();

#endif 
