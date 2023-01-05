/*******************************************************************************
 *				 _ _                                             _ _
                |   |                                           (_ _)
                |   |        _ _     _ _   _ _ _ _ _ _ _ _ _ _   _ _
                |   |       |   |   |   | |    _ _     _ _    | |   |
                |   |       |   |   |   | |   |   |   |   |   | |   |
                |   |       |   |   |   | |   |   |   |   |   | |   |
                |   |_ _ _  |   |_ _|   | |   |   |   |   |   | |   |
                |_ _ _ _ _| |_ _ _ _ _ _| |_ _|   |_ _|   |_ _| |_ _|
                                (C)2021 Lumi
 * Copyright (c) 2023
 * Lumi, JSC.
 * All Rights Reserved
 *
 * File name: main.c
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
#include <stdlib.h>
#include "main.h"

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
#define FILENAME "log.txt"
#define MAXLENGTHFILE 5000

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
static u8_t byFileStr[MAXLENGTHFILE];

/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/
static u32_t dwFileToString(u8_p byStr);

/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/******************************************************************************/
int main(void_t)
{
    dwFileToString(byFileStr);
    return 0;
}

/**
 * @func dwFileToString
 * @brief Convert file to string
 * 
 * @param [byStr] : 
 * @return u32_t 
 */
static u32_t dwFileToString(u8_p byStr)
{
    u32_t dwStatus;
    FILE *fp = NULL;

    fp = fopen(FILENAME, "r");
    if(fp == NULL)
    {
        printf("File does not exit\n");
        return -1;
    }
    dwStatus = fread(byStr, MAXLENGTHFILE, 1, fp);

    printf("Noi dung cua file log.txt: \n%s", byStr);

    fclose(fp);
    fp = NULL;

    return dwStatus;
}

