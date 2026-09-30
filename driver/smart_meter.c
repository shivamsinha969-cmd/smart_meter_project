#include <linux/atomic.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/uaccess.h>

static atomic_t simulated_pulses = ATOMIC_INIT(0);

static ssize_t smart_meter_read(struct file *file,
                                char __user *buffer,
                                size_t length,
                                loff_t *offset)
{
    char output[32];
    int pulses;
    int output_length;

    if (*offset != 0)
        return 0;

    pulses = atomic_add_return(10, &simulated_pulses);
    output_length = scnprintf(output, sizeof(output), "%d\n", pulses);

    if (length < output_length)
        return -EINVAL;

    if (copy_to_user(buffer, output, output_length))
        return -EFAULT;

    *offset += output_length;
    return output_length;
}

static const struct file_operations smart_meter_fops = {
    .owner = THIS_MODULE,
    .read = smart_meter_read,
};

static struct miscdevice smart_meter_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "smart_meter",
    .fops = &smart_meter_fops,
    .mode = 0444,
};

static int __init smart_meter_start(void)
{
    int result = misc_register(&smart_meter_device);

    if (result != 0)
        return result;

    pr_info("smart_meter: virtual device registered\n");
    return 0;
}

static void __exit smart_meter_stop(void)
{
    misc_deregister(&smart_meter_device);
    pr_info("smart_meter: virtual device removed\n");
}

module_init(smart_meter_start);
module_exit(smart_meter_stop);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Software-only smart meter simulator");
MODULE_AUTHOR("Adeel");
