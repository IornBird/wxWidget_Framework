#pragma once
#include <wx/wx.h>
#include <wx/gbsizer.h>
#include <thread>
#include <mutex>
#include <string>
using std::string;
using std::mutex;
using std::thread;
using std::lock_guard;
// include other files

class Launcher : public wxApp
{
public:
	// where program begins
	virtual bool OnInit();
};

DECLARE_APP(Launcher);

class MainFrame : public wxFrame
{
	wxPanel* panel;
	mutex m;
	bool processing = false, closeReq = false;

	//place elements here

	void CreateControls()
	{
		/* how elements placed
		 * example:
		wxPanel* panel
		wxSizer* sizer
		wxPanel* children = new wxPanel(panel);
		sizer->Add(childrens);
		panel->SetSizerAndFit(sizer);
		 */
	}
	/* how events handled, and call alogrithms
	 * place them into constructor, if needed
	 * examples:

	void OnButtonClicked(wxCommandEvent& ce)
	{
		if (processing) return;const auto f = [this]() {
			if (processing) return;
			processing = true;
			// code that ran in another thread
			processing = false;
		};
		thread bck{f};
		bck.detach();
		
	}
	*/
	/*
	 * all GUI changes must be in main thread
	 */
	void DoBackgroundProcess()
	{
		wxGetApp().CallAfter([this]() {
			lock_guard<mutex> lg(m);
			if (!processing) return;
			// all GUI changes must be in main 
		});
	}

	void Onclose(wxCloseEvent& evt)
	{
		if (processing)
		{
			evt.Veto();
			closeReq = true;
		}
		else
			Destroy();
	}
public:
	MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
	{
		CreateControls();
		Bind(wxEVT_CLOSE_WINDOW, &MainFrame::Onclose, this);
		// place functions for elements
	}
	string loadFile()
	{
		wxFileDialog fd(this, "OpenFile", "", "", "All files(*.*)|*.*"
			, wxFD_OPEN | wxFD_FILE_MUST_EXIST);
		if (fd.ShowModal() == wxCANCEL)
			return "";
		wxString s = fd.GetPath();
		return s.ToStdString();
	}

};


