// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "..\\..\\..\\MDF4Reader.dll" no_namespace
// CMDF4Writer wrapper class

class CMDF4Writer : public COleDispatchDriver
{
public:
	CMDF4Writer(){} // Calls COleDispatchDriver default constructor
	CMDF4Writer(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMDF4Writer(const CMDF4Writer& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IMDF4Writer methods
public:
	void CreateMDF4(LPCTSTR strToolName, LPCTSTR strToolVendor, LPCTSTR strToolVersion, LPCTSTR strComment, long lVersion)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, strToolName, strToolVendor, strToolVersion, strComment, lVersion);
	}
	CString get_strPathName()
	{
		CString result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_strPathName(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void AddGroup(LPCTSTR strComment, long ExpNValues, long * iNo)
	{
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_PI4 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, strComment, ExpNValues, iNo);
	}
	void AddGroup64(LPCTSTR strComment, __int64 ExpNValues, long * iNo)
	{
		static BYTE parms[] = VTS_BSTR VTS_I8 VTS_PI4 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, strComment, ExpNValues, iNo);
	}
	void AddSignal(long iGroupNo, LPCTSTR strName, LPCTSTR strLabel, long lDataType, long lnFirstBit, long lnBits, LPCTSTR strUnit, double yFactor, double yOffset, long bHasNovalues, double Novalue, long invalPos, long * iNo)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_R8 VTS_R8 VTS_I4 VTS_R8 VTS_I4 VTS_PI4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, iGroupNo, strName, strLabel, lDataType, lnFirstBit, lnBits, strUnit, yFactor, yOffset, bHasNovalues, Novalue, invalPos, iNo);
	}
	void AddTimeInfo(long iGroupNo, LPCTSTR strName, LPCTSTR strUnit, double Factor, double Offset)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_BSTR VTS_R8 VTS_R8 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, iGroupNo, strName, strUnit, Factor, Offset);
	}
	void AddTimeSignal(long iGroupNo, LPCTSTR strName, long lDataType, long lnFirstBit, long lnBits, LPCTSTR strUnit, double Factor, double Offset, long * iNo)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_R8 VTS_R8 VTS_PI4 ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, iGroupNo, strName, lDataType, lnFirstBit, lnBits, strUnit, Factor, Offset, iNo);
	}
	void MakeGroups()
	{
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetSignalValue(long iGroupNo, long iSignalNo, double Value, long bIsNovalue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_R8 VTS_I4 ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, iGroupNo, iSignalNo, Value, bIsNovalue);
	}
	void WriteRecord(long iGroupNo)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, iGroupNo);
	}
	void FlushGroup(long iGroupNo)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, iGroupNo);
	}
	void Close()
	{
		InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void CreateSRBlock(long lGroupNo, double dt, double xrange, double OldXFactor, double OldXOffset)
	{
		static BYTE parms[] = VTS_I4 VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lGroupNo, dt, xrange, OldXFactor, OldXOffset);
	}
	void SetFileTime(__int64 FileTime)
	{
		static BYTE parms[] = VTS_I8 ;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileTime);
	}
	void CopyGroup(unsigned __int64 ulMDF4File, long lGroupNo, __int64 iTimeDiff)
	{
		static BYTE parms[] = VTS_UI8 VTS_I4 VTS_I8 ;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ulMDF4File, lGroupNo, iTimeDiff);
	}
	void GroupDescription(long iGroupNo, LPCTSTR strAcqName, LPCTSTR strCGComment, LPCTSTR strSIName, LPCTSTR strSIPath, LPCTSTR strSIComment)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms, iGroupNo, strAcqName, strCGComment, strSIName, strSIPath, strSIComment);
	}
	void SignalDescription(long iGroupNo, long iSignalNo, LPCTSTR strSIName, LPCTSTR strSIPath, LPCTSTR strSIComment)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms, iGroupNo, iSignalNo, strSIName, strSIPath, strSIComment);
	}
	long get_RecordSize(long lGroupID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, lGroupID);
		return result;
	}
	void SetRecord(long lGroupNo, unsigned char * pBuffer)
	{
		static BYTE parms[] = VTS_I4 VTS_PUI1 ;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lGroupNo, pBuffer);
	}
	void SetMinMax(long iGroupNo, long iSignalNo, double Min, double Max)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_R8 VTS_R8 ;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms, iGroupNo, iSignalNo, Min, Max);
	}
	long get_InvalidBytes(long lGroupID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, lGroupID);
		return result;
	}
	void FileDescription(LPCTSTR strHDComment, long lTimerQualityClass, __int64 start_time_ns, unsigned short tz_offset_min, unsigned short dst_offset_min, unsigned char time_flags)
	{
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I8 VTS_UI2 VTS_UI2 VTS_UI1 ;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, parms, strHDComment, lTimerQualityClass, start_time_ns, tz_offset_min, dst_offset_min, time_flags);
	}
	void SetSignalDiscrete(long iGroupNo, long iSignalNo, LONG bDiscrete, LPCTSTR strN2T)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BSTR;
		InvokeHelper(23, DISPATCH_METHOD, VT_EMPTY, NULL, parms, iGroupNo, iSignalNo, bDiscrete, strN2T);
	}

	// IMDF4Writer properties
public:

};
