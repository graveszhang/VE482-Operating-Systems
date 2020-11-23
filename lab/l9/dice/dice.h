//
// Created by cyx on 2020/10/5.
//

#ifndef DEVICE_DICE_H
#define DEVICE_DICE_H

#define DICE_DEVS 3

#define DICE_NUM 2
#define GEN_SIDES 20     /* default number of sides of `arbitrary` dice game */

struct dice_dev{
    int num;            /* number of dice in this device */
    int dice_type;	    /* type of dice game:  regular; backgammon; generic */
    struct cdev d_cdev;
};

#endif //DEVICE_DICE_H
