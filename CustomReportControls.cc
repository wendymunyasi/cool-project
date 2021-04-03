/*
    CustomFormControls.CC
    Author...: Ken Mayer
    Date.....: January 24, 1999

    These controls are a subset of the Custom Form Controls
    found in REPCNTL.CC in the dUFLP 

    Controls included are:

    kmTitleText1 -- A larger font text object used for a main title
                    on a report
    kmDateText   -- prints "Date:" followed by the current date

    kmStandardText -- base class for most of the following
                    text controls
    kmFieldText  -- Used to display actual field, need to set
                    the codeblock appropriately ...
    kmFieldHeadingText -- Bold text used to display a field
                        heading
    kmRectangleShape -- base class for other shape controls
       
    kmLine       -- basic line object

    **************************************************************
    Note I have no containers. From Charles Overbeck (on the
    development team for VdBASE 7.x):

    "The container cannot have a band as its parent.  The problem 
    is that the container is currently a windowed control, and 
    we don't allow windowed controls in bands (because the band 
    is potentially rendered multiple times, but there is only 
    one window--so how do you display one window several times?)."
    **************************************************************

*/


/*
   Standard text placed on the pageTemplate, appears as a
   header at the top of each page. (If unclear on any
   of the properties, see onLine help)
*/
class kmTitleText1(parentObj) of TEXT(parentObj) custom
   with (this)
      alignHorizontal        := 1	// Center
      alignVertical          := 1	// Middle
      border                 := false
      borderStyle            := 0 // default
      colorNormal            := "BLACK"
      fixed                  := false
      fontBold               := false
      fontItalic             := true
      fontName               := "Arial"
      fontSize               := 18
      fontStrikeout          := false
      fontUnderline          := false
      height                 := 0.3229
      leading                := 0.00
      marginHorizontal       := 0.00
      marginVertical         := 0.00
      metric                 := 3	// Inches
      prefixEnable           := false
      rotate                 := 0 // normal
      text                   := "This is a Main Report Title"
      tracking               := 0.00
      trackJustifyThreshhold := 0.00
      transparent            := true
      variableHeight         := false
      verticalJustifyLimit   := 0.00
      width                  := 3.5313
      wrap                   := true
   endwith

endclass

/*
   this is a standard text control that most of the others
   here are subclassed from ...
*/
class kmStandardText(parentObj) of TEXT(parentObj) custom
   with (this)
      alignHorizontal        := 0 // Left
      alignVertical          := 0 // Top
      border                 := false
      borderStyle            := 0 // default
      colorNormal            := "BLACK"
      fixed                  := false
      fontBold               := false
      fontItalic             := false
      fontName               := "Arial"
      fontSize               := 10
      fontStrikeout          := false
      fontUnderline          := false
      height                 := 0.18
      leading                := 0.00
      marginHorizontal       := 0.00
      marginVertical         := 0.00
      metric                 := 3	// Inches
      prefixEnable           := false
      rotate                 := 0 // normal
      text                   := "kmStandardText"
      tracking               := 0.00
      trackJustifyThreshhold := 0.00
      transparent            := true
      variableHeight         := false
      verticalJustifyLimit   := 0.00
      width                  := 1.1667
   endwith
endclass


/*
   Basic text and date combination ... nice thing about
   VdBASE 7 is the auto casting of types, so that
   we can display the date without having to add the DTOC()
   function ... of course, if you want more detail, like
   character month, and such, you would need to code for
   it ...
*/
class kmDateText(parentObj) of kmStandardText(parentObj) custom
   with (this)
      alignHorizontal        := 1 // center
      alignVertical          := 1	// Middle
      text                   := {||"Date: "+date()}
   endwith
endclass

/* 
   want the text on this one to be bold and line up on the
   right side ...
*/
class kmFieldHeadingText(parentObj) of kmStandardText(parentObj) custom
   with (this)
      height          := 0.18
      width           := 0.75
      alignHorizontal := 2 // Right
      text            := "FieldHeading: "
      fontBold        := true
   endwith
endclass

/*
    FieldText: Suggestion -- place this on the report,
    and then bring up the text property in the codeblock
    editor. Standard text controls are "datalinked" by
    the TEXT codeblock:

      form.streamSource1.rowset.fields["fieldName"].value

    So, replace "field codeblock" with the above,
    and of course insert the proper fieldName, and
    you should be fine.

    In addition, you may want to pass the field through
    the string object, particularly if you have
    the potential of nulls and you are doing a
    calculated field, so your codeblock *might* look
    like:

     new String( form.streamSource1.rowset.fields["fieldName"].value ) +;
     " " + ;
     new String( form.streamSource1.rowset.fields["fieldName2"].value )

*/
class kmFieldText(parentObj) of kmStandardText(parentObj) custom
   with (this)
      width           := 1.2188
      variableHeight  := true
      // This needs to be modified for each object ... obviously
      text            := {||"field codeblock"}
   endwith

endclass


/*
   The standard Rectangle doesn't function properly -- this is a
   bug in the software -- if you render the report on screen,
   a rectangle works like you might expect. However, if you
   print it (at least to the several HP Laserjets I've tried
   it with), the rectangle will print offset (up/left) from
   where it should. The shape object, however, doesn't do this --
   so you can generate a rectangle using the shape and have it
   work properly.
*/

// Start with a base shape class:
class kmRectangleShape(parentObj) of SHAPE(parentObj) custom
   with (this)
      width       := 2.9479
      height      := 0.4063
      metric      := 3	// Inches
      colorNormal := "BLACK/WHITE"
      penStyle    := 0 // Solid
      penWidth    := 2
      shapeStyle  := 1	// Rectangle
   endwith
endclass

/*
    Basic line, but I set the width to 2, because
    when photocopying, I've found that a width
    of 1 often gets lost ...
*/
class kmLine(parentObj) of LINE(parentObj) custom
   with (this)
      left            := 0
      right           := 4.4722
      top             := 0
      bottom          := this.top
      fixed           := false
      width           := 1
      metric          := 3	// Inches
      colorNormal     := "Black"
   endwith

endclass


