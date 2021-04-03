// -- File: INI.CC

CLASS Ini(cIniFile)
/* -----------------------------------------------------------------------
    Description:
 
       CLASS Ini wraps GetPrivateProfileString and
       WritePrivateProfileString, the Windows API functions most commonly
       used to create, read, and write application-specific .INI files.
  
    Programmers:
 
       Keith Chuvala 
       Bowen Moursund
       Kenneth Chan 
 
    History:
 
       January 1996: Original publication in dBASE Advisor.
       08/13/1996:   Minor revisions and addition of GetSection, Flush,
                     DeleteSection, DeleteEntry, and supporting methods.
       12/11/1997:   Bowen Modified this to make it work for Visual dBASE
                     7, changing the API calls for the 32-bit API.

    Instantiation:
 
       set procedure to Ini.Cc additive
       oMyINI = new INI([cIniFile])
 
       Typical usage is to specify the full path to the .INI file via the
       cIniFile parameter. Examples:
 
           oMyIni = new Ini(set("directory")+"\MyApp.Ini")
           oMyIni = new Ini(home()+"MyApp.Ini")
           oMyIni = new Ini(_dbwinhome+"MyApp.Ini")
 
       The cIniFile parameter is optional. If cIniFile is not specified,
       the return of program() will be used as the file name. If the path
       is not specified, the VdB home() directory will be used. You may
       set the Inifile property directly to a name with no path if you
       wish to use the Windows home directory.

    Create/Write:
 
       oMyIni.SetValue(cSection,cEntry,cValue)
 
       If the .INI file does not exist, it will be created. The cSection
       section will be added to the .INI file if it does not exist. An
       entry in the form of Entry=Value will be added to the cSection
       section. Example:
 
           oMyIni.SetValue("Window","Top",str(form.Top))
 
    Read Entry:
 
       oMyIni.GetValue(cSection,cEntry)
 
       This method returns the value of the specified entry of the
       specified section as well as storing the value to the Value
       property of the Ini object. The return value will be blank
       if the entry is not found, the section does not exist, or
       if a problem occurs reading the .INI file, UNLESS you set
       the Default property. Example:
 
           oMyIni.Default = "1"
           oMyIni.GetValue("Window","Top")
 
    Read Section:
 
       oMyIni.GetSection(cSection)
 
       This method returns a reference to an array object containing all
       the entries of a section. Each element of the array will be in the
       form Entry=Value. The array reference will also be stored to the
       SectionArray property of the Ini object. The array will contain only
       a single element, a null string, if the section does not exist or if
       a problem occurs reading the .INI file.
 
    Parse Section Array:
 
       oMyIni.SectionArrayParse2Arrays([cDelimiter])
 
       This method parses the SectionArray array into two parallel arrays,
       one containing the Entries, the other the matching Values.
       References to the arrays are stored to the EntriesArray and
       ValuesArray properties of the Ini object. The method returns a
       reference to yet another array containing two elements: element 1 is
       a reference to the EntriesArray array, element 2 is a reference to
       the ValuesArray array. The array referenced by the return will be
       empty if the SectionArray array is empty.
 
       The cDelimiter parameter is optional. Some entries may have multiple
       Values, delimited by a certain character, usually the comma. If
       cDelimiter is specified and there actually are multiple Values
       delimited by the specified character, the ValuesArray array will be
       2 dimensional. The number of columns will be the maximum number of
       Values encountered for any single Entry.
 
    Delete Section:
 
       oIni.DeleteSection(cSection)
 
       This method deletes the specified section from the .INI file. It
       returns 0 if unsuccessful.
 
    Delete Entry:
 
       oIni.DeleteEntry(cSection,cEntry)
 
       This method deletes the specified entry of the specified section
       from the .INI file. It returns 0 if unsuccessful.
 
    Flush Updates:
 
       oIni.Flush()
 
       Flushes any updates to the .INI file to disk.
 
    New .INI file:
 
       oMyIni.SetIniFile(cIniFile)
 
       Notes are the same as for Instantiation, above.
 
    Release:
 
       oMyIni.Release()
 
	    Releases the Ini object.
 
    Properties:
 
       IniFile: File name of the .INI file
       Section: Last read/written section
       Entry: Last read/written entry
       Default: Default value for the GetValue method, normally blank
       SectionArray: Last read 1D array of Entries of a Section in the
                     form Entry=Value
       EntriesArray: Last parsed Entries from SectionArray
       ValuesArray: Last parsed Values from SectionArray

   Dependencies:
      STRINGEX // In dUFLP Library
      DUFLP.H  // also in this library
   --------------------------------------------------------------------- */
  class::Init() // initialize
	
  #define INI_RETSIZE 320
  #define INI_SECTION_RETSIZE 32000
  #ifndef NULL
      #define NULL 0
  #endif
  this.Section = ""
  this.Entry = ""
  this.Inifile = ""
  this.Value = ""
  this.Default = ""
  this.SectionArray = new array()
  this.SectionArray.add("")
  this.EntriesArray = new array()
  this.EntriesArray.add("")
  this.ValuesArray = new array()
  this.ValuesArray.add("")
  class::SetIniFile(cIniFile)

  if type("GetPrivateProfileString") <> "FP"
      extern CLONG GetPrivateProfileString( CSTRING,;
                                            CSTRING,;
                                            CSTRING,;
                                            CSTRING,;
                                            CLONG,;
                                            CSTRING ) ;
             kernel32 from "GetPrivateProfileStringA"
  endif
  if type("WritePrivateProfileString") <> "FP"
      extern CLOGICAL WritePrivateProfileString( CSTRING,;
                                                 CSTRING,;
                                                 CSTRING,;
                                                 CSTRING ) ;
             kernel32 from "WritePrivateProfileStringA"
  endif
	if type("GetPrivateProfileSection") <> "FP"
		extern CLONG GetPrivateProfileSection(CSTRING,;
                                            CPTR,;
                                            CLONG,;
														  CSTRING) ;
             kernel32 from "GetPrivateProfileSectionA"
	endif

  PROCEDURE Init
    // Initialize this class, setting up STRINGEX:
      PROTECT StringProc
//      if .not. SetProc( "STRINGEX.CC" )  //
         set procedure to stringex.cc additive
/*         this.StringProc = true   // 
      else
         this.StringProc = false
      endif
*/      this.String        = new stringex()  // 
      this.String.parent = this


   FUNCTION Release
      if this.StringProc
         close procedure stringex.cc
      endif
      release object this

   RETURN NULL
   // -- EoM: Release()

  PROCEDURE GetValue
     parameter cSection, cEntry
     local cBuffer, cDefault, cIniFile
     store space(INI_RETSIZE) to cBuffer, this.Value
     if type("cSection") == "C" .and. type("cEntry") == "C"
         this.Section = cSection
         this.Entry = cEntry
         cDefault = this.Default
         cIniFile = this.IniFile
         GetPrivateprofileString(cSection, cEntry, cDefault,;
                                 cBuffer, INI_RETSIZE, cIniFile)
         this.Value = trim(cBuffer)
     endif
  RETURN trim(this.Value)

  PROCEDURE SetValue
     parameter cSection, cEntry, cNewValue
     local lSuccess, cIniFile
     lSuccess = false
     if type("cSection") == "C" .and. type("cEntry") == "C" .and.;
        type("cNewValue") == "C"
         this.Section = cSection
         this.Entry = cEntry
         cIniFile = this.IniFile
         store ltrim(trim(cNewValue)) to cNewValue, this.Value
         lSuccess = WritePrivateProfileString(cSection, cEntry,;
                                             cNewValue, cIniFile)
     endif
  RETURN lSuccess

  PROCEDURE SetIniFile
     parameter cIniFile
     if type("cIniFile") <> "C" && no file name specified
         *-- use program name
         this.IniFile = left(program(),8)+".INI"
     else
         this.IniFile = ltrim(trim(cIniFile))
     endif
     if .not. ("\" $ this.IniFile)  && if no path specified
         *-- use VdB home directory
         this.IniFile = home() + this.IniFile
     endif
     if right(upper(this.IniFile),4) <> ".INI"
         *-- ensure correct extension
         local nPos
         nPos = at(".", this.IniFile)
         if nPos > 0
             this.IniFile = stuff(this.IniFile, nPos, 4, ".INI")
         else
             this.IniFile = this.IniFile + ".INI"
         endif
     endif

  PROCEDURE GetSection
     parameter cSection
     this.SectionArray = new array()
     if type("cSection") == "C"
         this.Section = cSection
         local nBytes, cBuffer, cIniFile, cDefault
         cBuffer = space(INI_SECTION_RETSIZE)
         cDefault = this.Default
         cIniFile = this.IniFile
         nBytes = GetPrivateProfileSection(cSection,;
                                           cBuffer,;
                                           INI_SECTION_RETSIZE,;
                                           cIniFile )
         if nBytes = 0
             this.SectionArray.add("")
         else
             local oStr, nLen, nEntry, nLastNull, nNextNull, nStart, nChars
             oStr = new StringEx()
             oStr.string = left(cBuffer, nBytes)
             oStr.SingleToDouble()
             cBuffer = trim(oStr.string)

             nLen = len(cBuffer)
             store 0 to nEntry, nLastNull, nNextNull, nStart, nChars
             do
                 nLastNull = nNextNull
                 nEntry++
                 nNextNull = at(chr(0), cBuffer, nEntry)
                 nStart = nLastNull+1
                 nChars = nNextNull-nLastNull-1
                 this.SectionArray.add(substr(cBuffer, nStart, nChars))
             until nNextNull >= nLen-1
         endif
     else
         this.SectionArray.add("")
     endif
  RETURN this.SectionArray

  PROCEDURE Flush
     local cIniFile
     cIniFile = this.IniFile
     WritePrivateProfileString(0, 0, 0, cIniFile)

  PROCEDURE DeleteEntry
     parameter cSection, cEntry
     local lSuccess, cIniFile
     cIniFile = this.IniFile
     lSuccess = false
     if type("cSection") == "C" .and. type("cEntry") == "C"
         lSuccess = WritePrivateProfileString(cSection, cEntry, 0, cIniFile)
     endif
  RETURN lSuccess

  PROCEDURE DeleteSection
     parameter cSection
     local lSuccess, cIniFile
     cIniFile = this.IniFile
     lSuccess = false
     if type("cSection") == "C"
         lSuccess = WritePrivateProfileString(cSection, 0, 0, cIniFile)
     endif
  RETURN lSuccess

  PROCEDURE SectionArrayParse2Arrays
     parameters cDelimiter
     local aArrays, aEntries, aValues, nRows, nCols, n, cString, nLen,;
           nPosition, nCol, cSubStr
     aArrays = new array()
     nRows= alen(this.SectionArray,1)
     if nRows > 0
         this.EntriesArray = new array()
         nCols = 1
         for n = 1 to nRows
             this.EntriesArray.add(left(this.SectionArray[n],;
                                   at("=",this.SectionArray[n])-1))
             if type("cDelimiter") = "C"
                 nCols = max(nCols, class::CharCount(cDelimiter,;
                             this.SectionArray[n]) + 1)
             endif
         endfor
         aArrays.add(this.EntriesArray)
         this.ValuesArray = new array(nRows, nCols)
         for n = 1 to nRows
             cString = substr(this.SectionArray[n],at("=",;
                              this.SectionArray[n])+1)
             if type("cDelimiter") = "C"
                 nLen = len(cString)
                 nPosition = 1
                 nCol = 1
                 do while nPosition < nLen .and. nCol <= nCols
                     cSubStr = substr(cString, nPosition)
                     if nCol < nCols
                         cSubStr = left(cSubStr, at(cDelimiter, cSubStr) - 1)
                     endif
                     nPosition = nPosition + len(cSubStr) + 1
                     this.ValuesArray[n,nCol] = cSubStr
                     nCol = nCol + 1
                 enddo
             else
                 this.ValuesArray[n,1] = cString
             endif
         endfor
         aArrays.add(this.ValuesArray)
     endif
  RETURN aArrays

  PROCEDURE Release
     release object this

  PROCEDURE CharCount(cChar, cStr)
     local cString, nCnt
     cString = cStr
     nCnt = 0
     do while cChar $ cString
         nCnt = nCnt + 1
         cString = substr( cString, at(cChar, cString)+1 )
     enddo
  RETURN nCnt

ENDCLASS
// - End of Class: INI

// #include <duflp.h>

/* ----------------------------------------------------------------
   End of File: INI.CC
   ---------------------------------------------------------------- */


