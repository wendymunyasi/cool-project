** END HEADER -- do not remove this line
class dialogCForm of BASECFORM custom from "Base.cfm"
   set procedure to MyControls.cc additive
   with (this)
      visible = true
      height = 16.0
      left = 59.8571
      top = 3.7273
      width = 40.0
      text = "CustomDialogForm"
      clientEdge = true
      autoCenter = true
      mdi = false
      smallTitle = true
      escExit = false
   endwith

   with (this.MYTITLETEXT1)
      text = "DialogForm"
   endwith

   this.PBSAVE = new MYPUSHBUTTON(this)
   with (this.PBSAVE)
      onClick = class::PBSAVE_ONCLICK
      height = 1.0909
      left = 3.0
      top = 6.5
      width = 15.2857
      text = "&OK"
      speedTip = '"Save"'
   endwith

   this.PBCANCEL = new MYPUSHBUTTON(this)
   with (this.PBCANCEL)
      height = 1.0909
      left = 21.0
      top = 6.5
      width = 15.2857
      text = "&CANCEL"
      speedTip = '"Cancel"'
   endwith


   function PBSAVE_onClick()
      // save and close the form:
		if form.rowset # NULL
			form.rowset.save()
		endif
		form.close()
		return

endclass

