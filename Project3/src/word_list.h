/*
*********************************************
*  314 Principles of Programming Languages  *
*  Spring 2023                              *
*  Project 3                                *
*********************************************
*/

#include <stdlib.h>

#ifndef WORD_LIST_H
#define WORD_LIST_H

typedef struct {
	char **words;
	size_t num_words;
} word_list;

word_list *create_word_list(const char *path);
const char *get_word(word_list * wl, size_t index);
size_t get_num_words(word_list * wl);
void destroy_word_list(word_list * wl);

#endif
