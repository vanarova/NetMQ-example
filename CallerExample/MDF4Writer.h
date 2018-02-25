// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\TL70\\MDF4\\MDF4Writer\\Debug\\MDF4Writer.dll" no_namespace
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
	void AddSignal(long iGroupNo, LPCTSTR strName, LPCTSTR strLabel, long lDataType, long lnBits, LPCTSTR strUnit, double yFactor, double yOffset, long bHasNovalues, double Novalue, long * iNo)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR VTS_R8 VTS_R8 VTS_I4 VTS_R8 VTS_PI4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, iGroupNo, strName, strLabel, lDataType, lnBits, strUnit, yFactor, yOffset, bHasNovalues, Novalue, iNo);
	}
	void AddTimeInfo(long iGroupNo, LPCTSTR strName, LPCTSTR strUnit, double Factor, double Offset)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_BSTR VTS_R8 VTS_R8 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, iGroupNo, strName, strUnit, Factor, Offset);
	}
	void AddTimeSignal(long iGroupNo, LPCTSTR strName, long lDataType, long lnBits, LPCTSTR strUnit, long * iNo)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR VTS_PI4 ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, iGroupNo, strName, lDataType, lnBits, strUnit, iNo);
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

	// IMDF4Writer properties
public:

};
