////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2005
// Packet Engineering, Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification is not permitted unless authorized in writing by a duly
// appointed officer of Packet Engineering, Inc. or its derivatives
//
// Description:
// This file is automatically generated by the TorturerGen facility.  
//
// Modification History:
// 06/08/2011: Created by Ketty 
////////////////////////////////////////////////////////////////////////////

#include "AppMgr/App.h"
#include "Debug/Debug.h"
#include "Porting/Sleep.h"
#include "XmlUtil/XmlTag.h"
#include "TransClient/Tester/main.cpp"
#include "TransServer/Tester/main.cpp"
#include "TransServer/Torturer/TransCheck.h"
#include "Util/OmnNew.h"
#include "util2/global_data.h"

#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

using namespace std;

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *arry;
};

int gAosLogLevel = 5;

char *firstAddr = 0;
char *triesAddr = 0;
char *clientSyncAddr = 0;
char *serverSyncAddr = 0;
int firstAddrSize = 0;
int syncAddrSize = 0;
int semidTries;
int semidClient;
int semidServer;
int semidKillClient;
int semidKillServer;
int semaphoreP(int semid);
int semaphoreV(int semid);
int cltSendConnNum = 5;		// change by config
int shareMemConnSize = 0; 
u32 totalTransNum = 2000000;	

int  clientMain(int, char**);
int	 serverMain(int, char**);
void testStart(int child_client_pid, int child_server_pid, int argc, char **argv);
int redirectOutPut(bool server);
void getSmareMemory(int size, const char* fn, char ** addr);
void semaphore(const char* fn, int &semid);
int status;

// totalNransNum ---(need)--- firstAddrSize
// 4096000       ---(need)--- 4096 * 2000
// 2048000		 ---(need)--- 4096 * 1000


int 
main(int argc, char **argv)
{
	signal(SIGUSR1, AosTransCheckGetSignal);
	signal(SIGUSR2, AosTransCheckGetSignal);
	int child_client_pid;
	int child_server_pid;

	const char *cmd = "rm /home/ice/AOS/src/TransClient/Tester/Data/* /home/ice/AOS/src/TransServer/Tester/Data/* server_* client_*";
	system(cmd);
	cout << "-------------------Parent ID:\t" << getpid() << "  -------------" << endl;
	
	// get share memory.
	int size = getpagesize();
	cout << "------ getpagesize():" << size << endl;

	firstAddrSize = size * 1000;	// can change.
	if(totalTransNum * 2 > (int)firstAddrSize)
	{
		cout << "--------- share memory is too small!" << endl;
		return 0;
	}

	syncAddrSize = firstAddrSize * 2;
	getSmareMemory(firstAddrSize, "a", &firstAddr);
	getSmareMemory(size, "b", &triesAddr);
	getSmareMemory(syncAddrSize, "c", &clientSyncAddr);
	getSmareMemory(syncAddrSize, "d", &serverSyncAddr);
	shareMemConnSize = syncAddrSize/cltSendConnNum; 

	cout << "firstAddr:" << (int)firstAddr
		<< "; triesAddr:" << (int)triesAddr
		<< "; clientSyncAddr:" << (int)clientSyncAddr
		<< "; serverSyncAddr:" << (int)serverSyncAddr << endl; 

	semaphore("e", semidTries);
	semaphore("f", semidClient);
	semaphore("g", semidServer);
	semaphore("h", semidKillClient);
	semaphore("i", semidKillServer);

	// start client ans server.
	if ((child_server_pid=fork())== 0)	
	{
		cout << "----------------init start server:\t" << getpid() << "  -----------" << endl;
		redirectOutPut(true);
		serverMain(argc, argv);
	}
	else
	{
		if ((child_client_pid=fork())== 0)
		{
			cout << "---------------init start client: \t" << getpid() << "  --------" <<  endl;
			redirectOutPut(false);
			clientMain(argc, argv);
		}
		else
		{
			//testStart(child_client_pid, child_server_pid, argc, argv);
		}
	}
	
	while(1)
	{
		wait(&status);
		OmnSleep(200);
	}
	return 0;
} 

void
getSmareMemory(int size, const char* fn, char ** addr)
{
	int shmid;
	key_t key = ftok(fn, 0);
	struct shmid_ds dsbuf;

	if( (shmid=shmget(key, size, 0664|IPC_CREAT)) < 0 )	
	{
	    perror("share memery allocate error!");
	    exit(1);
	}
	
	shmctl(shmid, IPC_STAT, &dsbuf);
	
	*addr = (char*)shmat(shmid, NULL, 0);
	if((int)*addr == -1)
	{
		perror("share memery load error!");
		exit(1);
	}
	memset(*addr, 0, size);
}


void
semaphore(const char* fn, int &semid)
{
	//semaphore
	key_t key = ftok(fn, 0);

	if( (semid=semget(key, 1, 0664|IPC_CREAT)) < 0)	
	{
		perror("semaphore init error!");
		exit(1);
	}	
	
	union semun arg;
	arg.val= 1;
	if (semctl(semid, 0, SETVAL, arg) < 0 )
	{
		perror("semaphore reset error!");
		exit(1);
	}
}


void
testStart(int child_client_pid, int child_server_pid, int argc, char **argv)
{
	bool killedClient = false; 
	bool killedServer = false;

	//int num = 30;
	//int add = 10;
	while(1)
	{
		int time = rand() % 60 + 20;
		//int time = rand() % num + 20;
		//num = num + add;
		//add = add + 5;
		cout << "..........................."
			 <<	"parent sleep:" << time
			 << ",to kill Server or client"
			 << "..........................."
			 << endl;
		OmnSleep(time);

		int aa = rand() & 0x0001;
		//int aa = 0;
		if ( aa == 1 && !killedClient)
		{
			cout << ">>>>>>>>------>>>>>>>>--------killclient:\t"
				<< child_client_pid << "(" << getpid() << ")" 
				<< "------<<<<<<<<<<-----------<<<<<<<<"
				<< endl;
			//cout << "want kill client lock1" << endl;
			semaphoreP(semidKillClient);
			kill(child_client_pid, 9);
			//cout << "kill client lock1" << endl;
			semaphoreV(semidKillClient);
			//cout << "kill client unlock1" << endl;
			wait(&status);
			killedClient = true;

			//The possibility of 10 percent to  kill server
			/*
			if((rand()%100) < 10 && !killedServer)
			{
				cout << ">>>>>>>>>------->>>>>>>>--------killserver(after kill client):\t"
					<< child_server_pid << "(" << getpid() << ")" 
					<< "-----------<<<<<<<<-------------<<<<<<<"
					<< endl;
				cout << "want kill server lock1" << endl;
				semaphoreP(semidKillServer);
				kill(child_server_pid, 9);
				cout << "kill server lock1" << endl;
				semaphoreV(semidKillServer);
				cout << "kill server unlock1" << endl;
				wait(&status);
				killedServer = true;
			}
			*/
		}
		else if(!killedServer)	
		{
			cout << ">>>>>>>>--------->>>>>>>>>-------killserver:\t"
				<< child_server_pid << "(" << getpid() << ")" 
				<< "----------<<<<<<<<<<----------<<<<<<<<"
				<< endl;
			//cout << "want kill server lock2" << endl;
			semaphoreP(semidKillServer);
			//cout << "kill server lock2" << endl;
			kill(child_server_pid, 9);
			semaphoreV(semidKillServer);
			//cout << "kill server unlock2" << endl;
			wait(&status);
			killedServer = true;
			
			//The possibility of 10 percent to  kill client
			/*
			if((rand()%100) < 10 && !killedClient)
			{
				cout << ">>>>>>>>>>---------->>>>>>>>>>>>>>---------killclient(after kill server):\t"
					<< child_client_pid << "(" << getpid() << ")" 
					<< "----------------<<<<<<<<<<<<<<<<<<--------------------<<<<<<<<<<<<"
					<< endl;
				cout << "want kill client lock2" << endl;
				semaphoreP(semidKillClient);
				cout << "kill client lock2" << endl;
				kill(child_client_pid, 9);
				semaphoreV(semidKillClient);
				cout << "kill client unlock2" << endl;
				wait(&status);
				killedClient = true;
			}
			*/
		}
			
		if(killedClient)
		{
			if ((child_client_pid=fork())== 0)	
			{
				OmnSleep(rand()% 10);
				cout << "-----*********------*********--------start client: "
					<< getpid() 
					<< " -----********-------********" << endl;
				redirectOutPut(false);
				clientMain(argc, argv);
			}
			killedClient = false;
		}

		if(killedServer)
		{
			if ((child_server_pid=fork())== 0)
			{
				OmnSleep(rand()% 10);
				cout << "-----*******-----********----------start server: "
					<< getpid() 
					<< " ----------****-----*********" << endl;
				redirectOutPut(true);
				serverMain(argc, argv);
			}
			killedServer = false;
		}	
	}
}


int redirectOutPut(bool server)
{
	//return 0;
	close(STDOUT_FILENO);	
	OmnString filename;
	if (server)
	{
		filename = "server_";
	}
	else
	{
		filename = "client_";
	}
	filename << getpid();

	int fd = open(filename.data(), O_RDWR|O_CREAT, S_IREAD | S_IWRITE);
	int fd2 = dup2(fd, STDOUT_FILENO);
	if (fd != fd2)
	{
		close(fd);
	}

	return 0;
}


int semaphoreV(int semid)
{
	//cout << "v" <<  (int)pthread_self()<<endl;
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = 1;
	sem_b.sem_flg = SEM_UNDO;
	if (semop(semid, &sem_b, 1) == -1)
	{
		perror("opr v error!");
		return -1;
	}
	return 0;
}


int semaphoreP(int semid)
{
	//cout << "p" <<  (int)pthread_self()<<endl;
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = -1;
	sem_b.sem_flg = SEM_UNDO;
	if (semop(semid, &sem_b, 1) == -1)
	{
		perror("opr p error!");
		return -1;
	}
	return 0;
}