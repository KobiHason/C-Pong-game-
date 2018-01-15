
// PongDlg.h : header file
//

#pragma once
#include "Solid.h"

// PongDlg dialog
class PongDlg : public CDialogEx
{
// Construction
public:
	PongDlg(CWnd* pParent = NULL);	// standard constructor
	Bat *leftbat;
	Ball *ball;
	Boarder *boarder;
	Brick* bricks[36];
	bool leftbatfirstmove;
	bool boarderfirstmove;
	bool ballfirstmove;
	bool bricksfirstmove;
	bool hit;
	CPoint startball;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY20170707PONG3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
//	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButtonOpen();
	virtual void Serialize(CArchive& ar);
	void SetBallStart();
};
