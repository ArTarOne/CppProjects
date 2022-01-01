#pragma once

class FilesFinder
{
private:
	
	std::string              m_mainfolderName;
	std::vector<std::string> m_subFoldersNames;
	std::vector<std::string> m_fileNames;

	std::vector<std::string> getAllDirOnTheMask(
        const std::string & mFolderName, const std::string &m);	

	bool checkMask(char *s, char *p);   // TODO Danger code!!!

public:

	void findSubFiles(const std::string & dirMask, const std::string & fileMask);

	std::string mainFolderName() const { return m_mainfolderName; }
	void setMainFolderName(std::string val) { m_mainfolderName = val; }
	
	std::vector<std::string> fileNames() const { return m_fileNames; }
	
};


