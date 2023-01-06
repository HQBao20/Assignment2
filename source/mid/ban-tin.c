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
#include <string.h>
#include "ban-tin.h"

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
#define TYPE_DEVICE "switch"
#define STATUS "set"
#define CMD "cmd"

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/
static bool_t checkBuff(u8_p pbyStr, u8_p pbyBuff, u8_t point);
static void_t bufClr(u8_p buf);
static bool_t compareBuffer(u8_t byBuff1[], u8_t byBuff2[], u8_t bySize);
static void_t copyBuffer(u8_t byBuff1[], u8_t byBuff2[], u8_t bySize);

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
    u32_t i = 0;
    u8_t j = 0;
    u8_t byStrRaw[4];
    u8_t byCount = 0;

    for(i = 153; i < dwNumOfStr; i++)
    {
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
            bufClr(&byStrRaw[0]);
            byCount++;
        }
    }

    return (byCount / 2);
}

u8_t soCongTac(u8_p pbyStr, u32_t dwNumOfStr, u8_t byBuffToken1[], u8_t byBuffToken2[])
{
   u32_t i = 0;
   u8_t j = 0;
   u8_t k = 0;
   u8_t byCount = 0;
   u8_t byCountSwitch = 1;
   bool_t boCheckEnd = false;
   bool_t boCheckDevice = false;
   u8_t byBufferNetwEndpoint1[8];
   u8_t byBufferNetwEndpoint2[8];
   u8_t byBufferNetwEndpointTemp[8] = {0};
   u8_p pbyBuffDevice = STATUS;

   for(i = 38; i < dwNumOfStr; i++)
   {
       if(*(pbyStr + i) == '\n')
       {
           boCheckEnd = true;
           byCount++;
       }
       //boCheckDevice = checkBuff(pbyStr, pbyBuffDevice, i);
       for(j = 0; j < strlen(pbyBuffDevice); j++)
       {
           if(*(pbyStr + i + j) != *(pbyBuffDevice + j))
           {
               boCheckDevice = false;
               break;
           }
           else
           {
               boCheckDevice = true;
           }
       }
       if(boCheckDevice)
       {
           for(k = 0; k < 8; k++)
           {
               if(!boCheckEnd)
               {
                   byBufferNetwEndpoint1[k] = *(pbyStr + i + k + 48);
               }
               else
               {
                   byBufferNetwEndpoint2[k] = *(pbyStr + i + k + 48);
               }
           }
           if(compareBuffer(&byBufferNetwEndpoint1[0], &byBufferNetwEndpoint2[0], 8) == true || byCount == 0)
           {
               bufClr(&byBufferNetwEndpoint2[0]);
           }
           else if(compareBuffer(&byBufferNetwEndpointTemp[0], &byBufferNetwEndpoint2[0], 8) == false)
           {
               byCountSwitch++;
               copyBuffer(&byBufferNetwEndpointTemp[0], &byBufferNetwEndpoint2[0], 8);
               bufClr(&byBufferNetwEndpoint2[0]);
           }
       }
   }
   copyBuffer(byBuffToken1, byBufferNetwEndpoint1, 8);
   copyBuffer(byBuffToken2, byBufferNetwEndpointTemp, 8);

   return byCountSwitch;
}

/**
 * @func bufClr
 * @brief Clear buffer
 * 
 * @param [byBuf] : Buffer needs to be cleared 
 * @return value : None 
 */
static void_t bufClr(u8_p pbyBuf)
{
    u8_t byLength = strlen(pbyBuf);
    u8_t i = 0;

    for (i = 0; i < byLength; i++)
    {
        *(pbyBuf + i) = 0;
    }
}

/**
 * @func compareBuffer
 * @brief Compare two arrays
 * 
 * @param byBuff1 
 * @param byBuff2 
 * @return bool_t 
 */
static bool_t compareBuffer(u8_p pbyBuff1, u8_p pbyBuff2, u8_t bySize)
{
    bool_t boCompare = true;
    u8_t i = 0;

    for(i = 0; i < bySize; i++)
    {
        if(*(pbyBuff1 + i) != *(pbyBuff2 + i))
        {	//WTF?
            boCompare = false;
            break;
        }
    }

    return boCompare;
}

/**
 * @brief Copy two arrays
 * 
 * @param byBuff1 
 * @param byBuff2 
 * @return void_t 
 */
static void_t copyBuffer(u8_p pbyBuff1, u8_p pbyBuff2, u8_t bySize)
{
    u8_t i = 0;

    for(i = 0; i < bySize; i++)
    {
       *(pbyBuff1 + i) = *(pbyBuff2 + i);
    }
}

/**
 * @brief Check text
 * 
 * @param [pbyStr] : String to check
 * @return bool_t 
 */
// static bool_t checkBuff(u8_p pbyStr, u8_p pbyBuff, u8_t point)
// {
//     u8_t i = 0;
//     bool_t boCheckText = false;

//     for(i = 0; i < strlen(pbyBuff); i++)
//     {
//         if(*(pbyStr + point + i) != *(pbyBuff + i))
//         {
//             boCheckText = false;
//             break;
//         }
//         else
//         {
//             boCheckText = true;
//         }
//     }

//     return boCheckText;
// }
