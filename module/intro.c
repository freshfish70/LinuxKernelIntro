/* 
	Team 7 Module - introduction to kernel programming 
	Christoffer Andersen Træen
	Nils-Jarle Haugen
	Trygve Woldseth
*/

/* Load the required libraries */
#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_ALERT */

// Module information
MODULE_LICENSE("GPL");				 // Module License
MODULE_DESCRIPTION("Team 7 module"); // Module Description
MODULE_AUTHOR("Team 7");			 // Module authors

/*
 * The init_module methos is executed when
 * the module is loaded into the kernel. 
 */
int init_module(void)
{
	printk("Team 7 module loaded :D \n");
	return 0;
}

/*
 * The cleanup_module method is executed when
 * the module is unloaded from the kernel 
 */
void cleanup_module(void)
{
	printk(KERN_ALERT "Team 7 module unloaded...\n");
}