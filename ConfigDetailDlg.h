#pragma once

#include "ConfigParse.h"
// CConfigDetailDlg �Ի���

class CConfigDetailDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConfigDetailDlg)

public:
	CConfigDetailDlg(CFGITEM& cfgitem, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CConfigDetailDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIGDETAIL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
    CEdit m_editbuild_min;
    CEdit m_editbuild_max;
    CEdit m_editappid;
    CEdit m_editpath;
    CEdit m_editpolicy_type;
    CEdit m_editpolicy_id;
    CEdit m_editswitch_id;
    CEdit m_editurl_id;
    CEdit m_editmd5_id;
    CEdit m_editnode;
    CEdit m_editmsgid;
    CEdit m_editnotifywhensuc;
    CEdit m_editcontext;
    CFGITEM& m_vecCfgItem;
};
