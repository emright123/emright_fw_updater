// SPDX-License-Identifier: GPL-2.0
/*
 * Hidraw Userspace Example
 *
 * Copyright (c) 2010 Alan Ott <alan@signal11.us>
 * Copyright (c) 2010 Signal 11 Software
 *
 * The code may be used by anyone for any purpose,
 * and can serve as a starting point for developing
 * applications using hidraw.
 */

/* Linux */
#include <linux/types.h>
#include <linux/input.h>
#include <linux/hidraw.h>
#include "hidapi.h"
/*
 * Ugly hack to work around failing compilation on systems that don't
 * yet populate new version of hidraw.h to userspace.
 */
#ifndef HIDIOCSFEATURE
#warning Please have your distro update the userspace kernel headers
#define HIDIOCSFEATURE(len)    _IOC(_IOC_WRITE|_IOC_READ, 'H', 0x06, len)
#define HIDIOCGFEATURE(len)    _IOC(_IOC_WRITE|_IOC_READ, 'H', 0x07, len)
#endif

/* Unix */
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* C */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>
	int HID_API_EXPORT get_FW_Version(void);
	int HID_API_EXPORT get_Ckecksum(void);
	int HID_API_EXPORT update_FW(/*void*/char*);
	unsigned char nIspDataByte = 32;
	unsigned char byteDumpBuf[0x8000] = { 0 };
	#define _n6573FW_VER_ 0x01
	#define CMD_OK 0x01
	#define DATA_8BYTEOK 0xE1
	#define DATA_WRITEEND 0xEF
	#define	DATA_ERR 0xE0
	#define	DATA_PAGEOK	0xE2
	#define _USB_BUF_LEN_  32
	#define	_ISP_DATA_ID  0x99
	#define	_ISP_DATA_ID_AX8 0x98
	#define	_nRdSfr_CMD_NO	21
    	#define	_nCMD_LEN	(8+1)
	#define	_nWrSpp_CMD1_NO	3
	#define	_nWrSpp_CMD3_NO	2
	#define	_nWrSpp_TAB_NO	2
	#define	_nISP_VERSION_ASIC7_ 0x10
	#define	_nIAP_VERSION_V22_	0xA6
	#define	_nIAP_VERSION_V30_	0xB0
	#define	_nIAP_VERSION_SUB_	0x10

	bool	bIsIapMode = 1;
	int fd;
	const char *bus_str(int bus);
	char buf[256];
	int CHS = 0;
int main(int argc, char **argv)
{
	
	int res,x,RST;
	struct hidraw_report_descriptor rpt_desc;
	struct hidraw_devinfo info;
	char *path; 
	__s16 vid,pid;
	const char *device = "/dev/hidraw1";
	/*if (argc > 1)
		device = argv[1];*/
	for(int a = 0 ; a < 17 ; a++){
		/* Open the Device with non-blocking reads. In real life,
	   	don't use a hard coded path; use libudev instead. */
		fd = open(device, O_RDWR,0666);//O_NONBLOCK
	
		//if (fd < 0) {
		//	perror("Unable to open device");
		//	return 1;
		//}
		memset(&rpt_desc, 0x0, sizeof(rpt_desc));
		memset(&info, 0x0, sizeof(info));
		memset(buf, 0x0, sizeof(buf));
		path = argv[2];

		// Get Raw Info 
		res = ioctl(fd, HIDIOCGRAWINFO, &info);
		if (res < 0) {
			//perror("HIDIOCGRAWINFO");
		} else {
			/*printf("Raw Info:\n");
			printf("\tbustype: %d (%s)\n",
				info.bustype, bus_str(info.bustype));
			printf("\tvendor: 0x%04hx\n", info.vendor);
			printf("\tproduct: 0x%04hx\n", info.product);*/
			vid = info.vendor;
			pid = info.product;
			//printf("VID:%X ,PID:%04hX\n",vid,pid);
		}
	
		if((vid == 11368) /*&& (pid == 58933)*/){
			// Get Raw Name 
			//res = ioctl(fd, HIDIOCGRAWNAME(256), buf);
			//if (res < 0)
			//	perror("HIDIOCGRAWNAME");
			//else
			//	printf("\nRaw Name: %s\n", buf);
	
			//printf(" 1- get_FW_Version\n 2- get_Ckecksum\n 3- update_FW\n");
			//printf("Choose your select\n");
			//scanf("%d",&x);
			sscanf(argv[1],"%d",&x);
			//printf("%d\n",x);
			switch (x)
			{
			case 1: 
				RST = get_FW_Version();
				printf("%d",RST);
				//printf("Get Firmware Success!!\n");
				break;
			case 2:
				//printf("----- Please wait!! -----\n");
				RST = get_Ckecksum();
				printf("%d",RST);
				//printf("Get Checksum Success!!\n");
				break;
			case 3:
				RST = update_FW(path); ///home/emright/Documents/Chrome116_HP_V0001_ASIC8_20190813_52D9.BIN /*path*/
				//printf("Update Firmware Success!!\n");
				printf("%d",RST);
				break;
			default://get_FW_Version();
				break;
			}	
			break;
		}else
		{
			close(fd);
			//a++;
			switch(a)
			{
			case 0:	
				device = "/dev/hidraw0";
				break;
			case 1:	
				device = "/dev/hidraw1";
				break;
			case 2:	
				device = "/dev/hidraw2";
				break;
			case 3:	
				device = "/dev/hidraw3";
				break;
			case 4:	
				device = "/dev/hidraw4";
				break;
			case 5:	
				device = "/dev/hidraw5";
				break;
			case 6:	
				device = "/dev/hidraw6";
				break;
			case 7:	
				device = "/dev/hidraw7";
				break;
			case 8:	
				device = "/dev/hidraw8";
				break;
			case 9:	
				device = "/dev/hidraw9";
				break;
			case 10:	
				device = "/dev/hidraw10";
				break;
			case 11:	
				device = "/dev/hidraw11";
				break;
			case 12:	
				device = "/dev/hidraw12";
				break;
			case 13:	
				device = "/dev/hidraw13";
				break;
			case 14:	
				device = "/dev/hidraw14";
				break;
			case 15:	
				device = "/dev/hidraw15";
				break;

			case 16:printf("Please check your device,thx!\n");
			}
		}
	}
	close(fd);
	return RST;
}

int get_FW_Version(void)
{
	int res,result[50],R;
	// Send a Feature Report to the device
	buf[0] = 0x01;
	buf[1] = 0x04;
	buf[2] = 0x00;
	buf[3] = 0x00;
	buf[4] = 0x00;
	res = ioctl(fd, HIDIOCSFEATURE(5), buf);
	if (res < 0) {
		printf("Unable to send a feature report.\n");
	}
	sleep(1);
	// Read a Feature Report from the device
	buf[0] = 0x01;
	res = ioctl(fd, HIDIOCGFEATURE(256), buf);
	if (res < 0) {
		//printf("Unable to get a feature report.\n");
		//printf("%ls", hid_error(fd));
	}
	else {
		// Print out the returned buffer.
		//printf("Feature Report\n   ");
		for (int i = 0; i < res; i++)
			buf[i];
			//printf("%02hhx \n", buf[i]);
		//printf("\n");
	}
	//printf("The Firmware Version is %2x.%02x\n",buf[2],buf[1]);
	result[2] = buf[2];
	result[1] = buf[1];
	R = result[2]*100 + result[1];
	return R;
}

int get_Ckecksum(void) 
{
	bool bRet = true;
	int result=1;
	unsigned char 	_cmdEnterISPMode_I2C[4] = { 0x84, 0x00, 0x01, 0x05 };
	unsigned char   _cmdISPReadStart[4] = { 0x84, 0x02, 0x00 ,0x06 };
	unsigned char   _cmdEnterIAPMode_I2C[4] = { 0x84, 0x00, 0x10, 0x14 };
	unsigned char   _cmdGetACK[2];
	unsigned short m_lnDownloadSize, g_dwDownloadStart, wDumpStartPos,g_ucCheckSum,nDumpIdx;
	m_lnDownloadSize = 0x8000;
	g_dwDownloadStart = 0;
	
	unsigned char byteReadBuf[_USB_BUF_LEN_ + 1] = { 0 };
	nDumpIdx = 0;
	g_ucCheckSum = 0;
	
	bRet = write(fd, _cmdEnterIAPMode_I2C/* _cmdEnterISPMode_I2C*/, 4);
	if (!bRet) {
		printf("Error write EnterISPMode!");
		return false;
	}
	if (!read(fd, _cmdGetACK, sizeof(_cmdGetACK)))
	{
		printf("Error read EnterIAPMode!");
		return false;
	}
	if (CMD_OK != _cmdGetACK[1])
	{
		printf("CMD Error!");
		return false;
	}
     	/*for (int i = 0; i < sizeof(_cmdGetACK); i++)
			printf("123 %02hhx ", _cmdGetACK[i]);
		printf("\n");*/

	unsigned short dwTemp = m_lnDownloadSize - g_dwDownloadStart;
	_cmdISPReadStart[2] = (dwTemp / 128 / 4);
	_cmdISPReadStart[3] = _cmdISPReadStart[0] ^ _cmdISPReadStart[1] ^ _cmdISPReadStart[2] ^ 0x80;
	if (!write(fd, _cmdISPReadStart, 4))
	{
		printf("Error write ISPReadStart!");
		return false;
	}
	if (!read(fd, _cmdGetACK, sizeof(_cmdGetACK)))
	{
		printf("Error read ISPReadStart!");
		return false;
	}
	if (CMD_OK != _cmdGetACK[1]) 
	{
		printf("CMD Error!");
		return false;
	}
	
	wDumpStartPos = g_dwDownloadStart + 0x1000;
	for (unsigned short nCount = 0; nCount < m_lnDownloadSize /*- g_dwDownloadStart*/; nCount += nIspDataByte) 
	{
		if(!read(fd, byteReadBuf, nIspDataByte+1))
		{
			printf("Error read byteReadData!");
			return false;
		}

		if(nCount < (m_lnDownloadSize - g_dwDownloadStart - nIspDataByte)){
			 _cmdGetACK[1] = DATA_8BYTEOK ;
		}
		else _cmdGetACK[1] = DATA_WRITEEND;
		if (!write(fd, _cmdGetACK, 2))
		{
			printf("Error write ISPReadData!");
			return false;
		}
		for (int nRdIdx = 1; nRdIdx <= nIspDataByte; nRdIdx++)
		{
			byteDumpBuf[nDumpIdx] = byteReadBuf[nRdIdx];
			g_ucCheckSum += byteReadBuf[nRdIdx];
			nDumpIdx++;
		}
		//printf("[%Xh , %Xh] 0x%X \n", 0x8000 + wDumpStartPos, 0x8000 + nDumpIdx - 1, g_ucCheckSum);
	}
	if(CHS == 0){
		//printf("[%xh , %xh] 0x%x\n", (0x8000+wDumpStartPos), (0x8000 + nDumpIdx - 1), g_ucCheckSum);
		result = 0;
	}
	return result;
}

int update_FW(char *path) 
{
	FILE *fp;
	CHS = 1;
	int result=1;
	char bin[500];
	unsigned short data[65536];
	unsigned char   _cmdGetACK[2];
	unsigned char _cmdGetACK3[3];
	unsigned short g_dwDownloadStart,m_lnDownloadSize = 0,readSize = 0 , g_ucCheckSum;
	unsigned char byteWriteBuf[_USB_BUF_LEN_ + 1] = { _ISP_DATA_ID, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	unsigned char byteReadBuf[_USB_BUF_LEN_ + 2] = { _ISP_DATA_ID, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	unsigned char 	_cmdISPGetVersion[4] = { 0x84, 0x04, 0x00, 0x00 };
	unsigned char   _cmdEnterIAPMode_I2C[4] = { 0x84, 0x00, 0x10, 0x14 };
	unsigned char	_cmdExitISPMode[4] = { 0x84 ,0x06 ,0x00 ,0x00 };
	unsigned char _cmdRdSfrStatus[_nRdSfr_CMD_NO][_nCMD_LEN] =
		//           0,    1,    2,    3,    4,    5,    6,    7,    8,} //    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,   19,   20,   21,   22,   23,   24,   25,   26,   27,   28,   29,   30,   31,   32  //
	{ { 0x98, 0x87, 0x05, 0x0E, 0x0A, 0x00, 0x31, 0x37, 0x00 }, 	//1.   swap PROM to XDATA (ISP Mode enable): XSFR[70A]=ucISPCtrl=0x31	
	{ 0x98, 0x86, 0x06, 0x0E, 0x0A, 0x00, 0x04, 0x00, 0x00 },   	//1.b  read ISP MODE status XSFR[70A]
	{ 0x98, 0x87, 0x05, 0x12, 0x08, 0x00, 0x20, 0x38, 0x00 },   	//2.b  Swap XDATA to eFlash SFR[.] Read Mode : XSFR[908]=ucEFCTLR[0]=0x20	

	{ 0x98, 0x86, 0x06, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00 }, 	//3.b  Read eFlash Protect SFR[.] Status: SFR[800E]?=0x3D/0x7D (.DISPUMP?=0/1)
	{ 0x98, 0x86, 0x06, 0x00, 0x01, 0x40, 0x41, 0x00, 0x00 }, 	//3.c  Read eFlash Protect SFR[.] Status: SFR[800F]
	{ 0x98, 0x86, 0x06, 0x00, 0x02, 0x40, 0x42, 0x00, 0x00 }, 	//3.b  Read eFlash Protect SFR[.] Status: SFR[800E]?=0x3D/0x7D (.DISPUMP?=0/1)
	{ 0x98, 0x86, 0x06, 0x00, 0x03, 0x40, 0x43, 0x00, 0x00 }, 	//3.c  Read eFlash Protect SFR[.] Status: SFR[800F]
	{ 0x98, 0x86, 0x06, 0x00, 0x04, 0x40, 0x44, 0x00, 0x00 }, 	//3.b  Read eFlash Protect SFR[.] Status: SFR[800E]?=0x3D/0x7D (.DISPUMP?=0/1)
	{ 0x98, 0x86, 0x06, 0x00, 0x05, 0x40, 0x45, 0x00, 0x00 }, 	//3.c  Read eFlash Protect SFR[.] Status: SFR[800F]
	{ 0x98, 0x86, 0x06, 0x00, 0x06, 0x40, 0x46, 0x00, 0x00 }, 	//3.b  Read eFlash Protect SFR[.] Status: SFR[800E]?=0x3D/0x7D (.DISPUMP?=0/1)
	{ 0x98, 0x86, 0x06, 0x00, 0x07, 0x40, 0x47, 0x00, 0x00 }, 	//3.c  Read eFlash Protect SFR[.] Status: SFR[800F]
	{ 0x98, 0x86, 0x06, 0x00, 0x08, 0x40, 0x48, 0x00, 0x00 }, 	//3.b  Read eFlash Protect SFR[.] Status: SFR[800E]?=0x3D/0x7D (.DISPUMP?=0/1)
	{ 0x98, 0x86, 0x06, 0x00, 0x09, 0x40, 0x49, 0x00, 0x00 }, 	//3.c  Read eFlash Protect SFR[.] Status: SFR[800F]
	{ 0x98, 0x86, 0x06, 0x00, 0x0A, 0x40, 0x4A, 0x00, 0x00 }, 	//3.b  Read eFlash Protect SFR[.] Status: SFR[800E]?=0x3D/0x7D (.DISPUMP?=0/1)
	{ 0x98, 0x86, 0x06, 0x00, 0x0B, 0x40, 0x4B, 0x00, 0x00 }, 	//3.c  Read eFlash Protect SFR[.] Status: SFR[800F]
	{ 0x98, 0x86, 0x06, 0x00, 0x0C, 0x40, 0x4C, 0x00, 0x00 }, 	//3.b  Read eFlash Protect SFR[.] Status: SFR[800E]?=0x3D/0x7D (.DISPUMP?=0/1)
	{ 0x98, 0x86, 0x06, 0x00, 0x0D, 0x40, 0x4D, 0x00, 0x00 }, 	//3.c  Read eFlash Protect SFR[.] Status: SFR[800F]
	{ 0x98, 0x86, 0x06, 0x00, 0x0E, 0x40, 0x4E, 0x00, 0x00 }, 	//3.b  Read eFlash Protect SFR[.] Status: SFR[800E]?=0x3D/0x7D (.DISPUMP?=0/1)
	{ 0x98, 0x86, 0x06, 0x00, 0x0F, 0x40, 0x4F, 0x00, 0x00 }, 	//3.c  Read eFlash Protect SFR[.] Status: SFR[800F]
	//			 {0x98, 0x86, 0x16, 0x00, 0x0E, 0x40, 0x5E, 0x00, 0x00}, //3.b  Read eFlash Protect SFR[.] Status: SFR[800E]?=0x3D/0x7D (.DISPUMP?=0/1)
	//			 {0x98, 0x86, 0x16, 0x00, 0x0F, 0x40, 0x5F, 0x00, 0x00}, //3.c  Read eFlash Protect SFR[.] Status: SFR[800F]
	{ 0x98, 0x87, 0x05, 0x12, 0x08, 0x00, 0x00, 0x18, 0x00 },   //4.   Swap SPP[.]/SFR[.] to XDATA: XSFR[908]=ucEFCTLR[0]=0x00	
	{ 0x98, 0x87, 0x05, 0x0E, 0x0A, 0x00, 0x30, 0x36, 0x00 } }; //5.   swap XDATA to PROM (ISP Mode disable): XSFR[70A]=ucISPCtrl=0x30

	unsigned char	_cmdSpp_IntoSfrMode[_nWrSpp_CMD1_NO][_nCMD_LEN] = {
	 {0x98, 0x87, 0x05, 0x0E, 0x0A, 0x00, 0x31, 0x37, 0x00},  //1.   swap PROM to XDATA (ISP Mode enable): XSFR[70A]=ucISPCtrl=0x31		
	 {0x98, 0x87, 0x05, 0x12, 0x08, 0x00, 0x10, 0x08, 0x00},  //2.a  Swap XDATA to eFlash SFR[.] Write Mode: XSFR[908]=ucEFCTLR[0]=0x10
    	 {0x98, 0x87, 0x05, 0x12, 0x09, 0x00, 0x00, 0x19, 0x00} }; 	//2.b  Swap XDATA to eFlash SFR[.] Write Mode: XSFR[909]=ucEFCTLR[1]=0x00

	unsigned char	_cmdSpp_SppTable[_nWrSpp_TAB_NO][_nCMD_LEN] = {
	{0x98, 0x87, 0x05, 0x00, 0x0E, 0x40, 0x3D, 0x71, 0x00}, //3.1  Unlock eFlash: SPP[800E]=0x3D	(.DISPUMP=0)
	{0x98, 0x87, 0x05, 0x00, 0x0F, 0x40, 0x00, 0x4D, 0x00} };  //3.2  Unlock eFlash: SPP[800F]=0x03	(.DISPUMP=0)
	
	unsigned char	_cmdSpp_RdSppRBBS[_nCMD_LEN] =
	{ 0x98, 0x86, 0x06, 0x12, 0x0A, 0x00, 0x18, 0x00, 0x00 };

	unsigned char	_cmdSpp_ExitSppMode[_nWrSpp_CMD3_NO][_nCMD_LEN] = {
	{0x98, 0x87, 0x05, 0x12, 0x08, 0x00, 0x00, 0x18, 0x00},  		//5.   Swap SPP[.]/SFR[.] to XDATA: XSFR[908]=ucEFCTLR[0]=0x00	
	{0x98, 0x87, 0x05, 0x0E, 0x0A, 0x00, 0x30, 0x36, 0x00} };   	//6.   swap XDATA to PROM (ISP Mode disable): XSFR[70A]=ucISPCtrl=0x30
	

	//printf("Please key in your *.bin  file all path ,thx!!!\n");
	//scanf("%s",bin);
	sscanf(path,"%s",bin); ///home/emr/Downloads/hidapi-master_0819/hidtest/Chrome116_HP_V0001_ASIC8_20190813_52D9.BIN
	/*printf("\n----- Please wait!! -----\n");*/printf("%s\n\n----- Please wait!! -----\n",bin);
	fp = fopen(bin, "r");
	while (1) {
		data[readSize] = fgetc(fp);
		if (feof(fp)) {
			break;
		}
		//printf("%x\n", data[readSize]);
		readSize++;
	}
	fclose(fp);
	m_lnDownloadSize = readSize;
	if(readSize > 32768)
	{
		for(int i = 0; i < 32768 ; i++) data[i] = data[32768+i];
		m_lnDownloadSize = readSize - 0x8000;
	}
	g_dwDownloadStart = 0;
	
	if(data[0] != 0x02) 
	{
		printf("Illegal BIN data file for ISP!!");
		return false;
	}
	//for(int i = 0 ; i < 0x8000 ; i++) wBinChkSum += data[i];
	/*for(int nIndex = m_lnDownloadSize - 1 ; nIndex >= 0 ; nIndex--)
	{
		if(data[nIndex] == 0) m_lnDownloadSize--;
		else break;
	}*/
	if(m_lnDownloadSize % 512) m_lnDownloadSize = m_lnDownloadSize + (512 - (m_lnDownloadSize % 512));
	else m_lnDownloadSize = 0x8000;


	unsigned short	byteFlashSFR[16];
	unsigned short	byteIspVer = 0x00;
	unsigned char 	_cmdISPGetDevInfo[4] = { 0x84, 0x05, 0x00, 0x01 };
	unsigned char   _cmdIAPGetVersion[4] = { 0x84, 0x04, 0x00 ,0x00 };
	unsigned char 	_cmdEnterISPMode_I2C[4] = { 0x84, 0x00, 0x01, 0x05 };
	byteIspVer = 0x00;
	if (bIsIapMode) {
		if (!write(fd, _cmdEnterIAPMode_I2C, 4))
		{
			printf("Error write EnterIAPMode");
			return false;
		}
		if (!read(fd, _cmdGetACK, 2))
		{
			printf("Error read EnterIAPMode");
			return false;
		}
		if (CMD_OK != _cmdGetACK[1])
		{
			printf("Error ");
			return false;
		}
		if (!write(fd, _cmdIAPGetVersion, 4)) {
			printf("WriteFile failed at GetIapVersion Command.");
			return false;
		}
		//get ACK
		if (!read(fd, _cmdGetACK3, 3)) {
			printf("ReadFile failed at Get IAP Firmware Information ACK.");
			return false;
		}
		if (_cmdGetACK3[1] < _nIAP_VERSION_V22_) {
			printf("Please Update IAP");
			//return FALSE;
		}
		else if ((_cmdGetACK3[1] == _nIAP_VERSION_V22_) || (_cmdGetACK3[1] == _nIAP_VERSION_V30_)) {
			if (_cmdGetACK3[2] < _nIAP_VERSION_SUB_) {
				printf("Warning!");
			}
		}
	}

	if (nIspDataByte == _USB_BUF_LEN_) {
		//>>> + Get Device Information of 6573 F/W >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		// 		this command is valid for new 6573 F/W only
		if(!write(fd, _cmdISPGetDevInfo,4))
		{
			printf("WriteFile failed at GetDeviceInformation Command.");
			return false;
		}
		//read ACK
		if(!read(fd, byteReadBuf, _USB_BUF_LEN_+1))
		 {
			printf("ReadFile failed at GetDeviceInformation ACK.");
			return false;
		}
		//check ACK
		if ((byteReadBuf[0] == _ISP_DATA_ID) || (byteReadBuf[0] == _ISP_DATA_ID_AX8)) {
			//@2013.04.01: check 6573 F/W Formal Release version if with ASIC5 eFlash Lock/Unlock function
			//HIGHBYTE(_nFW_VERSION_), LOWBYTE(_nFW_VERSION_), HIGHBYTE(_nFW_VERSION_^0xFFFF), LOWBYTE(_nFW_VERSION_^0xFFFF),
			if ((byteReadBuf[1] == (byteReadBuf[3] ^ 0xFF)) && (byteReadBuf[2] == (byteReadBuf[4] ^ 0xFF)) && (byteReadBuf[1] >= _n6573FW_VER_)){}	//bRes = true;
		}
		else {
			printf("DATA ID failed at Get Device Information.");
			return false;
		}
		// - ISP Get Device Information
	}
	

	//if ((!bIsIapMode) && (byteIspVer > 0x10)) {
		byteFlashSFR[0x0E] = 0x00;
		byteFlashSFR[0x0F] = 0x00;
		for (unsigned char nCmdIdx = 0; nCmdIdx < _nRdSfr_CMD_NO; nCmdIdx++) {

			if (!write(fd, _cmdRdSfrStatus[nCmdIdx], 9)) {	//JACK: must use USB_2 size "nIspDataByte+1"
				printf("WriteFile failed at ReadFlashSFR Command.");
				return false;
			}
			//read ACK
			if ((_cmdRdSfrStatus[nCmdIdx][2] & 0xEF) == 0x06) {	//is Read XDATA command
				if (!read(fd, _cmdGetACK3, 3)) {
					printf("ReadFile failed at ReadXData ACK.");
					return false;
				}
				if (CMD_OK != _cmdGetACK3[1]) {
					printf("ACK error at ReadXData ACK.");
					return false;
				}
				if (_cmdRdSfrStatus[nCmdIdx][4] == 0x0E)
				{
					byteFlashSFR[0x0E] = _cmdGetACK3[2];
				}
				else if (_cmdRdSfrStatus[nCmdIdx][4] == 0x0F)	byteFlashSFR[0x0F] = _cmdGetACK3[2];
			}
			else {	//is Write XDATA command or other commands			
				if (!read(fd, _cmdGetACK, 2)) {
					printf("ReadFile failed at WriteXData ACK.");
					return false;
				}
				//read ACK
				if (_cmdRdSfrStatus[nCmdIdx][1] == 0x87) {	//is WRITE XDATA command
					if (_cmdGetACK[1] != _cmdRdSfrStatus[nCmdIdx][6]) {
						printf("ACK error at WriteXData ACK.");
						return false;
					}
				}
				else if (CMD_OK != _cmdGetACK[1]) {
					printf("ACK error at WriteXData ACK.");
					return false;
				}
			}
		}

		for (unsigned char nCmdIdx = 0; nCmdIdx < _nWrSpp_CMD1_NO; nCmdIdx++) {
			if (!write(fd, _cmdSpp_IntoSfrMode[nCmdIdx], 9)) {	//JACK: must use USB_2 size "nIspDataByte+1"
				printf("WriteFile failed at UnlockFlash Command.");
				return false;
			}
			//read ACK
			if (!read(fd,_cmdGetACK, 2)) {
				printf("ReadFile failed at WriteXData ACK.");
				return false;
			}
		}

		for (unsigned char nCmdIdx = 0; nCmdIdx < _nWrSpp_TAB_NO; nCmdIdx++) {
			if (!write(fd,_cmdSpp_SppTable[nCmdIdx], 9)) {	//JACK: must use USB_2 size "nIspDataByte+1"
				printf("WriteFile failed at UnlockFlash Command.");
				return false;
			}
			//read ACK
			if (!read(fd,_cmdGetACK, 2)) {
				printf("ReadFile failed at WriteXData ACK.");
				return false;
			}
		}

		if (!write(fd, _cmdSpp_ExitSppMode[0], 9)) {	//JACK: must use USB_2 size "nIspDataByte+1"
			printf("WriteFile failed at UnlockFlash Command.");
			return false;
		}
		//read ACK
		if (!read(fd,_cmdGetACK, 2)) {
			printf("ReadFile failed at WriteXData ACK.");
			return false;
		}


		//wait RBBS flag ?= 1
		while (1) {
			if (!write(fd, _cmdSpp_RdSppRBBS, 9)) {	//JACK: must use USB_2 size "nIspDataByte+1"
				printf("WriteFile failed at UnlockFlash Command.");
				return false;
			}
			//read ACK
			if (!read(fd,_cmdGetACK3, 3)) {
				printf("ReadFile failed at ReadXData ACK.");
				return false;
			}
			if (0x02 == _cmdGetACK3[2])	break;
		}

		if (!write(fd, _cmdSpp_ExitSppMode[1], 9)) {	//JACK: must use USB_2 size "nIspDataByte+1"
			printf("WriteFile failed at UnlockFlash Command.");
			return false;
		}
		//read ACK
		if (!read(fd,_cmdGetACK, 2)) {
			printf("ReadFile failed at WriteXData ACK.");
			return false;
		}
	//}

	unsigned char _cmdISPWriteStart[4] = { 0x84, 0x01, 0x00 ,0x05 };
	unsigned short dwTemp = m_lnDownloadSize - g_dwDownloadStart;
	_cmdISPWriteStart[1] &= ~0x10;	//WRITE-ONLY mode
	_cmdISPWriteStart[2] = (dwTemp / 128 / 4);//g_bytePageNum;	//(BYTE) (0x8000 / 128 / 4);
	_cmdISPWriteStart[3] = _cmdISPWriteStart[0] ^ _cmdISPWriteStart[1] ^ _cmdISPWriteStart[2] ^ 0x80;

	if (!write(fd, _cmdISPWriteStart, 4)) {
		printf("WriteFile failed at WriteStart Command.");
		return false;
	}
	if (!read(fd,_cmdGetACK, 2)) {
		printf("ReadFile failed at WriteStart ACK.");
		return false;
	}
	if (CMD_OK != _cmdGetACK[1]) {
		printf("ACK error at WriteStart ACK.");
		return false;
	}

	int nCount = 0, nWrCnt = 0;
	unsigned short	*bpDestination = data + m_lnDownloadSize;
	g_ucCheckSum = 0;
	for (unsigned short *npBinBuff = data + g_dwDownloadStart; npBinBuff < bpDestination; npBinBuff += nIspDataByte) {
		for (int nWrIdx = 0; nWrIdx < nIspDataByte; nWrIdx++) {
			byteWriteBuf[nWrIdx + 1] = *(npBinBuff + nWrIdx);
			nWrCnt++;
			g_ucCheckSum += byteWriteBuf[nWrIdx + 1];
		}
		if (!write(fd, byteWriteBuf, nIspDataByte + 1)) {
			printf("WriteFile failed at SendIspData");
			return false;		//JACK
		}
		//read ACK
		if (!read(fd,_cmdGetACK, 2)) {
			printf("ReadFile failed at SendIspData ACK");
			return false;
		}
		//check ACK
		if (DATA_ERR == _cmdGetACK[1]) {
			printf("ACK error at SendIspData ACK.");
			return false;
		}
		else if (DATA_WRITEEND == _cmdGetACK[1]) {
			//bRes = true;
			break;
		}
		else if ((DATA_8BYTEOK == _cmdGetACK[1]) | (DATA_PAGEOK == _cmdGetACK[1])) {
		}
		
	}
	//printf("[%Xh, %Xh] 0x%X\n", (0x8000 + g_dwDownloadStart), /*(0x8000 + nWrCnt - 1)*/0x8000 +m_lnDownloadSize-1 , g_ucCheckSum);
	get_Ckecksum();
	for (int cou = 4096; cou < m_lnDownloadSize; cou++) {
		if (byteDumpBuf[cou] == data[cou]) {
			if (cou == m_lnDownloadSize-1) {
				if (!write(fd, _cmdExitISPMode, 4)) {
					printf("ExitISP Failed!!");
					return false;
				}
				sleep(2);
				get_Ckecksum();
				result = 0;
			}
		}
		else {
		        printf("ERROR EXITISP");
			//bRes = FALSE;
			break;
		}
	}
	return result;
}
