#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "types.h"
#include "Buffer.h"
#include "SimpleString.h"
#include "pugixml.hpp"

using namespace pugi;
class XMLNode
{
public:
	XMLNode();
	virtual ~XMLNode();

public:
	BOOL IsEmpty();

	const char* GetNodeName();

	BOOL GetChildNode(
		const char *nodeName,
		XMLNode *pNode);

	BOOL GetFirstChild(
		XMLNode *pNode);
	BOOL GetNextSibling(
		XMLNode *pNode);
	BOOL GetPrevSibling(
		XMLNode *pNode);

	BOOL AddChildNode(
		const char *nodeName,
		XMLNode *pNode);
	void DelChildNode(
		const char *nodeName);
	void DelChildNode(
		XMLNode *pNode);

	const char* GetNodeStrValue(
		const char *nodeName,
		const char *defValue);
	BOOL GetNodeByteValue(
		const char *nodeName,
		void *pValue);
	BOOL GetNodeUInt16Value(
		const char *nodeName,
		void *pValue);
	BOOL GetNodeUInt32Value(
		const char *nodeName,
		void *pValue);
	BOOL GetNodeUInt64Value(
		const char *nodeName,
		void *pValue);

	const char* GetAttrStrValue(
		const char *attrName,
		const char *defValue);
	BOOL GetAttrByteValue(
		const char *attrName,
		void *pValue);
	BOOL GetAttrBooleanValue(
		const char *attrName,
		void *pValue);
	BOOL GetAttrUInt16Value(
		const char *attrName,
		void *pValue);
	BOOL GetAttrUInt32Value(
		const char *attrName,
		void *pValue);
	BOOL GetAttrUInt64Value(
		const char *attrName,
		void *pValue);
	BOOL GetAttrDoubleValue(
		const char *attrName,
		void *pValue);

	BOOL AddStringAttribute(
		const char* attrName,
		const char* cValue);
	BOOL AddBooleanAttribute(
		const char* attrName,
		bool bValue);
	BOOL AddIntAttribute(
		const char* attrName,
		int nValue);
	BOOL AddDoubleAttribute(
		const char* attrName,
		double fValue);

private:
	friend class XMLParser;

private:
	xml_node node;
};

class XMLParser
{
public:
	XMLParser();
	virtual ~XMLParser();

	BOOL LoadFromFile(
		const char *fileName);

	BOOL LoadFromBuffer(
		CBuffer *pBuffer);

	BOOL SaveToFile(
		const char *fileName);

	BOOL GetNode(
		const char *nodeName,
		XMLNode *pNode);

	BOOL AddNode(
		const char *nodeName,
		XMLNode *pNode);

private:
	xml_document  mDocument;
};

BOOL XmlNodeLoadString(
	XMLNode *pNode,
	const char *elementName,
	CSimpleStringA *pString);
BOOL XmlNodeLoadRect(
	XMLNode *pNode,
	const char *elementName,
	RECT *pRect);
BOOL XmlNodeLoadSize(
	XMLNode *pNode,
	const char *elementName,
	SIZE *pSize);
BOOL XmlNodeLoadPoint(
	XMLNode *pNode,
	const char *elementName,
	POINT *pt);
#endif
