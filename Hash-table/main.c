//
//  main.c
//  Hash-Table-implement
//
//  Created by Giang Tran on 7/16/22.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define TABLE_SIZE 10
#define DELETED_NODE (Student*) (0xFFFFFFFFFFFFFFUL)

typedef struct student {
    char* name;
    char* euid;
    int group;
    
}Student;

Student* hash_table[TABLE_SIZE];

unsigned int hash(char* name) {
//    int hash = 0;
//    while (*name) {
//        hash += (*name);
//        name++;
//    }
//    return hash % TABLE_SIZE;
    int val = 0;
    unsigned long length = strlen(name);
    for (int i = 0; i < length; i++) {
        val += name[i];
    }
    return val % TABLE_SIZE;
}


void init_hash_table() {
    for (int i = 0; i < TABLE_SIZE;i++) {
        hash_table[i] = NULL; //table is empty
    }
}

//void load_table() {
//    FILE* inputF;
//
//    if ((inputF = fopen("data.txt", "r")) == NULL) {
//        printf("fail to open input file\n");
//    }
//}

void print_table(){
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] == NULL){
            printf("\t%d\t---\n",i);
        }
        else {
            printf("\t%d\t%s\n", i, hash_table[i]->name);
        }
    }
}

bool hash_table_insert(Student* student) {
    if (student == NULL) return false;
    int index = hash(student->name);
    
    //try a new approach to create a more efficient hash table
    for (int i = 0; i < TABLE_SIZE; i++) {
        int try = (i + index) % TABLE_SIZE;
        if (hash_table[try] == NULL || hash_table[try] == DELETED_NODE) {
            hash_table[try] = student;
            return true;
        }
    }
//    if (hash_table[index] != NULL) {
//        return false;
//    }
//    hash_table[index] = student;
    return false;
}


 //find a person in the table by their name
Student* hash_table_lookup(char* name) {
    int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int try = (index + i) % TABLE_SIZE;
        if (hash_table[try] == NULL) {
            return false;
        }
        if (hash_table[try] == DELETED_NODE) continue;
        if (strncmp(hash_table[try]->name, name, TABLE_SIZE) == 0) {
            return hash_table[try];
        }
    }
    return NULL;
}

//Student* hash_table_delete(char* name) {
//    int index = hash(name);
//    if (hash_table[index] != NULL && strncmp(hash_table[index]->name, name, TABLE_SIZE) == 0){
//        Student* tmp = hash_table[index];
//        hash_table[index] = NULL;
//        return tmp;
//    }
//    else {
//        return NULL;
//    }
//}

Student* hash_table_delete(char* name) {
    int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int try = (index + i) % TABLE_SIZE;
        if (hash_table[try] == NULL) return NULL;
        if (hash_table[try] == DELETED_NODE) continue;
        if (strncmp(hash_table[try]->name, name, TABLE_SIZE) == 0) {
            Student* tmp = hash_table[try];
            hash_table[try] = DELETED_NODE;
            return tmp;
        }
    }
    return NULL;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    init_hash_table();
    
    
    Student jacob = {.name = "Jacob", .euid = "jcc0032", .group = 4};
    Student lizzy = {.name = "Lizzy", .euid = "jss0035", .group = 2};
    Student lincy = {.name = "Lincy", .euid = "lkk0022", .group = 2};
    Student ben = {.name = "Ben", .euid = "btt2932", .group = 1};
    hash_table_insert(&jacob);
    hash_table_insert(&lizzy);
    hash_table_insert(&lincy);
    hash_table_insert(&ben);

    
//    Student *tmp = hash_table_lookup("George");
    print_table();

//    if(tmp == NULL) {
//        printf("Not found!\n");
//    }
//    else {
//        printf("Found %s.\n", tmp->name);
//    }
    
//    hash_table_delete("Lizzy");
    Student *tmp = hash_table_lookup("Lizzy");
    if(tmp == NULL) {
        printf("Not found!\n");
    }
    else {
        printf("Found %s.\n", tmp->name);
    }
    print_table();
    
    return 0;
}
