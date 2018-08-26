#pragma once
#include <atlfile.h>

class CRegistryHandler
{
public:
    CRegistryHandler()
        : m_lpstrFilePath(_T(""))
        , m_hkResult(NULL)
    {
    }

    CRegistryHandler(HKEY hKey, LPCWSTR lpstrFilePath)
        : m_lpstrFilePath(lpstrFilePath)
        , m_hkResult(NULL)
    {
        Load(hKey);
    }

    ~CRegistryHandler()
    {
        UnLoad();
    }

    /*
    * Load��Ҫ�����ڼ���ע���
    * ����ļ�·���´��ڶ�Ӧ��ע���,����TRUE
    * ����ļ�·����û�ж�Ӧ��ע������д���,����ʧ�ܷ���FALSE�������ɹ�����TRUE
    */
    BOOL Load(HKEY hKEY);
    
    /*
    * �رռ��ص�ע���
    */
    void UnLoad();
    
    /*
    * ��ѯlpValueName��Ӧ��ֵ
    */
    template<typename TRet>
    BOOL QueryValue(LPCWSTR lpValueName, DWORD dwtype, TRet* pret, DWORD dwSize);
    
    /*
    * �޸ĵ�ǰlpValueName��Ӧ��ֵ
    */
    template<typename T>
    BOOL Motify(LPCWSTR lpValueName, DWORD dwType, T value, DWORD dwSize);

private:
    LPCWSTR m_lpstrFilePath;
    //��������ʱ���Զ��رվ��
    HKEY m_hkResult;
};

inline BOOL CRegistryHandler::Load(HKEY hKey)
{
    BOOL bRet = FALSE;
    do
    {
        DWORD dwOptions = REG_OPTION_NON_VOLATILE;
        DWORD dwDisposition;

        LSTATUS lresult = RegCreateKeyEx(hKey,
            m_lpstrFilePath,
            0,
            NULL,
            dwOptions,
            KEY_ALL_ACCESS | KEY_WOW64_32KEY,
            NULL,
            &m_hkResult,
            &dwDisposition);

        if (lresult != ERROR_SUCCESS)
        {
            HLOCAL hLocal;

            FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS, 
                NULL, 
                lresult,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), 
                (PTSTR)&hLocal, 
                0, 
                NULL
            );

            MessageBox(NULL, (PCTSTR)LocalLock(hLocal), TEXT("����"), MB_OK);
            break;
        }
        bRet = TRUE;
    } while (FALSE);

    return bRet;
}

inline void CRegistryHandler::UnLoad()
{
    if (m_hkResult)
    {
        ::RegCloseKey(m_hkResult);
        m_hkResult = NULL;
    }
}

template<typename TRet>
inline BOOL CRegistryHandler::QueryValue(LPCWSTR lpValueName, DWORD dwtype, TRet* pret, DWORD dwSize)
{
    BOOL bRet = FALSE;

    do
    {
        if (!m_hkResult)
            break;

        LSTATUS lresult = ::RegQueryValueEx(m_hkResult,
            lpValueName,
            0,
            &dwtype,
            (LPBYTE)(pret),
            &dwSize
        );

        if (lresult != ERROR_SUCCESS)
        {
            HLOCAL hLocal;

            FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                lresult,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
                (PTSTR)&hLocal,
                0,
                NULL
            );

            //MessageBox(NULL, (PCTSTR)LocalLock(hLocal), TEXT("����"), MB_OK);
            break;
        }

        bRet = TRUE;
    } while (FALSE);

    return bRet;
}

template<typename T>
inline BOOL CRegistryHandler::Motify(LPCWSTR lpValueName, DWORD dwType, T value, DWORD dwSize)
{
    BOOL bRet = FALSE;

    do
    {
        if (!m_hkResult)
            break;

        LSTATUS lresult = ::RegSetValueEx(m_hkResult,
            lpValueName,
            0,
            dwType,
            (BYTE *)&value,
            dwSize
        );

        if (lresult != ERROR_SUCCESS)
        {
            HLOCAL hLocal;

            FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                lresult,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
                (PTSTR)&hLocal,
                0,
                NULL
            );

            MessageBox(NULL, (PCTSTR)LocalLock(hLocal), TEXT("����"), MB_OK);

            break;
        }

        bRet = TRUE;
    } while (FALSE);

    return bRet;
}