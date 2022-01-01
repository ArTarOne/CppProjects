#include "StdPlus/StdPlus.h"
#include "FilesFinder.h"



void FilesFinder::findSubFiles(const std::string & dirMask, const std::string & fileMask)
{
	m_subFoldersNames = getAllDirOnTheMask(m_mainfolderName, dirMask);

	for (auto & fold : m_subFoldersNames)
	{
		std::vector<std::string > subFile = stdplus::getSubFiles(fold, fileMask);
		m_fileNames.insert(m_fileNames.end(), subFile.begin(), subFile.end());
	}

}

bool FilesFinder::checkMask( char *s,  char *p)
{
	char *rs = 0, *rp;
    while (1)
    {
        if (*p == '*')
            rs = s, rp = ++p;
        else if (!*s)
            return !*p;
        else if (*s == *p || *p == '?')
            ++s, ++p;
        else if (rs)
            s = ++rs, p = rp;
        else
            return false;
    }
}

std::vector<std::string> FilesFinder::getAllDirOnTheMask(const std::string & mFolderName, const std::string &m)
{
	std::string mainName;
	for (unsigned i = mFolderName.size(); i != 0; i--)
	{
		if (mFolderName[i] != '\\')
			mainName.insert(mainName.begin(), mFolderName[i]);
		else
			break;
	}
	std::vector<std::string > subFold;
	if (checkMask(const_cast<char*>(mainName.c_str()), const_cast<char*>(m.c_str())))
	{
		subFold.push_back(mainFolderName());
		std::vector<std::string > tmp = stdplus::getSubFolders(mainFolderName(), m);
		subFold.insert(subFold.end(), tmp.begin(), tmp.end());
	}
	else
		subFold = stdplus::getSubFolders(mainFolderName(), m);

	return subFold;
}