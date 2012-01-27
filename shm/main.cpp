#include <iostream>
#include "scx/SemVar.hpp"
using namespace scx;
using namespace std;

#include <unistd.h>
#include <semaphore.h>
#include <sys/fcntl.h>
#include <sys/shm.h>
#include <sys/ipc.h>

void parent(sem_t* semp, int shmid) {
    int* data = (int*)shmat(shmid, NULL, 0);

    int x;
    while (true) {
	cin >> x;
	*data = x;
	sem_post(semp);
	if (x == 0)
	    break;
    }

    sem_close(semp);
    sem_unlink("/mous");
    shmdt(NULL);
    shmid_ds ds;
    shmctl(shmid, IPC_RMID, &ds);

    cout << "#end parent" << endl;
}

void child(sem_t* semp, int shmid) {
    int* data = (int*)shmat(shmid, NULL, 0);

    while (true) {
	sem_wait(semp);
	int x = *data;
	if (x == 0)
	    break;
	cout << "pow:" << x*x << endl;
    }

    shmdt(NULL);
    shmid_ds ds;
    shmctl(shmid, IPC_RMID, &ds);

    cout << "#end child" << endl;
}

int main() {
    sem_t* semp = sem_open("/mous", O_CREAT, 0644, 0);
    //sem_t* semc = sem_open("/mous/child", O_CREAT, 0644, 0);
    cout << semp << endl;

    int shmsize = 4;//33554432 - 31514624 + 1;
    int shmid = shmget(IPC_PRIVATE, shmsize, IPC_CREAT | SHM_R | SHM_W);
    cout << "shmsize " << shmsize << endl;
    cout << "shmid " << shmid << endl;

    int ret = fork();
    if (ret == 0) {
	cout << "child ret:" << ret << endl;
	child(semp, shmid);
    } else {
	cout << "parent ret:" << ret << endl;
	parent(semp, shmid);
    }
    return 0;
}
