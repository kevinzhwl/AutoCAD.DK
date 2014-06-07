//
// (C) Copyright 1998-1999 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//
//

#ifndef ARXDBGTRANSACTIONREACTOR_H
#define ARXDBGTRANSACTIONREACTOR_H

/****************************************************************************
**
**	CLASS ArxDbgTransactionReactor:
**
**	**jma
**
*************************************/

class ArxDbgTransactionReactor : public AcTransactionReactor {

public:
    ACRX_DECLARE_MEMBERS(ArxDbgTransactionReactor);

        // constructors/destructor
					ArxDbgTransactionReactor();
    virtual			~ArxDbgTransactionReactor();

    virtual void    transactionAboutToStart(int& numTransactions);
    virtual void    transactionAboutToEnd(int& numTransactions);
    virtual void    transactionAboutToAbort(int& numTransactions);

    virtual void    transactionStarted(int& numTransactions);
    virtual void    transactionEnded(int& numTransactions);
    virtual void    transactionAborted(int& numTransactions);
    virtual void    endCalledOnOutermostTransaction(int& numTransactions);

    virtual void	transactionAboutToStart(int& numTransactions, AcDbTransactionManager* transactionManagerPtr);
    virtual void	transactionAboutToEnd(int& numTransactions, AcDbTransactionManager* transactionManagerPtr);
    virtual void	transactionAboutToAbort(int& numTransactions, AcDbTransactionManager* transactionManagerPtr);

    virtual void	transactionStarted(int& numTransactions, AcDbTransactionManager* transactionManagerPtr);
    virtual void	transactionEnded(int& numTransactions, AcDbTransactionManager* transactionManagerPtr);
    virtual void	transactionAborted(int& numTransactions, AcDbTransactionManager* transactionManagerPtr);
    virtual void	endCalledOnOutermostTransaction(int& numTransactions, AcDbTransactionManager* transactionManagerPtr);
    virtual void	objectIdSwapped(const AcDbObject* pTransResObj, const AcDbObject* pOtherObj, AcDbTransactionManager* transactionManagerPtr);


private:
    void    printReactorMessage(LPCTSTR event, int numTransactions) const;
    void    printReactorMessage(LPCTSTR event, int numTransactions, AcDbTransactionManager* transactionManagerPtr) const;
	void	printReactorMessage(LPCTSTR event, const AcDbObject* obj1,
							const AcDbObject* obj2,
							AcDbTransactionManager* transactionManagerPtr) const;

        // outlawed functions
								ArxDbgTransactionReactor(const& ArxDbgTransactionReactor);
    ArxDbgTransactionReactor&    operator=(const& ArxDbgTransactionReactor);        
};


#endif    // ARXDBGTRANSACTIONREACTOR_H
