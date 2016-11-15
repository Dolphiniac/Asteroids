Known Issues

As far as I know, there aren't any issues with play, though when I first built my release .exe, it crashed, complaining about a heap error.  I never figured it out.  The game always ran as expected when started from VS, and when I rebuilt the solution several times, it stopped building the bad .exe.  No guarantees it won't do it again, though.

How to Use

W and up arrow cause the ship to accelerate in the direction it is pointing
A and left arrow cause the ship to rotate anticlockwise
D and right arroj cause the ship to rotate clockwise
P respawns the ship after its destruction
O spawns an asteroid in a random location with a random velocity
L destroys a random asteroid

Deep Learning

	While structuring my classes for this assignment, I noticed that I tend to build as I need features.  I understand that this is inescapable to some extent, as almost no-one can foresee everything he needs, but I think that I take it further than necessary.  I spent a grand total of 0.0f hours at the whiteboard beyond what was done in class, and the result was a willy-nilly shenanigans-y approach to problem solving.  The values I used for approximation of vertices contained several magic numbers, and once, I started to parameterize the Render function across the entire project before I realized that, not only was there an easier way to accomplish what I was trying to, but the action that I was taking would require even further destructuring to even work.
	I think that, in the future, I need to rely on my whiteboard more and plan what I will code well before I touch the keyboard.  Doing so should reduce the guesswork in implementation and afford more readability for my code and the overall structure of my projects.