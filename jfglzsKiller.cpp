#include <cstdlib>
#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <queue>
using namespace std;

int main(void) {
	queue<HANDLE> ProList;
	HANDLE hSnapshort=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(hSnapshort==INVALID_HANDLE_VALUE) {
		printf("CreateToolhelp32Snapshot failed!\n");
		return -1;
	}
	begin:;
	PROCESSENTRY32 stcProcessInfo;
	stcProcessInfo.dwSize=sizeof(stcProcessInfo);
	BOOL bRet=Process32First(hSnapshort,&stcProcessInfo);
	while(bRet) {
		if(!(strcmp(stcProcessInfo.szExeFile,"jfglzs.exe")
		* strcmp(stcProcessInfo.szExeFile,"prozs.exe")
		* strcmp(stcProcessInfo.szExeFile,"srvany.exe")
		* strcmp(stcProcessInfo.szExeFile,"zmservice.exe"))) {
			ProList.push(::OpenProcess(PROCESS_TERMINATE,FALSE,stcProcessInfo.th32ProcessID));
		}
		bRet=Process32Next(hSnapshort,&stcProcessInfo);
	}
	while(ProList.size()){
		::TerminateProcess(ProList.front(),0);
		CloseHandle(ProList.front());
		ProList.pop();
	}
	bRet=Process32First(hSnapshort,&stcProcessInfo);
	while(bRet) {
		if(!(strcmp(stcProcessInfo.szExeFile,"jfglzs.exe")
		* strcmp(stcProcessInfo.szExeFile,"prozs.exe")
		* strcmp(stcProcessInfo.szExeFile,"srvany.exe")
		* strcmp(stcProcessInfo.szExeFile,"zmservice.exe"))) {
			goto begin;
		}
		bRet=Process32Next(hSnapshort,&stcProcessInfo);
	}
	CloseHandle(hSnapshort);
	return 0;
}
