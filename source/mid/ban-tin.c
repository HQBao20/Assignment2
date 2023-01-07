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
#define SET "set"
#define STATUS "status"
#define CMD "cmd"
#define RAW "raw"
#define REQUID "reqid"
#define LENGTH_NWT_ENDPOINT 8
#define START_POINT_SET 38
#define START_POINT_NWT 48
#define START_POINT_RAW 153
#define LENGTH_NWT_RAW 6
#define LENGTH_SET_REQUID 138
#define LENGTH_STATUS_REQUID 152
#define LENGTH_REQUID_CODELOG 9
#define LENGTH_CODELOG 4

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/
static bool_t compareText(u8_p pbyStr, u8_p pbyBuff, u32_t point);
static bool_t compareMultiText(u8_p pbyStr, u8_p pbyBuff1, u8_p pbyBuff2, 
    u32_t point);
static void_t bufClr(u8_p buf);
static bool_t compareBuffer(u8_p pbyBuff1, u8_p pbyBuff2, u8_t bySize);
static void_t copyBuffer(u8_p pbyBuff1, u8_p pbyBuff2, u8_t bySize);
static void_t copyString(u8_p byBuff1, u8_p byBuff2, u32_t point, u8_t bySize);

/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/******************************************************************************/
u8_t soBanTinGuiDi(u8_p pbyStr, u32_t dwNumOfStr)
{
    u32_t i = 0;
    u8_t byCount = 0;
    u8_p pbyCompareStr = SET;
    bool_t boCheckStatus = false;

    for(i = START_POINT_SET; i < dwNumOfStr; i++)
    {
        boCheckStatus = compareText(pbyStr, pbyCompareStr, i);
        if(boCheckStatus)
        {
            byCount++;
        }
    }

    return byCount;
}

u8_t soBanTinGuiTuThietBi(u8_p pbyStr, u32_t dwNumOfStr, u8_t byBuffer[])
{
    u32_t i = 0;
    u8_p pbyCompareStr = RAW;
    bool_t boCheckStatus = false;
    bool_t boCheckNWT = false;
    u8_t byCount = 0;

    for(i = START_POINT_RAW; i < dwNumOfStr; i++)
    {
        boCheckStatus = compareText(pbyStr, pbyCompareStr, i);
        if(boCheckStatus)
        {
            boCheckNWT = compareText(pbyStr, &byBuffer[0], (i + LENGTH_NWT_RAW));
        }
        if(boCheckNWT)
        {
        	boCheckNWT = false;
            byCount++;
        }
    }

    return (byCount / 2);
}

u8_t soCongTac(u8_p pbyStr, u32_t dwNumOfStr, u8_t byBuffToken1[], u8_t byBuffToken2[])
{
   u32_t i = 0;
   u8_t j = 0;
   u8_t byCount = 0;
   u8_t byCountSwitch = 1;
   u8_t byBufferNetwEndpoint1[LENGTH_NWT_ENDPOINT];
   u8_t byBufferNetwEndpoint2[LENGTH_NWT_ENDPOINT];
   u8_t byBufferNetwEndpointTemp[LENGTH_NWT_ENDPOINT] = {0};
   u8_p pbyCompareStr = SET;
   bool_t boCheckEnd = false;
   bool_t boCompare = false;

   for(i = START_POINT_SET; i < dwNumOfStr; i++)
   {
        if(*(pbyStr + i) == '\n')
        {
            boCheckEnd = true;
            byCount++;
        }
        boCompare = compareText(pbyStr, pbyCompareStr, i);
        if(boCompare)
        {
            for(j = 0; j < LENGTH_NWT_ENDPOINT; j++)
            {
                if(!boCheckEnd)
                {
                    byBufferNetwEndpoint1[j] = *(pbyStr + i + j + START_POINT_NWT);
                }
                else
                {
                    byBufferNetwEndpoint2[j] = *(pbyStr + i + j + START_POINT_NWT);
                }
            }
            if(compareBuffer(&byBufferNetwEndpoint1[0], &byBufferNetwEndpoint2[0],
                LENGTH_NWT_ENDPOINT) == true || byCount == 0)
            {
                bufClr(&byBufferNetwEndpoint2[0]);
            }
            else if(compareBuffer(&byBufferNetwEndpointTemp[0], &byBufferNetwEndpoint2[0],
                LENGTH_NWT_ENDPOINT) == false)
            {
                byCountSwitch++;
                copyBuffer(&byBufferNetwEndpointTemp[0], &byBufferNetwEndpoint2[0],
                    LENGTH_NWT_ENDPOINT);
                bufClr(&byBufferNetwEndpoint2[0]);
            }
        }
    }
    copyBuffer(byBuffToken1, byBufferNetwEndpoint1, LENGTH_NWT_ENDPOINT);
    copyBuffer(byBuffToken2, byBufferNetwEndpointTemp, LENGTH_NWT_ENDPOINT);

    return byCountSwitch;
}

u8_t soBanTinGuiLoi(u8_p pbyStr, u32_t dwNumOfStr)
{
    u32_t i = 0;
    u8_t j = 0;
    u8_t byCount = 0;
    u8_p pbyCompareSet = SET;
    u8_p pbyCompareStatus = STATUS;
    u8_p pbyCompareRequid = REQUID;
    u8_t pbyBufferSet[LENGTH_CODELOG] = {0};
    u8_t pbyBufferStatus[LENGTH_CODELOG] = {0};
    bool_t boCheckSetStatus = false;
    bool_t boCheckRequid = false;
    bool_t boCheckStatus = false;

    for(i = START_POINT_SET; i < dwNumOfStr; i++)
    {
        boCheckSetStatus = compareMultiText(pbyStr, pbyCompareSet,
            pbyCompareStatus, i);
        if(boCheckSetStatus)
        {
            boCheckRequid = compareText(pbyStr, pbyCompareRequid,
                (i + LENGTH_SET_REQUID));
            if(boCheckRequid)
            {
                copyString(&pbyBufferSet[0], pbyStr, (i + LENGTH_SET_REQUID +
                    LENGTH_REQUID_CODELOG), LENGTH_CODELOG);
            }
        }
        else
        {
            boCheckRequid = compareText(pbyStr, pbyCompareRequid,
                (i + LENGTH_STATUS_REQUID));
            if(boCheckRequid)
            {
                boCheckStatus = true;
                copyString(&pbyBufferStatus[0], pbyStr, (i + LENGTH_STATUS_REQUID +
                    LENGTH_REQUID_CODELOG), LENGTH_CODELOG);
            }
        }

        if(boCheckStatus)
        {
            boCheckStatus = false;
            if(compareBuffer(pbyBufferSet, pbyBufferStatus, LENGTH_CODELOG) == false)
            {
                byCount++;
                bufClr(pbyBufferSet);
                bufClr(pbyBufferStatus);
            }
        }
    }

    return byCount;
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
        {
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
 * @func compareText
 * @brief Compare string
 * 
 * @param pbyStr 
 * @param pbyBuff 
 * @param point 
 * @return bool_t 
 */
static bool_t compareText(u8_p pbyStr, u8_p pbyBuff, u32_t point)
{
    u8_t i = 0;
    bool_t boCheckString = false;

    for(i = 0; i < strlen(pbyBuff); i++)
    {
        if(*(pbyStr + point + i) != *(pbyBuff + i))
        {
            boCheckString = false;
            break;
        }
        else
        {
            boCheckString = true;
        }
    }

    return boCheckString;
}

static bool_t compareMultiText(u8_p pbyStr, u8_p pbyBuff1, u8_p pbyBuff2,
    u32_t point)
{
    u8_t i = 0;
    bool_t boCheckString = false;

    for(i = 0; i < strlen(pbyBuff1); i++)
    {
        if(*(pbyStr + point + i) != *(pbyBuff1 + i))
        {
            boCheckString = false;
            break;
        }
        else
        {
            boCheckString = true;
        }
    }
    for(i = 0; i < strlen(pbyBuff2); i++)
    {
        if(*(pbyStr + point + i) != *(pbyBuff2 + i))
        {
            boCheckString = true;
            break;
        }
        else
        {
            boCheckString = false;
        }
    }

    return boCheckString;
}

static void_t copyString(u8_p byBuff1, u8_p byBuff2, u32_t point, u8_t bySize)
{
    uint8_t i = 0;

    for(i = 0; i < bySize; i++)
    {
        *(byBuff1 + i) = *(byBuff2 + i + point);
    }
}