//#include <linux/time64.h>
//#include <linux/timekeeping.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/random.h>
#include <linux/export.h>
#include <linux/uaccess.h>
#include "dice.h"

int dice_major;
int dice_devs = DICE_DEVS;    	/* number of devices */
int dice_num = DICE_NUM; 	    /* initial number of dice in a device */
int gen_sides = GEN_SIDES; 	    /* initial number of sides of `arbitrary` dice game */
static int printed = 0;

module_param(gen_sides, int, 0);

struct dice_dev *dice_devices;

unsigned counter = 0;

static int dice_open(struct inode *inode, struct file *filp)
/*
 * EFFECTS: called when device is opened;
 *          sets up `filp->private_data` as current device
 */
{
    filp->private_data = (struct dice_dev*)container_of(inode->i_cdev, struct dice_dev, d_cdev);
    return 0;
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
    struct dice_dev *dev = (struct dice_dev *)filp->private_data;
    int dice_type = dev->dice_type;
    int rand[999];
    int temp = 0, i = 0, n=0;
    int pos = 0;
    char result[99];
    unsigned rand_num[999];

    //Initialize random number
    get_random_bytes(&rand_num, 999);

    if (printed == 1){
        printed = 0;
        return 0;
    }
    switch(dice_type){
        // regular
        case 0:
            for (i = 0; i< dev->num; i++){
                rand[i] = rand_num[counter++]%6+1;
                sprintf(result,"%d", rand[i]);
                __put_user(result[0], buff+pos);
                pos++;
                __put_user(' ', buff+pos);
                pos++;
            }
            break;
        // backgammon
        case 1:
            for (i = 0; i< dev->num; i++){
                rand[i] = rand_num[counter++]%6+1;
                temp = 1;
                while (rand[i] >0){
                    rand[i]--;
                    temp *= 2;
                }
                rand[i] = temp;
                n = 0;
                sprintf(result,"%d", rand[i]);
                while (temp > 0){
                    __put_user(result[n], buff+pos);
                    temp /= 10;
                    pos++;
                    n++;
                }
                __put_user(' ', buff+pos);
                pos++;
            }
            break;
        // arbitrary number of sides
        case 2:
            for (i = 0; i< dev->num; i++){
                rand[i] = rand_num[counter++]%gen_sides+1;
                temp = rand[i];
                sprintf(result,"%d", rand[i]);
                n=0;
                while (temp > 0){
                    __put_user(result[n], buff+pos);
                    temp /= 10;
                    pos++;
                    n++;
                }
                __put_user(' ', buff+pos);
                pos++;
            }
            break;
    }
    __put_user('\n', buff+pos);
    pos++;
    printed = 1;
    return pos;
}

static ssize_t dice_write(struct file *filp, const char __user *buff, size_t count, loff_t *offp)
/*
 * EFFECTS: called when `write` is performed on the device;
 *          change `dice_num` according to the number written
 */
{
    long temp;
    char number[999];
    int i = 0;
    for (; i < count; i++){
        __get_user(number[i] , &buff[i]);
    }
    number[count] = '\0';
    kstrtol(number, 10, &temp);
    ((struct dice_dev *)filp->private_data)->num = temp;
    return count;
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
    // TODO Register your major dynamically
    dev_t dev;
    int i;
    alloc_chrdev_region(&dev, 0, dice_devs, "dicedevice");
    dice_major = MAJOR(dev);
    printk(KERN_ALERT "major: %d", dice_major);

    //Char device registration; three devices (three minor numbers) for three types of dice
    dice_devices = kmalloc(dice_devs * sizeof(struct dice_dev), GFP_KERNEL);
    memset(dice_devices, 0, dice_devs * sizeof(struct dice_dev));

    for (i =0; i < dice_devs; i++){
        dice_setup_cdev(&dice_devices[i].d_cdev , i);
        dice_devices[i].dice_type = i;
        dice_devices[i].num = dice_num;
    }

    return 0;
}

static void __exit dice_cleanup(void)
/*
 * EFFECTS: Cleanup; called when rmmod
 */
{
    //Free char device
    int i;
    for (i = 0; i < dice_devs; i++){
        cdev_del(&dice_devices[i].d_cdev);
    }
    kfree(dice_devices);

    //Unregister
    unregister_chrdev_region(MKDEV(dice_major, 0), dice_devs);
}

module_init(dice_initialization);
module_exit(dice_cleanup);

MODULE_LICENSE("GPL");
