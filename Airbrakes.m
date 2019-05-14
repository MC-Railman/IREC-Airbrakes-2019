%% Drag Code for Air Brake Activation
% By: Harrison Lewis

% The purpose of this code is to analyze and assess the proper time to
% activate the air brakes in order to have the rocket reach its desired
% apogee. The program will require the drag coefficients of the rocket with
% the air brakes active and closed, the desired height, and standard
% dimensions of the rocket and environment.

%% Warnings and Concerns

%It should be known that this code is utilizing a constant mass assumption,
%and as such, it is recommended to begin the loop post burnout. Again, the
%mass entered should the dry rocket mass. This loop is only as accurate as
%the data given from the available hardware sensors. The activation points
%must be adjusted based on preference to tolerance and by safety factor for
%reaching desired height.

%% Defining Variables

% A:   Surface area of brake fins ft^2
% Cdc: Coefficient of Drag with closed fins
% Cdo: Coefficient of Drag with open fins
% d:   Distance left to be traveled ft
% g:   Acceleration due to gravity ft/s^2
% h:   The height given by the altimeter ft
% hf:  Final projected height of the rocket ft
% hi:  Initial height ft
% ho:  Final desired height ft
% m:   Mass of rocket slugs
% p:   Density of air slugs/ft^3
% t:   Established vector for time s
% v:   Current velocity of the rocket ft/s
% vi:  Initial velocity ft/s
% vo:  Final velocity ft/s

%% Establishing Known Values
%These values should be known and stay relatively constant through the
%development of the rocket. These must be changed manually if a change in
%the rocket is made.

g=32.17;         %ft/s^2
hi=0;            %ft
vi=0;            %ft/s
A=.25;           %ft^2
Cdo=1;           %No unit
Cdc=.75;         %No unit
t=0.1;           %Seconds, this is based on how quickly the loop will input new data
h=0;             %ft Current height
hf=0;            %ft final projected rocket height (initial input)
v=0;             %ft/s Current velocity of rocket
%% Establishing Input Values
%These values will be requested each time the code is run. These are likely
%to change based on what is desired from the team and updates made to the
%rocket.

m=input('Input mass of rocket in slugs');   %slugs
ho=input('Input the desired apogee of the rocket in feet'); %ft
d= ho-hi;       %ft   

%% Finding the Values
%As the rocket launches, these values will need to be updated. Using an
%altimeter, the height will be adjusted, but for the sake of having this
%code work, I will do a simplified vector that will replace the information
%from the altimeter.

vo=d*2/t-vi;
vi=vo;  %each time the loop runs, the final velocity from the previous run will become the initial velocity.

%%  Establishing Overshoot Loop
%This loop will run until the projected apogee of the rocket exceeds the
%desired height of the rocket. With this in mind, if the rocket is never
%projected to reach desired apogee, the brakes will never deploy and
%further hinder the height. However, if the rocket is projected to exceed
%desired height, a secondary loop will activate in order to find the best
%time to activate the brakes. This loop will constantly calculate the
%projected height of the rocket using the work balance equation and
%utilize the changing environment.

while hf<ho  %until the final height of the rocket is above the desired apogee (ho) this loop will continue to run
    hi=h;
    h=input('Input current height of rocket'); %This manual input will act for the altimeter.
    vi=v; %each time the loop runs, the current velocity from the previous run will become the initial velocity. 
    d=ho-h;  %h uses the altimeter height, this is the distance left to reach, supplying d for how much drag will be instigated
    %We need to establish a changing air density. Using an altimeter, this
    %will already be known, however, here, will use use engineeringtoolbox
    %references based on the h of the rocket.
    if h<5000
        p=23.77*10^-4 %slugs/ft^3
    elseif h<10000
        p=20.48*10^-4 %slugs/ft^3
    else 
        p=17.56*10^-4 %slugs/ft^3
    end
    % We can also do an input prompt here, similar to the height prompt,
    % but I'm just exploring options while also saving input processing
    % time.
    hf=(.5*m*vi^2-d*Cdc*p*vi^2*A/2)/(m*g); %Energy Balance equation, assuming final velocity is zero and initial height is zero
    v=(h-hi)/t    %current velocity using the change of height divided by the time interval ft/s
    end

%Signal for secondary loop (mainly to check if it will activate
disp('Activate second loop')

%% Activation Loop

%Ok, so assuming we made it this far, yay, the brakes are going to be
%activated! This loop will run its course with an updated Coefficient of
%Drag based on the rocket with the air brake fins activated. By running the
%while loop until the project height is close to the desired apogee, this
%loop will optimize the instant of activation.

while hf<=ho 
    %The earlier the brakes activate, the lower the rocket will go, so 
    %this loop will only end when the rocket will reach or slightly exceed 
    %the desired height.
    %NOTE: IF WANTING A TIGHTER TOLERANCE, IT IS ADVISED TO INPUT A SLIGHTLY
    %LOWER ho ex. hf<=(ho-20)
    hi=h;
    h=input('Input current height of rocket');
    vi=v;
    d=ho-h;
    if h<5000
        p=23.77*10^-4 %slugs/ft^3
    elseif h<10000
        p=20.48*10^-4 %slugs/ft^3
    else 
        p=17.56*10^-4 %slugs/ft^3
    end
    hf=(.5*m*vi^2-d*Cdo*p*vi^2*A/2)/(m*g);
    v=(h-hi)/t
    %This loop will keep running until the projected height reaches the
    %desired apogee, otherwise, the brakes will not open and the rocket
    %will go as high as possible without the brakes. This is intended as a
    %safety deligation.
    end

%% Activating Brakes

%Welp, it happened, its time to activate the brakes. The rocket is
%projected to peak at the closest point possible for the desired apogee
%based on the activation. Hooray!

disp('ACTIVATE BRAKES, I REPEAT ACTIVATE BRAKES')

