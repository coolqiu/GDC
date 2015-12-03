
#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f30x.h"
#include "stm32f3_discovery.h"
#include <stdio.h>
#include "stm32f3_discovery_lsm303dlhc.h"
#include "stm32f3_discovery_l3gd20.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "platform_config.h"
#include "math.h"
#include "suncti_m500.h"
#include "mavlink.h"
#include "alexmos32.h"
#include "lense_coordinate_finding.h"
#include "parameters.h"
#include "mav_state.h"

extern __IO uint64_t system_time;
extern __IO uint32_t time_boot;

//void Demo_USB (void);
void sort_mavlink_message(void);
void sort_alex_mos_message(void);
void TimingDelay_Decrement(void);
void Delay(__IO uint32_t nTime);

#endif /* __MAIN_H */

/*****************************END OF FILE**************************************/
