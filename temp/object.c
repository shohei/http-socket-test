#include <stdio.h>
#include <string.h>

typedef struct Person{
    char name[20];
    int age;
} Person;

typedef struct Meibo{
    Person people[10];
} Meibo;

void makePerson(Person *p, char *name, int age){
    sprintf(p->name,"shohei");
    p->age = 28;
}

void addMeibo(Meibo *m,Person* people){
    for(int i=0;i<sizeof(Person)/sizeof(people);i++){
        m->people[i] = people[i];
    }
};

int main(int argc, char **argv){
    Person shohei = {"shohei",28};
    Person john = {"john",25};
    Person matt = {"matt",20};
    Person people[] = {shohei,john,matt};

    Meibo m;
    memset(&m,'\0',sizeof(m));
    addMeibo(&m,people);

    //show
    for(int i=0;i<sizeof(m.people)/sizeof(Person);i++){
        printf("Person %d\n",i);
        printf("    name: %s\n",m.people[i].name);
        printf("    age: %d\n",m.people[i].age);
    }

    return 0;
}
