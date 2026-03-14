#include "function.h"

char kname[2][10] = {"A+~F", "P/F"}; // String for grading

int loadData(struct st_class* c[]){
	int count=0;
	FILE* file;

	file=fopen("classes.txt", "r");
	while(!feof(file)){
		c[count] = (struct st_class*)malloc(sizeof(struct st_class));
		int r = fscanf(file, "%d %s %d %d", &(c[count]->code),c[count]->name, &(c[count]->unit), &(c[count]->grading));
		if(r < 4) break;
		count++;
	}
	fclose(file);
	return count;
}

void printAllClasses(struct st_class* c[], int csize){
	for(int i=0; i<csize; i++){
		printf("[%d] %s [credit %d - %s]\n",c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading-1]);
	}
}

void saveAllClasses(struct st_class* c[], int csize){
	FILE* file;
	file = fopen("classes.txt", "w");
	for(int i=0; i<csize; i++){
		fprintf(file, "%d %s %d %d\n",c[i]->code, c[i]->name, c[i]->unit, c[i]->grading);
	}
	fclose(file);	
}

void findClasses(char* name, struct st_class* c[], int csize){
	int count = 0;

	printf("Searching (keyword : %s)\n", name);
	for(int i=0; i<csize; i++){
		if(strstr(c[i]->name, name)){
			printf("[%d] %s [credit %d - %s]\n",c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading-1]);
			count++;
		}
	}
	printf("%d classes found.\n", count);
}

// You must complete these functions.
int addNewClass(struct st_class* c[], int csize){
// Caution : Don't allow the duplicate class code.
// You must complete this function.

	struct st_class* p = (struct st_class*)malloc(sizeof(struct st_class));

    int right = 0;

    while(right == 0) {
        printf(">> code number > ");
	    scanf("%d", &(p->code));

		right = 1;

        for(int i = 0; i < csize; i++) {
            if(p->code == c[i]->code) {
                printf("Code duplicated! Retry.\n");
                right = 0;
				break;
            }
        }
    }
    
	printf(">> class name > ");
	scanf("%s", p->name);
	printf(">> credits > ");
	scanf("%d", &(p->unit));
	printf(">> grading (1: A+~F, 2: P/F) > ");
	scanf("%d", &(p->grading));

	c[csize] = p;
	return csize+1;
}

void editClass(struct st_class* c[], int csize){
	struct st_class* p;

	int code;

	int right = 0;

    while(right == 0) {
        printf(">> Enter a code of class > ");
		scanf("%d", &code);

		right = 1;

		for(int i = 0; i < csize; i++) {
            if(code == c[i]->code) {
				p = c[i];
                printf("> Current: [%d] %s [credits %d - %s]\n", p->code, p->name, p->unit, kname[p->grading-1]);

				printf("> Enter new class name > ");
				scanf("%s", (p->name));
				printf("> Enter new credits > ");
				scanf("%d", &(p->unit));
				printf("> Enter new grading(1:Grade, 2: P/F) > ");
				scanf("%d", &(p->grading));

				printf("> Modified.\n");
				right = 1;
				break;
            }
			else {
				right = 0;
			}
        }

		if (right == 0) {
			printf("No such class.\n");
		}
    }
}


// You must make all these functions.

int applyMyClasses(int my[], int msize, struct st_class* c[], int csize){
	struct st_class* p;
	int code;
	int right = 0;
	int count = 0;

	while(right != 1) {
        if(count == 10) {
            printf("You can no longer apply because you have already applied for 10 courses!\n");
            break;
        }
		printf(">> Enter a class code > ");
		scanf("%d", &code);

		for(int i = 0; i < csize; i++) {
            right = 0;

            for(int j = 0; j < msize + count; j++) {
                if(my[j] == code) {
                    right = 3;
                    break;
                }
            }
            if (right == 3)
                break;

            if(code == c[i]->code) {
				p = c[i];
				my[count] = p->code;
				printf(">> [%d] %s [credit %d - %s]\n", p->code, p->name, p->unit, kname[p->grading-1]);
                count++;

                int index = 3;
				while(index != 1 && index != 2) {
					printf(">> Add more?(1:Yes 2:No) > ");
					scanf("%d", &index);
					if (index == 1) {
						right = 0;
						break;
					}
					else if (index == 2) {
						right = 1;
						break;
					}
					else continue;
				}
                break;
            }
			else right = 2;
        }

		if (right == 2) {
			printf("No such code of class.\n");
		}
        else if (right == 3) {
            printf("The class code is already applied!\n");
        }
	}
	
	return count;
}

void printMyClasses(int my[], int msize, struct st_class* c[], int csize){
	struct st_class* p;
	int sum = 0;

	for(int i = 0; i < msize; i++) {
		for(int j = 0; j < csize; j++) {
			if(c[j]->code == my[i]) {
				p = c[j];
				printf("%d. [%d] %s [credit %d - %s]\n", i + 1, p->code, p->name, p->unit, kname[p->grading-1]);
				sum += p->unit;
			}
		}
		p = NULL;
	}
	printf("All : %d credits\n", sum);
}

void saveMyClass(int my[], int msize, struct st_class* c[], int csize){
	struct st_class* p;
	int sum = 0;
	int grade_sum = 0;
	int pf_sum = 0;

	FILE* file;
	file = fopen("my_classes.txt", "w");

	fprintf(file, "My Classes\n");

	for(int i = 0; i < msize; i++) {
		for(int j = 0; j < csize; j++) {
			if(c[j]->code == my[i]) {
				p = c[j];
				fprintf(file, "%d. [%d] %s [credit %d - %s]\n", i + 1, p->code, p->name, p->unit, kname[p->grading-1]);
				sum += p->unit;
				if(p->grading == 1) grade_sum += p->unit;
				if(p->grading == 2) pf_sum += p->unit;
			}
		}
		p = NULL;
	}
	fprintf(file, "All : %d classes, %d credits (A+~F %d credits, P/F %d credits)\n", msize, sum, grade_sum, pf_sum);

	fclose(file);
}