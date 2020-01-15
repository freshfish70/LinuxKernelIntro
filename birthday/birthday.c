/*
	Birthday module

	Respurces:
	https://www.oreilly.com/library/view/linux-device-drivers/0596000081/ch10s05.html
	http://www.makelinux.net/ldd3/
	https://github.com/Bovojon/OS-Linux-Kernel-exercises/blob/master/linux_kernel_linked_list.c
	https://gist.github.com/lomomike/770dd7df03bb951fac4e

*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/printk.h>
#include <linux/slab.h>

struct birthday
{
	int day;
	int month;
	int year;
	struct list_head list;
};

// Creates a list_head struct with name persons_birthdays
LIST_HEAD(persons_birthdays);

struct birthday *create_person_birthday(int day, int month, int year)
{
	struct birthday *person_birthday;

	// kmalloc is the same as malloc (memory allocation) but it allocates kernel memory instead.
	// GFP_KERNEL flag indicates that routine kernel memory allocation
	// Allocate a memory section to the person pointer. So it gets its pointer reference.
	person_birthday = kmalloc(sizeof(*person_birthday), GFP_KERNEL);
	person_birthday->day = day;
	person_birthday->month = month;
	person_birthday->year = year;

	return person_birthday;
}

// Initialization function
int birthday_init(void)
{
	printk(KERN_INFO "Birthday module is loaded.\n");

	struct birthday *person;
	person = create_person_birthday(3, 3, 1993);
	// Adds the person memory location to the persons birthday list
	list_add_tail(&person->list, &persons_birthdays);
	person = create_person_birthday(4, 4, 1994);
	// Adds the person memory location to the persons birthday list
	list_add_tail(&person->list, &persons_birthdays);

	struct birthday *ptr;
	list_for_each_entry(ptr, &persons_birthdays, list)
	{
		printk("Person birthday: %d/%d/%d\n", ptr->day, ptr->month, ptr->year);
	}
	return 0;
}

// Destruct function
void birthday_exit(void)
{
	printk(KERN_INFO "Birthday module cleanup.\n");

	// Cleanup
	struct birthday *ptr, *next;
	list_for_each_entry_safe(ptr, next, &persons_birthdays, list)
	{
		list_del(&ptr->list);
		kfree(ptr);
	}

	if (list_empty(&persons_birthdays))
	{
		printk("The birthday list is empty\n");
	}
}

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Birthday module description");
MODULE_AUTHOR("Team X");

// Called when module is inited/loaded
module_init(birthday_init);

// Called when module is exiting/unloaded
module_exit(birthday_exit);