function repaint
        parameter oForm
   if type("oForm") == "U" or empty(oForm)
                oForm = form
        endif
        if type("UpdateWindow") # "FP"
                 extern CLOGICAL UpdateWindow(CHANDLE) USER32
        endif
return UpdateWindow(oForm.hWnd)

** END HEADER -- do not remove this line


class BaseCForm of FORM custom
   set procedure to MyControls.cc additive
   with (this)
      onGotFocus = class::FORM_ONGOTFOCUS
      onLostFocus = class::FORM_ONLOSTFOCUS
      canClose = class::FORM_CANCLOSE
      onClose = class::FORM_ONCLOSE
      height = 21.4545
      left = 20.0
      top = 5.8636
      width = 94.0
      text = "BaseForm"
   endwith

   this.MYTITLETEXT1 = new MYTITLETEXT(this)
   with (this.MYTITLETEXT1)
      height = 1.5
      left = 0.0
      top = 0.0
      width = 93.7143
      anchor = 2	// Top
      text = "BaseForm"
   endwith


   function form_canClose()
      // avoid closing the form in the wrong state
		// if we have a rowset on the form, we need
		// to check the state -- 2 = Edit, 3 = Append
		if form.rowset # Null and;
			(form.rowset.state == 2 or form.rowset.state == 3)
			// if the row's been modified ...
			if form.rowset.modified
				nAnswer = msgbox("Save changes before leaving the record?",;
										"Data has changed", 32+3)
				// check the answer returned by clicking a button in the message box
				do CASE
					CASE nAnswer == 6
						form.rowset.save()
					CASE nAnswer == 7
						form.rowset.abandon()
					OTHERWISE
						return fasle
				ENDCASE
			endif
		endif
	return true

   function form_onClose()
      this.release()
	return

   function form_onGotFocus()
      // set application reference to this form:
		if type("_app.framewin") # "U"
			_app.framewin.currentForm = this
		endif
		form.repaint()
		return

   function form_onLostFocus()
      // null out applications's reference to this form:
		if type("_app.framewin.currentForm") # "U"
			_app.framewin.currentform := null
			endif
	return

endclass

