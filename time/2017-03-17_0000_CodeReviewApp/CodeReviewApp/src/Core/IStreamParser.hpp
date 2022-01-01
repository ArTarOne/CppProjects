#pragma once

#include "StdPlus/StdInclude.h"
#include "Core/FuncInfo.h"


class IStreamParser
{
private:
	std::string m_fileName;
protected:
    FuncInfoContainer m_funcs;
public:
	IStreamParser() {}
	virtual ~IStreamParser(){}

	virtual void calculate() = 0;
    
	std::string fileName() const { return m_fileName; }
	void setFileName(std::string val) { m_fileName = val; }
	
    FuncInfoContainer funcs() const { return m_funcs; }
	void setFuncs(FuncInfo val) { m_funcs.push_back(val); }
};






