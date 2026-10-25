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
using `AI`, I believe that is necessary in order to construct *quality code*.

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

- Next, we need to filter the output from the `C` program to an actual `CSV`
file. I could have modified the `C` code to do that more directly but practicing
`Bash` together with searching inside `man pages` and not using `AI` directly
makes me feel much better. Here is how I generate the `CSV` file:

*Make sure you are in the right directory as in the last session!*

```bash
$ ./orbita | grep '(x, y)' | cut -d " " -f 5,6 | tr "()" " " | tr -d " " > points.csv # Looks scary, I know :)
```

- Next I wrote the `Python` code that will generate the plot. This was done with
help from AI but I wrote the code from scratch after understanding what it
does, it's not hard at all from a high-level perspective.

**It's important to mention that I ordered `Claude` to rewrite the code until
it was understandable for me, since in many cases it used quirky `Python` things
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
learn more about them in detail with some documentation, therefore what other
place to see than
[`Beginner Makefile Tutorial`](https://www.youtube.com/watch?v=zeEMISsjO38).

- After writing the [`Makefile`](./simulation/src/Makefile) we can now build
easier.

*Make sure you are in the right directory as last time!*

```bash
$ make
$ make clean # Optional.
```

**Now it's time for some numeric analysis:**

- **First**, it's nice to see what happens if we change the `TIME_CHANGE` constant
at the beginning of the `C` code. It makes sense to get big errors if it's
too big. I left some possible values to play with by changing the `TIME_CHANGE`
defintion.

- I panicked because of a `donut` appearance for the `ONE_DAY` value of
`TIME_CHANGE`, that happens because the trajectory of each body was overlapping
with itself so much that a thicker trajectory appeared. In order to fix this
problem, I changed the `NR_STEPS` constant so that it satisfies the paper
equation.

- **Second**, the theoretical paper uses the `Explicit Euler Method`, but the `C`
code that I wrote uses the `Semi-Implicit Euler Method`. This was purely
unintentional and I figured it out while using AI, therefore this is a good
time to pause and think about which method fits best for the simulation.

- It all comes down to that `k`-th derivative term. `Claude` has made me a good
reference table for this method:

| Method | `Velocity`: `a` coming from | `Position`: `v` coming from |
| --- | --- | --- |
| Explicit Euler (same as in paper) | `k`-th `x` term: $(x^k)$ | `k`-th `v` term: $(v^k)$ |
| Semi-Implicit Euler (initial code) | `k`-th `x` term: $(x^k)$ | `k + 1`-th `v` term: $(v^{k + 1})$ |
| Implicit Euler | `k + 1`-th `x` term: $(x^{k + 1})$ | `k + 1`-th `v` term: $(v^{k + 1})$ |

- I am not gonna get into a deep analysis for each method, I will simply choose
the explicit Euler method as presented in the paper, it seems more intuitive at
first.

- After changing the code, it turns out that the simulation looks a little bit
**worse** than before, this is important to note. I am pretty sure that if I
take some time to understand *why* this happens, it will make sense. My feeling
is that the problem is related to the initial coordonates and the fact that we
want a circular trajectory.

- Since the simulation is not as powerful now, changing `TIME_CHANGE` to a
smaller constant seems appropiate.

**The second week was full of progress!**

### Week 03: TODO -> 26.10.2026 - 02.11.2026 (European dates)

*Off to an earlier start on Sunday before the week begins because the semester
starts to become hardcore.*

- Finally, we are ready to generalize the problem.

- The current work flow does not cut it. When more bodies will come into play,
the `CSV` file becomes too big because of computationally unnecessary text.

- Everything will now be handled from the `C` code directly, therefore that
little `Bash` script that I wrote becomes obsolete `:(`. Need to change the
`Makefile` as well now. After that, the `Python` code needs to be updated too.

- Next, the addition of body structures is done, in the `C` code.

*Here is a cool thing I somehow never really thought of but it makes much
sense:*

```c
#include <stdio.h>

struct my_struct {
    int x;
    int y;
};

int main(void)
{
    struct my_struct a = {
        .x = 0,
        .y = 0
    };
    struct my_struct b = {
        .x = 1,
        .y = 1
    };

    struct my_struct arr[2] = {a, b};
    arr[0].x = 123;
    arr[1].x = 123;
    a.y = 123;
    b.y = 123;
    
    printf("%d %d\n", a.x, a.y);
    return 0;
}

```

*Compile and run! Assembly knowledge does not dissapoint!*

- After this comes an important design decision:

**Should the `acceleration` be part of the `body` structure or a separate
entity?.**

- `Claude` recommended that we should have different structures for this,
however at the beginning it did not seem natural for me.
 
- After much thinking it has become clear why we **should** have different
objects:

**The hardware computes accelerations and accelerations only!**

Therefore we stick to different structures.

*Generalizing the code took some time...*
