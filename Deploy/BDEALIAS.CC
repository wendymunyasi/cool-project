/*
   File...: BDEALIAS.CC
   Author.: Romain Strieff
   Date...: 09/21/1998 (turned into a .CC by Ken Mayer)
            02/10/1999 added databaseFound method
            02/12/1999 moved BDECFG_FILE(), localShare(), and
                       fromUnicode() from MISCAPI.PRG to here.
            March 28, 1999 --
                       Fixed some minor things and added
                       the cTableFormat parameter to the 
                       createAlias() method.
            March 29, 1999 -- 
                       Gary fixed databaseFound a bit,
                       added databaseDir()
            Nov. 5, 1999 -- minor fix noted by Bruce Beacham ...

   This allows you to delete or create a BDE Alias without
   having to exit Visual dBASE and run the BDE Administrator
   application. This uses the BDE API ...

   Useful for deployment of an application ...

   Methods included here:

      databaseFound() -- returns logical value based on whether
        or not the BDE Alias you are looking for is set in your
        installation of the BDE or not. Can be used to determine
        if you should create it or not ...
      createAlias() -- creates a BDE Alias
      deleteAlias() -- deletes a BDE Alias
      BDECFG_File() -- returns the name of the BDE configuration
                       file "in use" by the BDE at that time.
      localShare()  -- returns a logical based on the state
                       of this setting in the BDE.
      DatabaseDir() -- returns the directory of an alias supplied
                       as a parameter

   Examples:

      set procedure to bdealias.cc additive
      b = new BDEAlias()
      ? b.databaseFound( "MYALIAS" )
      ? b.DeleteAlias( "MYALIAS" )
      ? b.CreateAlias( "MYALIAS", "C:\TEST" )
      ? b.BDECFG_File()
      ? b.localShare()
      ? b.databaseDir( "MYALIAS" )

      // example of creating an InterBase alias in detail:
      cIPath = "c:\MyTest;"+;
               "SERVER NAME:c:\MyTest\testdata.gdb;"+;
               "USER NAME:SYSDBA;"+;
               "LANGDRIVER:'ascii' ANSI;"+;
               "SQLQRYMODE:SERVER;"+;
               "SQLPASSTHRU MODE:SHARED NOAUTOCOMMIT"
     b.createAlias( "MYINTERBASE", cIPath, "INTRBASE" )
*/

class BDEALias

  function dataBaseFound( cDatabase )
      // Code by Gary White
      local d, dbArray, lFound, i
      d = new database()
      dbArray=d.getschema( "Databases" )
      release object d
      lFound = false
      for i = 1 to dbArray.size
         if upper( cDatabase ) == upper( dbArray[i] )
            lFound := true
            exit
         endif
      endfor
   return lFound

   function DatabaseDir
      parameters cDatabase
      local oDatabase
      /*
         Returns the path for the alias supplied
         as a parameter (null if it does not exist)

         Based on code posted by Romain Strieff 
         in the Visual dBASE Newsgroups

         Modified to accept a string for an alias name
         instead of a database object by Gary White
      */
      cRet = null
      if type("cDatabase") == "C" and not empty(cDatabase)
         if this.databaseFound( cDatabase )
            if type("GetAliasPath") # "FP"
               extern cint GetAliasPath(cHandle,cString,;
                  cString,cString);
                  IDAPI32 from "DbiFormFullName"
            endif
            cRet=space(261)
            oDatabase = new database()
            oDatabase.databaseName := cDatabase
            oDatabase.active := true
            if ( GetAliasPath(oDatabase.handle,"DummyTableName","",cRet ) == 0 )
               cRet=cRet.left(cRet.lefttrim().lastindexof("\"))
               else
               cRet=""
            endif
            oDatabase.active := false
            release object oDatabase
         endif
      endif
   return cRet

  function DeleteAlias(cAliasName)
     //Deletes an existing Alias
      if type("DbiDeleteAlias") # "FP"
         extern cint DbiDeleteAlias(;
                cHandle,;
                CPTR ) idapi32
      endif

    return DbiDeleteAlias(null,this.toUnicode(cAliasName))==0


  function CreateAlias(cAliasName, cPath, cTableFormat)
  // cAliasName = the Alias name that the database is to
  //              be referred to
  // cPath      = the full path to the database
  // cTableFormat = the table format (i.e., INTRBASE, DBASE, etc.)

     if pCount() < 3
        cTableFormat = "DBASE"
     endif
     //Creates an Alias

     if type("DbiAddAlias") # "FP"
        extern cint DbiAddAlias(;
               cHandle,;
               CPTR,;
               CPTR,;
               CPTR,;
               clogical) idapi32
     endif
  return DbiAddAlias(null,;
                     this.toUnicode(cAliasName),;
                     this.toUnicode(cTableFormat),;
                     this.toUnicode("PATH:" + cPath),;
                     TRUE)==0

   function BDECFG_File
      /*
         BDECFG_File -- returns the name of the currently
         used BDE Configuration file. (Uses BDE API)
         Note: this uses fromUnicode() below ...

         Posted by Romain Strieff in the Visual dBASE Newsgroups
         February 2, 1999
      */

      if type( "DbiGetSysConfig" ) # "FP"
         extern cInt DbiGetSysConfig( cPtr ) IDAPI32
      endif
      cBuffer = space( 256 )
      DbiGetSysConfig( cBuffer )
      cRet = substr( this.fromUnicode( cBuffer ), 54, 128 )
      cRet = left( cRet, at(chr(0), cRet ) - 1 )
   return cRet

   function LocalShare
      /*
         LocalShare -- returns a logical true/false based on
         the localShare setting of the BDE. 
         Note: this uses fromUnicode() below ...

         Posted by Romain Strieff in the Visual dBASE Newsgroups
         February 2, 1999
      */

      if type( "DbiGetSysConfig" ) # "FP"
         extern cInt DbiGetSysConfig( cPTR ) idapi32
      endif

      cBuffer = space( 256 )
      DbiGetSysConfig( cBuffer )

   return asc( left( this.fromUnicode( cBuffer ), 1 ) ) == 1

   function fromUnicode( c )
      /*
         fromUnicode returns standard characters rather than
         the Unicode character set (which is larger).

         Posted by Romain Strieff in the Visual dBASE Newsgroups
         February 2, 1999
      */
       local cText, nLen, nInd
       nLen = len( c )
       cText = ""
       for nInd = 0 to nLen - 1
           cText += chr( c.getByte( nInd ) )
       endfor

   return cText

   // Converts to Unicode
   Function ToUnicode(c)
      LOCAL cTemp, x

      cTemp = Replicate(Chr(0), ((Len(c) + 1) / 2) + ;
                                ((Len(c) + 1) % 2))
      For x = 1 To Len(c)
         cTemp.SetByte(x - 1, Asc(SubStr(c, x)))
      EndFor

   RETURN cTemp

endclass

/*
    End of File: BDEALIAS.CC
*/
