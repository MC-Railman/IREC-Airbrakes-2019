Drag Code for Air Brake Activation

The purpose of this code is to analyze and assess the proper time to
activate the air brakes in order to have the rocket reach its desired
apogee. The program will require the drag coefficients of the rocket with
the air brakes active and closed, the desired height, and standard
dimensions of the rocket and environment.

Warnings and Concerns

It should be known that this code is utilizing a constant mass assumption,
and as such, it is recommended to begin the loop post burnout. Again, the
mass entered should the dry rocket mass. This loop is only as accurate as
the data given from the available hardware sensors. The activation points
must be adjusted based on preference to tolerance and by safety factor for
reaching desired height.

Defining Variables

A:   Surface area of brake fins ft^2
Cdo: Coefficient of Drag with open fins
Cdc: Coefficient of Drag with closed fins
d:   Distance left to be traveled ft
g:   Acceleration due to gravity ft/s^2
h:   The height given by the altimeter ft
hf:  Final projected height of the rocket ft
hi:  Initial height ft
ho:  Final desired height ft
m:   Mass of rocket slugs
p:   Density of air slugs/ft^3
t:   Established vector for time s
v:   Current velocity of the rocket ft/s
vi:  Initial velocity ft/s
vo:  Final velocity ft/s

Authors: 
Harrison Lewis,
Matthew Reppa,
Ryan Hannaford,
Tristan Hess

