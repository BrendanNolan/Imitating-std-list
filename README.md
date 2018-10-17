# My (simplified version) of std::list 
I'd always meant to try to do something like writing my own imitation of a standard library class so I gave it a few hours and came up 
with a template class called `Lst` which has the basic functionality of the standard library `list` class, which I have called `Lst`. I implement all lists as 
linked lists. My code leaves leaves plenty to be desired and I will come back and clean it up at some point. In particular, I need to 
revisit the `const_iterator`s. I'm sure much can be done to improve speed, useability, functionality, everything. I'd be glad to hear from anyone about improvements or about rectifications of the many possible mistakes which may have crept in.

# If you are tempted for some thoroughly bizarre reason to try to use this class instead of the standard library list class, then:
don't. It would be a senseless and wreckless act.

# main.cpp 
This is just a quick example program showing some of the functionality of the `Lst` class. It outputs the following:

my_Lst.size(): 5  
10  
20  
30  
40  
50  
cpy_my_Lst.size(): 5  
10  
20  
30  
40  
50  
my_Lst.size(): 2  
20  
30  
