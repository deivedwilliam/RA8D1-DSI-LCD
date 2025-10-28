/*
 * hal_entry.h
 *
 *  Created on: 26 de out. de 2025
 *      Author: Deived
 */

#ifndef HAL_ENTRY_H_
#define HAL_ENTRY_H_


#define KIT_INFO_PRIMARY_TEXT                "\r\n 1. KIT INFORMATION \r\n\r\n a) Kit name: \t\t\t\t"\
                                              ""KIT_NAME_MACRO""\
                                             "\r\n b) Kit ordering part number:\t\t"\
                                              ""KIT_PARTNUM_MACRO""\


#define LINE_CODING_LENGTH          (0x07U)
#define READ_BUF_SIZE               (8U)

#define __weak __attribute__((weak))


#endif /* HAL_ENTRY_H_ */
