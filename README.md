# ICPC notebook (fork of KACTL)

Our team notebook: [kactl.pdf](./kactl.pdf), 37 pages of A4 landscape, 3 columns
(limit: 50). Page 1 is an index of every chapter, section and algorithm with page
numbers, plus a "what to use when" quick guide. Fill in the team name, members and
university at the top of `content/kactl.tex` before printing.

Build with `make kactl` (two LaTeX passes: the index is generated on the first one).
Run all stress tests with `make test`, and once more as if pasted under our template
(`#define int long long`) with `make test-int64`.

## What changed compared to upstream KACTL

* **Our template** (`content/contest/template.cpp`) replaces KACTL's. All library code
  compiles pasted below it: no `rep`/`sz`/`all`/`vi`/`pii` macros (plain `for` loops,
  `v.size()`, `vector<int>`), and everything works with `#define int long long`.
  `.vimrc` and `hash.sh` are gone from the PDF, and captions show only the line count.
* **No template parameters.** Geometry uses one `struct P` with `typedef double T`
  in `Point.h` (switch to `ll` for exact integer algorithms; `Point3D.h` has `P3`).
  Callbacks became plain outputs (`SCC`: `comp`/`comps`; `BiconnectedComponents`:
  `comps`, `isBridge`, `isCut`) or `std::function` parameters. `RMQ`, `Matrix`
  (now mod-p, runtime size), `SubMatrix`, `LIS`, `HLD` (`valsEdges` constructor
  argument), `WeightedMatching`, `FastFourierTransformMod` (`convMod(a, b, M)`),
  `Treap::each` and the rest are non-templated.
* **Every algorithm has a Description and a one/two line Usage example.**
* **Added** (from Bohdan's library and foreverbell's
  [acm-icpc-cheat-sheet](https://github.com/foreverbell/acm-icpc-cheat-sheet),
  rewritten in KACTL style, each with a brute-force stress test):
  PersistentSegmentTree, LiChao, XorBasis, PersistentXorTrie, UnionFind, Dinic,
  MinMeanCycle, SteinerTree, DominatorTree, DynamicConnectivity,
  CentroidDecomposition, GeneralMatching (deterministic Edmonds blossom, replaces
  the randomized one), HalfPlane, MinkowskiSum, CircleUnion, PlanarFaces, CircleLine,
  LineProjectionReflection, PolygonUnion, ManhattanMST, SuffixAutomaton,
  PalindromicTree, Lyndon, BitsetLCS, CyclicLCS, PrimitiveRoot, LinearSieve,
  Binomial, SolveLinearMod, PolyOps (formal power series), MultipointEval, SMAWK,
  SlopeTrick, Aliens trick, `stress.sh`.
* **Mathematics** chapter extended with the cheat sheet's formulas (volumes, Pick,
  Euler, hyperspheres, rotations, power sums, ...) and its full table of integrals.
  Every integral was checked numerically; several errors in the source were fixed.
* **Tips & tricks** chapter: constraints vs complexity, "if you see X think Y",
  C++ pitfalls, contest strategy.
* Removed from the PDF (files still in the repo): EdmondsKarp, MaximalCliques,
  MaximumClique, MaximumIndependentSet, ConstantIntervals, HillClimbing, SuffixTree,
  BumpAllocator(STL), SmallPtr, SIMD.
* Code is set in Inconsolata, slightly larger than KACTL's Courier, at the same
  63-column line width.
* Fixes: `ModSqrt.h` and `NumberTheoreticTransform.h` now compile exactly as
  printed, and the normal distribution sum formula is corrected.

## Conventions for new code

* Tabs, at most 63 columns (tab = 2), no macros: the code is pasted under our
  template. It must also survive `#define int long long`: no `int(x)` casts, write
  `max<int>(0, x)` instead of `max(0, x)`, and system `#include`s (e.g.
  `<bits/extc++.h>`) go above the define.
* Header comment needs `Author` and `Description`; add `Usage`. A comment line
  must not start with a capitalised word followed by `:` (the preprocessor takes it
  as a command), and `Usage` must not contain `#` or `%`.
* Lines containing `exclude-line` are not printed. Geometry tests pick the
  coordinate type with `typedef ll T; #define POINT_T` before including headers;
  `MOD_SET` / `LIM_SET` do the same for `ModPow.h` / `Binomial.h`.

---

# KACTL

This repo hosts KACTL, [KTH](https://en.wikipedia.org/wiki/KTH_Royal_Institute_of_Technology)'s ICPC team reference document.
It consists of 25 pages of copy-pasteable C++ code, for use in ICPC-style programming competitions.

See [kactl.pdf](./kactl.pdf) for the final, browsable version, and [content/](./content/) for raw source code.

## Aspirations

KACTL algorithms should be: useful, short, fast enough, well tested, and if relevant, readable and easy to modify.
They should *not* be overly generic, since code is manually typed and that just adds overhead.
Due to space issues, we also exclude algorithms that are very common/simple (e.g., Dijkstra), or very uncommon (general weighted matching).

If you feel that something is missing, could be cleaned up, or notice a bug, please file an issue or [send a pull request](https://help.github.com/articles/fork-a-repo/)!

## Customizing KACTL

While KACTL is usable as is, it's also easy to modify if you want to create a personalized copy.
In particular, you may want to change the cover page, or make your own choice of algorithms to include --
due to space concerns, not all algorithms in the repo are included in the pdf.
You may also want to enable colored syntax highlighting.

`content/kactl.tex` is the main file of KACTL, and can be edited to change team name, logo, syntax highlighting, etc.
It imports `chapter.tex` files from each of the `content/` subdirectories, which define the contents of each chapter.
These include source code, text and math in the form of LaTeX.
To add/remove code from a chapter, add/remove a corresponding `\kactlimport` line from the `chapter.tex` file.
For nicer alignment you might want to insert `\hardcolumnbreak`, `\columnbreak` or `\newpage` commands,
though this is usually only done before important contests, and not on the main branch.
The algorithms that are not included in the pdf are left commented out in `chapter.tex`.

To build KACTL, type `make kactl` (or `make fast`) on a \*nix machine -- this will update `kactl.pdf`.
(Windows might work as well, but is not tested.) `doc/README` has a few more notes about this.

Tips:
1. Check out what's excluded by default by running `make showexcluded`.
The default configuration is chosen to be a reasonable balance for beginners
and advanced teams.
2. Take advantage of the hashing when typing in these algorithms. Each
algorithm has a 6 character MD5 hash in the upper right. This hash can be
generated by using `hash.sh` or the `:Hash` command from the `.vimrc`. The
hashing ignores whitespace and comments.

## Coding style

KACTL uses a relatively terse coding style, with a handful of macros/typedefs defined in the
[template](./content/contest/template.cpp) that help shorten the code.
Line width is 63 chars, with tabs for indentation (tab = 2 spaces in the pdf).

Each algorithm contains a header with the author of the code, the date it
was added, a description of the algorithm, its testing status, and preferably also
source, license and time complexity.

kactl.pdf is to be kept to 25 pages + cover page.
Occasionally the generated kactl.pdf is committed to the repo for convenience, but not too often because it makes git operations slower.

## Testing

KACTL aims for a high level of confidence in algorithm correctness.
Testing is done both on online judges and (for newer algorithms) with stress tests
that compare output to a more naive algorithm for a large amount of randomly generated cases.
These tests live in the `stress-tests` directory, and are run with CI on every commit. The CI also verifies that all headers compile (except for an exclude list in `docs/scripts/skip_headers`) and that the latex compiles.

`old-unit-tests` contains a couple of broken unit tests, last touched about ten years ago.

## License

As usual for competitive programming, the licensing situation is a bit unclear.
Many source files are marked with license (we try to go with
[CC0](https://creativecommons.org/share-your-work/public-domain/cc0/)), but many also aren't.
Presumably good will is to be assumed from other authors, though, and in many cases permission should not be needed since the code is not distributed.
To help trace things back, sources and authors are noted in source files.

Everything in `stress-tests` is implicitly CC0, except reference implementations taken from around the Internet.
