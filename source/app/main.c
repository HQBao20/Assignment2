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
#include <string.h>
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
static u32_t dwFileToString(u8_p pbyStr);
static void_t printNetwEndpoint(u8_p pbyBuff);

/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/******************************************************************************/
int main(void_t)
{
    u8_t byNumBanTinGuiDi = 0;
    u8_t byNumBanTinGuiDiThietBi = 0;
    u8_t byNumSwitch = 0;
    u8_t byBuffer[4];
    u8_t byBuffTok1[8];
    u8_t byBuffTok2[8];

    dwFileToString(byFileStr);
    byNumBanTinGuiDi = soBanTinGuiDi(byFileStr, strlen(byFileStr));
    printf("\nSo ban tin duoc gui di la: %d", byNumBanTinGuiDi);
    printf("\nNhap networking: ");
    gets(byBuffer);
    byNumBanTinGuiDiThietBi = soBanTinGuiTuThietBi(byFileStr, strlen(byFileStr), byBuffer);
    printf("\nSo ban tin duoc gui di tu thiet bi: %d", byNumBanTinGuiDiThietBi);
//    byNumSwitch = soCongTac(byFileStr, strlen(byFileStr), &byBuffTok1[0], &byBuffTok2[0]);
//    printf("\nSo cong tac la: %d", byNumSwitch);
//    printNetwEndpoint(&byBuffTok1[0]);
//    printNetwEndpoint(&byBuffTok2[0]);

    return 0;
}

/**
 * @func dwFileToString
 * @brief Convert file to string
 * 
 * @param [byStr] : 
 * @return u32_t 
 */
static u32_t dwFileToString(u8_p pbyStr)
{
    u32_t dwStatus;
    FILE *fp = NULL;

    fp = fopen(FILENAME, "r");
    if(fp == NULL)
    {
        printf("File does not exit\n");
        return -1;
    }
    dwStatus = fread(pbyStr, MAXLENGTHFILE, 1, fp);

    printf("Noi dung cua file log.txt: \n%s", pbyStr);

    fclose(fp);
    fp = NULL;

    return dwStatus;
}

static void_t printNetwEndpoint(u8_p pbyBuff)
{
    u8_p byToken = strtok(pbyBuff, "-");

    printf("\nNWK - %s, ", byToken);
    byToken = strtok(NULL, "-");
    printf("ENDPOINT - %s", byToken);
}
