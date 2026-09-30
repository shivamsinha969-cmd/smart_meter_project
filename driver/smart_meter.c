#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int __init smart_meter_start(void)
{
    pr_info("smart_meter: module loaded\n");
    return 0;
}

static void __exit smart_meter_stop(void)
{
    pr_info("smart_meter: module unloaded\n");
}

module_init(smart_meter_start);
module_exit(smart_meter_stop);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Software-only smart meter learning project");
MODULE_AUTHOR("Adeel");
