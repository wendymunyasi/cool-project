/*
   ----------------------------------------------------------------
   Program...: DUFLP.H
   Programmer: Ken Mayer, based on suggestions by Jim Sare and
               Romain Streiff
   Date......: 12/09/1997
   Notes.....: Any routines necessary for dUFLP library that are
               shared routines.
   ----------------------------------------------------------------
*/

FUNCTION SetProc( cProcName )
/*
   ----------------------------------------------------------------
    Programmer..: Ken Mayer, Romain Strieff
    Date........: 12/09/1997
    Notes.......: Checks to see if a procedure file is open and
                  available.
    Written for.: Visual dBASE 5.5
                  Minor modifications for VdBASE 7 -- note:
                  this version will not run under earlier versions!
    Rev. History: 12/07/1996 -- Original Code
                  12/20/1996 -- Romain posted a better version
                  12/09/1997 -- Modified for VdBASE 7
                  April 30, 1999 -- updated by Gary White
                    to handle full path for a procedure
    Calls.......: None
    Usage.......: SetProc( <cProcName> )
    Example.....: if .not. SetProc( "MyProcedure.PRG" )
                     set procedure to myprocedure additive
                  endif
    Returns.....: Logical
    Parameters..: cProcName = Name of procedure file, needs to
                              have the extension, and if necessary,
                              (not in current directory), the path.
   ----------------------------------------------------------------
*/

   if not "\" $ cProcname
      cProcname = set("directory") + "\" + cProcName
   endif
   lRet= false
   n=1
   cCheck=set("procedure",n)
   do while not empty( cCheck )
      if upper(cProcname)==upper(cCheck)
         lRet= true
         exit
      endif
      n++
      cCheck=set("procedure",n)
   enddo
   
RETURN lret
// -- EoM: SetProc()

/*
   ----------------------------------------------------------------
   End of file: dUFLP.H
   ----------------------------------------------------------------
*/

