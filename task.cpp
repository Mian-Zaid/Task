// Tasks.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cstdlib>
#include <string.h>
#include <tchar.h>
#include <urlmon.h> 
#include <Windows.h>
#include<functional>
#include <thread>         // std::thread


#pragma comment(lib, "urlmon.lib")
using namespace std;


#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60


void printProgress(double percentage) {
	int val = (int)(percentage * 100);
	int lpad = (int)(percentage * PBWIDTH);
	int rpad = PBWIDTH - lpad;
	printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
	fflush(stdout);
}

int downloadfile(int threadNo) {

	for (float i = 0; i <= 1.1;) {
		printProgress(i);
		cout.flush();
		Sleep(100);
		i += 0.1;
	}


	// the URL to download from 
	const wchar_t* srcURL;

	// the destination file 
	const wchar_t* destFile;

	if (threadNo == 1) {
		destFile = L"image1.jpg";
		srcURL = L"https://image.shutterstock.com/image-photo/mountains-under-mist-morning-amazing-260nw-1725825019.jpg";

	}
	else if (threadNo == 2) {
		destFile = L"image2.jpg";
		srcURL = L"https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTox5E01fO85XuoTcPe8IqOhDWABpwm6RIOG9R5f26aqb3aixlleapS4abM4m_3UVJUxWU&usqp=CAU";

	}
	else if (threadNo == 3) {
		destFile = L"image3.jpg";
		srcURL = L"https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcR0_u7nNn6jT6WycQKaCUNGc-_ieyCSrbSpOCt7RZg-kBn6ihNEgoFJNgLgotpFFWi4-HA&usqp=CAU";

	}

	// URLDownloadToFile returns S_OK on success 
	if (S_OK == URLDownloadToFile(NULL, srcURL, destFile, 0, NULL))
	{	

		return 0;

	}
	else
	{

		cout << "Failed\n";
		return -1;
	}
}


int main()
{
	

	std::thread first(downloadfile,1);     
	std::thread second(downloadfile,2);  
	std::thread third(downloadfile,3);

	std::cout << "Downloading started..\n";

	// synchronize threads:
	first.join();                // pauses until first finishes
	second.join();    
	third.join();			// pauses until second finishes

	std::cout << "Download completed.\n";
	

}
