#pragma once
#include "ConfigStruct.h"
#include <vector>

class CConfigSyncRegistry
{
public:
    CConfigSyncRegistry();
    ~CConfigSyncRegistry();

#define CONFIGSYNC_KEY          HKEY_LOCAL_MACHINE
#define CONFIGSYNC_LPSUBKEY     _T("SOFTWARE\\Wow6432Node\\Tencent\\ConfigSync")
#define CONFIGSYNC_TYPE         REG_DWORD
#define CONFIGSYNC_TYPE_SIZE    (sizeof(DWORD))

    void InitVecSwitchState(std::vector<CFGITEM>& vecCfgItem);
    
    //��ע�����ȡ��guid��Ӧ��ֵ
    //pdwstateΪNULL��ֻ��ѯע������Ƿ���guid�ļ�ֵ����ΪNULL����״̬pdwstate����
    BOOL FetchStateFromReg(CFGITEM& cfgitem, DWORD* pdwstate = 0);

    //bwritethroughΪTRUE��ʾ�Ƿ�Ҫд��ע���
    //bwritethroughΪFALSE��ʾ��д��ע���ֻд��m_vecswitchstate
    //Ĭ�ϲ�д��
    BOOL SetSwitchState(CFGITEM& cfgitem, DWORD pdwstate, BOOL bwritethrough = FALSE);
};

