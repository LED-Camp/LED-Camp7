#include <unistd.h>
#include <linux/i2c-dev.h>

#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>

#include "bh1745nuc.h"
#include "bh1745nuc_reg.h"

#include <stdio.h>

#define BH1745NUC_DEVICE_ADDRESS 0x39

static int fd;

int32_t bh1745nuc_init(void)
{
    char *bus = "/dev/i2c-1";
    if ((fd = open(bus, O_RDWR)) < 0)
    {
        printf("Faild to open i2c port\n");
        return -1;
    }

    if (ioctl(fd, I2C_SLAVE, BH1745NUC_DEVICE_ADDRESS) < 0)
    {
        printf("Unable to get bus access to talk to slave\n");
        return -1;
    }

    uint8_t config[2] = {0};

    config[0] = BH1745NUC_MODE_CONTROL1;
    config[1] = 0x00; // RGBCデータ測定期間160ms毎
    write(fd, config, 2);

    config[0] = BH1745NUC_MODE_CONTROL2;
    config[1] = 0x92; // 測定実施,ゲイン16X
    write(fd, config, 2);

    config[0] = BH1745NUC_MODE_CONTROL3;
    config[1] = 0x02; // 常に0000 0010とする(DSより)
    write(fd, config, 2);

    return 0;
}


int32_t bh1745nuc_get_val(uint16_t * r, uint16_t * g, uint16_t * b, uint16_t * c)
{
    uint8_t reg[1] = {BH1745NUC_RED_DATA_LSB};
    write(fd, reg, 1);

    uint8_t data[8] = {0};
    if(read(fd, data, 8) != 8)
    {
        printf("Input/output erorr \n");
        return -1;
    }
    else
    {
        // Convert the data
        *r = (data[1] * 256 + data[0]);
        *g = (data[3] * 256 + data[2]);
        *b = (data[5] * 256 + data[4]);
        *c = (data[7] * 256 + data[6]);
    }

    return 0;
}
