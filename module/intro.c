/* 
	Team X Module introduction to kernel programming 
	Christoffer
	Nils-Jarle 
*/

/* Load the require library */
#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_ALERT */

MODULE_LICENSE("GPL");				 // Module License
MODULE_DESCRIPTION("Team X module"); // Module Description
MODULE_AUTHOR("Team X");			 // Module authors

// Called when module is loaded into the kernel
int init_module(void)
{
	printk("Team X module loaded :D \n");
	return 0;
}

// Run when module is unloaded from the kernel
void cleanup_module(void)
{
	printk(KERN_ALERT "Team X module unloaded...\n");
}