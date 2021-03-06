#pragma once
#include "rapid\rapidxml.hpp"
#include "Log.h"
#include <atlfile.h>
#include <typeinfo.h>
#include <sstream>
#include <memory>

template<typename T = char>
class CXmlParser
{
public:
	CXmlParser();
	~CXmlParser();

	BOOL Load(LPCWSTR lpstrFilePath);
	void UnLoad();
	BOOL LoadFromData(T* data);
	BOOL FindElem(const T* ElemName);
	void IntoElem();
	void OutOfElem();
	template<typename TRet>
	TRet GetAttrib(const T* AttrKey);
	LPCWSTR GetValue();
	LPCWSTR GetFilePath();

private:
	BOOL LoadFile(LPCWSTR lpstrFilePath, CAutoVectorPtr<char>& pFileData, ULONG& nSize);
    //template<typename TRet>
	//TRet Convert(T* Value);

private:
	rapidxml::xml_document<T>	m_xmlDoc;
	ATL::CAtlString	m_strFile;
	CAutoVectorPtr<T> m_pXmlData;

	rapidxml::xml_node<T>*	m_pNodeFirst;
	rapidxml::xml_node<T>*	m_pNodeNext;
};

template<typename T>
inline CXmlParser<T>::CXmlParser()
	: m_pNodeFirst(NULL)
	, m_pNodeNext(NULL)
{

}

template<typename T>
inline CXmlParser<T>::~CXmlParser()
{
	UnLoad();
}

template<>
inline BOOL CXmlParser<char>::Load(LPCWSTR lpstrFilePath)
{
	BOOL bRet = FALSE;
	m_strFile = lpstrFilePath;

	do
	{
		CAutoVectorPtr<char> pData;
        ULONG nSize;
		if (!LoadFile(lpstrFilePath, pData, nSize))
		{
			break;
		}

		if (!pData.m_p)
		{
			break;
		}

        m_pXmlData.Attach(pData.Detach());

        if (!m_pXmlData.m_p)
            break;

		if (!LoadFromData(m_pXmlData.m_p))
		{
			break;
		}

		bRet = TRUE;

	} while (FALSE);

	return bRet;
}

//template<>
//inline BOOL CXmlParser<wchar_t>::Load(LPCWSTR lpstrFilePath)
//{
//	BOOL bRet = FALSE;
//	m_strFile = lpstrFilePath;
//
//	do
//	{
//		CAutoVectorPtr<char> pData;
//		if (!LoadFile(lpstrFilePath, pData))
//		{
//			break;
//		}
//
//		if (!pData.m_p)
//		{
//			break;
//		}
//
//		//m_pXmlData.Allocate(_msize(pData.m_p) / sizeof(char));
//		m_pXmlData.Attach(CA2W(pData.Detach(), CP_UTF8));
//		if (!m_pXmlData.m_p)
//		{
//			break;
//		}
//
//		bRet = LoadFromData(m_pXmlData.m_p);
//
//	} while (FALSE);
//
//	return bRet;
//}

template<typename T>
inline void CXmlParser<T>::UnLoad()
{
	m_pNodeFirst = NULL;
	m_pNodeNext = NULL;
	m_pXmlData.Free();
	m_xmlDoc.clear();
}

template<typename T>
inline BOOL CXmlParser<T>::LoadFile(LPCWSTR lpstrFilePath, CAutoVectorPtr<char>& pFileData, ULONG& nSize)
{
	BOOL bRet = FALSE;

	do
	{
		ATL::CAtlFile file;
		HRESULT hr = file.Create(
			lpstrFilePath,
			GENERIC_READ,
			FILE_SHARE_READ,
			OPEN_EXISTING);
		if (FAILED(hr))
		{
			break;
		}
		nSize = 0;
		{
			ULONGLONG nFileSize = 0;
			file.GetSize(nFileSize);
			if (nFileSize == 0)
			{
				break;
			}
			nSize = (ULONG)nFileSize;
		}

		if (!pFileData.Allocate(nSize))
		{
			break;
		}

		if (FAILED(file.Read(
			pFileData.m_p,
			nSize)))
		{
			break;
		}
		file.Close();

		bRet = TRUE;

	} while (FALSE);

	return bRet;
}

// 显示实例化，并且禁止其他实例化
template<>
inline BOOL CXmlParser<char>::LoadFromData(char* data)
{
	BOOL bRet = FALSE;

	do
	{
		if (!data)
		{
			break;
		}

		try
		{
			m_xmlDoc.parse<0>(data);
		}
		catch (rapidxml::parse_error& err)
		{
			LOG_PRINT(L"%s, xml(%s) parse error, where(%s) what(%s)",
				__FUNCTIONW__,
				m_strFile,
				/*(LPCWSTR)((typeid(err.where<T>()) == typeid(char*)) ? CA2W(err.where<T>(), CP_UTF8) : err.where<T>()),*/
				(LPCWSTR)CA2W(err.where<char>(), CP_UTF8),
				(LPCWSTR)(CA2W(err.what(), CP_UTF8)));
			break;
		}

		bRet = TRUE;

	} while (FALSE);
	
	return bRet;
}

//template<>
//inline BOOL CXmlParser<wchar_t>::LoadFromData(wchar_t* data)
//{
//	BOOL bRet = FALSE;
//
//	do
//	{
//		if (!data)
//		{
//			break;
//		}
//
//		try
//		{
//			m_xmlDoc.parse<0>(data);
//		}
//		catch (rapidxml::parse_error& err)
//		{
//			//LOG_PRINT(L"%s, xml(%s) parse error, where(%s) what(%s)",
//			//	__FUNCTIONW__,
//			//	m_strFile,
//			//	/*(LPCWSTR)((typeid(err.where<T>()) == typeid(char*)) ? CA2W(err.where<T>(), CP_UTF8) : err.where<T>()),*/
//			//	err.where<wchar_t>(),
//			//	(LPCWSTR)(CA2W(err.what(), CP_UTF8)));
//			break;
//		}
//
//		bRet = TRUE;
//
//	} while (FALSE);
//
//	return bRet;
//}

template<typename T>
inline BOOL CXmlParser<T>::FindElem(const T* ElemName)
{
	rapidxml::xml_node<T>* pNode = NULL;
	if (!m_pNodeFirst)
	{
		pNode = m_xmlDoc.first_node(ElemName);
		if (pNode)
		{
			m_pNodeFirst = pNode;
			m_pNodeNext = pNode;
		}
	}
	else
	{
		if (!m_pNodeNext)
		{
			pNode = m_pNodeFirst->first_node(ElemName);
			if (pNode)
			{
				m_pNodeNext = pNode;
			}
		}
		else
		{
			pNode = m_pNodeNext->next_sibling(ElemName);
			if (pNode)
			{
				m_pNodeNext = pNode;
			}
			else
			{
				pNode = m_pNodeNext->first_node(ElemName);
				if (pNode)
				{
					m_pNodeNext = pNode;
				}
			}
		}
	}
	
	return (pNode != NULL);
}

template<typename T>
inline void CXmlParser<T>::IntoElem()
{
	if (m_pNodeNext)
	{
		m_pNodeFirst = m_pNodeNext;
		m_pNodeNext = NULL;
	}
}

template<typename T>
inline void CXmlParser<T>::OutOfElem()
{
	if (m_pNodeFirst)
	{
		m_pNodeNext = m_pNodeFirst;
		m_pNodeFirst = m_pNodeFirst->parent();
	}
}

template<>
template<typename TRet>
inline TRet CXmlParser<char>::GetAttrib(const char* AttrKey)
{
	TRet ret = TRet();

	if (m_pNodeNext && m_pNodeNext->first_attribute(AttrKey) && m_pNodeNext->first_attribute(AttrKey)->value())
	{
		std::istringstream iss(m_pNodeNext->first_attribute(AttrKey)->value());
		iss >> ret;
	}

	return ret;
}

template<>
template<typename TRet>
inline TRet CXmlParser<wchar_t>::GetAttrib(const wchar_t* AttrKey)
{
	TRet ret = TRet();

	if (m_pNodeNext && m_pNodeNext->first_attribute(AttrKey) && m_pNodeNext->first_attribute(AttrKey)->value())
	{
		std::wistringstream iss(m_pNodeNext->first_attribute(AttrKey)->value());
		iss >> ret;
	}

	return ret;
}

template<>
template<>
inline ATL::CAtlString CXmlParser<char>::GetAttrib(const char* AttrKey)
{
    ATL::CAtlString ret;

	if (m_pNodeNext && m_pNodeNext->first_attribute(AttrKey))
	{
		ret = CA2W(m_pNodeNext->first_attribute(AttrKey)->value(), CP_UTF8);
	}

	return ret;
}

//template<>
//template<>
//inline ATL::CAtlString CXmlParser<wchar_t>::GetAttrib(const wchar_t* AttrKey)
//{
//    ATL::CAtlString ret;
//
//	if (m_pNodeNext && m_pNodeNext->first_attribute(AttrKey))
//	{
//		ret = m_pNodeNext->first_attribute(AttrKey)->value();
//	}
//
//	return ret;
//}

template<typename T>
inline LPCWSTR CXmlParser<T>::GetValue()
{
	ATL::CAtlString strValue;

	if (m_pNodeNext)
	{
		if (typeid(m_pNodeNext->value()) == typeid(char*))
		{
			strValue = CA2W(m_pNodeNext->value(), CP_UTF8);
		}
		else
		{
			strValue = m_pNodeNext->value();
		}
	}
	
	return strValue;
}

template<typename T>
inline LPCWSTR CXmlParser<T>::GetFilePath()
{
	return m_strFile.GetString();
}