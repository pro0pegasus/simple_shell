#ifndef GET_H
#define GET_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "main.h"
#define DO_DEBBUG 0
#if DO_DEBBUG
#define DEBBUG(x) (x)
#else
#define DEBBUG(x) ((void)0)
#endif

/**
 * struct fileD - open file descrip buff
 * @fileD: file descriptor
 * @buff: char buffer pointer
 * @j: buffer index
 * @leng: buffer length
 * @nxt: following node in linked list
 */
typedef struct fileD
{
	int fileD;
	char *buff;
	size_t j;
	size_t leng;
	struct fileD *nxt;
} fileDBuff;

#define READ_SIZE 1024
char *__get(const int fileD);
char *__read_buff(fileDBuff *fileB);
fileDBuff *get_fileDBuff(fileDBuff *hd, const int fileD);
char *_strchr(char *t, char b, ssize_t s);

#endif
