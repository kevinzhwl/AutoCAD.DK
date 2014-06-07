//Copyright (C) 2004 by Autodesk, Inc.
//
//Permission to use, copy, modify, and distribute this software in
//object code form for any purpose and without fee is hereby granted, 
//provided that the above copyright notice appears in all copies and 
//that both that copyright notice and the limited warranty and
//restricted rights notice below appear in all supporting 
//documentation.
//
//AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
//AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
//MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
//DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
//UNINTERRUPTED OR ERROR FREE.
//
//Use, duplication, or disclosure by the U.S. Government is subject to 
//restrictions set forth in FAR 52.227-19 (Commercial Computer
//Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
//(Rights in Technical Data and Computer Software), as applicable

using System;
using Autodesk.AutoCAD.Runtime;
using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.DatabaseServices;

namespace EventsWatcher
{
	/// <summary>
	/// LayoutManEvents.
	/// </summary>
	public class LayoutManEvents
	{
		public LayoutManEvents()
		{
			m_bDone = false;
			m_lm = LayoutManager.Current;
			Do();
		}

		private LayoutManager m_lm;
		private bool m_bDone;
		
		public void Do()
		{
			if(m_bDone == false)
			{
				m_bDone = true;
			}
			else
			{
				WriteLine("\nLayoutMan watcher is working.");
				return;
			}

			try
			{
				m_lm.AbortLayoutCopied += new LayoutEventHandler(callback_AbortLayoutCopied);
				m_lm.AbortLayoutRemoved += new LayoutEventHandler(callback_AbortLayoutRemoved);
				m_lm.AbortLayoutRename += new LayoutRenamedEventHandler(callback_AbortLayoutRename);
				m_lm.LayoutCopied += new LayoutCopiedEventHandler(callback_LayoutCopied);
				m_lm.LayoutCreated += new LayoutEventHandler(callback_LayoutCreated);
				m_lm.LayoutRemoved += new LayoutEventHandler(callback_LayoutRemoved);
				m_lm.LayoutRenamed += new LayoutRenamedEventHandler(callback_LayoutRenamed);
				m_lm.LayoutsReordered += new EventHandler(callback_LayoutsReordered);
				m_lm.LayoutSwitched += new LayoutEventHandler(callback_LayoutSwitched);
				m_lm.LayoutToBeCopied += new LayoutEventHandler(callback_LayoutToBeCopied);
				m_lm.LayoutToBeRemoved += new LayoutEventHandler(callback_LayoutToBeRemoved);
				m_lm.LayoutToBeRenamed += new LayoutRenamedEventHandler(callback_LayoutToBeRenamed);
				m_lm.PlotStyleTableChanged += new PlotStyleTableChangedEventHandler(callback_PlotStyleTableChanged);
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		}

		public void Undo()
		{
			if(m_lm == null || m_bDone == false)
				return;

			try
			{
				m_lm.AbortLayoutCopied -= new LayoutEventHandler(callback_AbortLayoutCopied);
				m_lm.AbortLayoutRemoved -= new LayoutEventHandler(callback_AbortLayoutRemoved);
				m_lm.AbortLayoutRename -= new LayoutRenamedEventHandler(callback_AbortLayoutRename);
				m_lm.LayoutCopied -= new LayoutCopiedEventHandler(callback_LayoutCopied);
				m_lm.LayoutCreated -= new LayoutEventHandler(callback_LayoutCreated);
				m_lm.LayoutRemoved -= new LayoutEventHandler(callback_LayoutRemoved);
				m_lm.LayoutRenamed -= new LayoutRenamedEventHandler(callback_LayoutRenamed);
				m_lm.LayoutsReordered -= new EventHandler(callback_LayoutsReordered);
				m_lm.LayoutSwitched -= new LayoutEventHandler(callback_LayoutSwitched);
				m_lm.LayoutToBeCopied -= new LayoutEventHandler(callback_LayoutToBeCopied);
				m_lm.LayoutToBeRemoved -= new LayoutEventHandler(callback_LayoutToBeRemoved);
				m_lm.LayoutToBeRenamed -= new LayoutRenamedEventHandler(callback_LayoutToBeRenamed);
				m_lm.PlotStyleTableChanged -= new PlotStyleTableChangedEventHandler(callback_PlotStyleTableChanged);
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}

			m_bDone = false;
		}

		private void callback_AbortLayoutCopied(object sender, LayoutEventArgs e)
		{
			WriteLine(String.Format("AbortLayoutCopied - {0}", e.Name));
		}

		private void callback_AbortLayoutRemoved(object sender, LayoutEventArgs e)
		{
			WriteLine(String.Format("AbortLayoutRemoved - {0}", e.Name));
		}

		private void callback_AbortLayoutRename(object sender, LayoutRenamedEventArgs e)
		{
			WriteLine(String.Format("AbortLayoutRename - {0} to: {1}", e.Name, e.NewName));
		}

		private void callback_LayoutCopied(object sender, LayoutCopiedEventArgs e)
		{
			WriteLine(String.Format("LayoutCopied - {0} to: {1}", e.Name, e.NewName));
		}

		private void callback_LayoutCreated(object sender, LayoutEventArgs e)
		{
			WriteLine(String.Format("LayoutCreated - {0}", e.Name));
		}

		private void callback_LayoutRemoved(object sender, LayoutEventArgs e)
		{
			WriteLine(String.Format("LayoutRemoved - {0}", e.Name));
		}

		private void callback_LayoutRenamed(object sender, LayoutRenamedEventArgs e)
		{
			WriteLine(String.Format("LayoutRenamed - to: {0}", e.NewName));
		}

		private void callback_LayoutsReordered(object sender, EventArgs e)
		{
			WriteLine("LayoutReorderd");
		}

		private void callback_LayoutSwitched(object sender, LayoutEventArgs e)
		{
			WriteLine(String.Format("LayoutSwitched - {0}", e.Name));
		}

		private void callback_LayoutToBeCopied(object sender, LayoutEventArgs e)
		{
			WriteLine(String.Format("LayoutToBeCopied - {0}", e.Name));
		}

		private void callback_LayoutToBeRemoved(object sender, LayoutEventArgs e)
		{
			WriteLine(String.Format("LayoutToBeRemoved - {0}", e.Name));
		}

		private void callback_LayoutToBeRenamed(object sender, LayoutRenamedEventArgs e)
		{
			WriteLine(String.Format("LayoutToBeRenamed - from: {0} to: {1}", e.Name, e.NewName));
		}

		private void callback_PlotStyleTableChanged(object sender, PlotStyleTableChangedEventArgs e)
		{
			WriteLine(String.Format("PlotStyleTableChanged - {0}", e.NewName));
		}

		private void WriteLine(object obj)
		{
			try
			{
				string str = "\nLayoutMan Events: " + obj.ToString();
				Helper.StreamMessage(str);	
			}
			catch (System.Exception ex)
			{
				Helper.Message(ex);
			}
		} // end of WriteLine() function

	}	// end of class LayoutManEvents
}

