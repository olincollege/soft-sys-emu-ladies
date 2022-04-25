# EMU Ladies: A Gameboy Emulator

by Annabelle Platt and Emma Mack

## Goals For This Project
We plan to make a Game Boy emulator that can run the Tetris home screen. As a lower bound, we would like to emulate the CPU and the graphics system, integrated in a main loop with basic timings. We have implemented most of this, and once done, we will start implementing the necessary opcodes.

Our stretch goal, which we will not reach, is to implement simple ROM banking, which swaps out ROMS, allowing games to be larger than can be stored in the physical memory at any given time. This is not necessary for Tetris, but is necessary for most Gameboy games. 


## Learning Goals
Annabelle: I had such a fun time with my first emulator, and I want to further my knowledge by learning about a more advanced system. In particular I want to learn more about techniques for rendering graphics. The CHIP-8 has a very simple, black and white graphics system, but Game Boys have so much more going on, and I want to learn more about graphics on a processing level.

Emma: I am excited to understand more concretely how a simple(ish) program runs on a base level - work more directly with registers, program counters, decoding instructions, etc.

## Getting Started
So far we have implemented the CPU, and are nearly done with a minimalist version of the graphics system. The way graphics are rendered on the Gameboy is quite complex and interesting, taking advantage of every possible bit of the system’s small resources. 

A significant portion of this project for us has been parsing documentation, watching videos, and otherwise researching how the system, and in particular the graphics system, works. While our code is not extensive so far, we have both learned a ton about how these systems operate. Annabelle feels she has really built on her baseline understanding of emulators from her previous project in learning about the more complex architecture, moving pieces, and memory-saving hacks in Gameboy development. Emma feels she has already learned more than in her previous project about how low-level systems operate, which was her learning goal for this project.

In short, we’re both having a very good time and learning a ton, although our code is not necessarily very complex. 

## Resources

We are still using the resources we found at the beginning of the project, particularly the codeslinger tutorial, listed first here.

[A tutorial](http://www.codeslinger.co.uk/pages/projects/gameboy.html) on writing a Game Boy emulator in C++. We have been referencing the code, but never copying and always ensuring a full understanding and making our own judgment calls. A GitHub page is also linked, which will be useful if we get really stuck but which we will not rely on.
We have found [a tutorial](http://imrannazar.com/GameBoy-Emulation-in-JavaScript:-The-CPU) on writing a Game Boy emulator in Javascript. This has been a good resource for us to have as a translation from purely conceptual to implementation, but will require us to do a lot of work ourselves to identify the best implementation solution in C++.

Another [tutorial](https://cturt.github.io/cinoop.html) in C, this one more high level conceptual and less in depth.

Also, a [file](http://www.codeslinger.co.uk/pages/projects/gameboy/files/GB.pdf) documenting the Game Boy opcodes.

We also have been referencing [an emulator we found on GitHub](https://github.com/jgilchrist/gbemu), which strongly utilizes classes in C++. We have found it helpful to see how someone broke up their classes to emulate a Gameboy, but we have been weighing options and making our own judgment calls on how we actually want to structure our architecture.

## What's Next

Here is our to-do list that will bring us to our goal of emulating the Tetris home screen.

* Wrap our draw_scanline() function in an update_graphics() function that will draw all scanlines with the correct timing
    * DOD: to be honest, this one is really hard to isolate and test, it’s more of a take our best stab and debug on integration situation. So it’s done when we think the function does what we want. 
* Write a load_ROM() function that loads the Tetris game into memory
    * DOD: being able to successfully identify opcodes when running the emulator, which will mean the ROM is loaded correctly. We can also check different locations in memory to make sure they are not empty and contain the correct values
* Flesh out the main loop so that it grabs opcodes and calls the corresponding functions (a switch statement)
    * DOD: write the switch statement
* Implement as few opcodes as possible to be able to display the Tetris home screen. We are planning on writing a function that will check if the next opcode is implemented and print a note for us if it is not.
    * DOD: can see the home screen


