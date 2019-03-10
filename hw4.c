/*goulias_iwannhs_1785_gkourmpatshs_nikolaos_1791*/

/*auto to programma einai ipeu8ino gia tin diaxeirhsh ergastiriwn, einai ikano na dimiourgei tmhmata ergasthriwn na pros8etei foithtes se ayta na tous antallasei metaksi twn tmimatwn kai na tous diagrafei ka8w kai na tipwnei
 * tin katastasi twn ergastiriwn*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE	30
#define COM_SIZE 20

struct student { 
	char *name;
	int section;
	struct student *next;
};

typedef struct student student_list; 

enum workdays {Mon = 1, Tue, Wed, Thu, Fri};


struct lab_section {
	student_list *head;
	int lab_time;
	enum workdays day;
};

typedef struct lab_section lab_list;

enum message {OFF = 0, ON};

enum message debug;

void list_destroy_rec(student_list *curr); /*anadromiki sinartisi pou apelu8erwnei oli ti dinamika desmeumeni twn listwn kai twn onomatwn mnimi ston termatismo t programmatos*/
void clear_mem(lab_list *array, int section); /*sinartisi pou apeleu8erwnei ti dinamika desmeumeni mnimi kai me ti boi8eia tis list_destroy_rec*/
void delete_student(char *student_name, lab_list *array, int size_array); /*sinartisi pou diagrafei enan foithth me ti  boi8eia tis isolate_student*/
void swap_students(char *student_name_1, char *student_name_2, lab_list *array, int size_array); /*sinartisi pou antallasei foithtes metaksi duo tmhmatwn me ti boi8eia tis isolate_student*/
student_list *isolate_student(lab_list *array,char *student_name, int size_array); /*sinartisi pou apomonwnei enan foithth apo tin lista kai epistrefi ton kombo tou */
void print_names(lab_list *array, int section); /*sinartisi pou tipwnei ta onomata twn foithtwn kai to tmhma sto opoio anhkoun*/
void add_student(lab_list *array, student_list *root, int section); /*sinartisi opou eisagwntai oi foithtes se lista (sto katallilo tmima)*/
lab_list *data_insert(int *section_count);/*apothikeuei ston pinaka kai stis listes ta dedomena*/

int main (int argc, char *argv[]) {
	
	int labs = 0; /*arithmos twn ergastiriwn*/
	lab_list *array;/*o pinakas pou exei to head twn listwn*/
	char formatstring[13];
	char command[COM_SIZE], student1[SIZE], student2[SIZE];
	
	if (!argc) 
		debug = OFF;
	if (argc == 2) {
		if(!(strcmp(argv[1],"-debug") && strcmp(argv[1],"-d"))) /*an do8ei eite -debug eite -d tote debug = ON*/
			debug = ON;
		else {
			if (argv[1][0] != '-'){
				printf("%s: illegal option -- %s\nUsage: hw4 [-d]",argv[0], argv[1]);
				return 0;
			}
			else {
				printf("%s: illegal option -- %s\nUsage: hw4 [-d]",argv[0], argv[1] + 1);
				return 0;
			}
		}
	}
	
	if (argc > 2){
		printf("%s: wrong number of arguments %d", argv[0], argc);
		return 0;
	}
	
	array = data_insert(&labs); /*klisi tis data_insert kai pairnei tin timi t array ka8ws kai ton ari8mo twn ergastiriwn*/
	print_names(array, labs); /*klisi tis print_names me parametrous ton array kai ta ergastiria*/
	
	while(1) {
		
		printf("Enter action: ");
		sprintf(formatstring,"%%%ds",COM_SIZE - 1);
		scanf(formatstring,command);
		
		if(!strcmp(command,"SWAP")) {
			printf("Enter first name: ");
			sprintf(formatstring,"%%%ds",SIZE - 1);
			scanf(formatstring,student1);
			
			printf("Enter second name: ");
			sprintf(formatstring,"%%%ds",SIZE - 1);
			scanf(formatstring,student2);
			
			swap_students(student1,student2,array,labs); /*klhsh swap_students*/
		}
		else if(!strcmp(command,"PRINT")) print_names(array, labs); /*klhsh print_names*/
		else if(!strcmp(command,"REMOVE")) {
			printf("Enter name: ");
			sprintf(formatstring,"%%%ds",SIZE - 1);
			scanf(formatstring,student1);
			delete_student(student1,array,labs); /*klhsh delete_student*/
		}
		else if(!strcmp(command,"EXIT")) {
			clear_mem(array, labs); /*klhsh clear_mem*/
			break;
		}
		else {
			printf("Invalid action. Valid actions are SWAP, REMOVE, PRINT, EXIT.\n");
		}
		
	}
	
	return(0);
}

lab_list *data_insert(int *section_count) {
	int students_num = 0, pc_num = 0, sections_needed = 0, i = 0, t = 8, lab = 1, d = Mon;
	char formatstring[13], temp_string[SIZE-1];
	student_list *curr;
	
	printf("Enter number of students: ");
	scanf("%d", &students_num);
	
	printf("Enter maximum lab size: ");
	scanf("%d" , &pc_num);
	
	
	sections_needed = students_num / pc_num;/*ipologismos twn ergastiriwn*/
	
	if (students_num % pc_num != 0) 
		sections_needed = sections_needed + 1;/*ipologismos twn ergastiriwn*/
	
	lab_list *array_lab = (lab_list*)malloc(sections_needed * sizeof(lab_list));
	
	if (array_lab == NULL) {
		printf("Failed to allocate memory");
		free(array_lab);
		return(NULL);
	}
	
	for (i = 0; i < sections_needed; i++) {
		array_lab[i].lab_time = t;/*pros8iki katallilis wras ston pinaka twn ergastiriwn*/
		array_lab[i].day = d;/*pros8iki katallilis imeras ston pinaka twn ergastiriwn*/
		t++;/*auksisi tis wras kata ena epanaliptika*/
		if (t == 22) {
			d++;/*an i wra ftasei sto megisto diladi 22:00 tote allazei i mera kai i wra ksanapairnei timi 8*/
			t = 8;
		}
	}
	
	
	if (debug == ON) 
		printf("\n>>Created %d sections<<\n",sections_needed);
	
	
	for (i = 0; i < students_num; i++) {
		printf("Enter student name: ");
		sprintf(formatstring,"%%%ds", SIZE - 1);
		scanf(formatstring,temp_string);
		curr = (student_list*)malloc(sizeof(student_list));
		curr->name = strdup(temp_string);
		if (curr == NULL) {
			printf("Failed to allocate memory");
			clear_mem(array_lab, sections_needed);
			exit(1);
		}
		if (!curr->name){
			printf("Failed to allocate memory");
			clear_mem(array_lab, sections_needed);
			exit(1);
		}
		
		curr->section = lab;
		add_student(array_lab, curr, lab);/*topo8etisi tou foithth sto ergastirio*/
		lab++;/*auksisi t lab gia na topo8eteitai ka8e diadoxikos foithths se diaforetiko ergastirio*/
		if (lab > sections_needed) 
			lab = 1;  /*epanafora t lab otan iperbei ton megalitero dinato*/
	}
	*section_count = sections_needed;/*epistrofi tou ari8mou twn ergastiriwn kai t pinaka*/
	return(array_lab);
}

void add_student(lab_list *array, student_list *root, int section) {
	
	if (debug == ON) 
		printf("\n>>Adding student \"%s\" in section %d<<\n",root->name, section);
	root->next = array[section - 1].head;/*pros8iki t kombou tou foithth pou prokeitai na proste8ei*/
	array[section - 1].head = root;
}

void print_names(lab_list *array, int section) {
	int i;
	student_list *node;
	
	printf("\n==========LABS==========\n");
	for (i = 0;i < section; i++){/*gia ka8e section tipwnei imera k wra*/
		printf("\n*Section %d,", i + 1);
		switch (array[i].day){
			case (Mon):
				printf(" Monday");break;
			case (Tue):
				printf(" Tuesday");break;
			case (Wed):
				printf(" Wednesday");break;
			case (Thu):
				printf(" Thursday");break;
			case (Fri):
				printf(" Friday");break;
		}
		printf(" %d:00*\n",array[i].lab_time);
		for(node = array[i].head; node!=NULL; node=node->next)/*tipwsi twn onomatwn twn foithtwn p anhkoun sto sigkekrimeno lab*/
			printf("\t%s", node->name);
	}
	printf("\n========================\n");
}

student_list *isolate_student(lab_list *array,char *student_name, int size_array) {
	student_list *node = NULL,*prev = NULL;
	int i;
	
	for (i = 0; i < size_array; i++) {
		if (debug == ON)
			printf("\n>>Searching section %d...<<\n",i+1);
		for (prev = NULL, node = array[i].head; node != NULL; prev = node, node = node->next) {
			if (debug == ON)
				printf("%s...",node->name);
			if (!strcmp(node->name, student_name)) {/*euresh t kombou p prokeitai na apomonw8ei*/
				if (!prev)
					array[i].head = node->next;/*parakampsi t sigkekrimenou kombou xwris progoumeno kombo*/
				else
					prev->next = node->next;/*parakampsi t sigkekrimenou kombou me proigoumeno kombo*/
				node->next=NULL;
				return(node);/*epistrofi t kombou tou sigkekrimenou foithth*/
			}
		}
	}
	return(NULL);
}

void swap_students(char *student_name_1, char *student_name_2, lab_list *array, int size_array) {
	student_list *node1 = NULL , *node2 = NULL;
	int temp;
	
	node1 = isolate_student(array,student_name_1,size_array);/*klhsh ths isolate_student kai epistrofi t kombou t foithth p exei to onoma student1*/
	node2 = isolate_student(array,student_name_2,size_array);/*klhsh ths isolate_student kai epistrofi t kombou t foithth p exei to onoma student2*/
	if (node1 == NULL) {
		printf("Student \"%s\" not in lab. Swap canceled.\n", student_name_1);
		if (node2 != NULL)
			add_student(array,node2, node2->section);/*klhsh ths add_student gia epistrofi t student 2 sto tmhma tou ean o student1 dn iparxi sto sigkekrimeno tmhma p psaxthke*/
		return;
	}
	if (node2 == NULL) {
		printf("Student \"%s\" not in lab. Swap canceled.\n", student_name_1);
		add_student(array,node1, node1->section);/*klhsh add_student gia epistrofi t student1 sto tmima t an o student 2 dn iparxi sto sigkekrimeno tmhma p psaxthke*/
		return;
	}
	if(node1->section == node2->section)/*an oi foithtes briskontai sto idio tmhma epistrefontai sto tmhma tous*/
			printf("Students \"%s\" and \"%s\" are in the same section. Swap canceled.\n", student_name_1, student_name_2);
	add_student(array,node1, node2->section);/*allagh tmhmatos t foithth 1*/
	add_student(array,node2, node1->section);/*allagh tmhmatos t foithth 2*/
	temp=node1->section;/*antimeta8esi twn tmimatwn me proswrini metabliti temp*/
	node1->section=node2->section;
	node2->section=temp;
}

void delete_student(char *student_name, lab_list *array, int size_array) {
	student_list *isolated_student = NULL;
	
	isolated_student = isolate_student(array, student_name, size_array); /*klhsh tis isolate_student pou epistrefi ton foithth me to onoma pou do8ike ws parametro kai prokeitai na diagrafei*/
	
	if(isolated_student) {
		if(debug == ON) {
			printf("\n>>Removed student \"%s\" from section %d<<\n", isolated_student->name, isolated_student->section);
		}
		free(isolated_student);/*apeleu8erwsh t kombou tou sigkekrimenou foithth*/
	}
	else printf("Student \"%s\" not in lab.Remove canceled.\n", student_name);
}

void clear_mem(lab_list *array, int section) {
	int i = 0;
	
	for(i = 0; i < section; i++) /*klhsh ths list_destroy_rec gia ka8e arxh listas ka8e tmhmatos*/
		list_destroy_rec(array[i].head);
	
	free(array);
}

void list_destroy_rec(student_list *curr) {
	
	if (!curr)return; /*if curr == NULL return*/
	list_destroy_rec(curr->next);/*anadromiki klhsh ths list_destroy_rec*/
	free(curr->name);/*apodesmeusi dinamika desmeumenis mnhmhs*/
	free(curr);
}