/*
    START.PRG
    Author: Ken Mayer
    Date..: January 07, 1999

    Tutorial project START program

    This program is used to start the TUTORIAL 
    application. 

    There is a reference to another .CC, which is
    the genericMDIApp.CC file -- this contains
    the generic application object, and below we 
    subclass it ...

    The idea is that you have a lot of "things" that
    you always do for any application that is
    an MDI app. You create one object that handles
    all of that, and then you subclass that for
    the specifics for an application, as each is
    at least slightly different.

*/

local app
set talk off
set procedure to genericMDIApp.cc additive

app = new TutorialApp()
app.open()

return

class TutorialApp of GenericMDIApp
   // set any specific code for the subclassed
   // MDI application here:
   this.FrameWinText = "dBASE Plus Tutorial Project"

   // note this is not the file name -- the 
   // SETUP program will do a "set procedure ..." that
   // will open the file "TUTORIAL.MNU" ... the class
   // will be available from that point on.
   this.MenuClassName = "TutorialMenu"

endclass


