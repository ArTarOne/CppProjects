#pragma once
#include "Item.h"


typedef std::vector<TypeEnum> Rule;
typedef std::vector<Rule> Rules;


class CppParser : public IStreamParser
{
private:
	
	std::vector<std::string> m_stl_types;
	std::vector<std::string> m_types;
	std::vector<std::string> m_reservedWords;
	Rules                    m_rulebook;
	
	void replaceCommentOnSpace(std::string & str);


	bool parseCppWord(const std::string &);
	bool parseTypeData(const std::string &);
	TypeEnum makeType(const std::string &);
	Item changeItem(const TypeEnum & t, const unsigned & sL,
		const unsigned & eL, const std::string &iD);
	
	unsigned getBlockSize(const std::string & b);
	std::vector<Item> getItems(std::istringstream & is);
	void emptyItemsFiltr(std::string &buff, 
        unsigned lineCounter, std::vector<Item> &vI);
	
	int checkRule(std::map<std::string, NumberOfLines> & keeper, const int & itemNumber,
		const int & ruleNumber, const std::vector<Item> & items);

	std::map<std::string, NumberOfLines> getDictFuncNameAndSize(const std::vector<Item> & ); 

    void initAllTypes();
    void initRuleBook();

public:

	CppParser();

	virtual void calculate() override;
    	
};