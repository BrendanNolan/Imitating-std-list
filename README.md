# List_container 
I'd always meant to try to do something like writing my own imitation of a standard library class so I gave it a few hours and came up 
with a template class called `Lst` which has the basic functionality of the standard library `list` class, which I have called `Lst`. I implement all lists as 
linked lists. My code leaves leaves plenty to be desired and I will come back and clean it up at some point. In particular, I need to 
revisit the `const_iterator`s. I'm sure much can be done to improve speed, useability, functionality, everything. I'd be glad to hear from anyone about improvements or about rectifications of the many possible mistakes which may have crept in.

# If you are tempted for some thoroughly bizarre reason to try to use this class instead of the standard library list class, then:
Take a deep breath and walk away. It's the worst idea you've ever had. 

# main.cpp 
This is just a quick example program showing some of the functionality of the `Lst` class.