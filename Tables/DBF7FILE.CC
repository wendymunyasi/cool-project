// -- File: DBF7File.Cc

class DBF7File(cDBF) of BFile from "BFile.Cc"
/*
   --------------------------------------------------------------------

   Programmer...: Bowen Moursund (bowen@nerds.com)
   Last modified: 08/13/1998
   Written for..: Visual dBASE 7.01

   Note: Jay Parsons started the original work on this,
         sent it to Ken Mayer -- neither of us could get
         it to function quite correctly. Bowen, after
         a discussion at ICon 98 on Undocumented Features
         dug this code up and finished it the day after
         the conference was over. (This was after I (Ken)
         had explained that to the best of my knowledge
         it wasn't possible to reset the autoincrement
         value ... figures <G>)
   --------------------------------------------------------------------

   Purpose:
   Extends Jim Sare's BFile class with level 7 DBF utility methods.

   --------------------------------------------------------------------

   Notes:
   The SetNextAutoIncValue method is based on information supplied by
   Jay Parsons and acquired second hand via Ken Mayer <g>. Ken's notes
   concerning Jay's info:

       According to Jay:
         "1. In a VdB7 .DBF, the main header is longer, 44h (68 bytes).
             The table of field descriptors starts next, at offset
             44h/68d.
          2. The field name comes first, as usual. The type byte
             indicating the type of the field is 32 bytes into the
             descriptor, which is 48 bytes long.
          3. The Autoinc type is marked by a "+" type byte, 2Bh.
          4. The next available autoinc number starts 10 bytes
             farther along and is stored in 4 bytes binary, least-
             significant first.

   --------------------------------------------------------------------
   Methods:
      SetNextAutoIncValue()
         Allows the developer to see the value of the next
         number returned by an AutoIncrement Field in a
         DBF 7 table. NOTE THIS WILL NOT WORK FOR OTHER
         TABLE TYPES (i.e., .DB, or SQL tables).

      MDXFlag()
         Allows the developer to turn on/off the flag in
         the table header that notifies dBASE that there
         is a production .MDX. This can be useful if
         performing a long task that is slowed down by
         updating the index tags for your table for
         each record processed -- turn the flag off,
         when done, turn it back on and issue a reindex.

    Examples of use:
         set procedure to DBF7File.CC additive
         oDBF7File = new DBF7File( "Foo.DBF" )

         // reset autoinc field
         oDBF7File.SetNextAutoIncValue( "FOO_ID", 1 ) 

         // detach production MDX
         oDBF7File.SetMDXFlag( false ) 

    Dependencies:
       BFILE.CC (in the dUFLP library)
   --------------------------------------------------------------------
*/

   set procedure to BFile.Cc additive
   protect DBF, DBFDef

   class::SetDBF(cDBF)

   function SetDBF
      parameters cDBF
      local bSuccess
      bSuccess = false

      if argCount() == 1 and type("cDBF") == "C" and file(cDBF)
         this.DBF = cDBF
         bSuccess := true
      else
         this.DBF = null
         bSuccess := false
      endif
      return bSuccess

   function GetDBF
      return this.DBF

   function VerifyDBF
      return type("this.DBF") == "C" and file(this.DBF)

   function SetNextAutoIncValue( cFieldName, nNextValue )
      if not this.VerifyDBF()
         return 1 // DBF not found
      endif
      local i, nReturn, nFieldNo, oDBFDef, oFields, bIsField, bIsAutoinc
      nReturn = 0
      nFieldNo = 0
      oDBFDef = new tableDef()
      oDBFDef.tableName = this.DBF
      try
         oDBFDef.load()
      catch (exception e)
         return 6  // Could not load tableDef object
      endtry
      oFields = oDBFDef.fields
      bIsField = false
      bIsAutoinc = false
      for i = 1 to oFields.size
         if upper(oFields[i].fieldName) == upper(cFieldName)
            bIsField := true
            if oFields[i].type == "AUTOINC"
               bIsAutoinc := true
               nFieldNo := i
            endif
            exit
         endif
      next i
      if not bIsField
         return 2 // Field name not found
      endif
      if not bIsAutoinc
         return 3 // Field not an autoinc field
      endif
      try
         this.open(this.DBF, "RW")
      catch (exception e)
         return 4 // Cannot open DBF
      endtry
      nOffset = (68+(48*(nFieldNo-1))+42)
      if this.seek( nOffSet, 0 ) <> nOffset
         this.close()
         return 5 // Low level seek failed
      endif
      this.WriteULong( nNextValue )
      this.close()
      return 0 // Success!

   function SetMDXFlag( bValue )
      if not this.VerifyDBF()
         return 1 // DBF not found
      endif
      try
         this.open(this.DBF, "RW")
      catch (exception e)
         return 4 // Cannot open DBF
      endtry
      if this.seek( 28, 0 ) <> 28
         this.close()
         return 5 // Low level seek failed
      endif
      this.write( iif(bValue, chr(1), chr(0)) )
      this.close()
      return 0 // Success!

endclass

/* -----------------------------------------------------------------------
   End of File: DBF7FILE.CC
   ----------------------------------------------------------------------- */
