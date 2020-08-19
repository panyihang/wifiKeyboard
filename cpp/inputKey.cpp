#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>
#include <cstring>
 
void simulate_key(int fd, int kval)
{
    struct input_event event;
    gettimeofday(&event.time, 0);
    event.type = EV_KEY;
    event.value = 1;
    event.code = kval;
    write(fd, &event, sizeof(event));
    event.type = EV_SYN;
    event.value = 0;
    event.code = SYN_REPORT;
    write(fd, &event, sizeof(event));
    memset(&event, 0, sizeof(event));
    gettimeofday(&event.time, 0);
    event.type = EV_KEY;
    event.value = 0;
    event.code = kval;
    write(fd, &event, sizeof(event));
    event.type = EV_SYN;
    event.value = 0;
    event.code = SYN_REPORT;
    write(fd, &event, sizeof(event));
}

int main(int argc, char **argv)
{
    int fd_kbd = -1;
    int i = 0;
    fd_kbd = open("/dev/input/by-id/usb-SINO_WEALTH_Rapoo_Gaming_Keyboard-event-kbd", O_RDWR);
    if(fd_kbd <= 0)
    {
        printf("Can not open keyboard input file\n");
        return -1;
    }
    for (i = 0; i < 50; i++)
    {
        simulate_key(fd_kbd, KEY_NUMLOCK); 
        sleep(3);
    }
    close(fd_kbd);
}