/*******************************************************************************
 *	             _ _                                             _ _
                |   |                                           (_ _)
                |   |        _ _     _ _   _ _ _ _ _ _ _ _ _ _   _ _
                |   |       |   |   |   | |    _ _     _ _    | |   |
                |   |       |   |   |   | |   |   |   |   |   | |   |
                |   |       |   |   |   | |   |   |   |   |   | |   |
                |   |_ _ _  |   |_ _|   | |   |   |   |   |   | |   |
                |_ _ _ _ _| |_ _ _ _ _ _| |_ _|   |_ _|   |_ _| |_ _|
                                (C)2023 Lumi
 * Copyright (c) 2023
 * Lumi, JSC.
 * All Rights Reserved
 *
 * File name: ban-tin.h
 *
 * Description:
 *
 * Author: BaoHQ
 *
 * Last Changed By:  $Author: baohq $
 * Revision:         $Revision: $
 * Last Changed:     $Date: $Jan 4, 2023
 *
 * Code sample:
 ******************************************************************************/
// Enclosing macro to prevent multiple inclusion
#ifndef BAN_TIN_H_
#define BAN_TIN_H_
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include "../utils/typedefs.h"

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/

/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/******************************************************************************/
/**
 * @func soBanTinGuiDi
 * @brief Calculate the number of log sent
 * 
 * @param [pbyStr] : String to parse
 * @return u8_t
 */
u8_t soBanTinGuiDi(u8_p pbyStr, u32_t dwNumOfStr);

/**
 * @func soBanTinGuiTuThietBi
 * @brief Print out the log that was sent
 * 
 * @param [pbyStr] : String to parse
 * @param [dwNumOfStr] : Number of element of the Buffer
 * @return value : None
 */
u8_t soBanTinGuiTuThietBi(u8_p pbyStr, u32_t dwNumOfStr, u8_t byBuffer[]);

/**
 * @func soCongTac
 * @brief Count switch
 * 
 * @param [pbyStr] : String to parse
 * @param [dwNumOfStr] : Number of element of the Buffer
 * @return u8_t 
 */
u8_t soCongTac(u8_p pbyStr, u32_t dwNumOfStr, u8_p pbyBuffToken1, u8_p pbyBuffToken2);

/**
 * @func soBanTinGuiLoi
 * @brief Calculate the number of log not sent
 * 
 * @param [pbyStr] : String to parse
 * @param [dwNumOfStr] : Number of element of the Buffer
 * @return u8_t 
 */
u8_t soBanTinGuiLoi(u8_p pbyStr, u32_t dwNumOfStr);

/**
 * @func thoiGianTreLonNhat
 * @brief Calculate the max delay time
 * 
 * @param [pbyStr] : String to parse
 * @param [dwNumOfStr] : Number of element of the Buffer
 * @return float_t
 */
u32_t thoiGianTreLonNhat(u8_p pbyStr, u32_t dwNumOfStr);

/**
 * @func thoiGianTreTrungBinh
 * @brief Calculate the average time
 * 
 * @param [pbyStr] : String to parse
 * @param [dwNumOfStr] : Number of element of the Buffer
 * @return u32_t 
 */
u32_t thoiGianTreTrungBinh(u8_p pbyStr, u32_t dwNumOfStr);

#endif /* BAN_TIN_H_ */ 
