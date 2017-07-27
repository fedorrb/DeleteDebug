// This is the main project file for VC++ application project 
// generated using an Application Wizard.

#include "stdafx.h"
#include "finddebug.h"

#using <mscorlib.dll>

using namespace System;

int _tmain(int argc, char** argv)
{
	if(argc == 2) {
		FindDebug deleteDebug;
		deleteDebug.findDebugDir(argv[1]);
	}
	return 0;
}