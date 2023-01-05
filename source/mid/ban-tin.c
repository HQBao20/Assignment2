/*******************************************************************************
 *               _ _                                             _ _
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
 * File name: function.c
 *
 * Description:
 *
 * Author: BaoHQ
 *
 * Last Changed By:  $Author: baohq $
 * Revision:         $Revision: $
 * Last Changed:     $Date: $Jan 3, 2023
 *
 * Code sample:
 ******************************************************************************/
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "ban-tin.h"

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
u8_t soBanTinGuiDi(u8_p pbyStr, u32_t dwNumOfStr)
{
    u32_t i = 0;
    u8_t byCount = 0;

    for(i = 32; i < dwNumOfStr; i++)
    {
        if(*(pbyStr + i) == 'c')
        {
            if(*(pbyStr + i + 1) == 'm')
            {
                if(*(pbyStr + i + 2) == 'd')
                {
                    if(*(pbyStr + i + 6) == 's')
                    {
                        if(*(pbyStr + i + 7) == 'e')
                        {
                            if(*(pbyStr + i + 8) == 't')
                            {
                                byCount++;
                            }
                        }
                    }
                }
            }
        }
    }

    return byCount;
}

u8_t soBanTinGuiTuThietBi(u8_p pbyStr, u32_t dwNumOfStr, u8_t byBuffer[])
{
    u8_t i = 0;
    u8_t j = 0;
    u8_t byStrRaw[4];
    u8_t byCount = 0;
    // bool_t boCheckReqid = false;
    // u8_t byStrRequid1[4];
    // u8_t byStrRequid2[4];

    for(i = 176; i < dwNumOfStr; i++)
    {
        // if(*(pbyStr + i) == '\0')
        // {
        //     boCheckReqid = true;
        // }
        if(*(pbyStr + i) == 'r')
        {
            if(*(pbyStr + i + 1) == 'a')
            {
                if(*(pbyStr + i + 2) == 'w')
                {
                    for(j = 0; j < 4; j++)
                    {
                        byStrRaw[j] = *(pbyStr + j + i + 6);
                    }
                }
            }
        }
        if(strcmp(byBuffer,byStrRaw) == 0)
        {
            byCount++;
        }
        // if(*(pbyStr + i) == 'r')
        // {
        //     if(*(pbyStr + i + 1) == 'e')
        //     {
        //         if(*(pbyStr + i + 2) == 'q')
        //         {
        //             if(*(pbyStr + i + 3) == 'i')
        //             {
        //                 if(*(pbyStr + i + 7) == 'd')
        //                 {
        //                     for(j = 0; j < 4; j++)
        //                     {
        //                         if(!boCheckReqid)
        //                         {
        //                             byStrRequid1[j] = *(pbyStr + i + j + 9);
        //                         }
        //                         else
        //                         {
        //                             byStrRequid2[j] = *(pbyStr + i + j + 9);
        //                         }
        //                     }
        //                 }
        //             }
        //         }
        //     }
        // }
    }

    return byCount;
}
