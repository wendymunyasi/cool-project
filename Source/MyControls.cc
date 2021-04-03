/*
    Mycontrols.cc 
    This custom control file is part of the dBBASE SE tutorial project. 
*/


//  Change "Blue" to : 0x804000



class MYENTRYFIELD(parentObj) of ENTRYFIELD(parentObj) custom
   with (this)
      onGotFocus = {;this.keyboard( "{Home}" )}
      height = 1
      left = 1
      top = 0.5
      width = 17
      metric = 0        // Chars
      colorHighLight = "White/Blue"
      value = "MyEntryfield"
      selectAll = false
   endwith

endclass
class MYCOMBOBOX(parentObj) of COMBOBOX(parentObj) custom

   with (this)
      onGotFocus = class::combobox_onGotFocus 
      onLostFocus = {;this.colorNormal = "WindowText/Window"}
      onChange = class::combobox_onChange
      height = 1
      left = 1
      top = 2.5
      width = 18
      metric = 0        // Chars
      style = 2        
   endwith
   
   function combobox_onGotFocus
      this.colorNormal = "White/Blue"
      this.savedValue = this.value
      return

   function combobox_onChange
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
class MYSPINBOX(parentObj) of SPINBOX(parentObj) custom
   with (this)
      onGotFocus = {;this.keyboard( "{Home}" )}
      height = 1
      left = 1
      top = 4
      width = 16
      metric = 0        // Chars
      picture = "99999"
      colorHighLight = "White/Blue"
      rangeMax = 100
      rangeMin = 1
      value = 1
      selectAll = false
   endwith

endclass




class MYGRID(parentObj) of GRID(parentObj) custom
   //  READ-ONLY GRID

   with (this)
      bgColor = "white"
      rowSelect = true
      colorRowSelect = "White/Blue"
      allowEditing = false
      allowAddRows = false
      height = 5.5
      left = 1
      top = 9.5
      width = 43
      metric = 0        // Chars
   endwith

endclass
class MYTITLETEXT(parentObj) of MYTEXT(parentObj) custom
   with (this)
      height = 1.5
      left = 22
      top = 0
      width = 32
      metric = 0        // Chars
      colorNormal = "Blue/BtnFace"
      alignHorizontal = 1        // Center
      fontSize = 14
      fontBold = true
      text = "Title"
      borderStyle = 1        // Raised
   endwith

endclass

class MYEDITOR(parentObj) of EDITOR(parentObj) custom
   with (this)
      onGotFocus = {; this.colorNormal = "White/Blue"}
      onLostFocus = {; this.colorNormal = "WindowText/Window"}
      height = 4
      left = 39
      top = 2
      width = 25
      metric = 0        // Chars
      value = ""
      evalTags = false
      popupEnable = false
   endwith

endclass

class MYTABBOX(parentObj) of TABBOX(parentObj) custom
   with (this)
      onSelChange = class::MYTABBOX_ONSELCHANGE
      onOpen = class::MYTABBOX_ONOPEN
      id = 114
      height = 1
      left = 0
      top = 21.4545
      width = 80
      metric = 0        // Chars
      colorNormal = "Blue"
      colorHighLight = "Blue/SILVER"
      dataSource = 'ARRAY {"Individual Record","Find Record"}'
   endwith

   function MYTABBOX_onSelChange
      form.pageNo := this.curSel
      //repaint(form) // repaint this form -- API calls 
                    // by Jim Sare -- function toward end
                    // of this file
      
      return
   function MYTABBOX_onOpen
      this.curSel := 1
      form.pageNo := 1

      return
endclass


class MYTOOLBAR(parentObj) of CONTAINER(parentObj) custom
   with (this)
      left = 2
      top = 17.5
      width = 71
      height = 1.4
      metric = 0        // Chars
      borderStyle = 4        // Single
   endwith

   this.PBNEW = new MYPUSHBUTTON(this)
   with (this.PBNEW)
      onClick = class::PBNEW_ONCLICK
      height = 1.09
      left = 0.5
      top = 0.0909
      width = 11
      text = "&New"
      upBitmap = "RESOURCE TS_APPEND"
      fontSize = 8
      pageno = 0
   endwith

   this.PBEDIT = new MYPUSHBUTTON(this)
   with (this.PBEDIT)
      onClick = class::PBEDIT_ONCLICK
      height = 1.09
      left = 11.8
      top = 0.0909
      width = 11
      text = "&Edit"
      upBitmap = "RESOURCE TS_EDIT"
      fontSize = 8
      pageno = 0
   endwith

   this.PBSAVE = new MYPUSHBUTTON(this)
   with (this.PBSAVE)
      onClick = class::PBSAVE_ONCLICK
      height = 1.09
      left = 23.1
      top = 0.0909
      width = 11
      text = "&Save"
      upBitmap = "RESOURCE TS_SAVE"
      fontSize = 8
      pageno = 0
   endwith

   this.PBCANCEL = new MYPUSHBUTTON(this)
   with (this.PBCANCEL)
      onClick = class::PBCANCEL_ONCLICK
      height = 1.09
      left = 34.4
      top = 0.0909
      width = 11
      text = "&Cancel"
      upBitmap = "RESOURCE TS_ABANDON"
      fontSize = 8
      pageno = 0
   endwith

   this.PBDELETE = new MYPUSHBUTTON(this)
   with (this.PBDELETE)
      onClick = class::PBDELETE_ONCLICK
      height = 1.09
      left = 45.7
      top = 0.0909
      width = 11
      text = "&Delete"
      upBitmap = "RESOURCE TS_DELETE"
      fontSize = 8
      pageno = 0
   endwith

   this.PBPREV = new MYPUSHBUTTON(this)
   with (this.PBPREV)
      onClick = class::PBPREV_ONCLICK
      height = 1.0909
      left = 59.8571
      top = 0.0909
      width = 4
      text = ""
      upBitmap = "RESOURCE #104"
      pageno = 0
   endwith

   this.PBNEXT = new MYPUSHBUTTON(this)
   with (this.PBNEXT)
      onClick = class::PBNEXT_ONCLICK
      height = 1.09
      left = 64.5714
      top = 0.0909
      width = 4
      text = ""
      upBitmap = "RESOURCE #100"
      pageno = 0
   endwith

   function PBNEXT_onClick
      if ( not form.rowset.next() )
         form.rowset.next(-1)
         msgbox("At end of rowset", "Can't Navigate", 64)
      endif
      return
   function PBPREV_onClick
      if ( not form.rowset.next(-1) )
         form.rowset.next()
         msgbox("At beginning of rowset", "Can't Navigate",64)
      endif
      return
   function PBDELETE_onClick
      if msgbox( "Delete this row?", "Delete Row?", 36 ) == 6
         form.rowset.delete()
      endif
      return
   function PBCANCEL_onClick
      if form.rowset.modified
         if msgbox( "Abandon changes to this row?", "Abandon changes?", 36 ) == 6
            form.rowset.abandon()
         endif
      else
         form.rowset.abandon()
      endif
      return
   function PBSAVE_onClick
      form.rowset.save()
      return
   function PBEDIT_onClick
      form.rowset.beginEdit()
      return
   function PBNEW_onClick
      form.rowset.beginAppend()
      return
endclass

class MYCONTAINER(parentObj) of CONTAINER(parentObj) custom
   with (this)
      transparent = true
      left = 23
      top = 7
      width = 29
      height = 3
      metric = 0        // Chars
      borderStyle = 4        // Single
   endwith

endclass
class MYPUSHBUTTON(parentObj) of PUSHBUTTON(parentObj) custom
   with (this)
      height = 1.0909
      left = 3
      top = 8
      width = 13
      text = "Button"
      metric = 0        // Chars
      mousePointer = 13        // Hand
   endwith

endclass
class MYRADIOBUTTON(parentObj) of RADIOBUTTON(parentObj) custom
   with (this)
      transparent = true
      height = 1.0909
      left = 2
      top = 6
      width = 15.7143
      text = "Radiobutton"
      metric = 0        // Chars
      group = false
      value = false
   endwith

endclass
class MYTEXTLABEL(parentObj) of TEXTLABEL(parentObj) custom
   with (this)
      height = 1
      left = 1
      top = 1.5
      width = 17
      metric = 0        // Chars
      transparent = true
      text = "MyTextlabel"
      fontBold = true
      alignVertical = 1        // Middle
      alignHorizontal = 2        // Right
   endwith

endclass


class MYIMAGE(parentObj) of IMAGE(parentObj) custom
   with (this)
      height = 3
      left = 58
      top = 0.5
      width = 14
      metric = 0        // Chars
      alignment = 3     // Keep Aspect Stretch
   endwith

endclass

class MYDISABLEDENTRYFIELD(parentObj) of MYENTRYFIELD(parentObj) custom
   with (this)
      onGotFocus = {;this.keyboard( "{Home}" )}
      when = class::MYDISABLEDENTRYFIELD_WHEN
      height = 1
      left = 39
      top = 2.5
      width = 17
      colorNormal = "WindowText/cyan"
      colorHighLight = "White/Blue"
      value = "MyDisabledEntryfield"
      selectAll = false
      mousePointer = 12        // No

   endwith

   function MYDISABLEDENTRYFIELD_when(bOpen)
      
      return false
endclass


class MYTEXT(parentObj) of TEXT(parentObj) custom
   with (this)
      height = 1
      left = 38.8571
      top = 3.3636
      width = 16.7143
      metric = 0        // Chars
      text = "MyText"
      borderStyle = 10        // Etched Out
   endwith

endclass


