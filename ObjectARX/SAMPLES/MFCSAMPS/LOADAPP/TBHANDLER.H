// TBHandler.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTBHandler window

class CTBHandler : public CWnd
{
// Construction
public:
	CTBHandler();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTBHandler)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTBHandler();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTBHandler)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
