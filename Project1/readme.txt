ΛΕΙΤΟΥΡΓΙΚΑ ΣΥΣΤΗΜΑΤΑ ΕΡΓΑΣΙΑ 1 
1) εχω θεωρήσει ότι κάθε entry αποτελεί διαφορετικό resource  συνεπώς για ΚΑΘΕ entry έχω χρησιμοποιήσει  δυο σημαφορους( mutex,wrt) και ένα counter (που μετράει πόσοι readers  βρίσκονται την εκάστοτε στιγμή στο entry)

2)εχω χρήσιμοποιησει unnamed POSIX semaphores



3) εχω δεσμεύσει 4 κομμάτια διαμοιραζομενης μνήμης ένα πίνακα από σημαφορους (mutex)  ένα πίνακα από σημαφορους (wrt) ,ένα πίνακα από counters , και την βάση δεδομένων με τα entries
Πίνακες χρήσιμοποιω επειδή όπως ανέφερα βλέπω κάθε entry σαν διαφορετικό resource

4) η έννοια  entry  υλοποιείται  από ένα structure  που εμπεριέχει  2 counters  έναν που αυξάνεται  κάθε φορά που κάποιος Peer γράφει και έναν που αυξάνεται κάθε φορά που κάποιος peer διαβάζει.

5) η δημιουργία και η αποδέσμευση  των shared memories γίνεται Στον coordinator στο πρόγραμμα peer που υλοποιήει  την ρουτίνα του peer (child of coordinator process) γίνεται απλά attach/detach


6)Ο coordinator κάνει τα εξής:δημιουργεί και αρχικοποιει  τα shared δεδομένα, παίρνει από την γραμμή εντολών  τον αριθμό των entries , των peers , τον αριθμό των επαναλήψεων και το ποσοστό των readers ( το ποσοστό των writers προκύπτει -> 100-ποσοστό readers ), δημιουργεί τα παιδιά τα οποία εκτελούν το peer.c Και δέχονται όσα ορίσματα χρειάζονται για αυτο  , στο τέλος διαβάζει την βάση δεδομένων με τα entries Και προσθέτει τα αθροίσματα readings/writings σε συνολικά αθροίσματα τα οποία εκτυπώνει


7) το peer.c κάνει τα εξής: τρέχει μια επανάληψη μέχρι τον αριθμό των επαναλήψεων  και  μέσω μιας συναρτήσης  που δέχεται ως ορισμα  τα ποσοστά read/write αποφασίζει ποια ενέργεια -ρουτίνα θα εκτελεστεί στην εκάστοτε επανάληψη,μετά εχω υλοποιήσει τις ρουτίνες του reader και το writer  όπως τις έχουμε διδαχτεί στο μάθημα όμως στην συγκεκριμένη περίπτωση κάθε entry έχει τις δικές του δομές συγχρονισμού  τις οποίες χρησιμοποιηω ανάλογα με την τυχαία επιλογή entry που γίνεται.Στο critical section αύξανω  τον counter του entry και σταματάω να μετράω το χρόνο αναμονής  για read και write αντίστοιχα επισης η διεργασια κοιμαται για εκθετικο χρονο ωστε να μεινει δεδμευμενο το entry(resource) για καποιο χρονο, για κάθε peer προφανώς όπως ζητείται καταγραφω πόσες φορές έγραψε πόσες διάβασε και τα τυπώνω  μαζί με το μέσο χρόνο αναμονής για read Η write αντίστοιχα

8)η σειρα με την οποια το προγραμμα coordinator δεχεται τα ορισματα ειναι η εξης: entries peers numberofrepetitions percentage_of_readers  



compile the programms :make
examples:
1)

./coordinator 10 80 100 70


Peer with process id->8809 total readings -> 80
Peer with process id ->8809 total writings-> 20
Peer with process id ->8809 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8809 average_waiting_for_writing-> 0.000013 sec 
Peer with process id->8775 total readings -> 73
Peer with process id ->8775 total writings-> 27
Peer with process id ->8775 average_waiting_for_reading -> 0.000006 sec
Peer with process id ->8775 average_waiting_for_writing-> 0.000017 sec 
Peer with process id->8793 total readings -> 70
Peer with process id ->8793 total writings-> 30
Peer with process id ->8793 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8793 average_waiting_for_writing-> 0.000018 sec 
Peer with process id->8816 total readings -> 72
Peer with process id ->8816 total writings-> 28
Peer with process id ->8816 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8816 average_waiting_for_writing-> 0.000015 sec 
Peer with process id->8748 total readings -> 65
Peer with process id ->8748 total writings-> 35
Peer with process id ->8748 average_waiting_for_reading -> 0.000005 sec
Peer with process id ->8748 average_waiting_for_writing-> 0.000018 sec 
Peer with process id->8750 total readings -> 70
Peer with process id ->8750 total writings-> 30
Peer with process id ->8750 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8750 average_waiting_for_writing-> 0.000021 sec 
Peer with process id->8747 total readings -> 70
Peer with process id ->8747 total writings-> 30
Peer with process id ->8747 average_waiting_for_reading -> 0.000009 sec
Peer with process id ->8747 average_waiting_for_writing-> 0.000018 sec 
Peer with process id->8822 total readings -> 77
Peer with process id ->8822 total writings-> 23
Peer with process id ->8822 average_waiting_for_reading -> 0.000006 sec
Peer with process id ->8822 average_waiting_for_writing-> 0.000015 sec 
Peer with process id->8751 total readings -> 77
Peer with process id ->8751 total writings-> 23
Peer with process id ->8751 average_waiting_for_reading -> 0.000009 sec
Peer with process id ->8751 average_waiting_for_writing-> 0.000019 sec 
Peer with process id->8790 total readings -> 75
Peer with process id ->8790 total writings-> 25
Peer with process id ->8790 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8790 average_waiting_for_writing-> 0.000024 sec 
Peer with process id->8777 total readings -> 76
Peer with process id ->8777 total writings-> 24
Peer with process id ->8777 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8777 average_waiting_for_writing-> 0.000021 sec 
Peer with process id->8753 total readings -> 69
Peer with process id ->8753 total writings-> 31
Peer with process id ->8753 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8753 average_waiting_for_writing-> 0.000019 sec 
Peer with process id->8801 total readings -> 76
Peer with process id ->8801 total writings-> 24
Peer with process id ->8801 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8801 average_waiting_for_writing-> 0.000025 sec 
Peer with process id->8779 total readings -> 75
Peer with process id ->8779 total writings-> 25
Peer with process id ->8779 average_waiting_for_reading -> 0.000006 sec
Peer with process id ->8779 average_waiting_for_writing-> 0.000012 sec 
Peer with process id->8786 total readings -> 72
Peer with process id ->8786 total writings-> 28
Peer with process id ->8786 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8786 average_waiting_for_writing-> 0.000015 sec 
Peer with process id->8824 total readings -> 72
Peer with process id ->8824 total writings-> 28
Peer with process id ->8824 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8824 average_waiting_for_writing-> 0.000023 sec 
Peer with process id->8807 total readings -> 72
Peer with process id ->8807 total writings-> 28
Peer with process id ->8807 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8807 average_waiting_for_writing-> 0.000014 sec 
Peer with process id->8823 total readings -> 72
Peer with process id ->8823 total writings-> 28
Peer with process id ->8823 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8823 average_waiting_for_writing-> 0.000015 sec 
Peer with process id->8818 total readings -> 78
Peer with process id ->8818 total writings-> 22
Peer with process id ->8818 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8818 average_waiting_for_writing-> 0.000023 sec 
Peer with process id->8746 total readings -> 70
Peer with process id ->8746 total writings-> 30
Peer with process id ->8746 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8746 average_waiting_for_writing-> 0.000017 sec 
Peer with process id->8796 total readings -> 78
Peer with process id ->8796 total writings-> 22
Peer with process id ->8796 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8796 average_waiting_for_writing-> 0.000019 sec 
Peer with process id->8755 total readings -> 68
Peer with process id ->8755 total writings-> 32
Peer with process id ->8755 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8755 average_waiting_for_writing-> 0.000021 sec 
Peer with process id->8788 total readings -> 64
Peer with process id ->8788 total writings-> 36
Peer with process id ->8788 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8788 average_waiting_for_writing-> 0.000010 sec 
Peer with process id->8759 total readings -> 69
Peer with process id ->8759 total writings-> 31
Peer with process id ->8759 average_waiting_for_reading -> 0.000006 sec
Peer with process id ->8759 average_waiting_for_writing-> 0.000018 sec 
Peer with process id->8752 total readings -> 64
Peer with process id ->8752 total writings-> 36
Peer with process id ->8752 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8752 average_waiting_for_writing-> 0.000014 sec 
Peer with process id->8749 total readings -> 74
Peer with process id ->8749 total writings-> 26
Peer with process id ->8749 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8749 average_waiting_for_writing-> 0.000018 sec 
Peer with process id->8804 total readings -> 72
Peer with process id ->8804 total writings-> 28
Peer with process id ->8804 average_waiting_for_reading -> 0.000006 sec
Peer with process id ->8804 average_waiting_for_writing-> 0.000013 sec 
Peer with process id->8815 total readings -> 72
Peer with process id ->8815 total writings-> 28
Peer with process id ->8815 average_waiting_for_reading -> 0.000009 sec
Peer with process id ->8815 average_waiting_for_writing-> 0.000010 sec 
Peer with process id->8808 total readings -> 66
Peer with process id ->8808 total writings-> 34
Peer with process id ->8808 average_waiting_for_reading -> 0.000006 sec
Peer with process id ->8808 average_waiting_for_writing-> 0.000016 sec 
Peer with process id->8758 total readings -> 65
Peer with process id ->8758 total writings-> 35
Peer with process id ->8758 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8758 average_waiting_for_writing-> 0.000018 sec 
Peer with process id->8810 total readings -> 73
Peer with process id ->8810 total writings-> 27
Peer with process id ->8810 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8810 average_waiting_for_writing-> 0.000012 sec 
Peer with process id->8795 total readings -> 72
Peer with process id ->8795 total writings-> 28
Peer with process id ->8795 average_waiting_for_reading -> 0.000006 sec
Peer with process id ->8795 average_waiting_for_writing-> 0.000016 sec 
Peer with process id->8776 total readings -> 77
Peer with process id ->8776 total writings-> 23
Peer with process id ->8776 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8776 average_waiting_for_writing-> 0.000019 sec 
Peer with process id->8798 total readings -> 72
Peer with process id ->8798 total writings-> 28
Peer with process id ->8798 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8798 average_waiting_for_writing-> 0.000014 sec 
Peer with process id->8765 total readings -> 72
Peer with process id ->8765 total writings-> 28
Peer with process id ->8765 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8765 average_waiting_for_writing-> 0.000019 sec 
Peer with process id->8787 total readings -> 75
Peer with process id ->8787 total writings-> 25
Peer with process id ->8787 average_waiting_for_reading -> 0.000006 sec
Peer with process id ->8787 average_waiting_for_writing-> 0.000020 sec 
Peer with process id->8821 total readings -> 73
Peer with process id ->8821 total writings-> 27
Peer with process id ->8821 average_waiting_for_reading -> 0.000009 sec
Peer with process id ->8821 average_waiting_for_writing-> 0.000017 sec 
Peer with process id->8774 total readings -> 74
Peer with process id ->8774 total writings-> 26
Peer with process id ->8774 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8774 average_waiting_for_writing-> 0.000017 sec 
Peer with process id->8756 total readings -> 70
Peer with process id ->8756 total writings-> 30
Peer with process id ->8756 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8756 average_waiting_for_writing-> 0.000009 sec 
Peer with process id->8813 total readings -> 70
Peer with process id ->8813 total writings-> 30
Peer with process id ->8813 average_waiting_for_reading -> 0.000006 sec
Peer with process id ->8813 average_waiting_for_writing-> 0.000019 sec 
Peer with process id->8819 total readings -> 69
Peer with process id ->8819 total writings-> 31
Peer with process id ->8819 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8819 average_waiting_for_writing-> 0.000015 sec 
Peer with process id->8799 total readings -> 64
Peer with process id ->8799 total writings-> 36
Peer with process id ->8799 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8799 average_waiting_for_writing-> 0.000017 sec 
Peer with process id->8768 total readings -> 68
Peer with process id ->8768 total writings-> 32
Peer with process id ->8768 average_waiting_for_reading -> 0.000006 sec
Peer with process id ->8768 average_waiting_for_writing-> 0.000013 sec 
Peer with process id->8761 total readings -> 69
Peer with process id ->8761 total writings-> 31
Peer with process id ->8761 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8761 average_waiting_for_writing-> 0.000014 sec 
Peer with process id->8770 total readings -> 73
Peer with process id ->8770 total writings-> 27
Peer with process id ->8770 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8770 average_waiting_for_writing-> 0.000020 sec 
Peer with process id->8785 total readings -> 69
Peer with process id ->8785 total writings-> 31
Peer with process id ->8785 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8785 average_waiting_for_writing-> 0.000013 sec 
Peer with process id->8792 total readings -> 74
Peer with process id ->8792 total writings-> 26
Peer with process id ->8792 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8792 average_waiting_for_writing-> 0.000016 sec 
Peer with process id->8784 total readings -> 78
Peer with process id ->8784 total writings-> 22
Peer with process id ->8784 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8784 average_waiting_for_writing-> 0.000017 sec 
Peer with process id->8805 total readings -> 71
Peer with process id ->8805 total writings-> 29
Peer with process id ->8805 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8805 average_waiting_for_writing-> 0.000012 sec 
Peer with process id->8767 total readings -> 71
Peer with process id ->8767 total writings-> 29
Peer with process id ->8767 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8767 average_waiting_for_writing-> 0.000018 sec 
Peer with process id->8771 total readings -> 64
Peer with process id ->8771 total writings-> 36
Peer with process id ->8771 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8771 average_waiting_for_writing-> 0.000017 sec 
Peer with process id->8820 total readings -> 72
Peer with process id ->8820 total writings-> 28
Peer with process id ->8820 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8820 average_waiting_for_writing-> 0.000012 sec 
Peer with process id->8754 total readings -> 72
Peer with process id ->8754 total writings-> 28
Peer with process id ->8754 average_waiting_for_reading -> 0.000006 sec
Peer with process id ->8754 average_waiting_for_writing-> 0.000014 sec 
Peer with process id->8769 total readings -> 62
Peer with process id ->8769 total writings-> 38
Peer with process id ->8769 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8769 average_waiting_for_writing-> 0.000016 sec 
Peer with process id->8803 total readings -> 68
Peer with process id ->8803 total writings-> 32
Peer with process id ->8803 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8803 average_waiting_for_writing-> 0.000016 sec 
Peer with process id->8791 total readings -> 74
Peer with process id ->8791 total writings-> 26
Peer with process id ->8791 average_waiting_for_reading -> 0.000006 sec
Peer with process id ->8791 average_waiting_for_writing-> 0.000020 sec 
Peer with process id->8781 total readings -> 71
Peer with process id ->8781 total writings-> 29
Peer with process id ->8781 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8781 average_waiting_for_writing-> 0.000018 sec 
Peer with process id->8772 total readings -> 65
Peer with process id ->8772 total writings-> 35
Peer with process id ->8772 average_waiting_for_reading -> 0.000010 sec
Peer with process id ->8772 average_waiting_for_writing-> 0.000014 sec 
Peer with process id->8780 total readings -> 69
Peer with process id ->8780 total writings-> 31
Peer with process id ->8780 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8780 average_waiting_for_writing-> 0.000016 sec 
Peer with process id->8764 total readings -> 76
Peer with process id ->8764 total writings-> 24
Peer with process id ->8764 average_waiting_for_reading -> 0.000005 sec
Peer with process id ->8764 average_waiting_for_writing-> 0.000017 sec 
Peer with process id->8797 total readings -> 72
Peer with process id ->8797 total writings-> 28
Peer with process id ->8797 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8797 average_waiting_for_writing-> 0.000022 sec 
Peer with process id->8812 total readings -> 74
Peer with process id->8782 total readings -> 73
Peer with process id ->8782 total writings-> 27
Peer with process id ->8782 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8782 average_waiting_for_writing-> 0.000018 sec 
Peer with process id ->8812 total writings-> 26
Peer with process id ->8812 average_waiting_for_reading -> 0.000006 sec
Peer with process id ->8812 average_waiting_for_writing-> 0.000014 sec 
Peer with process id->8763 total readings -> 68
Peer with process id ->8763 total writings-> 32
Peer with process id ->8763 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8763 average_waiting_for_writing-> 0.000015 sec 
Peer with process id->8794 total readings -> 64
Peer with process id ->8794 total writings-> 36
Peer with process id ->8794 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8794 average_waiting_for_writing-> 0.000015 sec 
Peer with process id->8806 total readings -> 68
Peer with process id ->8806 total writings-> 32
Peer with process id ->8806 average_waiting_for_reading -> 0.000006 sec
Peer with process id ->8806 average_waiting_for_writing-> 0.000015 sec 
Peer with process id->8778 total readings -> 73
Peer with process id ->8778 total writings-> 27
Peer with process id ->8778 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8778 average_waiting_for_writing-> 0.000018 sec 
Peer with process id->8802 total readings -> 74
Peer with process id ->8802 total writings-> 26
Peer with process id ->8802 average_waiting_for_reading -> 0.000006 sec
Peer with process id ->8802 average_waiting_for_writing-> 0.000020 sec 
Peer with process id->8789 total readings -> 72
Peer with process id->8760 total readings -> 66
Peer with process id ->8760 total writings-> 34
Peer with process id ->8760 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8760 average_waiting_for_writing-> 0.000017 sec 
Peer with process id->8817 total readings -> 69
Peer with process id ->8817 total writings-> 31
Peer with process id ->8817 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8817 average_waiting_for_writing-> 0.000010 sec 
Peer with process id ->8789 total writings-> 28
Peer with process id ->8789 average_waiting_for_reading -> 0.000008 sec
Peer with process id->8811 total readings -> 67
Peer with process id ->8811 total writings-> 33
Peer with process id ->8811 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8811 average_waiting_for_writing-> 0.000013 sec 
Peer with process id ->8789 average_waiting_for_writing-> 0.000017 sec 
Peer with process id->8757 total readings -> 66
Peer with process id ->8757 total writings-> 34
Peer with process id ->8757 average_waiting_for_reading -> 0.000009 sec
Peer with process id ->8757 average_waiting_for_writing-> 0.000008 sec 
Peer with process id->8825 total readings -> 73
Peer with process id ->8825 total writings-> 27
Peer with process id ->8825 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8825 average_waiting_for_writing-> 0.000016 sec 
Peer with process id->8814 total readings -> 67
Peer with process id ->8814 total writings-> 33
Peer with process id ->8814 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8814 average_waiting_for_writing-> 0.000011 sec 
Peer with process id->8762 total readings -> 64
Peer with process id ->8762 total writings-> 36
Peer with process id ->8762 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8762 average_waiting_for_writing-> 0.000013 sec 
Peer with process id->8766 total readings -> 65
Peer with process id ->8766 total writings-> 35
Peer with process id ->8766 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8766 average_waiting_for_writing-> 0.000012 sec 
Peer with process id->8783 total readings -> 64
Peer with process id ->8783 total writings-> 36
Peer with process id ->8783 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8783 average_waiting_for_writing-> 0.000013 sec 
Peer with process id->8800 total readings -> 62
Peer with process id ->8800 total writings-> 38
Peer with process id ->8800 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8800 average_waiting_for_writing-> 0.000018 sec 
Peer with process id->8773 total readings -> 56
Peer with process id ->8773 total writings-> 44
Peer with process id ->8773 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8773 average_waiting_for_writing-> 0.000009 sec 
 Coordinator scanned the shared memory and the results are :
 Total_readings-->>> 5637 
 Total_writings -->>> 2363 




2)
./coordinator 5 20 0 60





Peer with process id->8844 total readings -> 21
Peer with process id ->8844 total writings-> 9
Peer with process id ->8844 average_waiting_for_reading -> 0.000011 sec
Peer with process id ->8844 average_waiting_for_writing-> 0.000035 sec 
Peer with process id->8855 total readings -> 21
Peer with process id ->8855 total writings-> 9
Peer with process id ->8855 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8855 average_waiting_for_writing-> 0.000037 sec 
Peer with process id->8856 total readings -> 18
Peer with process id ->8856 total writings-> 12
Peer with process id ->8856 average_waiting_for_reading -> 0.000006 sec
Peer with process id ->8856 average_waiting_for_writing-> 0.000019 sec 
Peer with process id->8851 total readings -> 17
Peer with process id ->8851 total writings-> 13
Peer with process id ->8851 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8851 average_waiting_for_writing-> 0.000032 sec 
Peer with process id->8846 total readings -> 20
Peer with process id ->8846 total writings-> 10
Peer with process id ->8846 average_waiting_for_reading -> 0.000006 sec
Peer with process id ->8846 average_waiting_for_writing-> 0.000032 sec 
Peer with process id->8842 total readings -> 20
Peer with process id ->8842 total writings-> 10
Peer with process id ->8842 average_waiting_for_reading -> 0.000010 sec
Peer with process id ->8842 average_waiting_for_writing-> 0.000015 sec 
Peer with process id->8857 total readings -> 17
Peer with process id ->8857 total writings-> 13
Peer with process id ->8857 average_waiting_for_reading -> 0.000009 sec
Peer with process id ->8857 average_waiting_for_writing-> 0.000026 sec 
Peer with process id->8848 total readings -> 13
Peer with process id ->8848 total writings-> 17
Peer with process id ->8848 average_waiting_for_reading -> 0.000014 sec
Peer with process id ->8848 average_waiting_for_writing-> 0.000033 sec 
Peer with process id->8860 total readings -> 17
Peer with process id ->8860 total writings-> 13
Peer with process id ->8860 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8860 average_waiting_for_writing-> 0.000042 sec 
Peer with process id->8845 total readings -> 20
Peer with process id ->8845 total writings-> 10
Peer with process id ->8845 average_waiting_for_reading -> 0.000006 sec
Peer with process id ->8845 average_waiting_for_writing-> 0.000017 sec 
Peer with process id->8861 total readings -> 16
Peer with process id ->8861 total writings-> 14
Peer with process id ->8861 average_waiting_for_reading -> 0.000005 sec
Peer with process id ->8861 average_waiting_for_writing-> 0.000023 sec 
Peer with process id->8858 total readings -> 18
Peer with process id ->8858 total writings-> 12
Peer with process id ->8858 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8858 average_waiting_for_writing-> 0.000018 sec 
Peer with process id->8854 total readings -> 19
Peer with process id ->8854 total writings-> 11
Peer with process id ->8854 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8854 average_waiting_for_writing-> 0.000040 sec 
Peer with process id->8843 total readings -> 17
Peer with process id ->8843 total writings-> 13
Peer with process id ->8843 average_waiting_for_reading -> 0.000009 sec
Peer with process id ->8843 average_waiting_for_writing-> 0.000022 sec 
Peer with process id->8852 total readings -> 17
Peer with process id ->8852 total writings-> 13
Peer with process id ->8852 average_waiting_for_reading -> 0.000017 sec
Peer with process id ->8852 average_waiting_for_writing-> 0.000014 sec 
Peer with process id->8847 total readings -> 19
Peer with process id ->8847 total writings-> 11
Peer with process id ->8847 average_waiting_for_reading -> 0.000019 sec
Peer with process id ->8847 average_waiting_for_writing-> 0.000054 sec 
Peer with process id->8850 total readings -> 14
Peer with process id ->8850 total writings-> 16
Peer with process id ->8850 average_waiting_for_reading -> 0.000005 sec
Peer with process id ->8850 average_waiting_for_writing-> 0.000037 sec 
Peer with process id->8849 total readings -> 15
Peer with process id ->8849 total writings-> 15
Peer with process id ->8849 average_waiting_for_reading -> 0.000009 sec
Peer with process id ->8849 average_waiting_for_writing-> 0.000015 sec 
Peer with process id->8853 total readings -> 19
Peer with process id ->8853 total writings-> 11
Peer with process id ->8853 average_waiting_for_reading -> 0.000014 sec
Peer with process id ->8853 average_waiting_for_writing-> 0.000028 sec 
Peer with process id->8859 total readings -> 19
Peer with process id ->8859 total writings-> 11
Peer with process id ->8859 average_waiting_for_reading -> 0.000016 sec
Peer with process id ->8859 average_waiting_for_writing-> 0.000034 sec 
 Coordinator scanned the shared memory and the results are :
 Total_readings-->>> 357 
 Total_writings -->>> 243 





3)./coordinator 8 50 40 50




Peer with process id->8994 total readings -> 19
Peer with process id ->8994 total writings-> 21
Peer with process id ->8994 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8994 average_waiting_for_writing-> 0.000019 sec 
Peer with process id->8974 total readings -> 23
Peer with process id ->8974 total writings-> 17
Peer with process id ->8974 average_waiting_for_reading -> 0.000014 sec
Peer with process id ->8974 average_waiting_for_writing-> 0.000016 sec 
Peer with process id->8990 total readings -> 19
Peer with process id ->8990 total writings-> 21
Peer with process id ->8990 average_waiting_for_reading -> 0.000005 sec
Peer with process id ->8990 average_waiting_for_writing-> 0.000026 sec 
Peer with process id->8951 total readings -> 18
Peer with process id ->8951 total writings-> 22
Peer with process id ->8951 average_waiting_for_reading -> 0.000009 sec
Peer with process id ->8951 average_waiting_for_writing-> 0.000020 sec 
Peer with process id->8970 total readings -> 22
Peer with process id ->8970 total writings-> 18
Peer with process id ->8970 average_waiting_for_reading -> 0.000006 sec
Peer with process id ->8970 average_waiting_for_writing-> 0.000018 sec 
Peer with process id->8960 total readings -> 22
Peer with process id ->8960 total writings-> 18
Peer with process id ->8960 average_waiting_for_reading -> 0.000014 sec
Peer with process id ->8960 average_waiting_for_writing-> 0.000025 sec 
Peer with process id->8991 total readings -> 24
Peer with process id ->8991 total writings-> 16
Peer with process id ->8991 average_waiting_for_reading -> 0.000014 sec
Peer with process id ->8991 average_waiting_for_writing-> 0.000033 sec 
Peer with process id->8986 total readings -> 17
Peer with process id ->8986 total writings-> 23
Peer with process id ->8986 average_waiting_for_reading -> 0.000010 sec
Peer with process id ->8986 average_waiting_for_writing-> 0.000029 sec 
Peer with process id->8969 total readings -> 22
Peer with process id ->8969 total writings-> 18
Peer with process id ->8969 average_waiting_for_reading -> 0.000013 sec
Peer with process id ->8969 average_waiting_for_writing-> 0.000017 sec 
Peer with process id->8977 total readings -> 21
Peer with process id ->8977 total writings-> 19
Peer with process id ->8977 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8977 average_waiting_for_writing-> 0.000022 sec 
Peer with process id->8983 total readings -> 25
Peer with process id ->8983 total writings-> 15
Peer with process id ->8983 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8983 average_waiting_for_writing-> 0.000031 sec 
Peer with process id->8971 total readings -> 18
Peer with process id ->8971 total writings-> 22
Peer with process id ->8971 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8971 average_waiting_for_writing-> 0.000025 sec 
Peer with process id->8959 total readings -> 15
Peer with process id ->8959 total writings-> 25
Peer with process id ->8959 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8959 average_waiting_for_writing-> 0.000022 sec 
Peer with process id->8957 total readings -> 22
Peer with process id ->8957 total writings-> 18
Peer with process id ->8957 average_waiting_for_reading -> 0.000017 sec
Peer with process id ->8957 average_waiting_for_writing-> 0.000025 sec 
Peer with process id->8952 total readings -> 18
Peer with process id ->8952 total writings-> 22
Peer with process id ->8952 average_waiting_for_reading -> 0.000013 sec
Peer with process id ->8952 average_waiting_for_writing-> 0.000020 sec 
Peer with process id->9000 total readings -> 17
Peer with process id ->9000 total writings-> 23
Peer with process id ->9000 average_waiting_for_reading -> 0.000010 sec
Peer with process id ->9000 average_waiting_for_writing-> 0.000023 sec 
Peer with process id->8968 total readings -> 13
Peer with process id ->8968 total writings-> 27
Peer with process id ->8968 average_waiting_for_reading -> 0.000006 sec
Peer with process id ->8968 average_waiting_for_writing-> 0.000020 sec 
Peer with process id->8972 total readings -> 28
Peer with process id ->8972 total writings-> 12
Peer with process id ->8972 average_waiting_for_reading -> 0.000012 sec
Peer with process id ->8972 average_waiting_for_writing-> 0.000037 sec 
Peer with process id->8981 total readings -> 23
Peer with process id ->8981 total writings-> 17
Peer with process id ->8981 average_waiting_for_reading -> 0.000013 sec
Peer with process id ->8981 average_waiting_for_writing-> 0.000018 sec 
Peer with process id->8953 total readings -> 19
Peer with process id ->8953 total writings-> 21
Peer with process id ->8953 average_waiting_for_reading -> 0.000017 sec
Peer with process id ->8953 average_waiting_for_writing-> 0.000019 sec 
Peer with process id->8961 total readings -> 20
Peer with process id ->8961 total writings-> 20
Peer with process id ->8961 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8961 average_waiting_for_writing-> 0.000020 sec 
Peer with process id->8958 total readings -> 21
Peer with process id ->8958 total writings-> 19
Peer with process id ->8958 average_waiting_for_reading -> 0.000013 sec
Peer with process id ->8958 average_waiting_for_writing-> 0.000019 sec 
Peer with process id->8984 total readings -> 19
Peer with process id ->8984 total writings-> 21
Peer with process id ->8984 average_waiting_for_reading -> 0.000012 sec
Peer with process id ->8984 average_waiting_for_writing-> 0.000016 sec 
Peer with process id->8962 total readings -> 20
Peer with process id ->8962 total writings-> 20
Peer with process id ->8962 average_waiting_for_reading -> 0.000011 sec
Peer with process id ->8962 average_waiting_for_writing-> 0.000022 sec 
Peer with process id->8955 total readings -> 27
Peer with process id ->8955 total writings-> 13
Peer with process id ->8955 average_waiting_for_reading -> 0.000007 sec
Peer with process id ->8955 average_waiting_for_writing-> 0.000037 sec 
Peer with process id->8967 total readings -> 20
Peer with process id ->8967 total writings-> 20
Peer with process id ->8967 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8967 average_waiting_for_writing-> 0.000021 sec 
Peer with process id->8993 total readings -> 19
Peer with process id ->8993 total writings-> 21
Peer with process id ->8993 average_waiting_for_reading -> 0.000010 sec
Peer with process id ->8993 average_waiting_for_writing-> 0.000030 sec 
Peer with process id->8992 total readings -> 25
Peer with process id ->8992 total writings-> 15
Peer with process id ->8992 average_waiting_for_reading -> 0.000012 sec
Peer with process id ->8992 average_waiting_for_writing-> 0.000017 sec 
Peer with process id->8979 total readings -> 16
Peer with process id ->8979 total writings-> 24
Peer with process id ->8979 average_waiting_for_reading -> 0.000010 sec
Peer with process id ->8979 average_waiting_for_writing-> 0.000020 sec 
Peer with process id->8997 total readings -> 16
Peer with process id ->8997 total writings-> 24
Peer with process id ->8997 average_waiting_for_reading -> 0.000005 sec
Peer with process id ->8997 average_waiting_for_writing-> 0.000023 sec 
Peer with process id->8976 total readings -> 23
Peer with process id ->8976 total writings-> 17
Peer with process id ->8976 average_waiting_for_reading -> 0.000012 sec
Peer with process id ->8976 average_waiting_for_writing-> 0.000017 sec 
Peer with process id->8988 total readings -> 18
Peer with process id ->8988 total writings-> 22
Peer with process id ->8988 average_waiting_for_reading -> 0.000018 sec
Peer with process id ->8988 average_waiting_for_writing-> 0.000025 sec 
Peer with process id->8989 total readings -> 18
Peer with process id ->8989 total writings-> 22
Peer with process id ->8989 average_waiting_for_reading -> 0.000013 sec
Peer with process id ->8989 average_waiting_for_writing-> 0.000025 sec 
Peer with process id->8965 total readings -> 17
Peer with process id ->8965 total writings-> 23
Peer with process id ->8965 average_waiting_for_reading -> 0.000009 sec
Peer with process id ->8965 average_waiting_for_writing-> 0.000017 sec 
Peer with process id->8975 total readings -> 18
Peer with process id ->8975 total writings-> 22
Peer with process id ->8975 average_waiting_for_reading -> 0.000016 sec
Peer with process id ->8975 average_waiting_for_writing-> 0.000021 sec 
Peer with process id->8998 total readings -> 24
Peer with process id ->8998 total writings-> 16
Peer with process id ->8998 average_waiting_for_reading -> 0.000014 sec
Peer with process id ->8998 average_waiting_for_writing-> 0.000019 sec 
Peer with process id->8996 total readings -> 16
Peer with process id ->8996 total writings-> 24
Peer with process id ->8996 average_waiting_for_reading -> 0.000019 sec
Peer with process id ->8996 average_waiting_for_writing-> 0.000019 sec 
Peer with process id->8980 total readings -> 19
Peer with process id ->8980 total writings-> 21
Peer with process id ->8980 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8980 average_waiting_for_writing-> 0.000031 sec 
Peer with process id->8956 total readings -> 21
Peer with process id ->8956 total writings-> 19
Peer with process id ->8956 average_waiting_for_reading -> 0.000014 sec
Peer with process id ->8956 average_waiting_for_writing-> 0.000016 sec 
Peer with process id->8985 total readings -> 18
Peer with process id ->8985 total writings-> 22
Peer with process id ->8985 average_waiting_for_reading -> 0.000017 sec
Peer with process id ->8985 average_waiting_for_writing-> 0.000025 sec 
Peer with process id->8966 total readings -> 19
Peer with process id ->8966 total writings-> 21
Peer with process id ->8966 average_waiting_for_reading -> 0.000016 sec
Peer with process id ->8966 average_waiting_for_writing-> 0.000019 sec 
Peer with process id->8954 total readings -> 17
Peer with process id ->8954 total writings-> 23
Peer with process id ->8954 average_waiting_for_reading -> 0.000013 sec
Peer with process id ->8954 average_waiting_for_writing-> 0.000017 sec 
Peer with process id->8963 total readings -> 18
Peer with process id ->8963 total writings-> 22
Peer with process id ->8963 average_waiting_for_reading -> 0.000015 sec
Peer with process id ->8963 average_waiting_for_writing-> 0.000015 sec 
Peer with process id->8978 total readings -> 19
Peer with process id ->8978 total writings-> 21
Peer with process id ->8978 average_waiting_for_reading -> 0.000017 sec
Peer with process id ->8978 average_waiting_for_writing-> 0.000021 sec 
Peer with process id->8987 total readings -> 23
Peer with process id ->8987 total writings-> 17
Peer with process id ->8987 average_waiting_for_reading -> 0.000012 sec
Peer with process id ->8987 average_waiting_for_writing-> 0.000022 sec 
Peer with process id->8982 total readings -> 25
Peer with process id ->8982 total writings-> 15
Peer with process id ->8982 average_waiting_for_reading -> 0.000010 sec
Peer with process id ->8982 average_waiting_for_writing-> 0.000028 sec 
Peer with process id->8999 total readings -> 17
Peer with process id ->8999 total writings-> 23
Peer with process id ->8999 average_waiting_for_reading -> 0.000013 sec
Peer with process id ->8999 average_waiting_for_writing-> 0.000025 sec 
Peer with process id->8964 total readings -> 15
Peer with process id ->8964 total writings-> 25
Peer with process id ->8964 average_waiting_for_reading -> 0.000010 sec
Peer with process id ->8964 average_waiting_for_writing-> 0.000022 sec 
Peer with process id->8973 total readings -> 20
Peer with process id ->8973 total writings-> 20
Peer with process id ->8973 average_waiting_for_reading -> 0.000012 sec
Peer with process id ->8973 average_waiting_for_writing-> 0.000019 sec 
Peer with process id->8995 total readings -> 21
Peer with process id ->8995 total writings-> 19
Peer with process id ->8995 average_waiting_for_reading -> 0.000008 sec
Peer with process id ->8995 average_waiting_for_writing-> 0.000020 sec 
 Coordinator scanned the shared memory and the results are :
 Total_readings-->>> 994 
 Total_writings -->>> 1006 






