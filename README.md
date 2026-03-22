# Panda's Drivers
Repositry of various embedded peripheral drivers

## guidelines
generally these drivers will include stdio.h or stdlib.h or stdint.h from some vendor. 
these drivers should be written such that the includes could change source for a vendor and still work fine. 

there should be no other dependancies except the basics of the C language, and the standard embedded type names

such as:
- uint32_t
- int16_t
- etc. 

