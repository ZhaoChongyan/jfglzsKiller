#include <stdio.h>
#include <windows.h>
#include <TlHelp32.h>
#include <stdlib.h>
#include <time.h>
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

int Kill_Pro(TCHAR Kill_Name[]) {
	while(1) {
		HANDLE hSnapshort=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
		if(hSnapshort==INVALID_HANDLE_VALUE) {
			printf("CreateToolhelp32Snapshotµ÷ÓÃÊ§°Ü£¡\n");
			return -1;
		}
		PROCESSENTRY32 stcProcessInfo;
		stcProcessInfo.dwSize=sizeof(stcProcessInfo);
		BOOL  bRet=Process32First(hSnapshort,&stcProcessInfo);
		while (bRet) {
			if(strcmp(stcProcessInfo.szExeFile,Kill_Name)==0) {
				Sleep(2000);
				HANDLE hProcess=::OpenProcess(PROCESS_TERMINATE,FALSE,stcProcessInfo.th32ProcessID);
				::TerminateProcess(hProcess,0);
				CloseHandle(hProcess);
			}
			bRet=Process32Next(hSnapshort,&stcProcessInfo);
		}
		CloseHandle(hSnapshort);
	}
	return 0;
}

int main(void) {
	clock_t st=clock();
	while(clock()-st<=10) {
		Kill_Pro("jfglzs.exe");
		Kill_Pro("prozs.exe");
		Kill_Pro("srvany.exe");
		Kill_Pro("zmservice.exe");
	}
	Kill_Pro("StudentMain.exe");
	return 0;
}
