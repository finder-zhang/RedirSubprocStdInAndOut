//============================================================================
// Name        : rtr_demo.cpp
// Author      : finder
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <iostream>
using namespace std;


int OpenSubProcessAndReplaceInOut(const char* chFileName,int* pZbcStdin,int* pZbcStdout)
{
	int fd_sub_in[2];		//use to cat the sub process's stdin
	int fd_sub_out[2];
	pipe(fd_sub_in);		//use to cat the sub process's stdout
	pipe(fd_sub_out);

	pid_t pid = fork();
	if ( 0 == pid ) {
		dup2(fd_sub_in[0],STDIN_FILENO);		//cat the STDIN to fd_sub_in
		dup2(fd_sub_out[1],STDOUT_FILENO);		//cat the STDOUT to fd_sub_out
		execlp(chFileName,"",(char*)0);			//run sub process
	}
	if ( pid < 0 ) {
		return 0;
	}

	*pZbcStdin = fd_sub_in[1];
	*pZbcStdout = fd_sub_out[0];

	return 1;
}

int main() {

//	int fd_sub_in[2];		//use to cat the sub process's stdin
//	int fd_sub_out[2];
//	pipe(fd_sub_in);		//use to cat the sub process's stdout
//	pipe(fd_sub_out);
//
//	char chRead[100];		//use to test the pipe's input and output
//	char chWrite[100];
//
//	pid_t pid = fork();	//make a fork
//
//	if ( 0 == pid ) {
//		// fork process here
//		dup2(fd_sub_in[0],STDIN_FILENO);		//cat the STDIN to fd_sub_in
//		dup2(fd_sub_out[1],STDOUT_FILENO);		//cat the STDOUT to fd_sub_out
//		execlp("/root/workspace/router_proj/zbc/Debug/zbc","",(char*)0);		//run zbc process
//		//will not reach here
//	}
//
//		//trunk code here
//	for (char ch = 'm';ch <= 'q';++ch) {
//		int iLen = sprintf(chWrite,"%c\r\n",ch);
//		write(fd_sub_in[1],chWrite,iLen);		//write to fd_sub_in,then zbc process getchar()
//		//sleep(1);
//	}
//
//	read(fd_sub_out[0],chRead,50);				//zbc process getchar() and putchar(),trunk read it back
//	for (int i=0;i<50;++i) {
//		printf("%02x ",chRead[i]);
//	}

	int zbcIn,zbcOut;

	char chRead[100];		//use to test the pipe's input and output
	char chWrite[100];

	OpenSubProcessAndReplaceInOut("/root/workspace/router_proj/zbc/Debug/zbc",&zbcIn,&zbcOut);

	//trunk code here
	for (char ch = 'm';ch <= 'q';++ch) {
		int iLen = sprintf(chWrite,"%c\r\n",ch);
		write(zbcIn,chWrite,iLen);		//write to fd_sub_in,then zbc process getchar()
	}

	read(zbcOut,chRead,50);				//zbc process getchar() and putchar(),trunk read it back
	for (int i=0;i<50;++i) {
		printf("%02x ",chRead[i]);
	}

	printf("++++++++\r\n");

	return 0;
}
