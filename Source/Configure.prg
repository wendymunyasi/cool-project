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

// Setup custom controls for use with forms
// set procedure to mycontrols.cc additive
// set procedure to :FormControls:SEEKER.CC additive

// Setup custom controls for use the reports
// set procedure to CustomReportControls.cc additive
// set procedure to :ReportControls:report.cc additive
