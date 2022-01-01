#pragma once

#include "ExportCodeReviewCore.h"
#include "FuncInfo.h"

class CODE_REVIEW_CORE_API CodeReviewCore
{
private:
    std::string       m_fileMask;
    std::string       m_folderMask;
    std::string       m_path;
    FuncInfoContainer m_functions;    

    bool isFile(const std::string & name);
    void appendFunctionsFromFile(const std::string & fileName);

public:
	std::string fileMask() const { return m_fileMask; }
	void setFileMask(std::string val) { m_fileMask = val; }
	
	std::string folderMask() const { return m_folderMask; }
	void setFolderMask(std::string val) { m_folderMask = val; }
	
	std::string path() const { return m_path; }
    void setPath(std::string val) { m_path = val; }

    FuncInfoContainer functions()const { return m_functions; }

	void parse();	

};

