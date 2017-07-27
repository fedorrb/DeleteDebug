#pragma once

class FindDebug
{
public:
	FindDebug(void);
	~FindDebug(void);
	void findAllFiles( std::string _patch );
	void findDebugDir( std::string _patch );
	bool isDeleteFile( std::string _file );
};
