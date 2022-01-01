#pragma once

#include "StdPlus/StdPlus.h"
#include "Core/CodeReviewCore.h"


void showFuncsInfo(const FuncInfoContainer & f);


int main(int argc, char* argv[])
{	

	std::vector<std::string> rawFilesAndFolders = stdplus::fillingVectorFromCMD(argc, argv);

	CodeReviewCore core;
	core.setFolderMask("*");
	core.setFileMask("*.cpp");

    FuncInfoContainer functions;
	for (auto & fileOrFolder : rawFilesAndFolders)
	{
		core.setPath(fileOrFolder);
		core.parse();
        FuncInfoContainer tmp = core.functions();
		functions.insert(functions.end(), tmp.begin(), tmp.end());
	}
	showFuncsInfo(functions);

	std::cin.get();
}


void showFuncsInfo(const FuncInfoContainer & f)
{
	if (!f.empty())
	{
		for (unsigned i = 0; i < f.size(); i++)
		{
			std::cout << i + 1 << ") " << f[i] << std::endl;
		}
	}
	else
		std::cout << "There are no functions in this files";
}




