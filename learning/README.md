# Serenity
## The Learning Process

Here you will find info about every bit of progress I do along the way.

### Week 01:

*The first week had a pretty rough start, since the vision of the project
changed a lot on the go. Info about the first week was written in the
second week of the project.*

**Here are the core points of the week that were achieved following the plan:**

- The main idea was to understand the n-body problem. One of the best ways
for me to do that is via pen and paper plus online resources. I even learned
new things involving the center of mass and why using it helps with being
exact with the problem. I learned other new things as well involving the
problem, but the interesting things are stated in the paper.

- With the help of **Claude Opus 5.5** I managed to generate a
[`PDF`](./simulation/doua-corpuri.pdf) document coming from
[`LaTeX`](./simulation/src/doua-corpuri.tex) that explains the core
theoretical part of `this` project.

- It's important to understand that paper before diving into code and hardware
afterwards. That document had seen many forms but in the end I think that my
instructions induced a good written paper. I believe in it.

- I love mathematical rigour. I love physics. Hopefully you can see that coming
from the paper.

- The [`C`](./simulation/src/orbita.c) code follows along the paper nicely,
it's easy to understand and **implement from scratch**. I wrote the code from
scratch following along the paper, it comes out nicely. The review was done
using `AI`, I believe that is necessary in order to get construct *code of
quality*.

- Here is how you run the code on a typical system that has a `Linux` kernel
with `GNU` tools:

*Make sure you are in the same directory as this README:*

```bash
$ cd simulation/src/
$ gcc -Wall -Wextra orbita.c -o orbita -lm
$ ./orbita
```

**The first week was full of progress!**

### Week 02:

*This session will be done in two days probably.*

**Here are the core points of the week that were achieved following the plan:**

- I first searched for what `CSV` files are and then what `Matplotlib` is.

- Next, we need to filter the output from the C program to a an actual `CSV`
file. I could have modified the C code to do that more directly but practicing
`Bash` together with searching insde [`man pages`] and not using AI directly
makes me feel much better. Here is how I generate the `CSV` file:

*Make sure you are in the right directory as in the last session!*

```bash
$ ./orbita | grep '(x, y)' | cut -d " " -f 5,6 | tr "()" " " | tr -d " " > points.csv # Looks scary, I know :)
```

- Next I wrote the Python code that will generate the plot. This was done with
help from AI but I wrote the code from scratch after understanding what it
does, it's not hard at all from a high-level perspective.

**It's important to mention that I ordered `Claude` to rewrite the code until
it was understandable for me, since in many cases it used quircky `Python` things
that are annoying to take time for understanding them!**

- Next step is to run the `Python` code that gives an image of the plot, then
open the image for analysis.

*Make sure you are in the right directory as last time!*

```bash
$ python3 plot_orbit.py
$ xdg-open orbita.png
```

- To automate things it's easier to use a `Makefile` that takes care of each
building step of the project. Another benefit of using `make` is that it only
builds things that were changed, it leaves everything else alone.

- Makefiles are useful in many places so this project is a great opportunity to
learn more about them in detail with official documentatino, therefore what
other place to see than
[`Beginner Makefile Tutorial`](https://www.youtube.com/watch?v=zeEMISsjO38).

- After writing the [`Makefile`](./simulation/src/Makefile) we can now build
easier.

*Make sure you are in the right directory as last time!*

```bash
$ make
$ make clean # Optional.
```

**Now it's time for some numeric analysis:**

- First, it's nice to see what happens if we change the `TIME_CHANGE` constant
at the beginning of the `C` code. It makes sense to get big errors if it's
too big. I left some possible values to play with by changing the `TIME_CHANGE`
defintion.

- I first panicked because of a `donut` appearance for the `ONE_DAY` value of
`TIME_CHANGE`, that happens because the trajectory of each body was overlapping
with itself so much that a thicker trajectory appeared. In order to fix this
problem, I changed the `NR_STEPS` constant so that it satisfies the paper
equation.

- Second, the theoretical paper uses the `Explicit Euler Method`, but the `C`
code that I wrote uses the `Semi-Implicit Euler Method`. This was purely
unintentional and I figured it out while using AI, therefore this is a good
time to pause and think about which method fits best for the simulation.

*TODO: Aici e buba.*
