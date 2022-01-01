#pragma once

#include "StdPlus/StdPlus.h"    
#include "ExportCodeReviewCore.h"

class CODE_REVIEW_CORE_API Prototype
{
private:
	std::string m_name;
public:
	Prototype() {}
	Prototype(std::string n) : m_name(n){}

	std::string name() const { return m_name; }
	void setName(std::string val) { m_name = val; }
};



class CODE_REVIEW_CORE_API FuncInfo
{
    friend std::ostream & operator<<(std::ostream & os,
        const FuncInfo & fI);

private:
	std::string m_filePath;
	Prototype   m_prototype;
	unsigned    m_funcSize;
    unsigned    m_startLine;
    unsigned    m_endLine;

public:
	FuncInfo(){}
	FuncInfo(std::string fP, Prototype p, unsigned fS) 
		: m_filePath(fP), m_prototype(p), m_funcSize(fS){}

	std::string filePath() const { return m_filePath; }
	void setFilePath(std::string val) { m_filePath = val; }
	
	Prototype prototype() const { return m_prototype; }
	void setPrototype(Prototype val) { m_prototype = val; }
	
	unsigned funcSize() const { return m_funcSize; }
	void setFuncSize(unsigned val) { m_funcSize = val; }
   
    unsigned startLine() const { return m_startLine; }
    void setStartLine(unsigned val) { m_startLine = val; }
	
    unsigned endLine() const { return m_endLine; }
    void setEndLine(unsigned val) { m_endLine = val; }   
};

inline std::ostream & operator<<(std::ostream & os, const FuncInfo & funcInfo)
{
    std::ostringstream oss;

    oss
        << "[" << std::setw(4) << funcInfo.m_funcSize
        << "=" << std::setw(4) << funcInfo.startLine()
        << "-" << std::setw(4) << funcInfo.endLine()
        << "] "
        ;

    oss.setf(std::ios_base::left);
    
    std::string shortFileName = stdplus::fileNamePrepare(funcInfo.m_filePath);
    std::string funcName = stdplus::removeFromString(funcInfo.m_prototype.name(), "\n");

    oss
        << std::setw(40) << shortFileName 
        << ":   "
        << funcName
        ;

    os << oss.str();

    return os;
}

typedef std::vector<FuncInfo> FuncInfoContainer;