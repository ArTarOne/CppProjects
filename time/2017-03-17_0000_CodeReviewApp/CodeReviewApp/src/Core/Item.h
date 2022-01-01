#pragma once

#include <iostream>

enum TypeEnum
{
	e_typesEnum_other,
	e_typesEnum_cppWord,
	e_typesEnum_typeData,
	e_typesEnum_userWord,
	e_typesEnum_brackets,
	e_typesEnum_figureBrackets,
	e_typesEnum_triangleBrackets,
	e_typesEnum_delimeterPoints,
    e_typesEnum_Points,
    e_typesEnum_breakPoints,
};



struct Item
{
	TypeEnum    m_type;
	unsigned    m_startLine;
	unsigned    m_endLine;
	std::string m_itemData;

	Item(TypeEnum t, unsigned sL, unsigned eL, std::string iD) 
		: m_type(t), m_startLine(sL), m_endLine(eL), m_itemData(iD){}
};

struct NumberOfLines
{
    unsigned    m_startLine;
    unsigned    m_endLine;
};

inline std::ostream& operator<<(std::ostream & os, const Item & item)
{
    std::cout 
        << "Type: "       << item.m_type      << ", " 
        << "start line: " << item.m_startLine << ", "
        << "end line: "   << item.m_endLine   << ", "
        << "DATA: "       << item.m_itemData  << ", "
        ;

    return os;
}