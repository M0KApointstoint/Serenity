# Serenity
## The Learning Process

Here you will find info about every bit of progress I do along the way.

**Week 01:**

*The first week had a pretty rough start, since the vision of the project
changed a lot on the go. Info about the first week was written in the
second week of the project.*

**Here are the core points of the week that were achieved following the plan:**

- The main idea was to understand the n-body problem. One of the best ways
for me to do that is via pen and paper plus online resources.

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
scratch following along the paper, it comes out nicely.

- Here is how you run the code on a typical system that has a `Linux` kernel
with `GNU` tools:

*Make sure you are in the same directory as this README:*

```bash
$ cd simulation/src/
$ gcc -Wall -Wextra orbita.c -o orbita -lm
$ ./orbita
```

**The first week was full of progress!**
