#include "StdAfx.h"
#include ".\finddebug.h"
#using <mscorlib.dll>
#include "stdafx.h"
#include <iomanip>
#include <cstdlib>
#include <stdio.h>
#include <windows.h>
#include <algorithm>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::string;
//using namespace std;

FindDebug::FindDebug(void)
{
}

FindDebug::~FindDebug(void)
{
}

void FindDebug::findAllFiles( std::string _patch )
{
	WIN32_FIND_DATA FindData;
	std::string modifiler_address =  _patch;
	modifiler_address += "*.*";
	HANDLE Handle = FindFirstFile( modifiler_address.c_str() , &FindData);
	std::string file_name_first = FindData.cFileName;
	bool delFile = false;
	while( FindNextFile(Handle, &FindData) )
	{
		std::string file_name = FindData.cFileName;
		if(!(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			delFile = false;
			std::string final_address = _patch;
			final_address += file_name;
			delFile = isDeleteFile(final_address);
			if(delFile) {
				remove(final_address.c_str()); //delete file
				//std::cout << final_address.c_str() << "\n";
			}
		} 
	}
}

bool FindDebug::isDeleteFile( std::string _file)
{
	std::string fe(_file.substr(_file.find_last_of(".") + 1));
	std::transform(fe.begin(), fe.end(), fe.begin(), ::tolower);
	int loc = fe.find("pch");
	if(loc != string::npos)
		return true;
	loc = fe.find("pdb");
	if(loc != string::npos)
		return true;
	loc = fe.find("obj");
	if(loc != string::npos)
		return true;
	loc = fe.find("idb");
	if(loc != string::npos)
		return true;
	loc = fe.find("bsc");
	if(loc != string::npos)
		return true;
	loc = fe.find("res");
	if(loc != string::npos)
		return true;
	loc = fe.find("exp");
	if(loc != string::npos)
		return true;
	loc = fe.find("cache");
	if(loc != string::npos)
		return true;
	loc = fe.find("sbr");
	if(loc != string::npos)
		return true;
	return false;
}

void FindDebug::findDebugDir( std::string _patch)
{
	WIN32_FIND_DATA FindData;
	std::string modifiler_address =  _patch;
	modifiler_address += "*.*";
	HANDLE Handle = FindFirstFile( modifiler_address.c_str() , &FindData);
	std::string file_name_first = FindData.cFileName;

	while( FindNextFile(Handle, &FindData) )
	{
		std::string file_name = FindData.cFileName;
		if( FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
		{
			if( ! !strcmp(FindData.cFileName, "..") )
			{
				std::string new_patch = _patch ;
				new_patch += file_name;
				new_patch += "\\"; 
				findDebugDir( new_patch );
				//std::cout << new_patch.c_str() << "\n";
				if( !strcmpi(FindData.cFileName, "debug") ) {
					findAllFiles(new_patch);
				}
				if( !strcmpi(FindData.cFileName, "release") ) {
					findAllFiles(new_patch);
				}
			}
		}
	}
}
