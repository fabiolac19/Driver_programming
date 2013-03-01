#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void){
	printk(KERN_INFO "Hello World");
	return 0;
}


static void hello_exit(void){
	printk(KERN_INFO "Good Bye Cruel World");
}

module_init(hello_init);
module_exit(hello_exit);
