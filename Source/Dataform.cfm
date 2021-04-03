/*
    DATAFORM.CFM
    This Custom form is part of the dBBASE SE tutorial project. 

*/

class DataFormCForm of BASECFORM custom from base.cfm
   set procedure to MyControls.cc additive
   set procedure to :FormControls:SEEKER.CC additive
   with (this)
      onOpen = class::FORM_ONOPEN
      height = 14.3182
      width = 80.7143
      text = "CustomDataForm"
      menuFile = "Tutorial.mnu"
      escExit = false
   endwith

   with (this.MYTITLETEXT1)
      height = 1.5
      left = 0
      top = 0
      width = 81
      text = "DataForm"
   endwith

   this.TABBOX1 = new MYTABBOX(this)
   with (this.TABBOX1)
      height = 1
      left = 0
      top = 13.3182
      width = 80.7143
   endwith

   this.TEXT2 = new MYTEXTLABEL(this)
   with (this.TEXT2)
      height = 1
      left = 6.1429
      top = 0.2273
      width = 4.7143
      transparent = true
      text = "Find:"
      pageno = 2
   endwith

   this.SEEKER1 = new SEEKER(this)
   with (this.SEEKER1)
      height = 1
      left = 12.1429
      top = 0.1818
      width = 57.4286
      value = ""
      pageno = 2
   endwith

   this.GRID1 = new MYGRID(this)
   with (this.GRID1)
      pageno = 2
      height = 11.1364
      left = 1
      top = 1.6364
      width = 77.2857
   endwith

   this.MYTOOLBAR1 = new MYTOOLBAR(this)
   with (this.MYTOOLBAR1)
      left = 6
      top = 1.5
      width = 71
      height = 1.4091
   endwith


   function rowset_canNavigate
      /*
          Check to save any changes before allowing navigation.
          For whatever reason, this gets called twice. If the
          user chooses Yes to Save, or No to abandon, then
          the next time through the rowset.modified property is
          false so there's no problem. If the user chooses to
          cancel the navigation, they'll get prompted twice.
          For that reason, we set a flag to indicate it's been
          here once. If the flag exists, we null it, if not we 
          run the validation.

          BIG NOTE: If a future version of VdB corrects the
          behavior so the canNavigate routine does NOT fire
          twice, this code will not work correctly.

          This was written for Visual dBASE 7.01 build 1419

          Code by Gary White
      */

      local bYes, nAnswer
      if type("_app.cancelNav") == "L" and _app.cancelNav
         _app.cancelNav := null
         bYes = false
      else
         bYes = true
         if this.modified
            nAnswer = msgbox("Save changes before leaving record?", "Data has changed",32+3)
            do case
               case nAnswer == 6 // Yes
                  this.save()
               case nAnswer == 7 // No
                  this.abandon()
               otherwise         // Cancel
                  bYes := false
                  _app.cancelNav = true
            endcase
         endif
      endif
   return bYes

   function form_onOpen
      // default is to move to the top of the rowset 
      // when the form opens:
      if form.rowset # null
         form.rowset.autoEdit := false // don't allow automatic editing
         // assign this method to the rowset's canNavigate:
         form.rowset.canNavigate := class::rowset_canNavigate
         // NOW go to the first row ...
         form.rowset.first()
      endif
   return
endclass
