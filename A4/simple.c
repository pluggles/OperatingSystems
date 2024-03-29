#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

/* This function is called when the module is loaded. */
int simple_init(void)
{
printk(KERN_INFO "Hello World\n");
}

/* This function is called when the module is loaded. */
int simple_exit(void)
{
printk(KERN_INFO "Goodbye World\n");
}
/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("Aron Lawrence");