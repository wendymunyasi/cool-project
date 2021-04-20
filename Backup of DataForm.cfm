** END HEADER -- do not remove this line
class DataFormCForm of BASECFORM custom from "Base.cfm"
   set procedure to :FormControls:seeker.cc additive
   set procedure to MyControls.cc additive
   with (this)
      onOpen = class::FORM_ONOPEN
      visible = true
      height = 16.0
      left = 42.4286
      top = 4.1364
      width = 74.2857
      text = ""
      escExit = false
   endwith

   with (this.MYTITLETEXT1)
      text = "DataForm"
   endwith

   this.MYTABBOX1 = new MYTABBOX(this)
   with (this.MYTABBOX1)
      height = 1.0
      left = 0.0
      top = 14.9091
      width = 74.0
   endwith

   this.SEEKER1 = new SEEKER(this)
   with (this.SEEKER1)
      height = 1.0
      left = 19.0
      top = 0.5
      width = 43.0
      pageno = 2
   endwith

   this.MYTEXTLABEL1 = new MYTEXTLABEL(this)
   with (this.MYTEXTLABEL1)
      height = 1.0
      left = 6.0
      top = 0.5
      width = 12.0
      text = "Find"
      pageno = 2
      alignHorizontal = 1	// Center
   endwith

   this.MYGRID1 = new MYGRID(this)
   with (this.MYGRID1)
      pageno = 2
      height = 9.5
      left = 6.0
      top = 4.0
      width = 61.0
   endwith

   this.MYTOOLBAR1 = new MYTOOLBAR(this)
   with (this.MYTOOLBAR1)
      left = 1.0
      top = 2.0
      width = 71.0
      height = 2.5
   endwith


   function form_onOpen()
      if form.rowset # NULL
			// don't allow automatic editing
			form.rowset.autoEdit := false
			// assign this method to the rowset's canNavigate:
			form.rowset.canNavigate := class::rowset_canNavigate
			// go to first row ...
			form.rowset.first()
		endif
      return

   endclass

