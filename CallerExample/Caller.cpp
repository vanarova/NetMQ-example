// Caller.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Caller.h"
#include "CMDF4Writer.h"
#include "CMdf4Reader.h"
#include <io.h>
#include <atlsafe.h>
#include <atlstr.h>
//#include <vld.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

void WriteMDF4Example(void); // forward
void ReadMDF4Example(int,int,int, CString); // forward

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{	int nRetCode = 0;
	int colEnd = _wtoi(argv[2]);
	colEnd = colEnd / 2;
	int colStart = _wtoi(argv[1]);
	int showMeta = _wtoi(argv[3]);
	

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
			// Test MDF4Writer
			//WriteMDF4Example();

			// Test MDF4Reader
			ReadMDF4Example(colStart, colEnd, showMeta, argv[4]);
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}

BOOL MyCreateSRBlocks(CMDF4Writer &m4, int iGroup, 
                      double xFactor, double xOffset, // mean x delta and offset
                      double xmin, double xmax,  // x range of data group
                      unsigned __int64  nValues) // cg_cycle_count
{
  double dt, xrange;
  ULONG cb = _MAX_PATH-1;
  DWORD dwFactor=5;
  DWORD dwSoll[3], nSoll=3; // projected no of intervals in SR block
  dwSoll[0] = 1000000;
  dwSoll[1] = 100000;
  dwSoll[2] = 10000;

  double fPoints;
  __int64 nPoints;
  __int64 nPointsToDo[10];
  xrange = xmax - xmin;
  if(xrange <= 0.0)
    return FALSE;
 
  memset(nPointsToDo, 0, sizeof(nPointsToDo));
  int nsr = 0, i=0;
  fPoints = nValues / dwFactor;
  if(fPoints < dwSoll[0])
  {
    while(i < nSoll && fPoints < dwSoll[i])
      i++;
    if(i >= nSoll)
      return FALSE;
  }
  while(i < nSoll)
    nPointsToDo[nsr++] = dwSoll[i++];
    
  for(i=0; i<nsr; i++) if(nPointsToDo[i])
  {
    nPoints = nPointsToDo[i];
    dt = xrange / nPoints;
		m4.CreateSRBlock( iGroup, dt, xrange, xFactor, xOffset);
  }
  return TRUE;
}

// enumeration for member cn_data_type
#define CN_D_UINT_LE   0  // Unsigned Integer LE Byte Order
#define CN_D_SINT_LE   2  // Signed Integer LE Byte Order
#define CN_D_FLOAT_LE  4  // Float (IEEE 754) LE Byte Order

//
//void WriteMDF4Example(void)
//{
//	CMDF4Writer m4;
//	long idGroup[2], idSignal[16], i;
//	__int64 i64N =  10000;
//	double xmin, xmax, xrange, x, xoffset = 0;
//	CString str, str1;
//
//	CoInitializeEx(NULL, 0); // don't forget this
//
//	//if (!m4.CreateDispatch(_T("{891BCB49-095B-417C-9235-564194E85533}")))
//	if (!m4.CreateDispatch(_T("MDF4WriterLib.1")))
//	{
//		DWORD dwErr = GetLastError();
//		_tprintf(_T("Cannot create dispatch interface\n"));
//		return;
//	}
//
//	// if file exists, delete it first
//	if (_taccess(_T("C:\\Temp\\M4Test.mf4"),0)==0)
//		_tunlink(_T("C:\\Temp\\M4Test.mf4"));
//	// Set the file name before you create the file
//	m4.put_strPathName( _T("C:\\Temp\\M4Test.mf4"));
//	m4.CreateMDF4( _T("Caller"), _T("Lego"), _T("1.0"), _T("No comment"), 410); // Version MDF4.10
//
//	// Add a group with an equidistant, virtual time signal with 10 Hz sampling rate and 10 s offset
//	m4.AddGroup64( _T("Group 1 Test"), i64N, &idGroup[0]);
//	m4.AddTimeInfo( idGroup[0], _T("Time"), _T("s"), 0.1, 10);
//	// Square wave, unsigned int 8 bit
//	m4.AddSignal( idGroup[0], _T("Square"), _T("Signal with square wave"),     CN_D_UINT_LE, -1, 8,   _T("V"), 1.0, 0.0, 0, 0.0, -1, &idSignal[0]);
//	// Sawtooth wave, signed int 8 bit
//	m4.AddSignal( idGroup[0], _T("Sawtooth"), _T("Signal with sawtooth wave"), CN_D_SINT_LE, -1, 8,   _T("A"), 1.0, 0.0, 0, 0.0, -1, &idSignal[1]);
//
//  // Rampe, double 
//	m4.AddSignal( idGroup[0], _T("Ramp"), _T("Signal with ramp wave"),         CN_D_FLOAT_LE, -1, 64, _T("°C"), 1.0, 0.0, 0, 0.0, -1, &idSignal[2]);
//
//	// Add 3 Bit Signals
//	for (i=0; i<3; i++)
//	{
//		str.Format(_T("Bit%d"),i);
//		m4.AddSignal( idGroup[0], str, _T("Bit Signal"),         CN_D_UINT_LE, -1, i+1, _T("-"), 1.0, 0.0, 0, 0.0, -1, &idSignal[i+3]);
//		if (i==0)
//			str = _T("0=ON|1=OFF|");
//		else if (i==1)
//			str = _T("0=ON|1=OFF|2=BOTH|3=missing");
//		else
//			str = _T("0=an|1=aus|2=uhu");
//
//		m4.SetSignalDiscrete( idGroup[0], idSignal[i+3], 1, str);
//	}
//
//  str = _T("0=Wert0");
//  for(i=0; i<2048; i++)
//  {
//    str1.Format(_T("|%d=Wert%d"), i, i);
//    str += str1;
//  }
//  m4.SetSignalDiscrete(idGroup[0], idSignal[2], 1, str);
//
//#if 0
//	// Add a group with a non-equidistant time signal with approx. 10 Hz sampling rate and 0 s offset
//	m4.AddGroup64( "Group 2 Test", i64N, &idGroup[1]);
//	m4.AddTimeSignal( idGroup[1], "Time",CN_D_FLOAT_LE, -1, 64, "s", 1.0, 0.0, &idSignal[6]);
//	m4.AddSignal( idGroup[1], "Square", "Signal with square wave",     CN_D_UINT_LE, -1,  8, "V", 1.0,  0.0, 1, -100.0, -1, &idSignal[7]);
//	m4.AddSignal( idGroup[1], "Sawtooth", "Signal with sawtooth wave", CN_D_SINT_LE, -1,  8, "A", 0.1, -5.0, 1,    0.0, -1, &idSignal[8]);
//	m4.AddSignal( idGroup[1], "Ramp", "Signal with ramp wave",         CN_D_FLOAT_LE,-1, 64, "m", 1.0,  0.0, 1,    0.0, -1, &idSignal[9]);
//#endif
//
//	// Now create the groups and channels in the MDF4 file 
//	m4.MakeGroups();
//	// After this, do not change/add groups or signals
//
//	// Write the data
//	for (i=0; i<i64N; i++)
//	{
//		// Group 1
//		m4.SetSignalValue( idGroup[0], idSignal[0], i<i64N/2 ? 0.0 : 255.0, 0);
//		m4.SetSignalValue( idGroup[0], idSignal[1], (double)(i%10)-5, 0);
//    m4.SetSignalValue (idGroup[0], idSignal[2], (double)i, 0);
//		m4.SetSignalValue( idGroup[0], idSignal[3], (double)(i & 1), 0);
//		m4.SetSignalValue( idGroup[0], idSignal[4], (double)(i % 3), 0);
//		m4.SetSignalValue( idGroup[0], idSignal[5], (double)(i % 4), 0);
//
//		m4.WriteRecord( idGroup[0] );
//
//#if 0
//		// Group 2
//		x = (double)i/10 + (double)(rand()-16384)/1638400.;
//		if (i > i64N/2 && xoffset == 0)
//			xoffset = x;
//		x += xoffset;
//		if (i==0)
//			xmin = x;
//		else
//			xmax = x;
//		m4.SetSignalValue( idGroup[1], idSignal[6], x, 0);
//		int noval = 0;
//		if (i == i64N/2)
//			noval = 1;
//		m4.SetSignalValue( idGroup[1], idSignal[7], i<i64N/2 ? 0.0 : 255.0, noval);
//		m4.SetSignalValue( idGroup[1], idSignal[8], (double)(i%10)-5, noval);
//		m4.SetSignalValue( idGroup[1], idSignal[9], (double)i, noval);
//		m4.WriteRecord( idGroup[1] );
//#endif
//	}
//	// Flush records, close open data blocks
//	m4.FlushGroup( idGroup[0] );
//	//m4.FlushGroup( idGroup[1] );
//
//	// Close the file
//	m4.Close();
//
//	MyCreateSRBlocks(m4, idGroup[0], 0.1, 10.0, // mean x delta and offset
//                   10.0, 10.0 + i64N * 0.1,  // x range of data group
//                   i64N);
//}

// Block types
#define ID_HEADER       1
#define ID_FILEHISTORY  2
#define ID_DATAGROUP    3
#define ID_CHANNELGROUP 4
#define ID_CHANNEL      5
#define ID_SI_GROUP     6
#define ID_SI_CHANNEL   7
#define ID_TEXTBLOCK    8

// Header Contents MDF3
#define ID_AUTHOR  0
#define ID_ORG     1
#define ID_PROJECT 2
#define ID_SUBJECT 3
#define ID_DATE    4
#define ID_TIME    5

#define BUFFERSIZE 150
#define ARRAYSIZE 2450

// enumeration for text/comment members
// Header
#define hd_md_comment 5
// File History
#define fh_md_comment 1
// Data Group
#define dg_md_comment 3
// Channel Group
#define cg_tx_acq_name 2
#define cg_md_comment  5
// Channel 
#define cn_tx_name     2
#define cn_md_comment  7
// Channel / Channel Group: SI Block
#define si_tx_name    0
#define si_tx_path    1
#define si_md_comment 2

static double c_data[BUFFERSIZE][ARRAYSIZE];

void ReadMDF4Example(int colStart, int colEnd, int showMeta, CString inpath)
{
	CMdf4Reader m4; // The COM object
	CString str;
	CString unt;
	int iGrp, nGroups, iSig, nSignals;
	LONG l,nCounter, lVersion,rowCount=1;
  BOOL bIsMDF4;
	double val;
	int r, r1,cnt = 1,st,en,head=1,rnt=0;
	long mon, nValues=10, idx1, idx2, buffCount,remainingRows,maxbuffCount,mxCount;
	double xmin, xmax, rmin, rmax, raster;
	////TODO:Check
	
	/*for (int i = 0; i < BUFFERSIZE; ++i)
		data[i] = new double[ARRAYSIZE];*/

	// Some BSTRs
	BSTR t,tTime;
	CString Name[ARRAYSIZE],Unit[ARRAYSIZE],Comment[ARRAYSIZE], Time[ARRAYSIZE];

	CoInitializeEx(NULL, 0); // don't forget this
	// Create the object
	//if (!m4.CreateDispatch(_T("{A5D406EA-0508-415E-B5E2-E868370D3721}")))
	if (!m4.CreateDispatch(_T("MDF4ReaderLib.1")))
	{
		DWORD dwErr = GetLastError();
		_tprintf(_T("Cannot create dispatch interface\n"));
		return;
	}

	// Get an MDF4 file
	//CFileDialog fdlg(TRUE,_T(".mf4"));
	//if (fdlg.DoModal() != IDOK)
	//	return;
	//if(showMeta == 1)
	//printf("File %S\n", fdlg.GetPathName());
	//m4.OpenMDF4(fdlg.GetPathName());


	std::string STDStr(CW2A(inpath.GetString()));
	
	
	LPCTSTR lpctszStr = inpath;
m4.OpenMDF4(lpctszStr);

  lVersion = m4.get_Version();
  bIsMDF4 = lVersion >= 400;

	// Get file time and other infos
	CTime ti(m4.get_FileTime());
	val = m4.get_TimeFraction()*1000; // ms
	str = ti.Format("%d:%m:%Y %H:%M:%S");
	if (showMeta == 1)
	printf("FileTime = %S.%03ld\n",str,(int)val);

  if(bIsMDF4)
  {
    str = m4.get_Comment(ID_HEADER, hd_md_comment);
	if (showMeta == 1) {
		if (!str.IsEmpty())
			printf("Header comment = %S\n", str);
	}

    str = m4.get_Comment(ID_FILEHISTORY, fh_md_comment);
	if (showMeta == 1) {
		if (!str.IsEmpty())
			printf("File history = %S\n", str);
	}
  }
  else
  {
    str = m4.get_Comment(ID_HEADER, ID_AUTHOR);
    if(!str.IsEmpty())
      printf("Author = %S\n", str);
    str = m4.get_Comment(ID_HEADER, ID_ORG);
    if(!str.IsEmpty())
      printf("Organisation = %S\n", str);
    str = m4.get_Comment(ID_HEADER, ID_PROJECT);
    if(!str.IsEmpty())
      printf("Project = %S\n", str);
    str = m4.get_Comment(ID_HEADER, ID_SUBJECT);
    if(!str.IsEmpty())
      printf("Sunject = %S\n", str);
    str = m4.get_Comment(ID_HEADER, ID_DATE);
    if(!str.IsEmpty())
      printf("Date = %S\n", str);
    str = m4.get_Comment(ID_HEADER, ID_TIME);
    if(!str.IsEmpty())
      printf("Time = %S\n", str);
    
    str = m4.get_Comment(ID_TEXTBLOCK, 0);
    if(!str.IsEmpty())
      printf("Text block = %S\n", str);
  }
  nGroups = m4.get_NGroups();
  if (showMeta == 1)
	printf("No. of groups = %ld\n",nGroups);
	// walk through all groups
  for (iGrp = 0; iGrp < nGroups; iGrp++)
  {
	  if (bIsMDF4) // MDF3 has no group name
	  {
		  // Calling a COM function which uses BSTR:
		  t = NULL; tTime = NULL; // BSTR must be NULL 
		  m4.GetGroupName(&t, iGrp); // allocates t
		  if (showMeta == 1)
			  printf("Group %ld = %S\n", iGrp + 1, t);
		  ::SysFreeString(t); // we must free this string
	  }
	  // Load the current group
	  m4.LoadGroup(iGrp);
	  tTime = NULL;

	  if (bIsMDF4 && showMeta == 1)
	  {
		  // Comment from data group:
		  str = m4.get_Comment(ID_DATAGROUP, dg_md_comment);
		  if (!str.IsEmpty())
			  printf("  Comment = %S\n", str);
		  // Comments from channel group:
		  str = m4.get_Comment(ID_CHANNELGROUP, cg_tx_acq_name);
		  if (!str.IsEmpty())
			  printf("  CG name = %S\n", str);
		  str = m4.get_Comment(ID_CHANNELGROUP, cg_md_comment);
		  if (!str.IsEmpty())
			  printf("  CG comment = %S\n", str);
		  // Comments from channel groups SI block :
		  str = m4.get_Comment(ID_SI_GROUP, si_tx_name);
		  if (!str.IsEmpty())
			  printf("  CG SI name = %S\n", str);
		  str = m4.get_Comment(ID_SI_GROUP, si_tx_path);
		  if (!str.IsEmpty())
			  printf("  CG SI path = %S\n", str);
		  str = m4.get_Comment(ID_SI_GROUP, si_md_comment);
		  if (!str.IsEmpty())
			  printf("  CG SI comment = %S\n", str);
	  }

	  // Load the time signal of the current group
	  m4.LoadTimeSignal(&tTime);

	  nSignals = m4.get_NSignals();
	  unsigned __int64 ll = m4.get_NSamples64();
	  l = m4.get_NSamples();
	  if (showMeta == 1) {
	  printf("  No. of signals = %ld\n", nSignals);
	  printf("  %ld samples \n", l);
		}
	  // Time range of group measurement:
	  xmin = m4.get_FirstTimestamp();
	  xmax = m4.get_LastTimestamp();
	  if (showMeta == 1) {
		  printf("  Time %lf to %lf\n", xmin, xmax);
		  printf("  Time signal %S\n", tTime);
	  }
	  //::SysFreeString(tTime);

	  // Get time raster information
	  // raster = delta t between data points
	  // rmin   = minimal delta
	  // rmax   = maximal delta, same as rmin for equidistant data
	  // mon    = Monotony, defined by MDF4 as 
	  // #define CN_MON_NOTDEFINED       0
	  // #define CN_MON_DECREASE         1
	  // #define CN_MON_INCREASE         2
	  // #define CN_MON_STRICT_DECREASE  3
	  // #define CN_MON_STRICT_INCREASE  4
	  // #define CN_MONOTONOUS           5
	  // #define CN_STRICT_MON           6
	  // #define CN_NOT_MON              7
	  t = NULL;
	  LONG bIsVirtual = FALSE;
	  m4.GetTimeSignal(&t, &mon, &rmin, &rmax, &raster, &bIsVirtual);
	  if (showMeta == 1)
		  printf("    Unit = %S  Raster = %lf (%lf - %lf)  %ld\n", t, raster, rmin, rmax, mon);
	  ::SysFreeString(t);

	  m4.TimeToIndex(xmin, 0, &idx1);
	  m4.TimeToIndex(xmax, idx1, &idx2);


	  nValues = idx2 - idx1 + 1; // Calc number of data points 
	  buffCount = nValues / BUFFERSIZE;
	  remainingRows = nValues % BUFFERSIZE;
	  if (remainingRows>0)
	  {
		  maxbuffCount = buffCount + 1;
	  }
	  
	  for (size_t ib = 1; ib <= maxbuffCount; ib++)
	  {
		  // Read data from time signal and the signal itself:
		  // Method 1: Use a SafeArray
		  // Create 2 SafeArrays
		  CComSafeArray<double> *pData;
		  CComSafeArray<double> *pTimeData;
		  CComSafeArrayBound bound;
		  // Wrap safearrays by a VARIANT
		  VARIANT vData, vTimeData;
		  // walk thru signals - nSignals
		  for (iSig = colStart; iSig < colEnd; iSig++)
		  {
			  t = NULL;
			  m4.LoadSignal(&t, iSig);
			
			  ::SysFreeString(t);
			  // Get signal description
			  LONG discrete; // signal has discrete values (logical signal)
			  BSTR tDisplayName = NULL, tAliasName = NULL, tUnit = NULL, tComment = NULL;
			  m4.GetSignal(&tDisplayName, &tAliasName, &tUnit, &tComment, &discrete);
			 
			  ::SysFreeString(tDisplayName);
			  ::SysFreeString(tAliasName);
			  ::SysFreeString(tUnit);
			  ::SysFreeString(tComment);
			  unt = tUnit;
			  if (showMeta == 1) {
				  printf("=========================\n");
				  // Comments from channel (same as above):
				  str = m4.get_Comment(ID_CHANNEL, cn_tx_name);
				  //name
				  if (!str.IsEmpty())
					  printf("Signal Name: %S\n", str);
				  //unit
				  printf("%S\n", unt);
				  str = m4.get_Comment(ID_CHANNEL, cn_md_comment);
				  //comment
				  if (!str.IsEmpty())
					  printf("%S\n", str);
				  // Comments from channel SI source
				  str = m4.get_Comment(ID_SI_CHANNEL, si_tx_name);
				  if (!str.IsEmpty())
					  printf("SN: %S\n", str);
				  str = m4.get_Comment(ID_SI_CHANNEL, si_tx_path);
				  if (!str.IsEmpty())
					  printf("SN: %S\n", str);
				  str = m4.get_Comment(ID_SI_CHANNEL, si_md_comment);
				  if (!str.IsEmpty())
					  printf("SN: %S\n", str);

			  }
			
			  else
			  {

				  //str = m4.get_Comment(ID_CHANNEL, cn_tx_name);
				  //::SysFreeString(str);
				  //Unit[410],Comment[410];
				  Name[iSig] = m4.get_Comment(ID_CHANNEL, cn_tx_name);
				  Time[iSig] = tTime;
				  ::SysFreeString(tTime);
				  Unit[iSig] = unt;
				  Comment[iSig] = m4.get_Comment(ID_CHANNEL, cn_md_comment);

				  st = (ib * BUFFERSIZE) - BUFFERSIZE;
				  en = (ib * BUFFERSIZE);

				  //Calculate last remaining rows, 
				  if (ib>buffCount) //last buffer
				  {	// add last few rows
					  en = (ib * BUFFERSIZE) - BUFFERSIZE + remainingRows;
				  }


				  bound.SetCount(nValues); // nValues has been claculated above
				  bound.SetLowerBound(0);
				  pData = new CComSafeArray<double>(&bound, 1);
				  pTimeData = new CComSafeArray<double>(&bound, 1);

				  vData.parray = *pData->GetSafeArrayPtr();
				  vData.vt = VT_ARRAY;
				  pData->Detach();
				  vTimeData.parray = *pTimeData->GetSafeArrayPtr();
				  vTimeData.vt = VT_ARRAY;
				  pTimeData->Detach(); // do not lock before call
				  // Get the data from the time signal
				  m4.GetData(TRUE, st, en, &vTimeData, &nCounter);
				  // Get the data form the signal
				  m4.GetData(FALSE, st, en, &vData, &nCounter);
				  pData->Attach(vData.parray);
				  pTimeData->Attach(vTimeData.parray);
				  //double tData,dData;

				  // Access the data:
				  for (int i = st; i < en; i++)
				  {
					  //printf("    %.3lf,  %.3lf, ", pTimeData->GetAt(rowCount), pData->GetAt(rowCount));
					  r = 2 * cnt - 1;
					  r1 = 2 * cnt;
					  //data[0][r] = 0;
					  c_data[rnt][r] = pTimeData->GetAt(rnt);
					  c_data[rnt][r1] = pData->GetAt(rnt);
					  //printf("%.3lf,%.3lf", data[i][r],data[i][r1]);
					  rnt++;
				  }
				  cnt++;
				  rnt = 0;// this runs from 0 - 20 each time. fills data, then data dumps its content on screen.
				  


			  }
		  } //for

		  if (showMeta == 1)
		  {//just one iteration is enough to print, all headers.
			  return;
		  }


		  if (showMeta == 0)
		  {
			  if (head==1) {
				  for (size_t j = 0; j < colEnd - colStart; j++)
				  {
					  printf("%S,",Time[j]);
					  printf("%S,", Name[j]);
				  }
				  printf("\n");
				  for (size_t j = 0; j < colEnd - colStart; j++)
				  {
					  printf(" ,");
					  printf("%S,", Unit[j]);
				  }
				  printf("\n");
				  for (size_t j = 0; j < colEnd - colStart; j++)
				  {
					  printf(" ,");
					  printf("%S,", Comment[j]);
				  }
				  printf("\n");
				  head = 0;
			  }

			  if (ib > buffCount)
				  mxCount = remainingRows;//WRITE Last rows, which were left by buffer.
			  else
				  mxCount = BUFFERSIZE;

			  for (size_t i = 0; i < mxCount-1; i++)
			  {
				  for (size_t j = 1; j <= (colEnd - colStart) * 2; j++)
				  {
					  printf("%0.6lf,", c_data[i][j]);
				  }
				  printf("\n");
			  }
		  }
		  // free memory
		  delete pTimeData;
		  delete pData;
		  cnt = 1;
		  rnt = 0;
		  //fflush(stdout);

	  }// buff count for
		  

	}
	// Release the COM object and free memory
	try
	{
		////clean data array from memory
		//for (int i = 0; i < BUFFERSIZE; ++i) {
		//	delete[] data[i];
		//}
		//delete[] data;
		m4.ReleaseDispatch();
	}
	catch (const std::exception&)
	{
			
	}
	
}

