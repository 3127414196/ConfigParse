
// ConfigParseDlg.h : ͷ�ļ�
//

#pragma once
#include "ConfigParse.h"
#include "ConfigSyncRegistry.h"
#include "afxcmn.h"

// CConfigParseDlg �Ի���
class CLocalConfigMapDlg : public CDialogEx
{
// ����
public:
    CLocalConfigMapDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOCALCONFIGMAP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
    CListCtrl m_ListCtrl;
    CImageList m_checkImgList;
    CMenu m_Menu;
    afx_msg void OnMenuitemImport();
    afx_msg void OnMenuitemExit();
    afx_msg void OnMenuitemCloaseall();
    afx_msg void OnMenuitemOpenall();
    afx_msg void OnMenuitemHelp();
    afx_msg void OnMenuitemContact();
    afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);

    //��ձ��
    void _Clear();
    //���ļ���Դ���������������ļ�·��
    BOOL GetXmlFilePath();

private:
    int m_Row;
    int m_Col;
    CConfigSyncRegistry m_ConfigSyncReg;
    CConfigParse m_CfgItemConfig;
public:
    afx_msg void OnGetfiledetail();
};
