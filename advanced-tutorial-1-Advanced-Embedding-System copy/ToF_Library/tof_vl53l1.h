#ifndef __TOF_VL53L1_H__
#define __TOF_VL53L1_H__

#include "vl53l1_platform.h"
#include "vl53l1_types.h"
#include "gpio.h"

typedef struct tof_vl53l1_dev{
    int status;
    uint16_t I2cDevAddr;
    uint8_t orgAddr;
    uint8_t Model_ID;
    uint8_t Module_Type;
    uint16_t ID;
    uint16_t Distance;
    uint16_t SignalRate;
    uint16_t AmbientRate;
    uint16_t SpadNum;
    uint8_t RangeStatus;
    uint8_t dataReady;
    GPIO_TypeDef *gpio_port;  // GPIO port for power control
    uint16_t gpio_pin;        // GPIO pin for power control
} tof_vl53l1_dev_t;

int tof_vl53l1_init(tof_vl53l1_dev_t *dev, uint16_t i2c_addr, uint8_t mode, uint8_t timing_budget, uint8_t inter_measurement_time, GPIO_TypeDef *gpio_port, uint16_t gpio_pin);
uint8_t tof_regular_sample(tof_vl53l1_dev_t *dev);


#endif /* __TOF_VL53L1_H__ */