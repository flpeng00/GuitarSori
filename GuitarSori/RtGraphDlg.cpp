
// RtGraphDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RtGraph.h"
#include "RtGraphDlg.h"
#include "paTest.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRtGraphDlg dialog
CRtGraphDlg::CRtGraphDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRtGraphDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRtGraphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRtGraphDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CRtGraphDlg message handlers

BOOL CRtGraphDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CRect rtGraph;
	GetDlgItem(IDC_STATIC_RT_GRAPH)->GetWindowRect(rtGraph);

	ScreenToClient(rtGraph);

	_rtGraph = new COScopeCtrl(3);		//cos,sin,tan 3개의 그래프 예약
	_rtGraph->Create(WS_VISIBLE | WS_CHILD, rtGraph, this, IDC_STATIC_RT_GRAPH);
	_rtGraph->SetRanges(-3., 3.);	
	_rtGraph->autofitYscale = true;
	_rtGraph->SetYUnits(TEXT("Value"));
	_rtGraph->SetXUnits(TEXT("Time"));
	_rtGraph->SetLegendLabel(TEXT("cos(t)"), 0);
	_rtGraph->SetLegendLabel(TEXT("sin(t)"), 1);
	_rtGraph->SetLegendLabel(TEXT("tan(t)"), 2);
	_rtGraph->SetPlotColor(RGB(255,0,0), 0);
	_rtGraph->SetPlotColor(RGB(0,255,0), 1);
	_rtGraph->SetPlotColor(RGB(0,0,255), 2);
	_rtGraph->InvalidateCtrl();

	SetTimer (1000, 1, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRtGraphDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRtGraphDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CRtGraphDlg::OnTimer(UINT_PTR nIDEvent)
{
	static paSample *paSample_test = NULL;
	static FILE *output;
	float *dummy_data;
	dummy_data = new float[1024];
	// TODO: Add your message handler code here and/or call default
	if (!paSample_test){
		paSample_test = new paSample();
		paSample_test->deviceInfo->name;
	}
	memcpy(dummy_data, paSample_test->dataout(), sizeof(float)* 1024);
	if(nIDEvent==1000) {
		double t = (double)GetTickCount ()/1000.;

		double value[1] = {dummy_data[0]};
		for (int i = 0; i < 1024; i++){
			value[0] = dummy_data[i];
			_rtGraph->AppendPoints(value);
		}
	}

	CDialog::OnTimer(nIDEvent);
}

void CRtGraphDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	delete _rtGraph;
}

paSample::paSample(){
	err = Pa_Initialize();
	deviceNum = Pa_GetDeviceCount();
	//i = Pa_GetDefaultInputDevice();
	i = 1;
	deviceInfo = Pa_GetDeviceInfo(i);
	/* poll for standard sample rates */
	inputParameters.device = i;
	inputParameters.channelCount = 1;
	inputParameters.sampleFormat = PA_SAMPLE_TYPE;
	inputParameters.suggestedLatency = 0; /* ignored by Pa_IsFormatSupported() */
	inputParameters.hostApiSpecificStreamInfo = NULL;
	bytesNum = FRAMES_PER_BUFFER * NUM_CHANNELS * SAMPLE_SIZE;
	sampleBlock = (char*)malloc(bytesNum);
	CLEAR(sampleBlock);
	stream_start();
}

paSample::~paSample(){
	stream_close();
}

void paSample::stream_start(){
	err = Pa_OpenStream(
		&inputStream, &inputParameters, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, NULL, NULL);
	err = Pa_StartStream(inputStream);
}

void paSample::stream_close(){
	Pa_StopStream(inputStream);
	CLEAR(sampleBlock);
	free(sampleBlock);
	Pa_Terminate();
}
char* paSample::dataout(){
	err = Pa_ReadStream(inputStream, sampleBlock, FRAMES_PER_BUFFER);
	return sampleBlock;
}