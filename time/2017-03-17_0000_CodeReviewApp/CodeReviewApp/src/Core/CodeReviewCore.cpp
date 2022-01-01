#include "StdPlus/StdPlus.h"
#include "Core/CodeReviewCore.h"
#include "IStreamParser.hpp"
#include "CppParser.h"
#include "FilesFinder.h"


bool CodeReviewCore::isFile(const std::string & name)
{
	for (unsigned i = name.size(); i != 0; i--)
	{
		if (name[i] != '.')
			continue;
		else
			return true;
	}
	return false;
}


void CodeReviewCore::appendFunctionsFromFile(const std::string & fileName)
{
    AVAR(fileName);

    CppParser pt;
    pt.setFileName(fileName);
    pt.calculate();
    FuncInfoContainer tmp = pt.funcs();
    m_functions.insert(m_functions.end(), tmp.begin(), tmp.end());

    // TODO cbOnFileProces
}


void CodeReviewCore::parse()
{
    m_functions.clear();

    if (m_path.empty())
        throw std::logic_error("path in core Empty!");

	if (isFile(m_path))
	{	
        appendFunctionsFromFile(m_path);
	}
	else  // this is folder
	{
		FilesFinder folderParser;
		folderParser.setMainFolderName(m_path);
		folderParser.findSubFiles(m_folderMask, m_fileMask);

		for (auto & fileN : folderParser.fileNames())
        {
            appendFunctionsFromFile(fileN);
		}	
	}
}
