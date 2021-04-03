/*
    BASE.CFM
    This custom form is the "base" form for the 
     dBBASE SE tutorial project. The purpose of
    this form is to give something that all the other
    forms are "based" on. Any changes to this form
    will alter the derived forms, including colors,
    and such.

*/
** END HEADER -- do not remove this line
/*
    BASE.CFM
    This custom form is the "base" form for the 
     dBBASE SE tutorial project. The purpose of
    this form is to give something that all the other
    forms are "based" on. Any changes to this form
    will alter the derived forms, including colors,
    and such.

*/
** END HEADER -- do not remove this line
class baseCForm of FORM custom
   set procedure to MyControls.cc additive
   with (this)
      onGotFocus = class::FORM_ONGOTFOCUS
      onLostFocus = class::FORM_ONLOSTFOCUS
      canClose = class::FORM_CANCLOSE
      onClose = class::FORM_ONCLOSE
      scaleFontBold = false
      height = 11.7727
      left = 58.5714
      top = 0.2727
      width = 46.8571
      text = "BaseForm"
      icon = "filename Mugs.ico"
   endwith

   this.MYTITLETEXT1 = new MYTITLETEXT(this)
   with (this.MYTITLETEXT1)
      height = 1.5
      left = 0
      top = 0
      width = 47
      text = "<h2>Base Form</h2>"
   endwith


   function form_canClose
      // is there a rowset associated with the form? And
      // if so, is the state set to edit or beginAppend?
      if form.rowset # NULL and;
         (form.rowset.state == 2 or form.rowset.state == 3)
         // if so, is the rowset modified?
         if form.rowset.modified
            nAnswer = msgbox("Save changes before leaving record?", "Data has changed",32+3)
            do case
               case nAnswer == 6
                  form.rowset.save()
               case nAnswer == 7
                  form.rowset.abandon()
               otherwise
                  return false
            endcase
         endif
      endif
  
      
      return true

   function form_onClose
      this.release()
      return

   function form_onGotFocus
      // set application reference to this form:
      if type( "_app.framewin" ) # "U"
         _app.framewin.currentForm = this
      endif
      form.repaint()
   return

   function form_onLostFocus
      // null out application's reference to this form:
      if type( "_app.framewin.currentForm" ) # "U"
         _app.framewin.currentForm := null
      endif

   return

   function Repaint
      parameter oForm
      if type( "oForm" ) == "U" or empty( oForm )
         oForm = form
      endif
      if type( "UpdateWindow" ) # "FP"
         extern CLOGICAL UpdateWindow( CHANDLE ) USER32
      endif
   RETURN UpdateWindow( oForm.hWnd )
endclass
