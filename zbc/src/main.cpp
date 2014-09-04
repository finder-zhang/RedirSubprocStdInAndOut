/*
 * main.cpp
 *
 *  Created on: 2014?9?4?
 *      Author: root
 */

#include <stdio.h>
#include <iostream>
using namespace std;


int main(int argc,char* argv[])
{
	printf("abc\r\n");
	int ch;
	do
	{
		ch = getchar();
		putchar(ch);
	}while ( 'q' != ch );
	printf("end\r\n");
	return 0;
}

