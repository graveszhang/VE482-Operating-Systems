# dice

To compile the module:

```bash
make
```

Load the module driver:

```bash
insmod dicedevice.ko
```

You can specify the number of sides of the dice with module parameter

```bash
insmod dicedevice.ko gen_sides=n
```

Create a dice device by:

```bash
mknod /dev/dice c major minor
```

where `MAJOR` can be found in `/var/log/kern.log`, `Minor` is the type of the dice, which is either 0(regular), 1(back_gamm) or 2(gen_sides).

Before using the dice device, it is required to change the authority of the file:

```bash
chmod 777 /dev/dice
```

The output of the dice can be display by

```bash
cat /dev/dice
```

The result will vary on each `cat`.

To change the number of dice to `x`:

```bash
echo x > /dev/dice
```