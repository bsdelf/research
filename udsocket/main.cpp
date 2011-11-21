#include <iostream>
using namespace std;

#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

const char* unpath = "mous.socket";

struct Message {
    int type;
    char data[1024];
};

void doServer(sem_t* ready, sem_t* done) {
    cout << "# begin server" << endl;

    int on;
    int fd;
    int ret;
    socklen_t len;
    sockaddr_un addr;

    fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    cout << "server fd:" << fd << endl;

    on = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    bzero(&addr, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, unpath);
    len = sizeof(addr.sun_family) + strlen(addr.sun_path);
    ret = bind(fd, (sockaddr*)&addr, len);
    if (ret != 0)
    	cout << "# bind failed:" << strerror(errno) << endl;

    //sem_wait(ready);

    while (true) {
	int x;
	ret = recvfrom(fd, &x, sizeof(x), 0, (sockaddr*)&addr, &len);
	if (ret == -1)
	    cout << "# recvfrom failed:" << strerror(errno) << endl;
	if (x == -1) {
	    //sem_post(done);
	    break;
	}
	cout << "pow:" << x*x << endl;
    }

    unlink(unpath);
    cout << "# end server" << endl;
}

void doClient(sem_t* ready, sem_t* done) {
    cout << "# begin client" << endl;

    int fd;
    int ret;
    socklen_t len;
    sockaddr_un addr;

    fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    cout << "client fd:" << fd << endl;

    bzero(&addr, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, unpath);
    len = sizeof(addr.sun_family) + strlen(addr.sun_path);

    for (int i = 0; i < 2; ++i) {
	ret = bind(fd, (sockaddr*)&addr, len);
	if (ret == 0) {
	    ret = fork();
	    if (ret == 0) {
		doServer(NULL, NULL);
		return;
	    }
	    break;
	} else {
	    // maybe exists
	    if (errno == EADDRINUSE) {
		ret = sendto(fd, NULL, 0, 0, (sockaddr*)&addr, len);
		// but can't sendto
		if (ret == -1) {
		    ret = unlink(unpath);
		    if (ret == 0)
			continue;
		    else 
			goto LABEL_FAILED;
		}
	    }
	}
    }

    while (true) {
	int x;
	int ret;
	cin >> x;
	ret = sendto(fd, &x, sizeof(x), 0, (sockaddr*)&addr, len);
	if (ret == -1)
	    cout << "# sendto failed:" << strerror(errno) << endl;
	if (x == 0)
	    break;
    }

    /*
    sem_wait(done);
    sem_close(done);
    sem_unlink("/mous/done");

    sem_close(ready);
    sem_unlink("/mous/ready");
    */

    cout << "# end client" << endl;
    return;

LABEL_FAILED:
    cout << "# failed to run" << endl;
}

int main(int argc, char** argv) {

    sem_t* ready = sem_open("/mous", 0644, O_CREAT, 0);
    sem_t* done = sem_open("/mous1", 0644, O_CREAT, 0);

    cout << ready << endl;
    cout << done << endl;

    doClient(ready, done);
    return 0;
}
