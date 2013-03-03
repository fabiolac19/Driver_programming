/* 
 	File: Hello.c
 	Brief: This file is used for initializing app2
	Date:  2nd March 2013
 	Author: Prakash Ranjan
*/
/* To insert Hello.ko use command
   sudo insmod Hello.ko param_var=23 param_var1=1,2,3,
*/


#include<linux/init.h>
#include<linux/module.h>

#include<linux/moduleparam.h>

int param_var = 0;

int param_var1[3] = {0,0,0};

//module_param(name_var, typr, permission)
module_param(param_var, int , S_IRUSR | S_IWUSR);
module_param_array(param_var1, int ,NULL , S_IRUSR | S_IWUSR);



void display(void)
{
    printk(KERN_ALERT "Test : Param_var = %d\n",param_var);
}
    
void display1(void)
{
    printk(KERN_ALERT "Test : Param_var1 = %d\n",param_var1[0]);
    printk(KERN_ALERT "Test : Param_var2 = %d\n",param_var1[1]);
    printk(KERN_ALERT "Test : Param_var3 = %d\n",param_var1[2]);
}

static int hello_init(void)
{
    printk(KERN_ALERT "Test : Hello World\n");
    display();
    display1();
    return 0;
}

static void hello_exit(void){
    printk(KERN_ALERT "Test: Good bye\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("PARAKASH");
MODULE_DESCRIPTION("Kernel module programming");
MODULE_LICENSE("GPL");
