/*
    DIALOGFORM.CFM
    This custom form is part of the dBBASE SE tutorial project. 
*/

class DialogFormCForm of BASECFORM custom from "Base.cfm"
   set procedure to MyControls.cc additive
   with (this)
      text = "DialogCustomForm"
      clientEdge = true
      autoCenter = true
      mdi = false
      smallTitle = true
   endwith

   with (this.MYTITLETEXT1)
      text = "DialogForm"
   endwith

   this.PBSAVE = new MYPUSHBUTTON(this)
   with (this.PBSAVE)
      onClick = class::PBSAVE_ONCLICK
      height = 1.1818
      left = 10
      top = 9.5
      text = "OK"
      speedTip = "Save Changes"
   endwith

   this.PBCANCEL = new MYPUSHBUTTON(this)
   with (this.PBCANCEL)
      onClick = class::PBCANCEL_ONCLICK
      height = 1.1818
      left = 25
      top = 9.5
      text = "Cancel"
      speedTip = "Cancel Changes"
   endwith


   function PBCANCEL_onClick
      // abandon changes and close the form:
      if form.rowset # NULL
         form.rowset.abandon()
      endif
      form.close()
   return

   function PBSAVE_onClick
      // Save and close the form:
      if form.rowset # NULL
         form.rowset.save()
      endif
      form.close()
   return
endclass
