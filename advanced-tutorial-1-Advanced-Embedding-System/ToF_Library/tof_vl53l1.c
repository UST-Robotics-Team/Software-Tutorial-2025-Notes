#include "tof_vl53l1.h"

#include "VL53L1X_api.h"
#include "i2c.h"
#include "vl53l1_platform.h"
#include "vl53l1_types.h"

/**
 * @brief  Specific initialization pipeline for multiple VL53L1 ToF sensors.
 * @param  dev Pointer to the VL53L1 device structure.
 * @param  i2c_addr I2C address of the VL53L1 sensor. There is serveral notes for the possible addresses:
 * @attention @param i2c_addr must be higher than 0x52 or the code cannot detect and find out the sensor.
 * @attention @param i2c_addr must be lower than 0x7F.
 * @attention @param i2c_addr should be an even number
 * @param  mode Operating mode of the sensor (e.g., ranging mode). 1=short, 2=long
 * @param  timing_budget Timing budget for the sensor in milliseconds (e.g., 20, 50, 100, 200, 500).
 * @param  inter_measurement_time Inter-measurement time in milliseconds (must be >= timing budget).
 */
int tof_vl53l1_init(tof_vl53l1_dev_t *dev, uint16_t i2c_addr, uint8_t mode, uint8_t timing_budget, uint8_t inter_measurement_time, GPIO_TypeDef *gpio_port, uint16_t gpio_pin) {
    dev->orgAddr = 0;
    dev->I2cDevAddr = i2c_addr;
    dev->Model_ID = 0;
    dev->Module_Type = 0;
    dev->ID = 0;
    dev->Distance = 0;
    dev->SignalRate = 0;
    dev->AmbientRate = 0;
    dev->SpadNum = 0;
    dev->RangeStatus = 0;
    dev->dataReady = 0;
    dev->status = 0;
    dev->gpio_port = gpio_port;                            // Set the GPIO port for power control
    dev->gpio_pin = gpio_pin;                              // Set the GPIO pin for power control
    HAL_GPIO_WritePin(gpio_port, gpio_pin, GPIO_PIN_SET);  // Set the GPIO pin high to power on the sensor
    // Initialize the VL53L1 device

    uint8_t sensorState = 0;

    for (dev->orgAddr = 0; dev->orgAddr < 0xFF; dev->orgAddr++) {
        dev->status = VL53L1_RdByte(dev->orgAddr, 0x010F, &dev->Model_ID);
        if (dev->Model_ID != 0)
            break;
    }
    VL53L1X_SetI2CAddress(dev->orgAddr, dev->I2cDevAddr);  // Set the I2C address of the device

    dev->status = VL53L1_RdByte(dev->I2cDevAddr, 0x010F, &(dev->Model_ID));
    dev->status = VL53L1_RdByte(dev->I2cDevAddr, 0x0110, &(dev->Module_Type));
    dev->status = VL53L1_RdWord(dev->I2cDevAddr, 0x010F, &(dev->ID));

    while (sensorState == 0) {
        dev->status = VL53L1X_BootState(dev->I2cDevAddr, &sensorState);
        HAL_Delay(2);
    }

    dev->status = VL53L1X_SensorInit(dev->I2cDevAddr);
    if (mode == 1 || mode == 2) {
        dev->status = VL53L1X_SetDistanceMode(dev->I2cDevAddr, mode);  // Set the device mode (1=short, 2=long)
    } else {
        dev->status = VL53L1X_SetDistanceMode(dev->I2cDevAddr, 2); /* 1=short, 2=long */
    }
    dev->status = VL53L1X_SetTimingBudgetInMs(dev->I2cDevAddr, timing_budget); /* in ms possible values [20, 50, 100, 200, 500] */
    if (inter_measurement_time < timing_budget) {
        inter_measurement_time = timing_budget;  // Ensure inter-measurement time is at least the timing budget
    }
    dev->status = VL53L1X_SetInterMeasurementInMs(
        dev->I2cDevAddr, inter_measurement_time);                      /* in ms, IM must be > = TB */
    dev->status = VL53L1X_StartRanging(dev->I2cDevAddr);               /* This function has to be called to enable the ranging */
    return dev->status;                                                // Return success
}


/* TODO: Complete this two functions */

/**
 * @brief  Regular sample from the VL53L1 ToF sensor.
 * @param  dev Pointer to the VL53L1 device structure.
 * @retval Status of the operation (0 for success, non-zero for error).
 */
int tof_regular_sample(tof_vl53l1_dev_t *dev) {
    return 0;
}

int tof_calibrate(tof_vl53l1_dev_t *dev) {
    return 0;
}