#include <sys/param.h>
#include <stdio.h>
#include <fetch.h>
#include <unistd.h>
#include <signal.h>

static void sig_handler(int sig)
{
    printf("sig: %d\n", sig);
}

int main(int argc, char** argv)
{
    FILE* local = NULL;
    FILE* remote = NULL;
    struct url* u;
    struct url_stat us; 
    char buf[10240];
    size_t n = 0;
    size_t sum = 0;
    char flags[8] = { 0 };
    
    u = fetchParseURL(argv[1]);
    remote = fetchXGet(u, &us, flags);
    local = fopen("foo.bin", "w+");
    signal(SIGINFO, sig_handler);
    while (1) {
        n = fread(buf, 1, sizeof(buf), remote);

        if (ferror(remote))
            printf("err\n");

        if (n == 0) {
            break;
        }
        sum += fwrite(buf, 1, n, local);
        printf("got: %d/%d, %d%%\r", sum, us.size, (int)((float)sum/us.size*100));
        fflush(stdout);
    }

    fclose(remote);
    fclose(local);
    fetchFreeURL(u);

    return 0;
}
