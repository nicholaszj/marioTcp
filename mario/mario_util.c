/*
 * MarioTCP:  Multi Libvent TCP Server  一个高性能的TCP服务器
 *
 * mario_util.c
 *	
 *  Created on: 
 *      Author: 
 *        Mail: 
 *
 *  修改记录：
 */
#define _GNU_SOURCE
#include "mario_util.h"
#include <sys/time.h>
#include <time.h>
#include <pthread.h>

void nsleep(uint32 ns) {
	struct timespec req;
	req.tv_sec = 0;
	req.tv_nsec = ns;
	nanosleep(&req, 0);
}

void susleep(uint32 s, uint32 us) {
	struct timeval tv;
	tv.tv_sec = s;
	tv.tv_usec = us;
	select(0, NULL, NULL, NULL, &tv);
}

void signal_handler(int sig, sighandler_t handler) {
	struct sigaction action;
	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	sigaction(sig, &action, NULL);
}

//子进程的创建用作daemon,用来接收相应的TCP的函数
void run_daemon() {
	pid_t pid;
	if ((pid = fork()) < 0) 
	{
		fprintf(stderr, "daemon can't fork\n");
		exit(1);
	} 
	else if (pid == 0) 
	{
		printf("这是子进程！");
	}
	else
	{
		printf("这是父进程！");
        exit(0);
	}
	setsid(); //为了子进行创建一个新的会话

	signal_handler(SIGHUP, SIG_IGN); //忽略SIGHUP
	signal_handler(SIGTERM, SIG_IGN);//忽略SIGTERM
	signal_handler(SIGPIPE, SIG_IGN);//忽略SIGPIPE
}

