/*
   The "setup program" for the MDI Tutorial
   application ... open any and all files
   needed to run the application and/or develop
   the application.
*/

// These always get me -- if the program
// crashes, and they usually do while developing --
// (due to programmer error), the speedBar and the
// statusBar in the IDE is not available ...  this 
// just puts them back. the MDI application class turns 
// them back off ...
_app.speedbar  := true
_app.statusBar := true

// this can also cause problems:
set design on

// Set procedures ...:
set procedure to START.PRG  additive

// make sure the menu is available:
set procedure to tutorial.mnu additive

// custom controls used by the application

set procedure to ":FormControls:SEEKER.CC"   additive
set procedure to ":ReportControls:report.cc"   additive
set procedure to "mycontrols.cc" additive
set procedure to "CustomReportControls.cc" additive

// add others as needed here:
set procedure to COUNTRY.WFM             additive
set procedure to CUSTOMER.WFM            additive
set procedure to INVENTORY.WFM           additive
set procedure to INVOICE.WFM             additive
set procedure to STATE.WFM               additive
set procedure to SUPPLIER.WFM            additive
set procedure to PREVIEW.WFM             additive

/*
   End of Program: SETUP.PRG
*/
