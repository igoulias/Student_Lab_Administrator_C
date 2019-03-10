Kante ta parakatw test gia tis parametrous tou programmatos:

=====
Test1:
=====

./hw4 -x

To programma prepei na ektupwsei:

./hw4: illegal option -- x
Usage: ./hw4 [-d]


=====
Test2:
=====

./hw4 debug

To programma prepei na ektupwsei:

./hw4: illegal option -- debug
Usage: ./hw4 [-d]


=====
Test3:
=====

./hw4 -d 10

To programma prepei na ektupwsei:

./hw4: wrong number of arguments 3


=====
Test4:
=====

./hw4 -de

To programma prepei na ektupwsei:

./hw4: illegal option -- de
Usage: ./hw4 [-d]


=====
Test5:
=====

./hw4 -debug

To programma den tha ektupwsei tipota, alla an elegksete tin timi tis
metablitis debug prin ton termatismo tou programmatos, tha prepei na 
einai ON (pithanws 0 'i 1, analoga pws exete kataskeuasei to enum). 


=====
Test 6:
=====

./hw4 -d

To programma den tha ektupwsei tipota, alla an elegksete tin timi tis
metablitis debug prin ton termatismo tou programmatos, tha prepei na 
einai ON (pithanws 0 'i 1, analoga pws exete kataskeuasei to enum). 



=====
Test 7:
=====

./hw4

To programma den tha ektupwsei tipota, alla an elegksete tin timi tis
metablitis debug prin ton termatismo tou programmatos, tha prepei na 
einai OFF (pithanws 0 'i 1, analoga pws exete kataskeuasei to enum). 
