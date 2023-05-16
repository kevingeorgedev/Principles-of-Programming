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

/*
* Will traverse instructions in groups of 3, searching for a patten of LOADI, LOADI, and ADD | SUB | MUL instructions 
*/

Instruction *constant_folding(Instruction *head) {

	/* STUDENTS - BEGIN */
	
	Instruction *tmpNode = head;
	

	while(head != NULL){
		if(head->opcode == LOADI && head->next->opcode == LOADI){
			
			OpCode tmp = head->next->next->opcode;
			int reg1 = head->field2;
			int reg2 = head->next->field2;

			int reg3 = head->next->next->field1;
			int reg4 = head->next->next->field2;
			if(reg1 != reg3 || reg2 != reg4){
				if(reg1 != reg4 || reg2 != reg3){
				
				}
				else if(tmp == ADD){
					int op1 = head->field1;
					int op2 = head->next->field1;
					head->next->next->field1 = op1 + op2;
					head->next->next->opcode = LOADI;
					head->next->next->field2 = head->next->next->field3;
					head->next->next->field3 = 0;
				}
				else if(tmp == MUL){
					int op1 = head->field1;
					int op2 = head->next->field1;
					head->next->next->field1 = op1 * op2;
					head->next->next->opcode = LOADI;
					head->next->next->field2 = head->next->next->field3;
					head->next->next->field3 = 0;
				}
			}
			else if(tmp == SUB){
				int op1 = head->field1;
				int op2 = head->next->field1;
				head->next->next->field1 = op1 - op2;
				head->next->next->opcode = LOADI;
				head->next->next->field2 = head->next->next->field3;
				head->next->next->field3 = 0;
			}
			else if(tmp == ADD){
				int op1 = head->field1;
				int op2 = head->next->field1;
				head->next->next->field1 = op1 + op2;
				head->next->next->opcode = LOADI;
				head->next->next->field2 = head->next->next->field3;
				head->next->next->field3 = 0;
			}
			else if(tmp == MUL){
				int op1 = head->field1;
				int op2 = head->next->field1;
				head->next->next->field1 = op1 * op2;
				head->next->next->opcode = LOADI;
				head->next->next->field2 = head->next->next->field3;
				head->next->next->field3 = 0;
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

	head = constant_folding(head);

	if (head) 
		PrintInstructionList(stdout, head);
	
	return EXIT_SUCCESS;
}

