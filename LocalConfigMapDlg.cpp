
// ConfigParseDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LocalConfigMap.h"
#include "LocalConfigMapDlg.h"
#include "afxdialogex.h"
#include "ConfigDetailDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CConfigParseDlg �Ի���



CLocalConfigMapDlg::CLocalConfigMapDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOCALCONFIGMAP_DIALOG, pParent)
    , m_Row(-1)
    , m_Col(-1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CLocalConfigMapDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST, m_ListCtrl);
}

BEGIN_MESSAGE_MAP(CLocalConfigMapDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CLocalConfigMapDlg::OnNMDblclkList)
    ON_COMMAND(ID_MENUITEM_IMPORT, &CLocalConfigMapDlg::OnMenuitemImport)
    ON_COMMAND(ID_MENUITEM_EXIT, &CLocalConfigMapDlg::OnMenuitemExit)
    ON_COMMAND(ID_MENUITEM_CLOASEALL, &CLocalConfigMapDlg::OnMenuitemCloaseall)
    ON_COMMAND(ID_MENUITEM_OPENALL, &CLocalConfigMapDlg::OnMenuitemOpenall)
    ON_COMMAND(ID_MENUITEM_HELP, &CLocalConfigMapDlg::OnMenuitemHelp)
    ON_COMMAND(ID_MENUITEM_CONTACT, &CLocalConfigMapDlg::OnMenuitemContact)
    ON_NOTIFY(NM_CLICK, IDC_LIST, &CLocalConfigMapDlg::OnNMClickList)
    ON_COMMAND(ID_GETFILEDETAIL, &CLocalConfigMapDlg::OnGetfiledetail)
END_MESSAGE_MAP()


// CConfigParseDlg ��Ϣ�������

BOOL CLocalConfigMapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


    // ��Ӳ˵�
    m_Menu.LoadMenuW(IDR_MENU1);
    SetMenu(&m_Menu);

    //��ʼ�����ͷ
    //�������Ű汾
    m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_OWNERDRAWFIXED | LVS_EX_SUBITEMIMAGES);
    m_ListCtrl.InsertColumn(0, _T("����"), LVCFMT_LEFT, 40);
    m_ListCtrl.InsertColumn(1, _T(CFGITEM_CONFIG_CFGITEM_ATTR_NAME), LVCFMT_LEFT, 150);
    m_ListCtrl.InsertColumn(2, _T(CFGITEM_CONFIG_CFGITEM_DOWN_ATTR_PATH), LVCFMT_LEFT, 300);

    //��ȡ����ͼƬ
    VERIFY(m_checkImgList.Create(IDB_BITMAP_SWITCH, 31, 2, RGB(255, 0, 255)));
    m_ListCtrl.SetImageList(&m_checkImgList, LVSIL_SMALL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CLocalConfigMapDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLocalConfigMapDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLocalConfigMapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLocalConfigMapDlg::OnMenuitemImport()
{
    _Clear();

    if (!GetXmlFilePath())
        return;

    if (!m_CfgItemConfig.Load())
    {
        MessageBox(_T("��ȡ�ļ�ʧ��"));
        return;
    }

    std::vector<CFGITEM>&veccfgtemp = m_CfgItemConfig.GetVecCfgItem();
    m_ConfigSyncReg.InitVecSwitchState(veccfgtemp);

    for (UINT nRow = 0; nRow < veccfgtemp.size(); nRow++)
    {
        LV_ITEM lvitem;
        memset((char *)&lvitem, '\0', sizeof(LV_ITEM));
        lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
        lvitem.iItem = nRow;
        lvitem.iSubItem = 0;
        lvitem.stateMask = 0;
        lvitem.iImage = veccfgtemp[nRow].SwitchState;
        m_ListCtrl.InsertItem(&lvitem);
        m_ListCtrl.SetItemText(nRow, 1, veccfgtemp[nRow].name);
        m_ListCtrl.SetItemText(nRow, 2, veccfgtemp[nRow].Download.path);
    }
}


void CLocalConfigMapDlg::OnMenuitemExit()
{
    CDialog::OnOK();
}


void CLocalConfigMapDlg::OnMenuitemCloaseall()
{
    UINT itemcount = m_ListCtrl.GetItemCount();
    if (itemcount <= 0)
    {
        MessageBox(_T("���ȵ���򿪵���xml�ļ�"));
        return;
    }

    std::vector<CFGITEM>&veccfgtemp = m_CfgItemConfig.GetVecCfgItem();

    for (UINT nRow = 0; nRow < itemcount; nRow++)
    {
        if (veccfgtemp[nRow].SwitchState)
        {
            if (m_ConfigSyncReg.SetSwitchState(veccfgtemp[nRow], 0, TRUE))
            {
                LV_ITEM lvitem;
                memset((char *)&lvitem, '\0', sizeof(LV_ITEM));
                lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
                lvitem.iItem = nRow;
                lvitem.iSubItem = 0;
                lvitem.stateMask = 0;
                m_ListCtrl.GetItem(&lvitem);
                lvitem.iImage = 0;
                m_ListCtrl.SetItem(&lvitem);
            }
        }
    }
}


void CLocalConfigMapDlg::OnMenuitemOpenall()
{
    UINT itemcount = m_ListCtrl.GetItemCount();
    if (itemcount <= 0)
    {
        MessageBox(_T("���ȵ���򿪵���xml�ļ�"));
        return;
    }

    std::vector<CFGITEM>&veccfgtemp = m_CfgItemConfig.GetVecCfgItem();

    for (UINT nRow = 0; nRow < itemcount; nRow++)
    {
        if (!(veccfgtemp[nRow].SwitchState))
        {
            if (m_ConfigSyncReg.SetSwitchState(veccfgtemp[nRow], 1, TRUE))
            {
                LV_ITEM lvitem;
                memset((char *)&lvitem, '\0', sizeof(LV_ITEM));
                lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
                lvitem.iItem = nRow;
                lvitem.iSubItem = 0;
                lvitem.stateMask = 0;
                m_ListCtrl.GetItem(&lvitem);
                lvitem.iImage = 1;
                m_ListCtrl.SetItem(&lvitem);
            }
        }
    }
}


void CLocalConfigMapDlg::OnMenuitemHelp()
{
    system("start explorer https://3127414196.github.io/ReadMe.html");
}


void CLocalConfigMapDlg::OnMenuitemContact()
{
    MessageBox(_T("����ϵannxiong@tencent.com лл"));
}

void CLocalConfigMapDlg::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    
    DWORD dwPos = GetMessagePos();
    CPoint pt(dwPos);
    m_ListCtrl.ScreenToClient(&pt);

    do
    {
        UINT nFlag;
        int nItem = m_ListCtrl.HitTest(pt, &nFlag);
        
        if (nFlag == LVHT_ONITEMICON)
        {
            std::vector<CFGITEM>&veccfgtemp = m_CfgItemConfig.GetVecCfgItem();
            BOOL nowState = (veccfgtemp[nItem].SwitchState == 0) ? FALSE : TRUE;
            m_ConfigSyncReg.SetSwitchState(veccfgtemp[nItem], !nowState, TRUE);
            //�ı�ͼ��
            LV_ITEM lvitem;
            memset((char *)&lvitem, '\0', sizeof(LV_ITEM));
            lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
            lvitem.iItem = nItem;
            lvitem.iSubItem = 0;
            lvitem.stateMask = 0;
            m_ListCtrl.GetItem(&lvitem);
            lvitem.iImage = !nowState;
            m_ListCtrl.SetItem(&lvitem);
        }
    } while (FALSE);

    *pResult = 0;
}

void CLocalConfigMapDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

    NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;
    m_Row = pNMListView->iItem;
    m_Col = pNMListView->iSubItem;

    do
    {
        if (m_Row < 0 || m_Col <= 0)  //ѡ�е��ǿհ״��������Ƕ�checkbox���е��
            break;

        std::vector<CFGITEM>&veccfgtemp = m_CfgItemConfig.GetVecCfgItem();
        CConfigDetailDlg configdetail(veccfgtemp[m_Row]);
        
        configdetail.DoModal();

    } while (FALSE);

    *pResult = 0;
}

void CLocalConfigMapDlg::_Clear()
{
    UINT RowCount = m_ListCtrl.GetItemCount();
    if (RowCount == 0)
        return;
    
    for (UINT nRow = 0; nRow < RowCount; nRow++)
    {
        if (!m_ListCtrl.DeleteItem(0))
            MessageBox(_T("��ձ��ʧ��"));
    }

    m_CfgItemConfig._Clear();
}

BOOL CLocalConfigMapDlg::GetXmlFilePath()
{
    BOOL bRet = FALSE;
    do
    {
        CFileDialog dlg(TRUE, _T("xml"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("LocalConfig(*.xml)|*.xml||"));
        INT_PTR nResponse = dlg.DoModal();
        if (nResponse == IDOK)
        {
            m_CfgItemConfig.m_strFilePath = dlg.GetPathName();
            bRet = TRUE;
        }
    } while (FALSE);

    return bRet;
}


void CLocalConfigMapDlg::OnGetfiledetail()
{
    if (m_ListCtrl.GetItemCount() <= 0)
    {
        MessageBox(_T("���ȵ���xml�ļ�"));
        return;
    }

    ATL::CAtlString str;
    str.Format(_T("�汾�ţ�%d\r\n����������%d"), m_CfgItemConfig.GetVersion(), m_ListCtrl.GetItemCount());
    MessageBox(str);
}
