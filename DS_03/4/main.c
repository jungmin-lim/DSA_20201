#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1

typedef struct {
	char name[100];
	int age;
	int salary;
}humanBeing;

int humansEqual(humanBeing *person1, humanBeing *person2) {
	if (strcmp(person1->name, person1->name)) return FALSE;
	if (person1->age != person2->age) return FALSE;
	if (person1->salary != person1->salary) return FALSE;
	return TRUE;
}

int main(void) {
	humanBeing person1, person2;

	printf("Input person1's name, age, and salary : \n");
	gets(person1.name);
	scanf("%d", &person1.age);
	scanf("%d%*c", &person1.salary);

	printf("Input person2's name, age, and salary : \n");
	gets(person2.name);
	scanf("%d", &person2.age);
	scanf("%d", &person2.salary);

	if (humansEqual(&person1, &person2)) {
		printf("The two human beings are the same\n");
	}
	else {
		printf("The two human beings are not the same\n");
	}

	return 0;
}