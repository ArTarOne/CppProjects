#include "StdPlus/StdPlus.h"
#include "IStreamParser.hpp"
#include "CppParser.h"


void CppParser::replaceCommentOnSpace(std::string & str)
{
	bool isBrackedOpen = false;
    if (!str.empty())
    { 
        for (unsigned i = 0; i < str.size() - 1; i++)
        {
            if (str[i] == '/' && str[i + 1] == '/')
            {
                while (str[i] != '\n')
                {
                    str[i] = ' ';
                    i++;
                    if (i >= str.size()) return;
                }
            }
            else if (str[i] == '/' && str[i + 1] == '*')
            {
                str[i] = ' ';
                str[i + 1] = ' ';
                i += 2;
                if (i >= str.size()) return;
                while (!isBrackedOpen)
                {
                    if (str[i] == '*' && str[i + 1] == '/')
                    {
                        str[i] = ' ';
                        str[i + 1] = ' ';
                        i += 2;
                        if (i >= str.size()) return;
                        isBrackedOpen = true;
                    }
                    else
                    {
                        if (str[i] != '\n')
                            str[i] = ' ';

                        i++;
                        if (i >= str.size()) return;
                    }
                }
            }
        }
		isBrackedOpen = false;
	}
}

void CppParser::initRuleBook()
{
    Rule rule_classic =
    {
        e_typesEnum_typeData,
        e_typesEnum_userWord,
        e_typesEnum_brackets,
        e_typesEnum_figureBrackets,
    };

    Rule rule_stl =
    {
        e_typesEnum_userWord,
        e_typesEnum_delimeterPoints,
        e_typesEnum_typeData,
        e_typesEnum_triangleBrackets,
        e_typesEnum_userWord,
        e_typesEnum_brackets,
        e_typesEnum_figureBrackets,
    };

    Rule rule_stlMemberOfClass = 
    { 
        e_typesEnum_userWord, 
        e_typesEnum_delimeterPoints,
        e_typesEnum_typeData, 
        e_typesEnum_triangleBrackets,
        e_typesEnum_userWord, 
        e_typesEnum_delimeterPoints,
        e_typesEnum_userWord, 
        e_typesEnum_brackets,
        e_typesEnum_figureBrackets,
    };

    Rule rule_classicMemberOfClass = 
    { 
        e_typesEnum_typeData, 
        e_typesEnum_userWord,
        e_typesEnum_delimeterPoints,
        e_typesEnum_userWord,
        e_typesEnum_brackets,
        e_typesEnum_figureBrackets,
    };

    Rule rule_myTypeReturn = 
    { 
        e_typesEnum_userWord,
        e_typesEnum_userWord,
        e_typesEnum_brackets,
        e_typesEnum_figureBrackets,
    };

    Rule rule_myTypeReturnMemberOfClass = 
    { 
        e_typesEnum_userWord,
        e_typesEnum_userWord,
        e_typesEnum_delimeterPoints,
        e_typesEnum_userWord,
        e_typesEnum_brackets,
        e_typesEnum_figureBrackets,
    };

    Rule rule_constMethodOfClass = 
    { 
        e_typesEnum_typeData, 
        e_typesEnum_userWord,
        e_typesEnum_delimeterPoints,
        e_typesEnum_userWord,
        e_typesEnum_brackets,
        e_typesEnum_cppWord,
        e_typesEnum_figureBrackets,
    };

    Rule rule_myTypeReturnConstMethodOfClass = 
    { 
        e_typesEnum_userWord,
        e_typesEnum_userWord,
        e_typesEnum_delimeterPoints,
        e_typesEnum_userWord,
        e_typesEnum_brackets,
        e_typesEnum_cppWord,
        e_typesEnum_figureBrackets
    };


    m_rulebook = 
    { 
        rule_classic, 
        rule_stl, 
        rule_stlMemberOfClass,
        rule_classicMemberOfClass,
        rule_myTypeReturn,
        rule_myTypeReturnMemberOfClass,
        rule_constMethodOfClass,
        rule_myTypeReturnConstMethodOfClass,
    };
}

void CppParser::initAllTypes()
{
	m_types = { "void","int","char","double","float","bool",
		"unsigned", "ifstream","ofstream","fstream",
		"string", "array", "vector", "deque", "forward_list",
		"list", "set", "multiset", "map",
		"multimap", "unordered_set", "unordered_multiset", "unordered_map",
		"unordered_multimap", "stack", "queue", "priority_queue" };

	m_reservedWords = { "void", "int", "char", "double", "float", "bool",
		"unsigned", "ifstream","ofstream","fstream",
		"string", "array", "vector", "deque", "forward_list",
		"list", "set", "multiset", "map",
		"multimap", "unordered_set", "unordered_multiset", "unordered_map",
		"unordered_multimap", "stack", "queue", "priority_queue",
		"asm", 	"else", 	"new", 	"this",
		"auto", 	"enum", 	"operator", 	"throw",
		"explicit", 	"private", 	"true",
		"break", 	"export", 	"protected", 	"try",
		"case", 	"extern", 	"public", 	"typedef",
		"catch", 	"false", 	"register", 	"typeid",
		"reinterpret_cast", 	"typename",
		"class", 	"for", 	"return", 	"union",
		"const", 	"friend", 	"short", 	"unsigned",
		"const_cast", 	"goto", 	"signed", 	"using",
		"continue", 	"if", 	"sizeof", 	"virtual",
		"default", 	"inline", 	"static",
		"delete",  	"static__cast", 	"volatile",
		"do", 	"long", 	"struct", 	"wchar_t",
		"mutable", 	"switch", 	"while",
		"dynamic_cast", 	"namespace", 	"template" };
}

CppParser::CppParser()
{
    initAllTypes();
    initRuleBook();
}

void CppParser::calculate() 
{
    m_funcs.clear();

	std::ifstream fin = stdplus::openTextFile(fileName());
	std::string inputText = stdplus::readText(fin);
	fin.close();
	replaceCommentOnSpace(inputText);
	std::istringstream inputStream(inputText);

	std::vector<Item> items = getItems(inputStream);
    
//     for (int i = 0; i < items.size(); i++)  //отладка
// 	{
//         std::cout <<"№"<<i+1<<") ";
//         AVAR(items[i]);
//         std::cout << std::endl;
//         std::cout << std::endl;
// 	}

	std::map<std::string, NumberOfLines> dictFuncNameAndSize 
        = getDictFuncNameAndSize(items); 

	FuncInfo funcInfo;
	funcInfo.setFilePath(fileName());

	for (auto it = dictFuncNameAndSize.begin(); it != dictFuncNameAndSize.end(); it++)
	{
		Prototype p;
		p.setName(it->first);
		funcInfo.setPrototype(p);
		funcInfo.setFuncSize(it->second.m_endLine-it->second.m_startLine); 
        funcInfo.setStartLine(it->second.m_startLine);
        funcInfo.setEndLine(it->second.m_endLine);
     //   AVAR(funcInfo);
		m_funcs.push_back(funcInfo);
	}
}

bool CppParser::parseCppWord(const std::string & word)
{
	for (unsigned i=0;i<m_reservedWords.size();i++)
	{
		if (word == m_reservedWords[i])
		{
			return true;
		}
	}
	return false;
}

bool CppParser::parseTypeData(const std::string & word)
{
	for (unsigned i = 0; i < m_types.size(); i++)
	{
		if (word == m_types[i])
		{
			return true;
		}
	}
	return false;
}

TypeEnum CppParser::makeType(const std::string & word)
{
	if (parseCppWord(word) && parseTypeData(word))
		return e_typesEnum_typeData;
	else if (parseCppWord(word) && !parseTypeData(word))
		return e_typesEnum_cppWord;

	return e_typesEnum_userWord;
}

unsigned CppParser::getBlockSize(const std::string & b)
{
	unsigned count=0;

	std::istringstream ss(b);
	std::string str;

	while (getline(ss, str))
		count++;
	return count;
}

void CppParser::emptyItemsFiltr(std::string &buff, unsigned lineCounter, std::vector<Item> &vI)
{
	if (buff == "")
	{
		buff.clear();
	}
	else
	{
		Item it(makeType(buff), lineCounter, lineCounter, buff);
		vI.push_back(it);
		buff.clear();
	}
}

Item CppParser::changeItem(const TypeEnum & t, const unsigned & sL,
	const unsigned & eL, const std::string &iD)
{
	Item it(t, sL, eL, iD);
	return it;
}

std::vector<Item> CppParser::getItems(std::istringstream & is)
{
	std::vector<Item> vI;
	std::string buff;

	unsigned lineCounter=0; //in console version must be 1. why???

	char ch;
	while (is.get(ch))
	{ 
		if (ch == '(' || ch == '{')
		{
			is.putback(ch);
			emptyItemsFiltr(buff, lineCounter, vI);

			char clDel = (ch == '(' ? ')' : '}');
			buff = stdplus::readBlock(ch, clDel, is);
			unsigned blockSize = getBlockSize(buff);
			TypeEnum t = (ch == '(' ? e_typesEnum_brackets : e_typesEnum_figureBrackets);
			Item it(t, lineCounter, lineCounter+blockSize, buff);  
			vI.push_back(it);
			lineCounter += blockSize-1;
            buff.clear();
		}
		else if (ch == '<')
		{
			is.putback(ch);
			emptyItemsFiltr(buff, lineCounter, vI);

			buff = stdplus::readBlock(ch, '>', is);
			TypeEnum t = e_typesEnum_triangleBrackets;
			Item it(t, lineCounter, lineCounter, buff);
			vI.push_back(it);
			buff.clear();
		}
		else if (ch == '#')
		{
			is.putback(ch);
			emptyItemsFiltr(buff, lineCounter, vI);

			buff = stdplus::readBlock(ch, '\n', is);
			TypeEnum t = e_typesEnum_other;
			Item it(t, lineCounter, lineCounter, buff);
			vI.push_back(it);
			buff.clear();

            lineCounter++;
		}
		else if (ch == ':')
		{
			emptyItemsFiltr(buff, lineCounter, vI);
			buff += ch;
			char nextCh;
			is.get(nextCh);
			if (nextCh == ':')
			{
				buff += nextCh;
				TypeEnum t = e_typesEnum_delimeterPoints;
				Item it(t, lineCounter, lineCounter, buff);
				vI.push_back(it);
				buff.clear();
			}
            else
            {
                is.putback(nextCh);
                TypeEnum t = e_typesEnum_Points;
                Item it(t, lineCounter, lineCounter, buff);
                vI.push_back(it);
                buff.clear();
            }
        }
		else if (ch == ' ')
		{
			emptyItemsFiltr(buff, lineCounter, vI);
		}
		else if (ch == ';')
		{
            TypeEnum t = e_typesEnum_breakPoints;
            Item it(t, lineCounter, lineCounter, buff);
            vI.push_back(it);
            buff.clear();
		}
        else if (ch == '\t')
        {
            emptyItemsFiltr(buff, lineCounter, vI);

        }
        else if (ch == ',')
        {
            emptyItemsFiltr(buff, lineCounter, vI);

        }
		else if (ch == '\n')
		{
			lineCounter++;
			emptyItemsFiltr(buff, lineCounter, vI);
  		}
		else
				buff += ch;
	}
	return vI;
}

std::map<std::string, NumberOfLines> CppParser::getDictFuncNameAndSize(const std::vector<Item> & items)
{
    // function name and (begin and and this item)
	std::map<std::string, NumberOfLines> fI;

	for (unsigned i = 0; i < items.size(); i++)
	{
		for (unsigned j = 0; j < m_rulebook.size(); j++)
		{
			if (items[i].m_type == m_rulebook[j].front())
			{                
				i += checkRule(fI, i, j, items);
                
			}	 			
		}
	}
	return fI;
}


int CppParser::checkRule(std::map<std::string, NumberOfLines> & keeper, const int & itemNumber,
	const int & ruleNumber, const std::vector<Item> & items)
{
    const Rule & curRule = m_rulebook.at(ruleNumber);
    const int curRuleLenght = curRule.size();
    
    for (int indexInRule = 0; indexInRule < curRuleLenght; indexInRule++)
    {
        const int curItemIndex = itemNumber + indexInRule;

        if (curItemIndex >= items.size())
            return 0;

        const Item & curItem = items.at(curItemIndex);
        const TypeEnum & curTypeRuleItem = curRule.at(indexInRule);
        
        if (curItem.m_type == curTypeRuleItem)
            continue;
        else
            return 0;
    }
    
	std::string functName;
    unsigned pos = 0;

    // remove one item from end - this is brecketes
	for (unsigned i = 0; i < curRuleLenght - 1; i++)
	{
		functName += items[itemNumber + i].m_itemData+" ";
        pos = i;
	} 

// 	int functSize = items[itemNumber + m_rulebook[ruleNumber].size()-1].m_endLine -
// 		items[itemNumber + m_rulebook[ruleNumber].size() - 1].m_startLine;
	
    NumberOfLines lines;
    lines.m_startLine = items[itemNumber+pos+1].m_startLine; 
    lines.m_endLine = items[itemNumber+pos+1].m_endLine;

	keeper[functName] = lines;
	
	return curRuleLenght - 1;
}