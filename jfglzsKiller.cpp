#include <cstdlib>
#include <windows.h>
#include <TlHelp32.h>
#include <queue>
using namespace std;

int main(void) {
	HANDLE hSnapshort = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshort == INVALID_HANDLE_VALUE) {
		throw "CreateToolhelp32Snapshot failed!\n";
		return -1;
	}
	queue<HANDLE> proList;
	bool finished = false; 
	do {
		finished = true;
		PROCESSENTRY32 stcProcessInfo;
		stcProcessInfo.dwSize = sizeof(stcProcessInfo);
		BOOL bRet = Process32First(hSnapshort, &stcProcessInfo);
		while(bRet) {
			if(!(strcmp(stcProcessInfo.szExeFile, "jfglzs.exe")
			        && strcmp(stcProcessInfo.szExeFile, "prozs.exe")
			        && strcmp(stcProcessInfo.szExeFile, "srvany.exe")
			        && strcmp(stcProcessInfo.szExeFile, "zmservice.exe"))) {
				proList.push(::OpenProcess(PROCESS_TERMINATE, FALSE, stcProcessInfo.th32ProcessID));
			}
			bRet = Process32Next(hSnapshort, &stcProcessInfo);
		}
		while (proList.size()) {
			if (!(::TerminateProcess(proList.front(), 0))) {
			    finished = false;
			}
			CloseHandle(proList.front());
			proList.pop();
		}
	} while(!finished);
	CloseHandle(hSnapshort);
	return 0;
}
