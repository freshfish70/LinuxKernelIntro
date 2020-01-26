/*
	Birthday module developed by
	Team 7
	Nils-Jarle Haugen
	Trygve Woldseth
	Christoffer A Træen

	Respurces:
	https://www.oreilly.com/library/view/linux-device-drivers/0596000081/ch10s05.html
	http://www.makelinux.net/ldd3/
	https://github.com/Bovojon/OS-Linux-Kernel-exercises/blob/master/linux_kernel_linked_list.c
	https://gist.github.com/lomomike/770dd7df03bb951fac4e

*/

/**
 * Loads nessecary header files
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/printk.h>
#include <linux/slab.h>

/**
 * Birthday struct, including list_head.
 */
struct birthday
{
	int day;
	int month;
	int year;
	struct list_head list;
};

/**
 * Creates a list_head struct with person_birthdays as name,
 * holds all the birthdays in the linked list.
 */
LIST_HEAD(persons_birthdays);

/**
 * Creates a person birthday struct with day, month and year of birth and returns its pointer.
 */
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

	// Creates a birthday for a person
	person = create_person_birthday(3, 3, 1993);
	// Adds the person memory location to the persons birthday list at then end.
	list_add_tail(&person->list, &persons_birthdays);

	person = create_person_birthday(4, 4, 1994);
	list_add_tail(&person->list, &persons_birthdays);

	person = create_person_birthday(5, 5, 1995);
	list_add_tail(&person->list, &persons_birthdays);

	person = create_person_birthday(6, 6, 1995);
	list_add_tail(&person->list, &persons_birthdays);

	person = create_person_birthday(7, 7, 1995);
	list_add_tail(&person->list, &persons_birthdays);

	struct birthday *person_ptr;
	// Iterate over the list of persons birthdays
	list_for_each_entry(person_ptr, &persons_birthdays, list)
	{
		printk("Person birthday: %d/%d/%d - Memory address: %p\n", person_ptr->day, person_ptr->month, person_ptr->year, person_ptr);
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