/*
   COPYDATA.PRG
   
   Author: Ken Mayer

   A simple program specifically created for APPTUTOR
   (Application Tutorial) to copy the data to the tables 
   created by the person using the tutorial, so that 
   they do not have to create data for this application ...

   USAGE: Copy this to the directory that the tables
   were created in (i.e., C:\DB2KTUTORIAL\TABLES ) for
   the tutorial. Double-click the icon in the navigator.
   That's all you should have to do, unless an error
   occurs ...

   ***********************************************
   DEPENDENCIES: BFILE.CC, DBF7FILE.CC
     these files must be in the same directory as
     this program and the tables!!
   ***********************************************

*/

close database
clear

/*
   Check to see if we even have the tables necessary
   to do anything ... this program is only supposed
   to be used at the end of the second part of the
   tutorial project ...
*/
if not file( "INVENTORY.DBF" )
   msgbox( "You need to create the tables necessary "+;
           "for the tutorial before you try running "+;
           "this program. It's going to blow up otherwise ...",;
           "Won't work!", 16 )
   return
endif

/*
   Empty the tables out, in case tester has tinkered ...
*/
? "Emptying Tables (in case you added some ...)"
d = _app.databases[1]
d.emptyTable( "country" )
d.emptyTable( "customer" )
d.emptyTable( "inventory" )
d.emptyTable( "invoice" )
d.emptyTable( "lineitem" )
d.emptyTable( "state" )
d.emptyTable( "supplier" )

/*
   Deal with autoincrement -- if user added any rows,
   the autoincrement value will be wrong, and when
   we copy data from MUGS, we will have incorrect
   data (the id fields that link tables won't 
   match) ...
*/
? "Setting AutoIncrement values to 1"
set procedure to dbf7file.cc additive
b = new dbf7file( "customer.dbf" )
b.SetNextAutoIncValue("customer id", 1)

b = new dbf7file( "inventory.dbf" )
b.SetNextAutoIncValue("item id", 1)

b = new dbf7file( "invoice.dbf" )
b.SetNextAutoIncValue("invoice id", 1)

b = new dbf7file( "supplier.dbf" )
b.SetNextAutoIncValue("supplier id", 1)

b=null
close procedure dbf7file.cc
close procedure bfile.cc

// --------------------------------------------------------
// append the data (yes, we're cheating and using the XDML,
// but this way I can be sure of getting all the data!!!
// There appears to be an issue with the UpdateSet object
// and referential integrity ...):

? "Copying country data"
use country
append from country1.dbf
? "Copying customer data"
use customer
append from customer1.dbf
? "Copying inventory data"
use inventory
append from inventory1.dbf
? "Copying invoice data"
use invoice
append from invoice1.dbf
? "Copying lineitem data"
use lineitem
append from lineitem1.dbf
? "Copying state data"
use state
append from state1.dbf
? "Copying supplier data"
use supplier
append from supplier1.dbf
use

msgbox( "The tables should now have data in them, and you "+;
        "can move on in the tutorial project ...","Done", 64 )

/*
   End of Program; CopyData.prg
*/
