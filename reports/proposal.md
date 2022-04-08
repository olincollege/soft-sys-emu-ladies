# EMU Ladies: A Gameboy Emulator

by Annabelle Platt and Emma Mack

## Learnings From the Last Project

Annabelle: The last project was very good for me in terms of becoming more comfortable working with C, working with bitwise operations, starting to get a handle on common graphics libraries like SDL. I do think that the way I structured the project ended up not being as streamlined as it could have been. I also struggled a lot without having classes available. For this project I will utilize my new knowledge and expand my understanding of SDL. We will use C++, which is very similar to C but has classes, so this will make structuring for code-sharing significantly easier, but I will also probably suggest structuring the project differently than last time.

Emma: My first project was not as relevant technically to emulation. I mainly learned the importance of choosing a topic I’m excited about and being in a smaller group, so I’ve gotten off to a good start.

# Goals For This Project
We plan to make a Game Boy emulator that can run at least some Game Boy games (due to something known as ROM banking, discussed below, the percentage of existing games we will be able to run will vary depending on how far we get). The Game Boy system is significantly more complicated than the CHIP-8 from Annabelle's first project, so this is an ambitious goal. As a lower bound, we would like to emulate the CPU, GPU, and the graphics system, integrated in a main loop with basic timings. Once we have implemented this, we will start building up opcodes.

Our stretch goal is to implement simple ROM banking, which swaps out ROMS, allowing games to be larger than can be stored in the physical memory at any given time. This is necessary to run most games, but is complex and will be a big challenge for us. There are two types of memory banking, one more common than the other. Our shorter stretch goal will be the more common type, known as MCB1. The less common kind, MCB2, will be a bigger stretch goal.

Another stretch goal we have is to accept user input. With the help of SDL this should be achievable reasonably easily, but integrating it into the system may be more complex and thus is less of a priority. A super super stretch goal is including audio, but we most likely will not get to this point.

We would like to write the emulator in C++, for the reasons mentioned in Annabelle’s learning section.

## Learning Goals
Annabelle: I had such a fun time with my first emulator, and I want to further my knowledge by learning about a more advanced system. In particular I want to learn more about techniques for rendering graphics. The CHIP-8 has a very simple, black and white graphics system, but Game Boys have so much more going on, and I want to learn more about graphics on a processing level.

Emma: I am excited to understand more concretely how a simple(ish) program runs on a base level - work more directly with registers, program counters, decoding instructions, etc.

## Resources
We have found [a tutorial](http://imrannazar.com/GameBoy-Emulation-in-JavaScript:-The-CPU) on writing a Game Boy emulator in Javascript. This will be a good resource for us to have as a translation from purely conceptual to implementation, but will require us to do a lot of work ourselves to identify the best implementation solution in C++.

Here is [another tutorial](http://www.codeslinger.co.uk/pages/projects/gameboy.html) on writing a Game Boy emulator in C++. Code snippets are included in the tutorial, but there is lots of high level stuff that will allow us to figure things out on our own. A GitHub page is also linked, which will be useful if we get really stuck but which we will not rely on.

Another [tutorial](https://cturt.github.io/cinoop.html) in C, this one more high level conceptual and less in depth.

Finally, a [file](http://www.codeslinger.co.uk/pages/projects/gameboy/files/GB.pdf) documenting the Game Boy opcodes.

## First Steps
* Task for Emma: go through Annabelle’s chip 8 implementation in detail to get brought up to speed.
* Planning: Both sit down and figure out the overall system architecture.
    * Deliverable: a diagram.
* Step 1 for implementation: implement the CPU and barebones main loop. 
    * Deliverable: passing unit tests such as loading something into memory and checking that it is where it is supposed to be
* Step 2 for implementation: understand how GPU works and interfaces with the graphics system
    * Deliverable: diagram
