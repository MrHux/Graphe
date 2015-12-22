#include "stdafx.h"

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
char ** Cfile::FILparse_file(const char* pcFile_to_parse) throw ()
{
	char ** ppFile_values = NULL; // Minimum values to store 2, a pair : description => value

	unsigned int uiIndexfile_values = 0; // Index in the table of cstring ppFile_values
	unsigned int uiNumber_values_per_line = 0; // Number of tokens read (a pair contains 2 tokens : descrpition and value)

	char pcBuffer[BUFFER_SIZE]; // Buffer to store the line read

	// Pointers needed for retrieving values from a line.
	char *pcValue = NULL;
	char *pcNext_value = NULL;

	// Opening a file stream towards the file to parse
	std::ifstream streamOfFileToParse(pcFile_to_parse);

	// If the file stream opening is successful
	if (streamOfFileToParse.is_open() == true)
	{
		// While we haven't reached the end of the file or some error occured
		while (streamOfFileToParse.getline(pcBuffer, BUFFER_SIZE))
		{
			uiNumber_values_per_line = 0; // For each line read, we reset the counter of values read per line

			pcValue = strtok_s(pcBuffer, CHARS_DELIMS_TOKENS, &pcNext_value); // Trying to retrieve a token into pcValue

			// If a token has been retrieved
			while (pcValue != NULL)
			{
				uiNumber_values_per_line++;

				// If we read a character of table end ']', we need to add only one columns to table
				if (strcmp(pcValue, CHAR_END_TABLE) == 0)
				{
					char ** ppTest_realloc = NULL;//pointer to test the realloc
					ppTest_realloc = (char **)realloc(ppFile_values, (uiIndexfile_values + 1) * sizeof(char *));
					if (ppTest_realloc == NULL)
					{
						Cexception exc(ERROR_CHANGING_SIZE_TABLE_VALUES);
						throw exc;
					}
				}
				// For each new pair read in the line, add 2 columns to our table.
				//when we read a value if there was no precedent value read and uiNumber_value_per_line = 0
				//then we know that is it the first value of a pair so we allocate the place for 2 values (the one we had read and the one who will be read just after)
				else if (uiNumber_values_per_line % 2 == 1)
				{
					char ** ppTest_realloc = NULL;
					ppTest_realloc = (char **)realloc(ppFile_values, (uiIndexfile_values + 2) * sizeof(char *));
					if (ppTest_realloc == NULL)
					{
						Cexception exc(ERROR_CHANGING_SIZE_TABLE_VALUES);
						throw exc;
					}
				}
				// we should'nt go in this branch, because uiNumber_values_per_line%2 should not be equal to 1 when ppFile_values has not been precedently allocated
				// we put this condition to verify that all went well.
				if (ppFile_values==NULL) {
					//we can't allocate on a null pointer, but that should not be the case
					Cexception exc(ERROR_NULL_POINTER);
					throw exc;
				}
				
				// Allocating a new cstring into our table to store the token
				ppFile_values[uiIndexfile_values] = new char[strlen(pcValue) + 1];
				// Copy in ppFile_values[uiIndexfile_values] (wich is strlen(pcValue) + 1 characters long) the cstring pcValue, 
				// if pcValue is bigger than ppFile_values[uiIndexfile_values], truncate pcValue to fit
				strncpy_s(ppFile_values[uiIndexfile_values], strlen(pcValue) + 1, pcValue, _TRUNCATE);

				uiIndexfile_values++;

				pcValue = strtok_s(NULL, CHARS_DELIMS_TOKENS, &pcNext_value);
			}
		}

		// Adding a new column to store NULL, indicating the end of the table
		char ** ppTest_realloc = NULL;//pointer to test the realloc
		ppTest_realloc = (char **)realloc(ppFile_values, (uiIndexfile_values + 1) * sizeof(char *));
		if (ppTest_realloc == NULL)
		{
			Cexception exc(ERROR_CHANGING_SIZE_TABLE_VALUES);
			throw exc;
		}

		// we should'nt go in this branch, because uiNumber_values_per_line%2 should not be equal to 1 when ppFile_values has not been precedently allocated
		// we put this condition to verify that all went well.
		if (ppFile_values == NULL) {
			//we can't allocate on a null pointer, but that should not be the case
			Cexception exc(ERROR_NULL_POINTER);
			throw exc;
		}

		ppFile_values[uiIndexfile_values] = NULL;

	}
	// The file to parse cannot be opened
	else
	{
		Cexception exc;
		exc.EXCsetValue(ERROR_INPUT_FILE_OPEN);

		throw exc;
	}

	return ppFile_values;
}