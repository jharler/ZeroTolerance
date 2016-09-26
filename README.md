# ZeroTolerance

#### What's the goal?
	This is a collection of single header file libraries for C/C++ development, with a focus on games.  The intent of this library is to make it easy enough to use in order to prototype quickly, but also allow for enough depth that a wide variety of games can be made with it.

#### What's with the name "Zero Tolerance?"
	I chose the name because my goal is to have a zero tolerance policy for slow, bloated software, slow compile times, and long development time.  I want this library to be fast in execution, fast in compile times and fast and easy to use.
	
#### Why single file headers?
	Anyone who has been developing software for any decent length of time has dealt with 3rd party libraries.  Most libraries need compiled and then linked into your program.  This can be easy or this can be incredibly painful, depending on your development environment and how well the library was put together.  With single file headers, using the library couldn't be more simple.  You drop the file into your project and #include it.

#### This is C++, so where are the classes and OOP?
	After using OOP for 20+ years, I've gotten to the point where I'm fed up with fighting with restrictions that are placed by "proper" OOP.  It's liberating to use a more C-like programming style and I'm finding it's much easier to design and implement things in.  I'm using C++ because there are a few features I like, such as function overloading and cleaner syntax, but for the most part, I'm avoiding the OOP features of C++ as well as templates (for compile time reasons).	
	
#### There are already libraries that do all of this, why are you reinventing the wheel?
	In order to effectively use a library, you need to understand how it works.  How better to understand how a library works than to develop it yourself?  I want to have the knowledge of how every aspect of my game engine works and the ability to change it if I don't like the way it works.  The primary motivation behind this library is to gain a deep understanding of every aspect of game engine development.  This library will evolve over the years and may eventually end up being extremely flexible and powerful.  Even if it never amounts to anything, I'm enjoying the work and learning a lot.
	
#### Why should I use your library over others?
	You probably shouldn't.  I'm not developing this library for you to use.  No offense intended, but I don't care if you use it or not.  If you do, great, if not, that's fine too.  I'm developing this library for me in order to have an easy to use, drop in solution for when I want to develop a game or tool.  It's designed to appeal to my personal preferences and features will be added, changed and maybe removed depending on my own personal needs.  I'll do my best not to break functionality, but that's not guaranteed.
	
#### Can you add a feature I need?
	Probably not, unless I need it too.  If you want a feature, feel free to add it.  If you are feeling generous and think your feature could benefit others, I'll look into adding it.
	
#### Special Thanks
	This library is inspired by the single file libraries by Sean Barrett.  Inspiration has also been drawn from Casey Muratori's Handmade Hero video series as well as Shawn McGrath's programming streams.
