#pragma once

#include "stdafx.h"

//!  Cfile_gvedit Class
class Cfile_gvedit
{
public:
	/***
	* FILparse_file(const char * pcFile_to_parse) - parse the graph file (designated by pcFile_to_parse)
	*											   and construct a 2D table of cstring representing the file's contents
	*
	*Purpose:
	*       Parse a graph file to get its values. This method is used to construct a Cgraph
	*
	*Entry:
	*		const char * pcFile_to_parse - the graph file's path
	*
	*Return:
	*		char **	- All the values of the graph in the file.
	*
	*******************************************************************************/
	static char ** FGVconvert_file_gvedit_to_file(const char* pcFile_to_parse);
};
