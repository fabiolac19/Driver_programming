#include <linux/init.h>  
#include <linux/module.h>  
#include <linux/fs.h>  
#include <linux/cdev.h>  
  
#include "mydriver_ioctls.h"  
  
#define DEV_NAME "mydriver"  


MODULE_LICENSE("Dual BSD/GPL");  
MODULE_AUTHOR("Daniel Lundborg");  
MODULE_DESCRIPTION("IOCTL example 1");  

struct mydriver_t  
{  
    struct cdev *cdev;  
    uint8_t major;  
    uint8_t minor;  
};  
  
static struct mydriver_t my_mydriver = {  
    .cdev = 0,  
    .major = 0,  
    .minor = 0,  
};  


static long mydriver_ioctl(struct file *f, unsigned int cmd, unsigned long arg) {  
    if (cmd == MYDRIVER_IOCTL_CMD1) {  
        printk(KERN_ALERT "Hello ");  
    } else if (cmd == MYDRIVER_IOCTL_CMD2) {  
        printk(KERN_ALERT "IOCTL ");  
    } else if (cmd == MYDRIVER_IOCTL_CMD3) {  
        printk(KERN_ALERT "World!\n");  
    }  
    return 0;  
}  

static struct file_operations mydriver_fops =  
{  
    owner: THIS_MODULE,  
    unlocked_ioctl: mydriver_ioctl,  
};  

static inline int mydriver_create_dev(void)  
{  
    struct mydriver_t *driver = &my_mydriver;  
    struct cdev *cdev;  
    dev_t devt;  
    int rc;  

    rc = alloc_chrdev_region(&devt, driver->minor, 1, DEV_NAME);  
    driver->major = MAJOR(devt);  

    if (rc)  
    {  
        printk(KERN_ERR "Failed to register chrdev region with major %d.\n", driver->major);  
        goto err_region;  
    }  

// register cdev  
    rc = -ENOMEM;  
    cdev = cdev_alloc();  
    if (!cdev)  
        goto err_cdev;  

    cdev->owner = THIS_MODULE;  
    cdev->ops = &mydriver_fops;  

    rc = cdev_add(cdev, devt, 1);  
    if (rc)  
        goto err_cdev;  

    driver->cdev = cdev;  

    printk( "Driver allocated major:%d minor:%d\n", MAJOR(devt), MINOR(devt));  
    return 0;
    err_cdev:  
    cdev_del(cdev);  
    err_region:  
    unregister_chrdev_region(devt, 1);  
    return -EFAULT;  
}  

static inline void mydriver_release_dev(void)  
{  
    struct mydriver_t *driver = &my_mydriver;  
  
    if (driver->cdev)  
    {  
        unregister_chrdev_region(driver->cdev->dev, 1);  
        cdev_del(driver->cdev);  
    }  
}  


static int __init mydriver_init(void)  
{  
    return mydriver_create_dev();  
}  
  
static void __exit mydriver_exit(void)  
{  
    mydriver_release_dev();  
}  
  
module_init(mydriver_init);  
module_exit(mydriver_exit);  
