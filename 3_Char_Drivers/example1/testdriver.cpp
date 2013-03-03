//   http://www.danielsprogramming.com/?p=265



#include <unistd.h>  
#include <string.h>  
#include <stdio.h>  
#include <fcntl.h>  
#include <linux/ioctl.h>  
#include <sys/ioctl.h>  
#include <inttypes.h>  
#include <stdlib.h>  
#include <iostream>  
  
#include "../driver/mydriver_ioctls.h"  
  
void printArgs()  
{  
    fprintf(stdout, "testDriver  \n");  
    fprintf(stdout, "Example: ./testDriver /dev/mydriver0 0\n");  
}  

int main(int argc, char **argv)  
{  
    if (argc != 3)  
    {  
        printArgs();  
        return -1;  
    }  
  
    const char* device_name = argv[1];  

    int fd;  
    if ((fd = open (device_name, O_RDWR)) == -1)  
    {  
        fprintf(stderr, "Error opening %s.\n", device_name);  
        return -1;  
    }  

    int ioctl_cmd;  
    std::stringstream ss;  
    ss << argv[2];   ss >> ioctl_cmd;  



    if (ioctl_cmd == 0)  
        ioctl_cmd = MYDRIVER_IOCTL_CMD1;  
    else if (ioctl_cmd == 1)  
        ioctl_cmd = MYDRIVER_IOCTL_CMD2;  
    else if (ioctl_cmd == 2)  
        ioctl_cmd = MYDRIVER_IOCTL_CMD3;  
  
    std::cout << "ioctl(fd, " << ioctl_cmd << ", 0)" << std::endl;  
  
    if (ioctl(fd, ioctl_cmd, 0) != 0 )  
    {  
        std::cerr << "ioctl " << ioctl_cmd << " failed." << std::endl;  
    }  
  
    close(fd);  
    return 0;  
}  
  



