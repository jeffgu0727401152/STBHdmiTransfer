/*
 * PlayerCmdServer.h
 *
 *  Created on: 2013-1-18
 *      Author: kyo
 */

#pragma once

#define HTTPCMD_VER	(int)0xDCBAABCD

#define HTTPCMD_SOCKETPORT 1280

typedef struct tagHTTPCMDHEADER
{
	int nHttpCmdVer;
	int nRequestID;
	int nCommandType;
	UINT64 uPrivData;

	// return buffer size
	UINT32 uSize;
} HTTPCMDHEADER;

// reboot Command
#define HTTPCMD_REQ_REBOOT			0
#define HTTPCMD_RES_REBOOT			1
typedef struct tagHTTPCMDREQREBOOTCMD : public HTTPCMDHEADER
{
} HTTPCMDREQREBOOTCMD;
typedef struct tagHTTPCMDRESREBOOTCMD : public HTTPCMDHEADER
{
} HTTPCMDRESREBOOTCMD;

// pause Command
#define HTTPCMD_REQ_PAUSE				2
#define HTTPCMD_RES_PAUSE				3
typedef struct tagHTTPCMDREQPAUSECMD : public HTTPCMDHEADER
{
	int nSecondsPerImage;
	RECT rcImagePosition;
	int nImageUrlBufLength;
} HTTPCMDREQPAUSECMD;
typedef struct tagHTTPCMDRESPAUSECMD : public HTTPCMDHEADER
{
} HTTPCMDRESPAUSECMD;

// resume Command
#define HTTPCMD_REQ_RESUME			4
#define HTTPCMD_RES_RESUME			5
typedef struct tagHTTPCMDREQRESUMECMD : public HTTPCMDHEADER
{
} HTTPCMDREQRESUMECMD;
typedef struct tagHTTPCMDRESRESUMECMD : public HTTPCMDHEADER
{
} HTTPCMDRESRESUMECMD;

// close room Command
#define HTTPCMD_REQ_CLOSEROOM	6
#define HTTPCMD_RES_CLOSEROOM	7
typedef struct tagHTTPCMDREQCLOSEROOMCMD : public HTTPCMDHEADER
{
	int nVideoUrlBufLength;
} HTTPCMDREQCLOSEROOMCMD;
typedef struct tagHTTPCMDRESCLOSEROOMCMD : public HTTPCMDHEADER
{
} HTTPCMDRESCLOSEROOMCMD;

// open room Command
#define HTTPCMD_REQ_OPENROOM	8
#define HTTPCMD_RES_OPENROOM	9
typedef struct tagHTTPCMDREQOPENROOMCMD : public HTTPCMDHEADER
{
	char cQRCodeString[1024];
	RECT rcQRCodePosition;
	int nVideoUrlBufLength;
} HTTPCMDREQOPENROOMCMD;
typedef struct tagHTTPCMDRESOPENROOMCMD : public HTTPCMDHEADER
{
} HTTPCMDRESOPENROOMCMD;

// check status Command
#define HTTPCMD_REQ_CHECKSTATUS	10
#define HTTPCMD_RES_CHECKSTATUS	11
typedef struct tagHTTPCMDREQCHECKSTATUSCMD : public HTTPCMDHEADER
{
} HTTPCMDREQCHECKSTATUSCMD;
typedef struct tagHTTPCMDRESCHECKSTATUSCMD : public HTTPCMDHEADER
{
} HTTPCMDRESCHECKSTATUSCMD;

// close room Command
#define HTTPCMD_REQ_PAYCALLBACK	12
#define HTTPCMD_RES_PAYCALLBACK	13
typedef struct tagHTTPCMDREQPAYCALLBACKCMD : public HTTPCMDHEADER
{
	int nVideoUrlBufLength;
} HTTPCMDREQPAYCALLBACKCMD;
typedef struct tagHTTPCMDRESPAYCALLBACKCMD : public HTTPCMDHEADER
{
} HTTPCMDRESPAYCALLBACKCMD;