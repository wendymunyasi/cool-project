class MYENTRYFIELD(parentObj) of ENTRYFIELD(parentObj) custom
   with (this)
      onGotFocus = {;this.keyboard("{Home}")}
      height = 1.0
      left = 8.4286
      top = 4.2273
      width = 21.5714
      metric = 0        // Chars
      colorHighLight = "White/Blue"
      value = "MyEntryField"
      selectAll = false
   endwith

endclass

class MYTEXT(parentObj) of TEXT(parentObj) custom
   with (this)
      height = 1.0
      left = 4.0
      top = 3.5
      width = 12.0
      metric = 0        // Chars
      text = "Text1"
      borderStyle = 10        // Etched Out
   endwith

endclass

class MYTEXTLABEL(parentObj) of TEXTLABEL(parentObj) custom
   with (this)
      height = 1.0
      left = 5.0
      top = 5.0
      width = 12.0
      metric = 0        // Chars
      transparent = true
      text = "MyTextLabel"
      fontBold = true
      alignHorizontal = 2        // Right
   endwith

endclass


class MYSPINBOX(parentObj) of SPINBOX(parentObj) custom
   with (this)
      onGotFocus = {;this.keyboard("{Home}")}
      height = 1.0
      left = 5.0
      top = 9.0
      width = 15.0
      metric = 0        // Chars
      picture = '"99999"'
      colorHighLight = "White/Blue"
      rangeMax = 100
      rangeMin = 1
      value = 1
      selectAll = false
   endwith

endclass

class MYCOMBOBOX(parentObj) of COMBOBOX(parentObj) custom
   with (this)
      onGotFocus = class::MYCOMBOBOX_ONGOTFOCUS
      onLostFocus = class::MYCOMBOBOX_ONLOSTFOCUS
      onChange = class::MYCOMBOBOX_ONCHANGE
      height = 1.0
      left = 5.0
      top = 11.5
      width = 12.0
      metric = 0        // Chars
      style = 2        // DropDownList
   endwith

   function MYCOMBOBOX_onGotFocus()
      this.colorNormal = "White/Blue"
                this.savedValue = this.value
                return
   function MYCOMBOBOX_onLostFocus()
      this.colornormal = "WindowText/Window"
                return
   function MYCOMBOBOX_onChange()
      // this = combobox
                // datalink = field
                // parent = field array
                // parent = rowset
                if this.datalink.parent.parent.state == 1
                        this.value = this.savedValue
                        this.datalink.parent.parent.modified = false
                        this.datalink.parent.parent.abandon()
                        endif
      return
endclass

class MYRADIOBUTTON(parentObj) of RADIOBUTTON(parentObj) custom
   with (this)
      transparent = true
      height = 1.0909
      left = 5.0
      top = 14.0
      width = 15.7143
      text = "Radiobutton"
      metric = 0        // Chars
   endwith

endclass

class MYTITLETEXT(parentObj) of MYTEXT(parentObj) custom
   with (this)
      height = 1.5
      left = 91.0
      top = 16.5
      width = 12.0
      colorNormal = "Blue/BtnFace"
      alignHorizontal = 1        // Center
      fontSize = 14.0
      text = "Title"
      borderStyle = 1        // Raised
   endwith

endclass
class MYPUSHBUTTON(parentObj) of PUSHBUTTON(parentObj) custom
   with (this)
      height = 1.0909
      left = 4.0
      top = 6.5
      width = 15.2857
      text = "Button"
      metric = 0        // Chars
      mousePointer = 13        // Hand
   endwith

endclass


class MYGRID(parentObj, name) of GRID(parentObj, name) custom
   with (this)
      bgColor = "White"
      rowSelect = true
      colorRowSelect = "White/Blue"
      allowEditing = false
      allowAddRows = false
      height = 4.0
      left = 62.0
      top = 2.0
      width = 36.0
      metric = 0        // Chars
   endwith

endclass

class IMAGE1(parentObj, name) of IMAGE(parentObj, name) custom
   with (this)
      height = 4.0
      left = 49.0
      top = 11.0
      width = 21.0
      metric = 0        // Chars
   endwith

endclass

class MYEDITOR(parentObj, name) of EDITOR(parentObj, name) custom
   with (this)
      onGotFocus = class::MYEDITOR_ONGOTFOCUS
      onLostFocus = class::MYEDITOR_ONLOSTFOCUS
      key = class::MYEDITOR_KEY
      height = 4.0
      left = 78.0
      top = 11.0
      width = 20.0
      metric = 0        // Chars
      value = ""
      evalTags = false
      popupEnable = false
   endwith

   function MYEDITOR_onGotFocus()
      this.colornormal = "White/Blue"
      return
   function MYEDITOR_onLostFocus()
      this.colornormal = "WindowText/Window"
      return
   function MYEDITOR_key(nChar, nPosition,bShift,bControl)
     
                */ This code by Gary White is provided to get around a problem with
                */ rowsets that have the autoEdit property set to false, and editors.
                */ The editor seems to be immune to this property once you make a change
                */ in it -- if you save or abandon, you can actually edit the contents
                */ of the editor object ...
                
                // this = editor
                // datalink = field
                // parent = fieldArray
                // parent = rowset
                if type("this.datalink.parent.parent") # "U"
                        r = this.datalink.parent.parent
                        if r.autoEdit == false and ;
                                (r.state # 2 and r.state #3)
                                return 0
                        endif
                endif
      return
endclass

class MYDISABLEDENTRYFIELD(parentObj, name) of MYENTRYFIELD(parentObj, name) custom
   with (this)
      when = class::MYDISABLEDENTRYFIELD_WHEN
      enabled = false
      height = 1.0
      left = 48.0
      top = 16.0
      width = 21.5714
      colorNormal = "WindowText/Aqua"
      value = "MyDisabledEntryField"
   endwith

   function MYDISABLEDENTRYFIELD_when(bOpen)
      
      return false
endclass
class MYTOOLBAR(parentObj, name) of CONTAINER(parentObj, name) custom
   with (this)
      transparent = true
      left = 15.0
      top = 19.0
      width = 71.0
      height = 2.5
      metric = 0	// Chars
      borderStyle = 4	// Single
   endwith

   this.PBNEW = new MYPUSHBUTTON(this)
   with (this.PBNEW)
      onClick = class::PBNEW_ONCLICK
      height = 1.0909
      left = 0.8571
      top = 0.4545
      width = 11.0
      text = "&New"
      upBitmap = "RESOURCE TS_APPEND"
      fontSize = 8.0
      speedTip = '"Add a new record"'
      pageno = 0
   endwith

   this.PBEDIT = new MYPUSHBUTTON(this)
   with (this.PBEDIT)
      onClick = class::PBEDIT_ONCLICK
      height = 1.0909
      left = 12.8571
      top = 0.4545
      width = 11.0
      text = "&Edit"
      upBitmap = "RESOURCE TS_EDIT"
      fontSize = 8.0
      speedTip = '"Edit current record"'
      pageno = 0
   endwith

   this.PBSAVE = new MYPUSHBUTTON(this)
   with (this.PBSAVE)
      onClick = class::PBSAVE_ONCLICK
      height = 1.0909
      left = 24.8571
      top = 0.4545
      width = 11.0
      text = "&Save"
      upBitmap = "RESOURCE TS_SAVE"
      fontSize = 8.0
      speedTip = '"Save current record"'
      pageno = 0
   endwith

   this.PBCANCEL = new MYPUSHBUTTON(this)
   with (this.PBCANCEL)
      onClick = class::PBCANCEL_ONCLICK
      height = 1.0909
      left = 36.8571
      top = 0.4545
      width = 11.0
      text = "&Cancel"
      upBitmap = "RESOURCE TS_ABANDON"
      fontSize = 8.0
      speedTip = '"Cancel changes"'
      pageno = 0
   endwith

   this.PBDELETE = new MYPUSHBUTTON(this)
   with (this.PBDELETE)
      onClick = class::PBDELETE_ONCLICK
      height = 1.0909
      left = 48.8571
      top = 0.4545
      width = 11.0
      text = "&Delete"
      upBitmap = "RESOURCE TS_DELETE"
      fontSize = 8.0
      speedTip = '"Delete current record"'
      pageno = 0
   endwith

   this.PBPREV = new MYPUSHBUTTON(this)
   with (this.PBPREV)
      onClick = class::PBPREV_ONCLICK
      height = 1.0909
      left = 60.8571
      top = 0.4545
      width = 4.0
      text = ""
      upBitmap = "RESOURCE #104"
      speedTip = '"Previous record"'
      pageno = 0
   endwith

   this.PBNEXT = new MYPUSHBUTTON(this)
   with (this.PBNEXT)
      onClick = class::PBNEXT_ONCLICK
      height = 1.0909
      left = 65.8571
      top = 0.4545
      width = 4.0
      text = ""
      upBitmap = "RESOURCE #100"
      pageno = 0
   endwith

   function PBNEXT_onClick()
      form.rowset.next()
		if (not form.rowset.next())
			form.rowset.next(-1)
			msgbox("At the end of rowset", "Can't Navigate", 64)
		endif
      return
   function PBCANCEL_onClick()
      if form.rowset.modified
			if msgbox("Abandon changes to this row?", "Abandon changes?", 36) == 6
				form.rowset.abandon()
			endif
		else
		form.rowset.abandon()
		endif
      return
   function PBNEW_onClick()
      form.rowset.beginappend()
      return
   function PBPREV_onClick()
      if(not form.rowset.next(-1))
			form.rowset.next()
			msgbox("At the begininng of rowset", "Can't Navigate", 64)
		endif
      return
   function PBEDIT_onClick()
      form.rowset.beginedit()
      return
   function PBDELETE_onClick()
      if msgbox("Delete this row?", "Delete row?", 36) == 6
			form.rowset.delete()
		endif
      return
   function PBSAVE_onClick()
      form.rowset.save()
      return
endclass

class MYTABBOX(parentObj, name) of TABBOX(parentObj, name) custom
   with (this)
      onSelChange = class::MYTABBOX_ONSELCHANGE
      onOpen = class::MYTABBOX_ONOPEN
      id = 110
      height = 1.0
      left = 0.0
      top = 23.0
      width = 102.7143
      metric = 0	// Chars
      colorNormal = "Blue"
      colorHighLight = "Blue/Silver"
      dataSource = 'ARRAY {"Individual Record", "Find Record"}'
   endwith

   function MYTABBOX_onSelChange()
      form.pageno := this.cursel
      return
   function MYTABBOX_onOpen()
      this.cursel := 1
		this.pageno := 1
      return
endclass

class MYCONTAINER(parentObj, name) of CONTAINER(parentObj, name) custom
   with (this)
      transparent = true
      left = 49.0
      top = 1.0
      width = 44.0
      height = 3.5
      metric = 0	// Chars
      borderStyle = 4	// Single
   endwith

endclass
