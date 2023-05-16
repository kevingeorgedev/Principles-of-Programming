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
#include <math.h>
#include "InstrUtils.h"
#include "Utils.h"

/*
* Will return log2(n) if it is an integer (meaning n is a power of 2), and -1 otherwise
*/
int int_log2(int n) {

	int s = 1, i = 0;

	while (s < n) {
		s = s << 1;
		i++;
	}

	if (s == n)
		return i;
	else
		return -1;

}

/*
* Will traverse instructions in groups of two, searching for a patten of LOADI 
* and MUL | DIV instructions 
* where LOADI is a power of 2, and collapse these instructions into on shift 
* operation of LSHIFTI | RSHIFTI
*/
Instruction *strength_reduction(Instruction *head) {

	/* STUDENTS - BEGIN */

	Instruction *tmpNode = head;
	head = head->next;
	
	while(head != NULL){
		
		if(head->opcode == LOADI){

			int x = head->field1;
			int count = int_log2(x);

			if(count != -1){
				OpCode tmp = head->next->opcode;
				int reg1 = head->field2;

				int reg3 = head->next->field2;
				if(reg1 == reg3){
					if(tmp == DIV){
						head->next->field2 = count;
						head->next->opcode = RSHIFTI;
					}
					else if(tmp == MUL){
						head->next->field2 = count;
						head->next->opcode = LSHIFTI;
					}
				}
				else if(reg1 == head->next->field1 && tmp == MUL){
					head->next->field1 = head->next->field2;
					head->next->field2 = 2;
					head->next->opcode = LSHIFTI;
				}
			}
		}
		head = head->next;
	}

	head = tmpNode;

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

	head = strength_reduction(head);

	if (head) 
		PrintInstructionList(stdout, head);
	
	return EXIT_SUCCESS;
}

