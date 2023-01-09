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
 * File name: ban-tin.c
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
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
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
#define LENGTH_TIME_SET 21
#define LENGTH_TIME 12
#define FIRST 0
#define SECOND 1
#define THIRD 2
#define NUM_OF_DELAY_TIME 20

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
static void_t bufClr(u8_p buf);
static bool_t compareBuffer(u8_p pbyBuff1, u8_p pbyBuff2, u8_t bySize);
static void_t copyBuffer(u8_p pbyBuff1, u8_p pbyBuff2, u8_t bySize);
static void_t copyString(u8_p byBuff1, u8_p byBuff2, u32_t point, u8_t bySize);
static float_t convertTimeToSecond(u8_p pbyBuffer);

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

/**
 * @func soBanTinGuiTuThietBi
 * @brief Print out the log that was sent
 * 
 * @param [pbyStr] : String to parse
 * @param [dwNumOfStr] : Number of element of the Buffer
 * @return value : None
 */
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

/**
 * @func soCongTac
 * @brief Count switch
 * 
 * @param [pbyStr] : String to parse
 * @param [dwNumOfStr] : Number of element of the Buffer
 * @return u8_t 
 */
u8_t soCongTac(u8_p pbyStr, u32_t dwNumOfStr, u8_t byBuffToken1[],
    u8_t byBuffToken2[])
{
    u32_t i = 0;
    u8_t j = 0;
    u8_t byCount = 0;
    u8_t byCountSwitch = 1;
    u8_t byBufferNetwEndpoint1[LENGTH_NWT_ENDPOINT] = {0};
    u8_t byBufferNetwEndpoint2[LENGTH_NWT_ENDPOINT] = {0};
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
            if(memcmp(byBufferNetwEndpoint1, byBufferNetwEndpoint2, LENGTH_NWT_ENDPOINT) == 0 ||
                byCount == 0)
            {
                bufClr(&byBufferNetwEndpoint2[0]);
            }
            if(memcmp(byBufferNetwEndpointTemp, byBufferNetwEndpoint2, LENGTH_NWT_ENDPOINT) != 0)
            {
                byCountSwitch++;
                memcpy(byBufferNetwEndpointTemp, byBufferNetwEndpoint2, LENGTH_NWT_ENDPOINT);
                bufClr(&byBufferNetwEndpoint2[0]);
            }
        }
    }
    memcpy(byBuffToken1, byBufferNetwEndpoint1, LENGTH_NWT_ENDPOINT);
    byBuffToken1[LENGTH_NWT_ENDPOINT] = '\0';
    memcpy(byBuffToken2, byBufferNetwEndpointTemp, LENGTH_NWT_ENDPOINT);
    byBuffToken2[LENGTH_NWT_ENDPOINT] = '\0';

    return byCountSwitch;
}

/**
 * @func soBanTinGuiLoi
 * @brief Calculate the number of log not sent
 * 
 * @param [pbyStr] : String to parse
 * @param [dwNumOfStr] : Number of element of the Buffer
 * @return u8_t
 */
u8_t soBanTinGuiLoi(u8_p pbyStr, u32_t dwNumOfStr)
{
    u32_t i = 0;
    u8_t byCount = 0;
    u8_p pbyCompareSet = SET;
    u8_p pbyCompareStatus = STATUS;
    u8_p pbyCompareRequid = REQUID;
    u8_t pbyBufferSet[LENGTH_CODELOG] = {0};
    u8_t pbyBufferStatus[LENGTH_CODELOG] = {0};
    bool_t boCheckSet = false;
    bool_t boCheckStatus = false;
    bool_t boCheckRequid = false;
    bool_t boCheck = false;

    for(i = START_POINT_SET; i < dwNumOfStr; i++)
    {
        boCheckSet = compareText(pbyStr, pbyCompareSet, i);
        boCheckStatus = compareText(pbyStr, pbyCompareStatus, i);
        if(boCheckSet)
        {
            boCheckRequid = compareText(pbyStr, pbyCompareRequid,
                (i + LENGTH_SET_REQUID));
            if(boCheckRequid)
            {
                copyString(&pbyBufferSet[0], pbyStr, (i + LENGTH_SET_REQUID +
                    LENGTH_REQUID_CODELOG), LENGTH_CODELOG);
            }
        }
        else if(boCheckStatus)
        {
            boCheckRequid = compareText(pbyStr, pbyCompareRequid,
                (i + LENGTH_STATUS_REQUID));
            if(boCheckRequid)
            {
                boCheck = true;
                copyString(&pbyBufferStatus[0], pbyStr, (i + LENGTH_STATUS_REQUID +
                    LENGTH_REQUID_CODELOG), LENGTH_CODELOG);
            }
        }

        if(boCheck)
        {
            boCheck = false;
            if(strcmp(pbyBufferSet, pbyBufferStatus) != 0)
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
 * @func thoiGianTreLonNhat
 * @brief Calculate the max delay time
 * 
 * @param [pbyStr] : String to parse
 * @param [dwNumOfStr] : Number of element of the Buffer
 * @return float_t
 */
u32_t thoiGianTreLonNhat(u8_p pbyStr, u32_t dwNumOfStr)
{
    u32_t i = 0;
    u8_p pbyCompareSet = SET;
    u8_p pbyCompareStatus = STATUS;
    u8_t byBufferTimeSet[LENGTH_TIME] = {0};
    u8_t byBufferTimeStatus[LENGTH_TIME] = {0};
    float_t byBufferSecond[NUM_OF_DELAY_TIME] = {0};
    float_t fSetSecond = 0;
    float_t fStatusSecond = 0;
    float_t fDelaySecond = 0;
    float_t fDelayTempSecond = 0;
    u32_t dwDelayMaxSecond = 0;
    bool_t boCheckSet = false;
    bool_t boCheckStatus = false;
    bool_t boCheck = false;

    for(i = START_POINT_SET; i < dwNumOfStr; i++)
    {
        boCheckSet = compareText(pbyStr, pbyCompareSet, i);
        boCheckStatus = compareText(pbyStr, pbyCompareStatus, i);
        if(boCheckSet)
        {
            copyString(&byBufferTimeSet[0], pbyStr, (i - LENGTH_TIME_SET),
                LENGTH_TIME);
            fSetSecond = convertTimeToSecond(&byBufferTimeSet[0]);
        }
        else if(boCheckStatus)
        {
            boCheck = true;
            copyString(&byBufferTimeStatus[0], pbyStr, (i - LENGTH_TIME_SET),
                LENGTH_TIME);
            fStatusSecond = convertTimeToSecond(&byBufferTimeStatus[0]);
        }

        if(boCheck)
        {
            boCheck = false;
            fDelaySecond = fStatusSecond - fSetSecond;
            if(fDelayTempSecond < fDelaySecond)
            {
                fDelayTempSecond = fDelaySecond;
            }
        }
    }
    dwDelayMaxSecond = fDelayTempSecond * 1000;

    return dwDelayMaxSecond;
}

/**
 * @func thoiGianTreTrungBinh
 * @brief Calculate the average time
 * 
 * @param [pbyStr] : String to parse
 * @param [dwNumOfStr] : Number of element of the Buffer
 * @return u32_t 
 */
u32_t thoiGianTreTrungBinh(u8_p pbyStr, u32_t dwNumOfStr)
{
    u32_t i = 0;
    u8_t byCount = 1;
    u8_t byCountTemp = 0;
    u8_p pbyCompareSet = SET;
    u8_p pbyCompareStatus = STATUS;
    u8_t byBufferTimeSet[LENGTH_TIME] = {0};
    u8_t byBufferTimeStatus[LENGTH_TIME] = {0};
    float_t fBufferSecond[NUM_OF_DELAY_TIME] = {0};
    float_t fSetSecond = 0;
    float_t fStatusSecond = 0;
    float_t fDelaySecond = 0;
    float_t fDelayTempSecond = 0;
    u32_t dwDelayAverageSecond = 0;
    bool_t boCheckSet = false;
    bool_t boCheckStatus = false;
    bool_t boCheck = false;

    for(i = START_POINT_SET; i < dwNumOfStr; i++)
    {
        boCheckSet = compareText(pbyStr, pbyCompareSet, i);
        boCheckStatus = compareText(pbyStr, pbyCompareStatus, i);
        if(boCheckSet)
        {
            copyString(&byBufferTimeSet[0], pbyStr, (i - LENGTH_TIME_SET),
                LENGTH_TIME);
            fSetSecond = convertTimeToSecond(&byBufferTimeSet[0]);
        }
        else if(boCheckStatus)
        {
            boCheck = true;
            copyString(&byBufferTimeStatus[0], pbyStr, (i - LENGTH_TIME_SET),
                LENGTH_TIME);
            fStatusSecond = convertTimeToSecond(&byBufferTimeStatus[0]);
        }

        if(boCheck)
        {
            boCheck = false;
            fDelaySecond = fStatusSecond - fSetSecond;
            fDelayTempSecond = (fDelayTempSecond * byCountTemp) / byCount +
                (fDelaySecond / byCount);
            byCountTemp = byCount;
            byCount++;
        }
    }
    dwDelayAverageSecond = fDelayTempSecond * 1000;

    return dwDelayAverageSecond;
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
 * @func compareText
 * @brief Compare string
 * 
 * @param [pbyStr] : Buffer needs to be copied
 * @param [pbyBuff] : Buffer to be copied
 * @param [point] : Location to copy
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

/**
 * @func copyString
 * @brief Copy Buff2 into Buff1
 * 
 * @param [byBuff1] : Buffer is copied data
 * @param [byBuff2] : Buffer needs to copy data
 * @param [point] : The position of byBuffer is copied
 * @param [bySize] : Buffer size copied
 * @return void_t 
 */
static void_t copyString(u8_p byBuff1, u8_p byBuff2, u32_t point, u8_t bySize)
{
    uint8_t i = 0;

    for(i = 0; i < bySize; i++)
    {
        *(byBuff1 + i) = *(byBuff2 + i + point);
    }
}

/**
 * @func convertTimeToSecond
 * @brief Convert time to seconds
 * 
 * @param [pbyBuffer] : Buffer to parse
 * @return float_t 
 */
static float_t convertTimeToSecond(u8_p pbyBuffer)
{
    float_t byHour = 0;
    float_t byMinute = 0;
    float_t bySecond = 0;
    u8_t byCount = 0;
    u8_p byToken = strtok(pbyBuffer, ":");

    while(byToken != NULL )
    {
        switch(byCount)
        {
            case FIRST:
            {
                byHour = atof(byToken);
            }break;
            case SECOND:
            {
                byMinute = atof(byToken);
            }break;
            case THIRD:
            {
                bySecond = atof(byToken);
            }break;
            default:
                break;
        }
        byToken = strtok(NULL, ":");
        byCount++;
    }
    bySecond = bySecond + byMinute * 60 + byHour * 3600;

    return bySecond;
}
