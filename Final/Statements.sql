--Database:DBASETUTORIAL
SELECT Customer."Customer ID", Customer."Last Name", Customer."First Name", Customer.Phone, Customer.Street1, Customer.Street2, Customer.City, Customer."State ID", Customer.Postal, Customer."Country ID", Invoice."Invoice ID", Invoice."Customer ID", Invoice."Order Date", Invoice."Pay Type", Invoice."Card Number", Invoice."Card Exp", Invoice."Card Name", Invoice."Check Number", Lineitem."Invoice ID", Lineitem."Item ID", Lineitem.Qty, Customer.Comment
FROM "customer.dbf" Customer
   INNER JOIN "invoice.dbf" Invoice
   ON  (Customer."Customer ID" = Invoice."Customer ID")  
   INNER JOIN "lineitem.dbf" Lineitem
   ON  (Invoice."Invoice ID" = Lineitem."Invoice ID")  
ORDER BY Customer."Last Name", Customer."Customer ID", Invoice."Order Date"