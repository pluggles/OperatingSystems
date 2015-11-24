/************************************************* 
* Course: CS 4540 – Fall 2015
* Assignment 4 - Problem 1
* Name: Aron Lawrence
* E-mail: aron.r.lawrence@wmich.edu
* Submitted: 11/23/15
*************************************************/


#include <linux/init.h>
#include <linux/kernel.h> void
#include <linux/module.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/slab.h>

/* was having some serious issues with floats, I guess kernal devs dont like them */

struct student {
int studentNumber;
int courseCredit;
int grade;
struct list_head list;
};

static LIST_HEAD(student_list);
/* init each student */
struct student *stud1, *stud2,
			  *stud3, *stud4,
			  *stud5, *stud6, *ptr,
			  *next;
/* This function is called when the module is loaded. */
int simple_init(void)
{
int total_credits;
int total_grade;
int gpa;
printk(KERN_INFO "Loading student Linked List module\n");

	/* student one */
stud1 = kmalloc(sizeof(*stud1), GFP_KERNEL);
stud1->studentNumber = 760120495;
stud1->courseCredit = 1;
stud1->grade = 3;
/*create the linked list */
INIT_LIST_HEAD(&stud1->list);
/* add stud1 to last index of linked list */
list_add_tail(&stud1->list, &student_list);

	/* student two */
stud2 = kmalloc(sizeof(*stud2), GFP_KERNEL);
stud2->studentNumber = 760120495;
stud2->courseCredit = 3;
stud2->grade = 3;
/* add stud2 to last index of linked list */
list_add_tail(&stud2->list, &student_list);

	/* student three */
stud3 = kmalloc(sizeof(*stud3), GFP_KERNEL);
stud3->studentNumber = 760120495;
stud3->courseCredit = 4;
stud3->grade = 2;
/* add stud3 to last index of linked list */
list_add_tail(&stud3->list, &student_list);

	/* student four */
stud4 = kmalloc(sizeof(*stud4), GFP_KERNEL);
stud4->studentNumber = 760120495;
stud4->courseCredit = 2;
stud4->grade = 4;
/* add stud4 to last index of linked list */
list_add_tail(&stud4->list, &student_list);

	/* student five */
stud5 = kmalloc(sizeof(*stud5), GFP_KERNEL);
stud5->studentNumber = 760120495;
stud5->courseCredit = 2;
stud5->grade = 3;
/* add stud5 to last index of linked list */
list_add_tail(&stud5->list, &student_list);

	/* student six */
stud6 = kmalloc(sizeof(*stud6), GFP_KERNEL);
stud6->studentNumber = 760120495;
stud6->courseCredit = 3;
stud6->grade = 4;
/* add stud6 to last index of linked list */
list_add_tail(&stud6->list, &student_list);





total_credits = 0;

total_grade = 0;
/* Traversal of each node */
	list_for_each_entry(ptr, &student_list, list) {
		/* on each iteration ptr points */
		/* to the next student struct */
		printk(KERN_INFO "Student number: %d, Course credit: %d, Grade: %d\n", ptr->studentNumber, ptr->courseCredit, ptr->grade);
		/* get a tally of total credits and grades */
		total_credits += ptr->courseCredit;
		total_grade +=(ptr->courseCredit * ptr->grade);
	}

	gpa = total_grade / total_credits;
	printk(KERN_INFO "student number %d total gpa is %d\n", stud1->studentNumber, gpa); 
	printk(KERN_INFO "Loaded student linked list module\n");
	return 0;

}

/* This function is called when the module is loaded. */
void simple_exit(void)
{
printk(KERN_INFO "Removing module...\n");

	/* Remove all nodes from linked list */
	printk(KERN_INFO "Deleting the linked list using list_for_each_entry_safe");
	list_for_each_entry_safe(ptr, next, &student_list, list) {
		printk(KERN_INFO "Removing node at %p\n", &ptr->list);
		list_del(&ptr->list);
		kfree(ptr);
	}

	/* Traversal to be double check list was removed */
	printk(KERN_INFO "Verifying that list is deleted... \n");
	list_for_each_entry(ptr, &student_list, list) {
		/* on each iteration ptr points */
		/* to the next student struct */
		printk(KERN_INFO "Student number: %d, Course credit: %d, Grade: %d\n",
				ptr->studentNumber, ptr->courseCredit, ptr->grade);
	}
	printk(KERN_INFO "If no student information is printed above this list was deleted\n");
	printk(KERN_INFO "Removed module\n");
}
/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("Aron Lawrence");