/*
 * commom_utils.h
 *
 *  Created on: 26 de out. de 2025
 *      Author: Deived
 */

#ifndef COMMOM_UTILS_H_
#define COMMOM_UTILS_H_


/* generic headers */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hal_data.h"

/* SEGGER RTT and error related headers */
/* SEGGER RTT disabling macro */
#define DISABLE_APP_PRINT       (0)
#define DISABLE_APP_ERR_PRINT   (0)
#define DISABLE_APP_ERR_TRAP    (0)
#define DISABLE_APP_READ        (0)
#define DISABLE_APP_CHECK_DATA  (0)


#define BIT_SHIFT_8  (8u)
#define SIZE_64      (64u)

#define LVL_ERR      (1u)       /* error conditions   */

#define RESET_VALUE             (0x00)


#endif /* COMMOM_UTILS_H_ */
