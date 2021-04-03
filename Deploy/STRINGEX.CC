// -- File: STRINGEX.CC

CLASS StringEx OF STRING() // extended 'string' class
/* ----------------------------------------------------------------------
   Description:
 
       This class contains many useful string-handling methods. 
 
   Programmers: 
 
       Ken Mayer
       Phil Steele
       Jay Parsons 
       Peter Stevens 
       Martin Leon
       Angus Scott-Fleming
       David G. Franknbach
       Richard Ozer
       Roland Bouchereau              
       Kelvin Smith
       Clinton L. Warren
       Sri Raju 
       Kenneth Chan
       David Kanter
       Bowen Moursund
       Peter Rorlick
       Bruce Beacham
 
    History: 
 
       12/27/1996 -- original version of these routines as a class.
       01/08/1998 -- Minor changes here and there ...
       August 9, 1999 - fix for ProperAdr() ...
       Sept. 27, 1999 -- added new methods StrTrans(), BreakString()
       Sept. 29, 1999 -- added code to load with string property ... 
                         see instantiation below
       Dec. 9, 1999 -- Added minor code fix to cutPaste() routine
                       provided by Bruce Beacham to scoping errors.
 
    Instantiation: 
 
       set procedure to stringex.cc additive
       _app.String = new StringEx()
       _app.String.string = "some string"
        
               OR
 
       set procedure to stringex.cc additive
       oMyString = new StringEx()
       oMyString.string = "some string"

               OR

       set procedure to stringex.cc additive
       oMyString = new StringEx("some string")

 
    Methods:
       More details on each of these is contained in the commentary for
       each method ... in many cases, if no string is passed as a 
       parameter, then the method will attempt to use the contents of
       the property "string" of this class. If this is empty, the
       method will return 'NULL'.
    
       Release()
         Releases this object (and others) from memory
 
       AllTrim()
         Trim left and right of string
 
       AtCount()
         Number of occurences of a string in another
  
       CutPaste()
         Replaces all occurances of a string in another
  
       Decode()
         De-code string encrypted with encode
 
       Encode()
         Simple encryption of a character string
 
       isAlNum()
         Checks first character of string to see if it is alphanumeric
 
       isASCII()
         Checks for first character of string -- is it ascii? (< 128)
 
       isCntrl()
         Checks if a character is a control character
  
       isDigit()
         Is first character of string a digit?
  
       isPrint()
         Is first character a printable character?
  
       isSpace()
         Is first character a space, tab, etc.?
 
       isState()
         Checks a two character string to see if it is one of the USA's
         50 states, or territories ...
 
       isTrueByte()
         Returns character byte # 0
 
       isTrueWord()
         Returns true if either of two characters # 0
  
       isUPCCode()
         Accepts a string containing a barcode number and returns true 
         if it is potentially a valid Universal Product Code number, 
         else false
 
       isValidCard()
         Same as above, but for credit-card numbers
 
       isXDigit()
         Checks to see if the first character of a string is a digit,
         includes hexidecimal ...
 
       Justify()
         Pad left, right, center with spaces, or specific character.
         (equivalent of FoxPro padr(), etc.)
  
       LastWord()
         Returns last word of string
 
       Name2Label()
         Returns a name held in five separate fields or memvars as it 
         should appear on a label of a given length in characters.
 
       ParseWord()
         Returns first word in string
  
       Plural()
         Returns string in plural form
 
       ProperAdr()
         Another smart proper() function, handles strings with numbers 
         better then others.
 
       StrComp()
         Compares two strings, returns numeric value ...
 
       Strip2Val()
         Removes characters from the left until finding a digit
 
       StripND()
         Strips non-digit characters from a string
 
       StripVal()
         Removes characters from left until non-numeric is found.
 
       StripWord()
         Removes first word of string
 
       StrpBrk()
         Search string for first occurrence of any of the characters in 
         charset
 
       StrRev()
         Reverse string of characters

       Truncate()
         Truncate this.string at first null

       SingleToDouble()
         Convert a single-byte this.string to a VdB double-byte string

       DoubleToSingle()
         Convert a VdB double-byte this.string to a single-byte string               

       StrTran()
         Clipper function translated to dBASE ... does
         a search and replace in a character string.

       BreakString()
         Breaks a character string into parts, with an
         optional separator character ...
 ---------------------------------------------------------------------- */

   // if instantiated with string in parens (s = new string("some string" ) )
   // assign it to the string property of this object:
   parameter cString
   if not empty( cString ) 
      this.string = cString
   endif

   FUNCTION Release
   /* -------------------------------------------------------------------
     Programmer..: Ken Mayer
     Date........: 11/24/1996
     Notes.......: Used to release this object from memory.
     Written for.: Visual dBASE 5.5
     Rev. History: 11/24/1996 -- Original Code
     Calls.......: none
     Usage.......: stringex.Release()
     Example.....: _app.String.Release()
                   _app.String = NULL   // not required, but a good 
                                        // idea
     Returns.....: Null
     Parameters..: None
   //----------------------------------------------------------------- */

      release object this

   RETURN NULL
   // EoM: Release()

   FUNCTION AllTrim( cString )
   /* -----------------------------------------------------------------
     Programmer..: Phil Steele
     Date........: 11/03/1996
     Notes.......: Complete trims edges of field (left and right)
     Written for.: dBASE IV, 1.1
     Rev. History: 05/23/1991 -- Original
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 Jay Parsons, 72662,1302 
                   11/03/1996 -- Modified to work with this class.
     Calls.......: None
     Usage.......: stringex.AllTrim(<cString>)
     Example.....: ? _app.String.AllTrim( "  Test String  ")
                           or
                   _app.String = new String()
                   _app.String.string = "  Test String  "
                   ? _app.String.AllTrim()
     Returns.....: Trimmed string, i.e.:"Test String"
     Parameters..: cString = string to be trimmed
    ------------------------------------------------------------------- */

      /* check to see if we need to use a parameter
         or "this.string": */
      if pCount() = 0 and not empty( this.string )
         cString = this.string
      elseif pcount() = 0 and empty( this.string )
         RETURN ""
      endif

   RETURN ( ltrim( trim( cString ) ) )
   // -- EoM: ALLTRIM

   FUNCTION AtCount( cFindStr, cString )
   /* -------------------------------------------------------------------
     Programmer..: Jay Parsons 
     Date........: 11/03/1996
     Notes.......: Get number of times a string occurs in another
     Written for.: dBASE IV
     Rev. History: 03/01/1992 -- Original Release
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 Jay Parsons
                   11/03/1996 -- Modified to work with this class.
     Calls.......: None
     Usage.......: stringex.AtCount( <cFindStr>, <cString> )
     Example.....: _app.String = new String()
                   _app.String.string ="This Test string has Test Data"
                   ? _app.String.AtCount( "Test" )
                       or
                   ? _app.String.AtCount( "Test","This Test string "+;
                                        "has Test Data")
     Returns.....: Numeric value
     Parameters..: cFindStr = string to find in cBigStr
                   cString  = string to look in
    ------------------------------------------------------------------- */
      
      local nCount, nLen

      // check to see if we need to use a parameter
      // or "this.string":
      if pCount() = 1 and not empty( this.string )
         cString = this.string
      elseif pcount() = 1 and empty( this.string )
         RETURN 0
      endif
      
      nCount = 0             // return -1 for empty cFindstr
      nLen = len( cString ) - len( cFindStr ) + 1
      if nLen > 0
         for nCount = 1 to nLen
            if at( cFindStr, cString, nCount ) = 0
               exit
            endif
         next
      endif
      
   RETURN nCount - 1
   // EoM: AtCount()

   FUNCTION CutPaste()
   /* 
     -----------------------------------------------------------------
     Programmer..: Martin Leon
     Date........: 11/05/1996
     Notes.......: Used to do a cut and paste within a field/
                   character string. (Taken from an issue of 
                   Technotes, can't remember which) This function 
                   will not allow you to overflow the field/char 
                   string -- i.e., if the Paste part of the function 
                   would cause the returned field to be longer than 
                   it started out, it will not perform the cut/paste 
                   (STUFF()). For example, if your field were 15 
                   characters, and you wanted to replace 5 of them 
                   with a 10 character string:
                          (CutPaste(field,"12345","1234567890"))
                   If this would cause the field returned to be 
                   longer than 15, the function will return the 
                   original field.
     Written for.: dBASE IV, 1.1
     Rev. History: Original function 12/17/1991
                   03/05/1992 -- minor change to TRIM(cFLD) in the 
                   early bits, solving a minor problem with phone 
                   numbers that Dave Creek (DCREEK) discovered.
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 Jay Parsons
                   11/05/1996 -- Modified to work with this class.
                   12/25/1996 -- Made parameters private instead of local
                                 to work with Type function
                   December, 1999 -- Minor fix based on above -- Bruce
                                 Beacham, addition of "IgnoreCase"
                                 parameter
     Calls.......: None
     Usage.......: stringex.CutPaste( <cFld>, <cLookFor>, <cRepWith>,;
                                      <lIgnoreCase> )
     Example.....: Replace all city with ;
                    _app.String.CutPaste( City, "L.A.", "Los Angeles" )
     Returns.....: Field with text replaced (or not, if no match 
                   found)
     Parameters..: cFld        = Field/Memvar/Expression to replace in 
                   cLookFor    = Item to look for (Cut)
                   cRepWith    = What to replace it with (Paste)
						 lIgnoreCase = if true, will ignore the case of the 
                                 string being looked for 
                                 (no IgnoreCase parameter = false) 
       ---------------------------------------------------------------- 
    */
      parameter cFld, cLookFor, cRepWith, lIgnoreCase
      local lMatched,nLookLen,nLen,nRepLen,cRetFld,nTrimLen,nCutAt

      // Make sure they're all character fields/strings
      if type("cFld")+type("cLookFor")+type("cRepWith") # "CCC"
         RETURN cFld
      endif
      
      lMatched = false
      nLookLen = len(cLookFor)  // length of field to look for
      nLen     = len(cFld)      // length of original field
      nRepLen  = len(cRepWith)  // length of field to replace with
      cRetFld  = trim(cFld)     // trim it ... (DCREEK's suggestion)
      
      // loop will allow a cut/paste to occur more than once in the 
      // field
      do while at(iif(lIgnoreCase, upper(cLookFor), cLookFor), ;
                  iif(lIgnoreCase, upper(cRetFld), cRetFld)) > 0
         lMatched = true
         cRetFld  = trim(cRetFld)
         nTrimLen = len(cRetFld)
         
         // the following IF statement prevents the replacement text
         // from overflowing the length of the original string ...
         if(nTrimLen - nLookLen) + nRepLen > nLen
            RETURN cRetFld
         endif
         
         // here we figure where to "cut" at
         nCutAt = at(iif(lIgnoreCase, upper(cLookFor), cLookFor), ;
                     iif(lIgnoreCase, upper(cRetFld), cRetFld))
         // let's do the paste ... (using dBASE STUFF() function)
         cRetFld = stuff(cRetFld,nCutAt,nLookLen,cRepWith)
      enddo
      
      if not lMatched  // no match with cLookFor, return original 
                         // field
         RETURN cFld
      endif
      
   RETURN cRetFld
   // EoM: CutPaste()

   FUNCTION Decode( cString )
   /* -------------------------------------------------------------------
     Programmer..: Angus Scott-Fleming 
     Date........: 11/05/1996
     Note........: Simple decoding for primitive password protection
     Written for.: dBASE IV 1.1+
     Rev. History: 11/25/1992 -- Original Release
                   08/02/1993 -- tuning for performance
                   04/25/1994 -- minor glitch fixed by Robert Johnson
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 Jay Parsons 
                   11/05/1996 -- Modified to work with this class.   
     Calls.......: None
     Usage.......: stringex.Decode(<cInput>)
     Example.....: Password = _app.String.Decode(cPassWd)
                         or
                   _app.String.string = "cPassWd"
                   Password = _app.String.Decode()
     Returns.....: decoded string
     Parameters..: cString = encoded string
    ------------------------------------------------------------------- */

      local cStr, n, cPw

      // check to see if we need to use a parameter
      // or "this.string":
      if pCount() = 0 and not empty( this.string )
         cString = this.string
      elseif pcount() = 0 and empty( this.string )
         RETURN ""
      endif
      
      cStr = cString
      if isblank(cStr)
         return cStr
      else
         cPw = cStr
         for n = 1 to len( trim( cStr ) )
         
            cStr = stuff( cStr, n, 1, ;
                    chr( asc( substr( cPw, n, 1 ) ) - n ) )
             
         endfor
      endif
      
   RETURN cStr
   // EoM: Decode()

   FUNCTION Encode( cString )
   /* -------------------------------------------------------------------
     Programmer..: Angus Scott-Fleming 
     Date........: 11/03/1996
     Note........: Simple encoding for primitive password protection
                   Source unknown; stolen from somewhere
     Written for.: dBASE IV 1.1+
     Rev. History: 11/25/1992 -- Original Release
                   08/02/1993 -- tuning for performance
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 Jay Parsons, 72662,1302
                   11/05/1996 -- Modified to work with this class.   
     Calls.......: None
     Usage.......: stringex.Encode(<cString>)
     Example.....: PassWord = _app.String.encode(cPassWd)
                        or
                   _app.String.string = cPassWd
                   PassWord =  _app.String.encode()
     Returns.....: encoded string
     Parameters..: cString = unencoded string
   ------------------------------------------------------------------- */
      
      local cStr, cPw, n
      
      // check to see if we need to use a parameter
      // or "this.string":
      if pCount() = 0 and not empty( this.string )
         cString = this.string
      elseif pcount() = 0 and empty( this.string )
         RETURN ""
      endif
      
      cStr = cString
      
      * encode the password
      cPw = cStr
      for n = 1 to len(trim(cStr))
          cStr = stuff( cStr, n, 1,;
                    chr( asc( substr( cPw, n, 1 ) ) + n ) )
      endfor
      
   RETURN cStr
   // EoM: Encode()

   FUNCTION IsAlNum( cString )
   /* ----------------------------------------------------------------------
     Programmer..: Jay Parsons 
     Date........: 11/05/1996
     Notes.......: Returns true if the first character of cChar is
                   alphanumeric, otherwise it is false.
     Written for.: dBASE IV
     Rev. History: 03/01/1992 -- Original Release
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 VERSIONS. Jay Parsons
                   11/05/1996 -- Modified to work with this class.   
     Calls.......: stringex.ISDIGIT
     Usage.......: stringex.isAlNum( <cChar> )
     Example.....: ? _app.String.isAlNum("Test")
                       or
                   _app.String.string = "Test"
                   ? _app.String.isAlNum()
     Returns.....: Logical
     Parameters..: cChar = character string to check for Alphanumeric
    -------------------------------------------------------------------- */

      // check to see if we need to use a parameter
      // or "this.string":
      if pCount() = 0 and not empty( this.string )
         cString = this.string
      elseif pcount() = 0 and empty( this.string )
         RETURN false
      endif

   RETURN ( isAlpha( cString ) .or. this.isDigit( cString ) )
   // EoM: IsAlNum()

   FUNCTION isASCII( cString )
   /* -------------------------------------------------------------------
     Programmer..: Jay Parsons 
     Date........: 03/01/1992
     Notes.......: Returns true if the first character of cChar is in 
                   the ASCII set ( asc() value < 128 )
     Written for.: dBASE IV
     Rev. History: 03/01/1992 -- Original Release
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 Jay Parsons
                   11/05/1996 -- Modified to work with this class.   
     Calls.......: None
     Usage.......: stringex.isASCII(<cString>)
     Example.....: ? _app.String.isASCII("Teststring")
                      or
                   _app.String.string = "Teststring"
                   ? _app.String.isASCII()
     Returns.....: Logical
     Parameters..: cChar = string to test
    ----------------------------------------------------------------- */

      // check to see if we need to use a parameter
      // or "this.string":
      if pCount() = 0 and not empty( this.string )
         cString = this.string
      elseif pCount() = 0 and empty( this.string )
         RETURN false
      endif

   RETURN ( asc(cString) < 128 )
   // EoM: isASCII()

   FUNCTION isCntrl( cString )
   /* -------------------------------------------------------------------
     Programmer..: Jay Parsons 
     Date........: 03/01/1992
     Notes.......: Returns true if the first character of cChar is a
                   delete or a control character.
     Written for.: dBASE IV
     Rev. History: 03/01/1992 -- Original Release
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 Jay Parsons
                   11/05/1996 -- Modified to work with this class.      
     Calls.......: None
     Called by...: Any
     Usage.......: stringex.isCntrl(<cString>)
     Example.....: ? _app.String.isCntrl("Test")
                        or
                   _app.String.string = "Test"
                   ? _app.String.isCntrl()
     Returns.....: Logical
     Parameters..: cChar = string to test
    ------------------------------------------------------------------- */

      if pCount() = 0 and not empty( this.string )
         cString = this.string
      elseif pcount() = 0 and empty( this.string )
         RETURN false
      endif

   RETURN ( asc(cString) = 127 .or. asc(cString) < 32 )
   // EoM: isCntrl()

   FUNCTION isDigit( cString )
   /* -------------------------------------------------------------------
     Programmer..: Jay Parsons
     Date........: 11/05/1996
     Notes.......: Test to see if first character of parm is a digit
     Written for.: dBASE IV
     Rev. History: 03/01/1992 -- Original Release
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 Jay Parsons
                   11/05/1996 -- Modified to work with this class.      
     Calls.......: None
     Usage.......: stringex.isDigit( <cString> )
     Example.....: ? _app.String.isDigit("123Test")
                        or
                   _app.String.string = "123Test"
                   ? _app.String.isDigit()
     Returns.....: Logical, true if first character is a digit
     Parameters..: cString = string to test
    ------------------------------------------------------------------- */

      if pCount() = 0 and not empty( this.string )
         cString = this.string
      elseif pcount() = 0 and empty( this.string )
         RETURN ""
      endif

   RETURN ( left( (cString) ,1) $ "0123456789" )
   // EoM: isDigit()
   
   FUNCTION isPrint( cString )
   /* -------------------------------------------------------------------
     Programmer..: Jay Parsons (CIS: 72662,1302)
     Date........: 11/05/1996
     Notes.......: Returns true if first character of cString is a 
                   printing character (space through chr(126) ).
     Written for.: dBASE IV
     Rev. History: 03/01/1992 -- Original Release
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 Jay Parsons, 72662,1302
                   11/05/1996 -- Modified to work with this class.
     Calls.......: None
     Usage.......: stringex.isPrint( <cString> )
     Example.....: ? _app.String.isPrint("Test")
                        or
                   _app.String.string = "Test"
                   ? _app.String.isPrint()
     Returns.....: Logical
     Parameters..: cString = string to test
    ------------------------------------------------------------------- */

      if pCount() = 0 and not empty( this.string )
         cString = this.string
      elseif pcount() = 0 and empty( this.string )
         RETURN ""
      endif

   RETURN ( asc(cString) > 31 ) // and asc(cString) < 127 )
   // EoM: isPrint()

   FUNCTION isSpace( cString )
   /* -------------------------------------------------------------------
     Programmer..: Jay Parsons
     Date........: 11/05/1996
     Notes.......: Returns true if first character of cString is in 
                   set of space, tab, carriage return, line feed, 
                   vertical tab or formfeed, otherwise false  Differs 
                   from C function of the same name in treating 
                   chr(141), used as carriage return in dBASE memo 
                   fields, as a space.
     Written for.: dBASE IV
     Rev. History: 03/01/1992 -- Original Release
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 Jay Parsons
                   11/05/1996 -- Modified to work with this class.      
     Calls.......: None
     Usage.......: stringex.isSpace(<cString>)
     Example.....: ? _app.String.isSpace(" Test")
                       or
                   _app.String.string = "Test"
                   ? _app.String.isSpace()
     Returns.....: Logical
     Parameters..: cString = string to test
    ------------------------------------------------------------------- */

      if pCount() = 0 and not empty( this.string )
         cString = this.string
      elseif pcount() = 0 and empty( this.string )
         RETURN false
      endif

   RETURN ( left((cString),1) $ " "+chr(9)+chr(10)+chr(11) ;
          + chr(12)+chr(13)+chr(141) )
   // EoM: isSpace()

   FUNCTION isState( cString )
   /* -------------------------------------------------------------------
     Programmer..: David G. Frankenbach
     Date........: 09/25/1994
     Notes.......: Validation of state codes -- used to ensure that a 
                   user doing data entry will enter the proper codes. 
                   Added a few US Territory codes as well (Puerto 
                   Rico, etc.)
     Written for.: dBASE IV, 1.1
     Rev. History: 12/02/1991
                   03/11/1992 -- Modified by Ken Mayer to handle
                   the extra US Territories, and to ensure that the 
                   data is at least temporarily in upper case when 
                   doing the check ...
                   04/22/1992 -- Modified by Jay Parsons to shorten
                   (simplify) the routine by removing the cSTATE2 
                   memvar.
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 Jay Parsons, 72662,1302
                   11/05/1996 -- Modified to work with this class.
     Calls.......: None
     Usage.......: stringex.isState(<cString>)
     Example.....: ? _app.String.isState( cState)
                       or
                   _app.String.string = cState
                   ? _app.String.isState()
     Returns.....: Logical (true if found, false otherwise)
     Parameters..: cString = state code to be checked ....
    ------------------------------------------------------------------- */

      // check to see if we need to use a parameter
      // or "this.string":
      if pCount() = 0 and not empty( this.string )
         cString = this.string
      elseif pcount() = 0 and empty( this.string )
         RETURN false
      endif

   RETURN ( upper(cString) $ "AL|AK|AZ|AR|CA|CO|CT|DE|DC|FL|" + ;
         "GA|HI|ID|IL|IN|IA|KS|KY|LA|ME|MD|MA|MI|MN|MS|MO|MT|NE|NV|"+ ;
         "NH|NJ|NM|NY|NC|ND|OH|OK|OR|PA|RI|SC|SD|TN|TX|UT|VT|VA|WA|"+ ;
         "WV|WI|WY|PR|AS|GU|CM|TT|VI|" and len(cString)=2 ;
         and not "|" $ (cString) )
   // EoM: isState()

   FUNCTION isTrueByte( cString, nPos ) 
   /* -------------------------------------------------------------------
     Programmer..: Jay Parsons 
     Date........: 11/06/1996
     Notes.......: Returns character cByte # 0 
     Written for.: dBASE 5.0 for Windows 
     Rev. History: 10/12/1994 -- Original Release 
                   11/06/1996 -- Modified to work with this class.
     Calls.......: None 
     Usage.......: stringex.isTrueByte( <cString>, <nPos> ) 
     Example.....: ? _app.String.isTrueByte( cMyString, 5 ) 
     Returns.....: true if chr() value is nonzero, or false 
     Parameters..: cString = the name of the character or string 
                   nPos    = the position of the byte within the 
                             string 
    ----------------------------------------------------------------- */

   RETURN ( asc( substr( (cString),(nPos),1 ) ) # 0 ) 
   // EoM: isTrueByte()

   FUNCTION isTrueWord( cString, nPos )
   /* -------------------------------------------------------------------
     Programmer..: Jay Parsons 
     Date........: 11/05/1996
     Notes.......: Returns true if either of two characters # 0 
     Written for.: dBASE 5.0 for Windows 
     Rev. History: 10/12/1994 -- Original Release 
                   11/06/1996 -- Modified to work with this class.
     Calls.......: stringex.isTrueByte() 
     Usage.......: isTrueWord( <cString>, <nPos> ) 
     Example.....: ? isTrueWord( cMyString, 5 ) 
     Returns.....: true if chr() value is nonzero, or false 
     Parameters..: cString = the name of the string 
                   nPos  = the position of the first byte within the 
                           string 
   ------------------------------------------------------------------- */

   RETURN ( CLASS::isTrueByte( (cString),(nPos) ) .OR. ;
            CLASS::isTrueByte( (cString), (nPos)+ 1 ) ) 
   // EoM: isTrueWord 
   
   FUNCTION isUPCCode( cString )
   /* -----------------------------------------------------------------
     Programmer..: Jay Parsons 
     Date........: 11/05/1996
     Notes.......: Accepts a string containing a barcode number and
                   returns true if it is potentially a valid 
                   Universal Product Code number, else false
                   Based on the comic strip "You Can", 10/02/1994,
                   by Jok Church, Internet jok@nbn.com, copyright
                   Universal Press Syndicate.
                   Internal spaces and hyphens are disregarded, but
                   the string must contain 12 digits in decoded 
                   order.
     Written for.: dBASE 5.0 for Windows
     Rev. History: 10/02/1994 -- original function.
                   11/05/1996 -- Modified to work with this class.
     Calls.......: stringex.alltrim()
                   stringex.isDigit()
     Usage.......: stringex.isUPCCode( <cString> )
     Example.....: ? _app.String.isUPCCode( "0-34000-31500-0" )
                        or
                   _app.String.string = "0-34000-31500-0"
                   ? _app.String.isUPCCode()
     Returns.....: true if code number is potentially valid, false if 
                       not.
     Parameters..: cString = string containing barcode number
    ------------------------------------------------------------------- */
      
      local lIsValid, nCheckSum, nMult, cC, nNext, cNext, nCount

      // check to see if we need to use a parameter
      // or "this.string":
      if pCount() = 0 and not empty( this.string )
         cString = this.string
      elseif pcount() = 0 and empty( this.string )
         RETURN ""
      endif
       
      lIsValid=false
      if pcount() = 0 .or. len( cString ) <= 11
         RETURN false
      endif
      store 0 to nCheckSum, nCount
      nMult=3
      
      ** process from right to left
      cC = CLASS::allTrim( cString )
      ** last character must be a digit
      if not CLASS::isDigit( right( cC, 1 ) )
         RETURN false
      endif
      ** last character is ignored in the loop
      for nNext = len( cC ) - 1 to 1 step -1
         cNext = substr( cC, nNext, 1 )
         if not CLASS::isDigit( cNext )
            if not cNext $ ' -'
               RETURN false
            endif
         else
            nCheckSum = nChecksum + val( cNext ) * nMult
            nMult = 4 - nMult
            nCount = nCount + 1
         endif
      endfor
      * see if the resulting checksum is equal to the last digit
      * checksum = the next greater multiple of 10, minus the current
      * checksum value
      nCheckSum = mod( 10 - mod( nCheckSum, 10 ), 10 )
      if nCount = 11 and nChecksum = val( right( cC, 1 ) )
         lIsValid=true
      endif
      
   RETURN lIsValid
   // EoM: isUPCCode()

   FUNCTION isValidCard( cString )
   /* -------------------------------------------------------------------
     Programmer..: Richard Ozer 
     Date........: 11/06/1996
     Notes.......: Accepts a string containing a credit card number 
                   and returns true if it is potentially a valid 
                   number, else false Based on a routine found in 
                   the Cobb group forum. Hyphens and spaces within 
                   the string are ignored, but the last nonspace 
                   character must be a digit. This function may be 
                   useful to organizations taking telephone orders 
                   to check that the digits of the cardnumber have 
                   been heard correctly. It does not, of course, 
                   provide any assurance that there is a credit
                   card of the number given, that the person giving 
                   the number is authorized to use the card, or that 
                   there is credit available on the card.
    
                   Donated to the library by Dominique Maniez, editor 
                   of the French publication "Point DBF" (.DBF).
     Written for.: dBASE 5.0 for DOS
     Rev. History: 09/28/1994 -- original function.
                   11/06/1996 -- Modified to work with this class.
     Calls.......: stringex.allTrim()
                   stringex.isDigit()
     Usage.......: stringex.isValidCard( <cString> )
     Example.....: ? _app.String.isValidCard( "4250-0100-9887-3615" )
                        or
                   _app.String.string = "4250-0100-9887-3615"
                   ? _app.String.isValidCard()
                   * note that sample above is an invalid number ... *
     Returns.....: true if card number is potentially valid, false if 
                   not.
     Parameters..: cString  = string containing credit card number
    ----------------------------------------------------------------- */
      
      local lIsValid, nCheckSum, nMult, cC, nNext, cNext, nDigit

      // check to see if we need to use a parameter
      // or "this.string":
      if pCount() = 0 and not empty( this.string )
         cString = this.string
      elseif pcount() = 0 and empty( this.string )
         RETURN false
      endif
      lIsValid=false
      * a one char string can inadvertently return a correct result
      if len( cString ) <= 1
         RETURN false
      endif
      nCheckSum=0  // start with 0 for checksum
      nMult=2
      
      ** process from right to left
      cC = CLASS::allTrim( cString )
      ** last character must be a digit
      if not CLASS::isDigit( right( cC, 1 ) )
         RETURN false
      endif
      ** last character is ignored in the loop
      for nNext = len( cC ) - 1 to 1 step -1
         cNext = substr( cC, nNext, 1 )
         if not CLASS::isDigit( cNext )
            if not cNext $ ' -'
               RETURN false
            endif
         else
            nDigit = val( cNext ) * nMult
            if nDigit > 9
               nDigit = int( nDigit / 10 ) + mod( nDigit, 10 )
            endif
            nCheckSum = nCheckSum + nDigit
            nMult = 3 - nMult
         endif
      endfor
      *  see if the resulting checksum is equal to the last digit
      * checksum = the next greater multiple of 10, minus the current
      * checksum value
      nCheckSum = mod( 10 - mod( nCheckSum, 10 ), 10 )
      if nChecksum = val(right( cC, 1 ) )
         lIsValid=true
      endif
      
   RETURN lIsValid
   // EoM: isValidCard()

   FUNCTION isXDigit( cString )
   /* -------------------------------------------------------------------
     Programmer..: Jay Parsons 
     Date........: 11/06/1996
     Notes.......: Returns true if first character of cChar is a 
                   possible hexadecimal digit.
     Written for.: dBASE IV
     Rev. History: 03/01/1992 -- Original Release
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 Jay Parsons
                   11/06/1996 -- Modified to work with this class.
     Calls.......: None
     Usage.......: stringex.isXDigit(<cString>)
     Example.....: ? _app.String.isXDigit("F000")
                        or
                   _app.String.string = "F000"
                   ? _app.String.isXDigit()
     Returns.....: Logical
     Parameters..: cChar = string to test
    ------------------------------------------------------------------- */

      // check to see if we need to use a parameter
      // or "this.string":
      if pCount() = 0 and not empty( this.string )
         cString = this.string
      elseif pcount() = 0 and empty( this.string )
         RETURN false
      endif

   RETURN ( left((cString),1) $ "0123456789ABCDEFabcdef" )
   // EoM: isXDigit()

   FUNCTION Justify( cFld, nLength, cType, cPadChar )
   /* -------------------------------------------------------------------
     Programmer..: Roland Bouchereau
     Date........: 11/06/1996
     Notes.......: Used to pad a field/string on the right, left or 
                   both, justifying or centering it within the length
                   specified. If the length of the string passed is 
                   greater than the size needed, the function will 
                   truncate it. Taken from Technotes, June 1990. 
                   Defaults to Left Justify if invalid TYPE is passed
    
                   This function now incorporates Ken Mayer's Dots()
                   function from the DOS libraries, adding a fourth
                   parameter. This makes it more-or-less equivalent 
                   to the F*xPr* functions PadR, PadL, and PadC ...
    
     Written for.: dBASE IV, 1.0
     Rev. History: Original function 06/15/1991
                   12/17/1991 -- Modified into ONE function from 
                      three by Ken Mayer, added a third parameter to
                      handle that.
                   12/23/1992 -- Modified by Joey Carroll to use 
                      STUFF() instead of TRANSFORM().
                   03/24/1993 -- Modified by Lee Hite, as the center
                      option wasn't working quite right ...
                   09/25/1994 -- Jay Parsons, changed to call 
                                 center(), incorporate Dots() 
                                 functionality with fourth parameter 
                                 and restore truncation.
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 Jay Parsons, 72662,1302
                   11/06/1996 -- Modified to work with this class.
     Calls.......: None
     Usage.......: stringEx.Justify(<cFld>[,<nLength>[,<cType>;
                                    [,<cPadChar>]]])
     Example.....: ?? _app.string.Justify(Address,25,"R",".")
     Returns.....: Padded/truncated field
     Parameters..: cFld    =  Field/Memvar/Character String to 
                              justify
                   nLength =  Width to justify within, default 80
                   cType   =  Type of justification: L=Left, 
                                  C=Center, R=Right, default Left
                   cPadChar=  Character to pad with, default space
    ------------------------------------------------------------------- */
      
      local cPad, cJust, nLen, nPad, cReturn
      
      cPad  = iif( pcount() > 3 and len( cPadChar ) > 0, ;
                  left( cPadChar, 1 ), " " )
      cJust = iif( pcount() > 2 and len( cType ) > 0, ;
                   upper( left( cType, 1 ) ), "L" )
      nLen  = iif( pcount() > 1, nLength, 80 )
      nPad  = nLen - len( cFld )
      
      do case
         case cJust = "C" .or. nPad <= 0   // Center or truncate
              cReturn = center( cFld, nLen, cPad )
         case cJust = "L"  // Left -- add trailing chars to field
              cReturn = cFld + replicate( cPad, nPad )
         case cJust = "R"  // Right -- add leading chars to field
              cReturn = replicate( cPad, nPad ) + cFld
         otherwise            // invalid parameter ... return nothing
              cReturn = ""
      endcase
      
   RETURN cReturn
   // EoM: Justify()

   FUNCTION LastWord( cString )
   /* -------------------------------------------------------------------
     Programmer..: Martin Leon
     Date........: 11/06/1996
     Notes.......: Returns the last word in a character string.
     Written for.: dBASE IV, 1.1
     Rev. History: 12/19/1991 -- Original
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 Jay Parsons
                   11/06/1996 -- Modified to work with this class.   
     Calls.......: None
     Usage.......: stringex.LastWord(<cString>)
     Example.....: ? _app.String.LastWord("This is a test string")
                         or
                   _app.String.string = "This is a test string"
                   ? _app.String.LastWord()
     Returns.....: the portion following the last space, i.e."string"
     Parameters..: cString = string to be searched 
    ----------------------------------------------------------------- */

      // check to see if we need to use a parameter
      // or "this.string":
      if pCount() = 0 and not empty( this.string )
         cString = this.string
      elseif pcount() = 0 and empty( this.string )
         RETURN ""
      endif

   RETURN ( substr( (cString), rat( " ", trim(cString) ) + 1 ) )
   // EoM: LastWord()

   FUNCTION Name2Label( nLength, cPrefix, cFirstname, cMidName, ;
                        cLastName, cSuffix )
   /* -------------------------------------------------------------------
     Programmer..: Jay Parsons 
     Date........: 03/01/1992
     Notes.......: Returns a name held in five separate fields or
                   memvars as it should appear on a label of a given
                   length in characters. The order of abbreviating is
                   somewhat arbitrary--you may prefer to remove the
                   suffix before the prefix, or to remove both before
                   abbreviating the first name.  This can be
                   accomplished by rearranging the CASE statements,
                   which operate in the order of their appearance.
     Written for.: dBASE IV
     Rev. History: 03/01/1992 -- Original Release
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 Jay Parsons
                   11/06/1996 -- Modified to work with this class.
     Calls.......: stringex.allTrim()
     Usage.......: stringex.Name2Label(<nLength>,<cPrefix>,;
                                     <cFirstName>,<cMidName>,;
                                     <cLastName>,<cSuffix>)
     Example.....: ? _app.String.Name2Label(20,"The Rev.","Elmore",;
                                         "Norbert","Smedley","III")
     Returns.....: Character String,in this case "E. N. Smedley, III"
     Parameters..: nLength    = length of label
                   cPrefix    = Prefix to name, such as Mr., Ms., Dr.
                   cFirstName = self explanatory
                   cMidName   = self explanatory
                   cLastName  = self explanatory
                   cSuffix    = "Jr.", "M.D.", "PhD", etc.
   ------------------------------------------------------------------- */
      
      local cTrypref, cTryfirst, cTrymid, cTrylast, cTrysuff, cTryname
      
      cTrypref  = CLASS::allTrim( cPrefix )
      cTryfirst = CLASS::allTrim( cFirstname ) 
      cTrymid   = CLASS::allTrim( cMidname ) 
      cTrylast  = CLASS::allTrim( cLastname ) 
      cTrysuff  = CLASS::allTrim( cSuffix ) 
      do while true
         cTryname = cTrylast
         if "" # cTrymid
            cTryname = cTrymid + " " + cTryname
         endif
         if "" # cTryfirst
            cTryname = cTryfirst + " " + cTryname
         endif
         if "" # cTrypref
            cTryname = cTrypref + " " + cTryname
         endif
         if "" # cTrysuff
            cTryname = cTryname + ", " + cTrysuff
         endif
         if len(cTryname) <= nLength
            exit
         endif
         do case
            case "" # cTrymid and right( cTrymid, 1 ) # "."
                 // convert middle name to initial
                 cTrymid = left( cTrymid, 1 ) + "."
            case "" # cTryfirst and right( cTryfirst, 1 ) # "."
                 // convert first name to initial
                 cTryfirst = left( cTryfirst, 1 ) + "."
            case "" # cTrypref
                 cTrypref = ""    // drop prefix
            case "" # cTrysuff
                 cTrysuff = ""    // drop suffix
            case "" # cTrymid
                 cTrymid = ""     // drop middle initial
            case "" # cTryfirst
                 cTryfirst = ""   // drop first initial
            otherwise
                 // truncate last name
                 cTrylast = left( cTrylast, nLength )
         endcase
      enddo

   RETURN cTryName
   // EoM: Name2Label()

   FUNCTION ParseWord( cString, cSeparator )
   /* -------------------------------------------------------------------
     Programmer..: Jay Parsons 
     Date........: 11/07/1996
     Notes.......: returns the first word of a string
     Written for.: dBASE IV, 1.1, 1.5
     Rev. History: 04/26/1992 -- Original Release
                   07/18/1993 -- Angus Scott-Fleming, add optional
                                 separator
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 Jay Parsons
                   11/07/1996 -- Modified to work with this class.
                   12/25/1996 -- Made parameters private instead of local
                                 to work with Type function
     Calls       : None
     Usage.......: ? stringex.ParseWord(<cString>,[<cSeparator>])
     Example.....: Command = _app.String.ParseWord( cProgramline )
     Returns.....: That portion, trimmed on both ends, of the passed 
                   string that includes the characters up to the 
                   first interior word-separator.
     Parameters..: cString    = character string to be stripped.
                   cSeparator = optional separating character 
                                (default is " ")
    ------------------------------------------------------------------- */

      local cW
      
      if not( type( "cSeparator" ) = "C" and len(cSeparator) = 1 )
         cSeparator = " "
      endif
      cW = trim( ltrim( cString ) )
      
   RETURN iif( cSeparator $ cW, ;
          rtrim(left( cW, at( cSeparator, cW ) - 1 )), cW )
   // EoM: ParseWord()

   FUNCTION Plural( nCnt, cNoun )
   /* -------------------------------------------------------------------
     Programmer..: Kelvin Smith 
     Date........: 11/07/1996
     Notes.......: Returns number in string form, and pluralized 
                   form of noun, including converting "y" to "ies", 
                   unless the "y" is preceded by a vowel.  Works with
                   either upper or lower case nouns (based on last 
                   character).

                   As no doubt all are aware, English includes many
                   irregular plural forms; to trap for all is not 
                   worthwhile (how often do you really need to print
                   out die/dice?). This should handle the vast 
                   majority of needs.
     Written for.: dBASE IV, 1.5
     Rev. History: 08/27/1992 1.0 - Original version
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 Jay Parsons
                   11/07/1996 -- Modified to work with this class.   
     Calls.......: None
     Usage.......: stringex.Plural(<nCnt>, <cNoun>)
     Examples....: _app.String.Plural(1, "flag")    returns "1 flag"
                   _app.String.Plural(0, "store")   returns "0 stores"
                   _app.String.Plural(5, "COMPANY") returns 
                                                      "5 COMPANIES"
     Returns.....: String with number and noun, no trailing spaces
     Parameters..: nCnt  = Count value for noun (how many of cNoun?)
                   cNoun = Noun to pluralize
    ------------------------------------------------------------------- */
       
      local cNounOut, cLast, c2Last, cLast2, lUpper
      
      cNounOut = trim(cNoun)
      if nCnt # 1
         cLast = right(cNounOut, 1)
         lUpper = isupper(cLast)         // Upper case?
         cLast = upper(cLast)
         c2Last = upper(substr(cNounOut, len(cNounOut) - 1, 1))
         cLast2 = c2Last + cLast
         
         * If the noun ends in "Y", normally we change "Y" to "IES".
         * However, if the "Y" is preceded by a vowel, just add "S".
         if cLast = "Y" and at(c2Last, "AEIOU") = 0
            cNounOut = left(cNounOut, len(cNounOut) - 1) +;
                       iif(lUpper, "IES", "ies")
         else
            if cLast = "S" .or. cLast = "X" ;
                           .or. cLast2 = "CH" .or. cLast2 = "SH"
               cNounOut = cNounOut + iif(lUpper, "ES", "es")
            else
               cNounOut = cNounOut + iif(lUpper, "S", "s")
            endif
         endif
      endif
      
   RETURN ltrim(str(nCnt)) + " " + cNounOut
   // EoM: Plural()

   FUNCTION ProperAdr( cString )
   /* -----------------------------------------------------------------
     Programmer..: Kelvin Smith & Clinton L. Warren 
     Date........: 11/07/1996
     Notes.......: Returns cBaseStr converted to proper case.  
                   Converts "Mc", "Mac", and "'s" as special cases.  
                   Inspired by A-T's CCB Proper function.  cBaseStr 
                   isn't modified.
                     dBASE for Windows includes a Proper() function.
                   This function, however, handles addresses better,
                   capitalizing letters following digits (such as
                   apartment numbers or directionals).
     Written for.: dBASE IV, 1.1
     Rev. History: 07/10/1991 1.0 - Original version (CLW)
                   10/18/1994 1.1 - Capitalize letters after digits 
                                    (KS)
                   11/07/1996 -- Modified to work with this class.
                   August 9, 1999 -- fix for 'S' handling ...
     Calls.......: None
     Usage.......: stringex.ProperAdr(<cString>)
     Examples....: _app.String.ProperAdr("mcdonald's") 
                                          returns "McDonald's"
                   _app.String.ProperAdr("17c hope st., #6d") 
                                          returns "17C Hope St., #6D"
                      or
                   _app.String.string = "Some value"
                   ? _app.String.ProperAdr()
     Returns.....: Propertized string (e.g. "Test String")
     Parameters..: cString = String to be propertized
    ----------------------------------------------------------------- */
      
      local nPos, cDeli, cWrkStr, cWrkChar

      // check to see if we need to use a parameter
      // or "this.string":
      if pCount() = 0 and not empty( this.string )
         cString = this.string
      elseif pcount() = 0 and empty( this.string )
         RETURN ""
      endif
       
      cWrkStr = lower(cString) + ' ' // space necessary for 's process
      
      nPos = at('mc', cWrkStr)        // "Mc" handling
      do while nPos # 0
         cWrkStr = stuff(cWrkStr, nPos, 3, ;
            upper(substr(cWrkStr, nPos, 1)) ;
            + lower(substr(cWrkStr, nPos + 1, 1)) ;
            + upper(substr(cWrkStr, nPos + 2, 1)))
         nPos = at('mc', cWrkStr)
      enddo
      
      nPos = at('mac', cWrkStr)       // "Mac" handling
      do while nPos # 0
         cWrkStr = stuff(cWrkStr, nPos, 4, ;
               upper(substr(cWrkStr, nPos, 1)) ;
               + lower(substr(cWrkStr, nPos + 1, 2)) ;
               + upper(substr(cWrkStr, nPos + 3, 1)))
         nPos = at('mac', cWrkStr)
      enddo
      
      cWrkStr = stuff(cWrkStr, 1, 1, upper(substr(cWrkStr, 1, 1)))
      nPos = 2
      cDeli = [ -.'"\/`]              // standard delimiters
      
      do while nPos <= len(cWrkStr)   // 'routine' processing
         if substr(cWrkStr,nPos-1,1) $ cDeli
            cWrkStr = stuff(cWrkStr, nPos, 1,;
                      upper(substr(cWrkStr,nPos,1)))
         endif
         if substr(cWrkStr,nPos-1,1) $ "0123456789"
            do while nPos <= len(cWrkStr)
               cWrkChar = substr(cWrkStr,nPos,1) 
               if cWrkChar $ "0123456789" // Digit
                  nPos = nPos + 1
                  loop
               endif
               if isalpha(cWrkChar)   // Alpha after digit--capitalize
                  cWrkStr = stuff(cWrkStr, nPos, 1, upper(cWrkChar))
                  nPos = nPos + 1
                  loop
               else
                  exit                 // Nonalphanumeric
               endif
            enddo
         endif
         nPos = nPos + 1
      enddo
      
      nPos = at("'S ", cWrkStr)           // 's processing
      do while nPos # 0
         cWrkStr = stuff(cWrkStr, nPos, 2, ;
                   lower(substr(cWrkStr, nPos, 2)))
         nPos = at('S', cWrkStr)
      enddo
      
   RETURN (cWrkStr)
   // EoM: ProperAdr()

   FUNCTION StrComp( cStr1, cStr2 )
   /* -------------------------------------------------------------------
     Programmer..: Sri Raju 
     Date........: 11/07/1996
     Notes.......: From Technotes, August, 1992, "Strings and Things"
                   This function compares the contents of two strings
                   If cStr1 is less than cStr2, return -1
                   If cStr1 is equal to  cStr2, return 0
                   If cStr1 is greater than cStr2, return 1
     Written for.: dBASE IV, 1.5
     Rev. History: 08/01/1992 -- Original Release
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 Jay Parsons
                   11/07/1996 -- Modified to work with this class.   
     Calls.......: None
     Usage.......: stringex.StrComp(<cStr1>,<cStr2>)
     Example.....: ? _app.String.StrComp("TEST","TEXT")
     Returns.....: Numeric (see notes)
     Parameters..: cStr1 = First string
                   cStr2 = Second string
   ------------------------------------------------------------------- */
      
      local cExact
      
      cExact = set("EXACT")
      set exact on
      
      do case
         case cStr1 = cStr2
              nReturn = 0
         case cStr1 > cStr2
              nReturn = 1
         case cStr1 < cStr2
              nReturn = -1
      endcase
      
      if cExact = "OFF"
         set exact off
      endif
      
   RETURN nReturn
   // EoM: StrComp()

   FUNCTION Strip2Val( cStr )
   /* -------------------------------------------------------------------
     Programmer..: Jay Parsons 
     Date........: 11/07/1996
     Notes.......: Strip characters from the left of a string until
                   reaching one that might start a number.
     Written for.: dBASE IV
     Rev. History: 03/01/1992 -- Original Release
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 Jay Parsons
                   11/07/1996 -- Modified to work with this class.
     Calls.......: None
     Usage.......: Strip2Val( <cStr> )
     Example.....: ? Strip2Val("Test345")
     Returns.....: character string
     Parameters..: cStr = string to search
    ----------------------------------------------------------------- */

      local nX
      
      for nX = 1 to len( cStr )
         if substr( cStr, nX, 1 ) $ "-.0123456789"
            exit
         endif
      endfor
      
   RETURN substr( cStr, nX )
   // EoM: Strip2Val()

   FUNCTION StripND( cNumArg )
   /* -------------------------------------------------------------------
     Programmer..: Ken Mayer 
     Date........: 11/07/1996
     Notes.......: Strips nondigits out of a numeric character 
                   string (like perhaps, a date: 01/04/93 would 
                   become 010493)
     Written for.: dBASE IV, 1.5
     Rev. History: 01/04/1993 -- Original Release
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 Jay Parsons
                   11/07/1996 -- Modified to work with this class.   
                   12/25/1996 -- Minor modifications
     Calls.......: stringex.isDigit()
     Usage.......: stringex.StripND(<cNumArg>)
     Example.....: ? _app.String.StripND(dtoc(date()))
     Returns.....: character string
     Parameters..: cNumArg = Character memvar containing a "numeric"
                             string
    ------------------------------------------------------------------- */
      
      local cRetVal, nCount, cChar
      
      cRetVal = ""
      for nCount = 1 to len( cNumArg )
         cChar = substr(cNumArg,nCount,1)
         if CLASS::ISDIGIT(cChar)
            cRetVal = cRetVal+cChar
         endif
      endfor
      
   RETURN cRetVal
   // EoM: StripND()

   FUNCTION StripVal( cStr )
   /* -----------------------------------------------------------------
     Programmer..: Jay Parsons 
     Date........: 11/07/1996
     Notes.......: Strip characters from the left of the string until
                   reaching one that is not part of a number.  A 
                   hyphen following numerics, or a second period,
                   is treated as not part of a number.
     Written for.: dBASE IV
     Rev. History: 03/01/1992 -- Original Release
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 Jay Parsons
                   11/07/1996 -- Modified to work with this class.
                   12/25/1996 -- Modified case statement
     Calls.......: None
     Usage.......: stringex.StripVal( <cStr> )
     Example.....: ? _app.String.StripVal("123.2Test")
     Returns.....: Character
     Parameters..: cStr = string to test
    ----------------------------------------------------------------- */
      
      private nX, cChar, lGotminus, lGotdot
      
      store false to lGotminus, lGotdot
      for nX = 1 to len( cStr )
         cChar = substr( cStr, nX, 1 )
         do case
            case not cChar $ "-.0123456789"
                 exit
            case cChar = "-"
                 if lGotminus
                    exit
                 else			//
                    lGotMinus = true	//
                 endif
            case cChar = "."
                 if lGotdot
                    exit
                 else
                    lGotdot = true
                 endif
            otherwise		//
              lGotMinus = false   //
              lGotDot = false	//
         endcase
         *lGotminus = true	//
      endfor
      
      cReturn = iif( nX > len( cStr ), "", substr( cStr, nX ) )
      
   RETURN cReturn
   // EoM: StripVal()
 
   FUNCTION StripWord( cString, cSeparator )
   /* -----------------------------------------------------------------
     Programmer..: Jay Parsons
     Date........: 11/07/1996
     Notes.......: discards first word of a string
     Written for.: dBASE IV, 1.1, 1.5
     Rev. History: 04/26/1992 -- Original Release
                   07/18/1993 -- Angus Scott-Fleming, add optional
                                 separator
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 Jay Parsons
                   11/07/1996 -- Modified to work with this class.
                   12/25/1996 -- Made parameters private instead of local
                                 to work with Type function
     Calls.......: None
     Usage.......: stringex.StripWord(<cString>,[<cSeparator>])
     Examples....: Lastname = _app.String.StripWord( "Carrie Nation" )
                             (returns "Nation")
                   InputData = ;
                     _app.String.StripWord( "RICHARD;HUGHES;AR;AN",";")
                             (returns "HUGHES;AR;AN" )
     Returns.....: string trimmed of trailing spaces, and trimmed on 
                   the left to remove leading spaces, with the first 
                   "word" removed. A "word" is defined as all 
                   characters up to the first space, or up to the 
                   first occurrence of the specified separator 
                   character. If the separator is not in the string,
                   routine returns an empty string instead.
     Parameters..: cString    = character string to be stripped.
                   cSeparator = optional separating character 
                                (default is " ")
    ------------------------------------------------------------------- */
      local cW
      
      if not(type("cSeparator") = "C" and len(cSeparator)=1)
         cSeparator = " "
      endif
      cW = trim( ltrim( cString ) )
      
   RETURN iif( cSeparator $ cW, ;
          ltrim(substr(cW, at( cSeparator, cW ) + 1)), "" )
   // EoM: StripWord()

   FUNCTION StrpBrk( cCharSet, cBigString )
   /* -------------------------------------------------------------------
     Programmer..: Jay Parsons 
     Date........: 11/07/1997
     Notes.......: Search string for first occurrence of any of the
                   characters in charset.  Returns its position as
                   with at().  Contrary to ANSI.C definition, returns
                   0 if none of characters is found.
     Written for.: dBASE IV
     Rev. History: 03/01/1992 -- Original version
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 Jay Parsons
                   11/07/1996 -- Modified to work with this class.
     Calls.......: None
     Usage.......: stringex.StrpBrk( <cCharSet>, <cBigString> )
     Example.....: ? _app.String.StrpBrk("Test",;
                                   "This Test string has Test data")
     Returns.....: Numeric value
     Parameters..: cCharSet = characters to look for in cBigStr
                   cBigStr  = string to look in
    ------------------------------------------------------------------- */
      
      local nPos
      
      for nPos = 1 to len( cBigString )
         if substr( cBigString, nPos, 1 ) $ cCharset
            exit
         endif
      endfor
      
   RETURN iif( nPos > len( cBigString ), 0, nPos)
   // EoM: StrpBrk()

   FUNCTION StrRev( cString )
   /* -------------------------------------------------------------------
     Programmer..: Jay Parsons
     Date........: 09/24/1994
     Notes.......: Reverses a string of characters
     Written for.: dBASE IV
     Rev. History: 03/01/1992 -- Original Release
                   Fall, 1994 -- revised for dBASE 5.0 for Windows.
                                 Jay Parsons
                   11/07/1996 -- Modified to work with this class.
                   12/25/1996 -- Modified by David Kanter to 
                                 simplify and speed up the code.
     Calls.......: None
     Usage.......: stringex.StrRev( <cString> )
     Example.....: ? _app.String.StrRev("This is a Test")
                          or
                   _app.String.string = "This is a test"
                   ? _app.String.StrRev()
     Returns.....: Character string, reversed from original input
     Parameters..: cString = String of characters to reverse ...
    ------------------------------------------------------------------- */
      
      local cRevstring, nX, nY

      // check to see if we need to use a parameter
      // or "this.string":
      if pCount() = 0 and not empty( this.string )
         cString = this.string
      elseif pcount() = 0 and empty( this.string )
         RETURN ""
      endif
      
      nX = len( cString )
      *Revstring = space( nX )
      *for nY = 1 to nX
      *  cRevstring = stuff( cRevstring, nY, 1, ;
                          substr( cString, nX - nY + 1, 1 ) )
      *endfor
      cRevString = ""
      for x = nX to 1 step -1
         cRevString = cRevString + substr( cString, x, 1 )
      next   
      
   RETURN cRevstring
   // EoM: StrRev()

   // ----------------------------------------
   // Bowen's additions, originally in INI.CC:
   // ----------------------------------------
   FUNCTION Truncate
      // Programmer: Bowen Moursund 
      // Date......: 11/22/1997
      // Truncate this.string at first null
      local nPos
      nPos = at(chr(0), this.string)
      if nPos > 0
         this.string = this.left(nPos-1)
	   endif
   return this.string

   FUNCTION SingleToDouble
      // Programmer: Bowen Moursund 
      // Date......: 11/22/1997
      // Convert a single-byte this.string to a VdB double-byte string
      local oStr, n
      oStr = new string()
      oStr.string = space(this.length*2)
      for n = 0 to this.length
          oStr.setByte(n*2, this.getByte(n))
      next n
      this.string = oStr.string
   return this.string

   FUNCTION DoubleToSingle
      // Programmer: Bowen Moursund)
      // Date......: 11/22/1997
      // Convert a VdB double-byte this.string to a single-byte string
      local oStr, n
      oStr = new string()
      oStr.string = space(ceiling(this.length/2))
      for n = 0 to (this.length*2-2) step 2
          oStr.setByte(n/2, this.getByte(n))
      next n
      this.string = oStr.string
   return this.string

   // --------------------------------------------------------------
   // Other additions:
   // --------------------------------------------------------------
   // new version of this by Gary ... posted in newsgroups, 10/8/99
   function StrTran( cString, cOld, cNew, nStart, nCount )
      local bReplAll, nReplaced, cWorkStr, cReturn, n
      if ArgCount() > 1
         bReplAll = ArgCount() < 5
         if ArgCount() < 4
            nStart = 1
            if ArgCount() < 3
               cNew = ''
            endif
         endif
         cWorkStr = substr( cString, nStart )
         cReturn = left( cString, nStart - 1)
         nReplaced = 0
         do while at(cOld, cWorkStr) > 0 .and. ;
            ( nReplaced < nCount or bReplAll )
            n = at( cOld, cWorkStr)
            cWorkStr = stuff( cWorkStr, ;
               at( cOld, cWorkStr ), ;
               len( cOld ), ;
               cNew )
               cReturn = cReturn + left( cWorkStr, n + len( cNew ) - 1 )
               cWorkStr = substr( cWorkStr, n + len( cNew ) )
            nReplaced = nReplaced + 1
         enddo
      else
         #if __vdb__ >= 7
            e = new exception()
            e.message := 'Not enough parameters - expecting at least 2'
            throw e
         #else
            msgbox('Not enough parameters','Error',16)
         #endif
         cReturn = cString
         cWorkStr = ''
      endif
   return cReturn + cWorkStr


   FUNCTION BreakString(instring, sepchar)
		// Programmer:  Bruce Beacham (bruce@beacham.co.uk)
      // Date........:9/26/1999
      // Break a string into parts where the parts are separated 
      // by a short string (can be >1 long).
      //   eg  break a path into the drive and directories by 
      //       virtue of the separator \
      // Creates an array    this.parts[]   which has no elements 
      // if there is something wrong instring is the string to be 
      // broken.   sepchar is the separator.
      // If only one parameter is given it is assumed to be 
      // the separator and this.string is assumed to be the string 
      // to be broken.
      //
      // Modified by Ken Mayer, so that if pCount() is zero,
      // and this.string has a value, a space is assumed to be
      // the separator character ... and if a single parameter
      // is passed and "this.string" is empty, assume the
      // parameter is the string to be broken (with space
      // as separator), rather than simply returning ...
      this.parts = new array()
      private is, sc
		do case
         // if nothing is passed to method, and "this.string"
         // is empty, return
         case pcount() == 0 and empty(this.string)
              return this.parts
         // if nothing is passed to method, and "this.string"
         // is NOT empty, assume a space as the separator
         case pCount() == 0 
              is = this.string
              sc = " "
         // if a single parameter is passed, and "this.string"
         // is empty, assume parameter is string to be
         // broken, and use a space as the separator:
         case pcount() == 1 and empty(this.string)
              is = instring
              sc = " "
         // if a single parameter is passed, "this.string" has
         // a value, then string to be broken is "this.string"
         // and the parameter is the separator:
         case pcount() == 1
         	is = this.string
            sc = instring
         // otherwise, regardless of number of parameters passed
         // (two or more), the first two are used as the 
         // string to be 'broken' and the 'separator':
         otherwise
	         is = instring
   	      sc = sepchar
      endcase
      // error handling:
      if type("is") <> "C"
         msgbox("String supplied is not a character string", "Cannot parse...", 16)
         return this.parts
      endif
      if type("sc") <> "C"
         msgbox("Separator supplied is not a character string", "Cannot parse...", 16)
         return this.parts
      endif

      // now to break it up:
      private left_is, right_is
      do while at(sc, is) <> 0
         left_is = left(is, at(sc, is)-1)
         right_is = right(is, len(is) - at(sc, is) - (len(sc) - 1))
         this.parts.add(left_is)
         is = right_is
      enddo
      this.parts.add(is)

      //the stringex object now has an array "parts" ...
   return this.parts

ENDCLASS
// End of Class: STRINGEX

//--------------------------------------------------------------------
// End of File: STRINGEX.CC
//--------------------------------------------------------------------



