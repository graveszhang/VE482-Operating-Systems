#include <linux/time64.h>
#include <linux/timekeeping.h>

#include "dice.h"

int dice_major;
int dice_devs = DICE_DEVS;    	/* number of devices */
int dice_num = DICE_NUM; 	    /* initial number of dice in a device */
int gen_sides = GEN_SIDES; 	    /* initial number of sides of `arbitrary` dice game */

module_param(gen_sides, int, 0);

struct dice_dev *dice_devices;

static int dice_open(struct inode *inode, struct file *filp)
/*
 * EFFECTS: called when device is opened;
 *          sets up `filp->private_data` as current device
 */
{
    // TODO hints: container_of
}

static int dice_release(struct inode *inode, struct file *filp)
/*
 * EFFECTS: called when device is closed; do nothing here
 */
{
    return 0;
}

static ssize_t dice_read(struct file *filp, char __user *buff, size_t count, loff_t *offp)
/*
 * EFFECTS: called when `read` is performed on the device;
 *          output `dice_num` dice, with faces randomly generated
 *          according to `dice_num` and `dice_type` stored in `filp->private_data`
 */
{
    // TODO hints: __put_user
    struct dice_dev *dev = (struct dice_dev *)filp->private_data;
    int dice_type = dev->dice_type;
    switch(dice_type){
        // regular

        // backgammon

        // arbitrary number of sides

    }
}

static ssize_t dice_write(struct file *filp, const char __user *buff, size_t count, loff_t *offp)
/*
 * EFFECTS: called when `write` is performed on the device;
 *          change `dice_num` according to the number written
 */
{
    // TODO hints: __get_user
}

static struct file_operations fops = {
        .read = dice_read,
        .write = dice_write,
        .open = dice_open,
        .release = dice_release,
};

static void dice_setup_cdev(struct cdev *dev, int i)
/*
 * EFFECTS: registers `dev` with major number `dice_major` and minor number `i`
 */
{
    int err, devno = MKDEV(dice_major, i);

    cdev_init(dev, &fops);
    dev->owner = THIS_MODULE;
    dev->ops = &fops;
    err = cdev_add(dev, devno, 1);
    /* Fail gracefully if need be */
    if (err)
        printk(KERN_NOTICE "Error %d adding dice%d", err, i);
}

static int __init dice_initialization(void)
/*
 * EFFECTS: Initialization; called when insmod
 */
{
    /*
     * TODO Register your major dynamically
     */

    /*
     * TODO Char device registration; three devices (three minor numbers) for three types of dice
     */
    dice_devices = kmalloc(dice_devs * sizeof(struct dice_dev), GFP_KERNEL);

    /*
     * TODO Initialize random number
     */

    return 0;
}

static void __exit dice_cleanup(void)
/*
 * EFFECTS: Cleanup; called when rmmod
 */
{
    /*
     * TODO Free char device
     */


    /*
     * TODO Unregister
     */
    unregister_chrdev_region(MKDEV(dice_major, 0), dice_devs);
}

module_init(dice_initialization);
module_exit(dice_cleanup);

MODULE_LICENSE("GPL");
