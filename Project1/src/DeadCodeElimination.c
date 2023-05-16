/*
 *********************************************
 *  314 Principles of Programming Languages  *
 *  Spring 2023                              *
 *  Student Version                          *
 *  Author:                                  *
 *********************************************
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"

void markCritical(int reg, Instruction *ptr, int c){
	if(ptr == NULL){
		return;
	}
	else if(ptr->critical){
		markCritical(reg, ptr->prev, c);
	}
	else{
		while(ptr != NULL){
			OpCode opcode = ptr->opcode;
			int output;

			switch(opcode){
				case(LOADI):
					output = ptr->field2;
					if(output == reg){
						ptr->critical = 1;
						return;
					}
					break;
				case(LOADAI):
					output = ptr->field3;
					if(output == reg && (c == ptr->field3 || c == -1)){
						ptr->critical = 1;
						markCritical(ptr->field1, ptr->prev, ptr->field2);
					}
					break;
				case(STOREAI):
					output = ptr->field2;
					if(output == reg && (c == ptr->field3 || c == -1)){
						ptr->critical = 1;
						markCritical(ptr->field1, ptr->prev, -1);
						return;
					}
					break;
				case(LSHIFTI):
				case(RSHIFTI):
					output = ptr->field3;
					if(output == reg && (c == ptr->field3 || c == -1)){
						ptr->critical = 1;
						markCritical(ptr->field1, ptr->prev, -1);
					}
					break;
				case(ADD):
				case(SUB):
				case(MUL):
				case(DIV):
					output = ptr->field3;
					if(output == reg){
						ptr->critical = 1;
						markCritical(ptr->field1, ptr->prev, -1);
						markCritical(ptr->field2, ptr->prev, -1);
					}
					break;
				case(OUTPUTAI):
					break;
			}

			ptr = ptr->prev;
		}
	}
}

Instruction *dead_code_elimination(Instruction *head) {

	/* STUDENTS - BEGIN */

	Instruction *tmp = head;
	head->critical = 1;
	while(tmp->next != NULL){
		if(tmp->opcode == OUTPUTAI){
			tmp->critical = 1;
		}
		tmp = tmp->next;
	}

	if(tmp->opcode == OUTPUTAI){
		tmp->critical = 1;
	}
	
	while(tmp != NULL){
		if(tmp->opcode == OUTPUTAI){
			markCritical(tmp->field1, tmp, tmp->field2);
		}

		tmp = tmp->prev;
	}
	
	Instruction *ptr = head;
	while(ptr != NULL){
		if(ptr->critical == 0){
			Instruction *ptr2 = ptr->next;
			if(ptr == head){
				head = head->next;
				free(head->prev);
				head->prev = NULL;
			}
			else{
				Instruction *toFree = ptr;
				ptr->prev->next = ptr->next;
				ptr->next->prev = ptr->prev;
				ptr = ptr->next;
				free(toFree);
			}
			ptr = ptr2;
		}
		else{
			ptr = ptr->next;
		}
	}

 	/* STUDENTS - END */

	return head;
}

int main()
{
	Instruction *head;

	head = ReadInstructionList(stdin);
	if (!head) {
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}

	head = dead_code_elimination(head);

	if (head) 
		PrintInstructionList(stdout, head);
	
	return EXIT_SUCCESS;
}

