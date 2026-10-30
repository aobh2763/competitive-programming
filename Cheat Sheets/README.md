**Competitive Programming Cheat Sheets**

Every topic below comes as a pair of files: a `.cpp` file with code you can copy into a contest, and a `.md` file that explains **when to use it, how fast it is, and which mistakes to avoid**. Each section folder also has its own `README.md` with a "which tool do I need?" table.

Folder layout: every section has a `code` folder (the `.cpp` files and scripts) and a `notes` folder (the `.md` explanations).

```
Cheat Sheets/
├── README.md                  <- this file
├── Trees/
│   ├── README.md              <- section overview and "which tool do I need?" table
│   ├── code/                  <- .cpp files
│   └── notes/                 <- .md files
├── Graphs/            (code, notes)
├── Number Theory/     (code, notes)
├── Dynamic Programming/ (code, notes)
├── Strings/           (code, notes)
├── Algorithms/        (code, notes)
└── Utilities/         (code, notes)
```

These sheets help you **recall** things you already understand. If a topic is new, first read its `.md` note, trace the idea by hand on a tiny example, then try to write it yourself, and only then compare with the code here.

A good order for beginners: Utilities (template, binary search, array utilities), then Graph Traversal, DSU, Dijkstra, Fenwick Tree, Segment Tree, Modular Arithmetic, Combinatorics, then Basic DP and Knapsack. Leave the "advanced" ones for later.

---

# Trees & Range Queries (`Trees/`)

These tools answer questions about long lists of numbers and about tree-shaped data **quickly**, such as "what is the sum of items 3 to 900?", without looping over everything each time. A *tree* is a set of connected dots with no loops, like a family tree or a company chart. Overview and chooser table: [Trees/README.md](Trees/README.md).

## Fenwick Tree
A small, fast structure for "change one number, then ask for the sum of a range". Think of a running total that stays correct after you edit a value, in about log n steps instead of re-adding everything. Use it when you need sums and updates together.
[Notes](Trees/notes/fenwick.md) · [Code](Trees/code/fenwick.cpp)

## Segment Tree
Like a Fenwick tree but more flexible: it can answer minimum, maximum, gcd and more, not only sums. Imagine a tournament bracket where each match remembers the winner of its part; changing one player only replays the matches above them.
[Notes](Trees/notes/segtree.md) · [Code](Trees/code/segtree.cpp)

## Lazy Segment Tree
A segment tree that can also change a **whole range at once** ("add 5 to items 10 through 500") without touching each item. It leaves a "to-do note" on a node and only passes the work down when it really has to.
[Notes](Trees/notes/lazy_segtree.md) · [Code](Trees/code/lazy_segtree.cpp)

## Sparse Table
Answers "what is the smallest (or largest) value between positions l and r?" in a single step, as long as the list **never changes**. It does the work up front by precomputing answers for blocks whose sizes are powers of two.
[Notes](Trees/notes/sparse_table.md) · [Code](Trees/code/sparse_table.cpp)

## DSU (Union-Find)
Keeps track of **groups**: you can merge two groups and ask "are these two things in the same group?", both almost instantly. Picture clubs that merge when two members become friends. It is used for connectivity questions and for building cheapest networks.
[Notes](Trees/notes/dsu.md) · [Code](Trees/code/dsu.cpp)

## Tree Basics (DFS, Euler Tour, Diameter)
Walks through a tree once to learn each node's parent, depth and subtree size, and finds the *diameter* (the longest path in the tree). It also numbers the nodes so that "everything below this node" becomes a simple range. This is the foundation for the other tree tools.
[Notes](Trees/notes/tree_basics.md) · [Code](Trees/code/tree_basics.cpp)

## LCA (Lowest Common Ancestor)
The lowest common ancestor of two nodes is the closest ancestor they share, like the nearest common grandparent of two cousins in a family tree. It also gives the distance between any two nodes. It works by jumping up the tree in steps of 1, 2, 4, 8, ... .
[Notes](Trees/notes/lca.md) · [Code](Trees/code/lca.cpp)

## Heavy-Light Decomposition
An advanced trick that cuts a tree into long straight "chains", so that questions about the path between two nodes (sum or max, even with updates) turn into range queries on a list. Learn it after LCA and segment trees.
[Notes](Trees/notes/hld.md) · [Code](Trees/code/hld.cpp)

---

# Graphs (`Graphs/`)

A *graph* is dots (nodes) joined by lines (edges): cities and roads, people and friendships, web pages and links. Graph problems ask things like "what is the shortest route?", "can I get from A to B?" or "what is the cheapest way to connect everything?". Overview and chooser table: [Graphs/README.md](Graphs/README.md).

## Graph Traversal (BFS, Components, Bipartite, Grid)
BFS explores a graph level by level, like ripples spreading from a stone dropped in water. That finds the **fewest steps** in a maze or any graph where every move costs the same. The same file counts connected groups and checks whether a graph can be split into two teams with no conflicts inside a team.
[Notes](Graphs/notes/graph_traversal.md) · [Code](Graphs/code/graph_traversal.cpp)

## Dijkstra & 0-1 BFS
Finds the **cheapest route** when roads have different costs (never negative), much like a GPS. It always finishes the nearest unfinished place next. 0-1 BFS is a faster special case for when every cost is 0 or 1.
[Notes](Graphs/notes/dijkstra.md) · [Code](Graphs/code/dijkstra.cpp)

## Bellman-Ford
Shortest paths when some edges can have **negative** cost, such as a discount or a refund. It can also detect a "negative cycle": a loop that makes the total cheaper every time you go around it.
[Notes](Graphs/notes/bellman_ford.md) · [Code](Graphs/code/bellman_ford.cpp)

## Floyd-Warshall
Computes the shortest distance between **every pair** of nodes in one run, with three simple nested loops. It is slow for big graphs, so use it only when there are a few hundred nodes at most.
[Notes](Graphs/notes/floyd_warshall.md) · [Code](Graphs/code/floyd_warshall.cpp)

## Topological Sort
Puts tasks in a valid order when some must come before others, like socks before shoes. If the rules contradict each other (A before B, B before A), it tells you there is a cycle. It also lets you do dynamic programming on dependency graphs.
[Notes](Graphs/notes/toposort.md) · [Code](Graphs/code/toposort.cpp)

## SCC (Strongly Connected Components)
In a graph of one-way streets, an SCC is a group of places where you can get from any place to any other place in the group. This file finds those groups and can shrink each one into a single node, which gives a simpler graph with no loops.
[Notes](Graphs/notes/scc.md) · [Code](Graphs/code/scc.cpp)

## Bridges & Articulation Points
In a network, a **bridge** is a link whose failure splits the network in two, and an **articulation point** is a node whose failure does the same. It finds those critical weak spots.
[Notes](Graphs/notes/bridges.md) · [Code](Graphs/code/bridges.cpp)

## MST (Minimum Spanning Tree, Kruskal)
Connects all nodes with the cheapest total set of edges and no loops, for example the cheapest cabling that links every house. It sorts edges from cheapest to most expensive and keeps an edge only if it does not create a loop (using DSU).
[Notes](Graphs/notes/mst.md) · [Code](Graphs/code/mst.cpp)

---

# Number Theory (`Number Theory/`)

Math with whole numbers: remainders, divisibility and prime numbers. Contest answers are often huge, so problems say "print the answer **modulo** 1,000,000,007", meaning the remainder after division by that number. These files give you the standard toolkit. Overview and chooser table: [Number Theory/README.md](Number%20Theory/README.md).

## Modular Arithmetic
Arithmetic on a clock: numbers wrap around after reaching the modulus. This file has safe addition, multiplication and powers with remainders, plus "division" (done through an inverse). Almost every other file in this section builds on it.
[Notes](Number%20Theory/notes/modular.md) · [Code](Number%20Theory/code/modular.cpp)

## GCD, Extended Euclid & CRT
The gcd is the largest number that divides two numbers evenly. Extended Euclid goes further and solves equations like a·x + b·y = gcd, which also gives inverses when the modulus is not prime. CRT combines clues such as "leaves remainder 2 when divided by 3 and remainder 3 when divided by 5" into one answer.
[Notes](Number%20Theory/notes/gcd_crt.md) · [Code](Number%20Theory/code/gcd_crt.cpp)

## Combinatorics
The math of counting: in how many ways can you choose 3 people out of 10, or arrange items in a row? It precomputes factorials so that "n choose r" answers come back instantly, and includes Catalan numbers, stars and bars, and Lucas' theorem.
[Notes](Number%20Theory/notes/combinatorics.md) · [Code](Number%20Theory/code/combinatorics.cpp)

## Sieves
A sieve finds all prime numbers up to n by crossing off multiples, like filtering out everything that has a smaller divisor. The linear sieve here also records each number's smallest prime factor, so you can factor numbers in a few steps, and computes Euler's phi and the Moebius function.
[Notes](Number%20Theory/notes/sieve.md) · [Code](Number%20Theory/code/sieve.cpp)

## Number Functions
Beginner-friendly helpers for one number at a time: break it into prime factors, count or add up its divisors, compute Euler's phi, take an exact integer square root, and divide correctly with negative numbers.
[Notes](Number%20Theory/notes/number_functions.md) · [Code](Number%20Theory/code/number_functions.cpp)

## Primality & Factorization (Miller-Rabin, Pollard Rho)
For huge numbers, up to about 10^18, where trying every divisor would take forever. Miller-Rabin quickly tests whether a number is prime (exact for all 64-bit numbers), and Pollard's rho finds its factors.
[Notes](Number%20Theory/notes/primality.md) · [Code](Number%20Theory/code/primality.cpp)

## Matrix Exponentiation
Computes the n-th term of a sequence like Fibonacci when n is astronomically large (up to 10^18), by squaring a small table of numbers (a matrix) repeatedly instead of stepping one term at a time.
[Notes](Number%20Theory/notes/matrix_expo.md) · [Code](Number%20Theory/code/matrix_expo.cpp)

## NTT (Number Theoretic Transform)
Multiplies two long lists of numbers (polynomials) quickly, much like multiplying huge numbers digit by digit but far faster. It works with the modulus 998,244,353 and is used for counting problems that combine two sets of choices.
[Notes](Number%20Theory/notes/ntt.md) · [Code](Number%20Theory/code/ntt.cpp)

## Discrete Log & Primitive Roots
Solves "which power x makes a^x leave remainder b?" under a modulus, and finds a *primitive root*, a number whose powers produce every nonzero remainder. This is an advanced topic you can leave for later.
[Notes](Number%20Theory/notes/discrete_log.md) · [Code](Number%20Theory/code/discrete_log.cpp)

---

# Dynamic Programming (`Dynamic Programming/`)

Dynamic programming (DP) solves a big problem by breaking it into **smaller versions of itself**, solving each small version once, writing the answer down, and building bigger answers from the written ones. It saves you from repeating the same work over and over. Every DP follows the same five steps: define the state, write the transition, set the base cases, choose the order, read the answer. Overview, recipe and chooser table: [Dynamic Programming/README.md](Dynamic%20Programming/README.md).

## Basic DP (1D and Grid)
The gentlest start: problems where the answer at step `i` depends on a few earlier steps, like counting the ways to climb stairs, picking numbers with no two neighbours, or finding the cheapest path across a grid. Begin here to learn the DP way of thinking.
[Notes](Dynamic%20Programming/notes/basic_dp.md) · [Code](Dynamic%20Programming/code/basic_dp.cpp)

## Knapsack & Coin Change
You have a bag with limited capacity and items with weights and values: which items should you take? The same idea answers "fewest coins to make an amount", "how many ways to make change" and "can some numbers add up to exactly S?". It teaches the key trick of looping direction.
[Notes](Dynamic%20Programming/notes/knapsack.md) · [Code](Dynamic%20Programming/code/knapsack.cpp)

## Sequence DP (LCS, Edit Distance, LIS)
Compares two strings or lists: the longest common subsequence, the fewest edits to turn one word into another (like a spell checker), the longest palindrome you can keep by deleting letters, and the longest increasing subsequence.
[Notes](Dynamic%20Programming/notes/sequence_dp.md) · [Code](Dynamic%20Programming/code/sequence_dp.cpp)

## Interval DP
For problems where you merge, split or remove parts of a segment and the order matters, such as multiplying a chain of matrices or popping balloons. The answer for a long segment is built from the answers for shorter segments inside it.
[Notes](Dynamic%20Programming/notes/interval_dp.md) · [Code](Dynamic%20Programming/code/interval_dp.cpp)

## Bitmask DP
Stores a **set of items as one number**, where each bit says whether an item is used. This lets you try every subset in an organized way, so it handles things like visiting every city once (travelling salesman) or giving each worker a different job. It only works for small sets, about 20 items at most.
[Notes](Dynamic%20Programming/notes/bitmask_dp.md) · [Code](Dynamic%20Programming/code/bitmask_dp.cpp)

## Digit DP
Counts how many numbers up to some huge limit (like 10^18) have a property of their digits, for example "digit sum divisible by 5" or "no two equal neighbouring digits". It builds the number one digit at a time instead of looping over all of them.
[Notes](Dynamic%20Programming/notes/digit_dp.md) · [Code](Dynamic%20Programming/code/digit_dp.cpp)

## Tree DP & Rerooting
DP on a tree: each node's answer is built from its children's answers, working from the leaves up to the root. Rerooting then answers "what is the result if **every** node were the root?" in a single extra pass, such as the sum of distances from each node to all the others.
[Notes](Dynamic%20Programming/notes/tree_dp.md) · [Code](Dynamic%20Programming/code/tree_dp.cpp)

## Convex Hull Trick (Li Chao Tree)
A speed-up for DPs that would take n x n steps. When the cost can be written as a line in terms of an earlier state, each earlier state becomes a straight line, and a Li Chao tree finds the best line at any point in about log n steps.
[Notes](Dynamic%20Programming/notes/convex_hull_trick.md) · [Code](Dynamic%20Programming/code/convex_hull_trick.cpp)

## DP Optimizations (Divide & Conquer, Knuth)
Two techniques to speed up a DP that is correct but too slow, by noticing that the best split point moves in one direction only. They turn O(k·n²) into O(k·n·log n) and O(n³) into O(n²). Always test them against the slow version first.
[Notes](Dynamic%20Programming/notes/dp_optimizations.md) · [Code](Dynamic%20Programming/code/dp_optimizations.cpp)

---

# Strings (`Strings/`)

A string is just a row of characters, and string problems ask things like "where does this word appear inside that text?", "is this a palindrome?" or "how many different pieces can I cut out?". Comparing characters one by one is too slow for long texts, so these tools use clever shortcuts to answer in a single pass. Overview, chooser table and a KMP-vs-Z-vs-hashing comparison: [Strings/README.md](Strings/README.md).

## KMP & the Prefix Function
Finds every place a word appears in a text without ever re-reading characters. It works by remembering, for every position, how much of the word's beginning has already matched, so a mismatch never makes you start over. It also reveals repeating patterns inside a string.
[Notes](Strings/notes/kmp.md) · [Code](Strings/code/kmp.cpp)

## Z-Function
Another way to do the same kind of matching: for every position it tells you how many characters from there on are identical to the beginning of the string. Many people find it easier to understand than KMP.
[Notes](Strings/notes/z_function.md) · [Code](Strings/code/z_function.cpp)

## String Hashing
Turns a piece of text into a single number (a fingerprint) so two pieces can be compared by comparing numbers instead of letters. After a quick preparation, the fingerprint of any substring costs one step. It is probabilistic, so this version uses a random base to stay safe against tricky tests.
[Notes](Strings/notes/string_hashing.md) · [Code](Strings/code/string_hashing.cpp)

## Manacher (Palindromes)
A palindrome reads the same forwards and backwards, like "level". Manacher's algorithm finds **all** palindromes inside a string in one pass, so you can get the longest one, count them all, or ask "is this part a palindrome?" instantly.
[Notes](Strings/notes/manacher.md) · [Code](Strings/code/manacher.cpp)

## Trie (Prefix Tree) & XOR Trie
A tree where every path from the top spells out a word, so words that begin the same way share the same branch, like an autocomplete box. The XOR version stores numbers bit by bit and quickly finds which stored number gives the biggest XOR with a given one.
[Notes](Strings/notes/trie.md) · [Code](Strings/code/trie.cpp)

## Suffix Array & LCP
Lists all the endings (suffixes) of a text in alphabetical order. Because similar endings sit next to each other, you can find every occurrence of a word, count the different substrings, or find the longest repeated part with a little extra bookkeeping. It is a heavier tool, best when you ask many questions about one text.
[Notes](Strings/notes/suffix_array.md) · [Code](Strings/code/suffix_array.cpp)

## Aho-Corasick
KMP's big brother: it searches for a whole **list of words** in a text at the same time, still reading the text only once. Think of a spam filter checking a message against a thousand banned words.
[Notes](Strings/notes/aho_corasick.md) · [Code](Strings/code/aho_corasick.cpp)

## Lyndon Words & Minimal Rotation
Shows how to find the alphabetically smallest way to rotate a string (move letters from the front to the back), which gives a standard form for circular strings, like bracelets that can be turned. Two circular strings are the same exactly when their standard forms match.
[Notes](Strings/notes/lyndon_rotations.md) · [Code](Strings/code/lyndon_rotations.cpp)

---

# Algorithm Techniques (`Algorithms/`)

General problem-solving patterns that are not tied to one particular data structure: ways of **thinking** about a problem. Learning to spot which pattern fits ("this is a sliding window", "this is greedy") is a big part of getting faster at contests. Overview, a "how to recognize it" table and a greedy-vs-DP comparison: [Algorithms/README.md](Algorithms/README.md).

## Two Pointers / Sliding Window
Slide a window along a list, moving its left and right ends only forward, instead of checking every possible piece separately. It answers things like "longest stretch of numbers adding up to at most K" or "shortest piece of text containing certain letters" in a single pass.
[Notes](Algorithms/notes/two_pointers.md) · [Code](Algorithms/code/two_pointers.cpp)

## Greedy
At every step, simply take the choice that looks best right now and never look back. It is fast and elegant but only works when you can argue it is safe. The file collects the classics: scheduling the most non-overlapping meetings, filling a bag with the best value per kilo, merging items cheaply (Huffman), and more.
[Notes](Algorithms/notes/greedy.md) · [Code](Algorithms/code/greedy.cpp)

## Sorting & Selection
How sorting works under the hood and how to go beyond it: sort by your own rules, find the k-th smallest or the median without fully sorting, and sort huge lists of numbers very quickly with counting or radix sort.
[Notes](Algorithms/notes/sorting_selection.md) · [Code](Algorithms/code/sorting_selection.cpp)

## Backtracking
Try a choice, go deeper, and if it leads nowhere, undo it and try the next one, like exploring a maze and retracing your steps. Used for puzzles and "list or count all arrangements" problems, such as placing 8 queens on a chessboard or solving a Sudoku.
[Notes](Algorithms/notes/backtracking.md) · [Code](Algorithms/code/backtracking.cpp)

## Meet in the Middle
When trying all 2^40 subsets is far too slow, split the items into two halves of 20, work out all possibilities for each half (about a million each), and then match them up. It turns an impossible amount of work into a manageable one.
[Notes](Algorithms/notes/meet_in_the_middle.md) · [Code](Algorithms/code/meet_in_the_middle.cpp)

## Sqrt Decomposition & Mo's Algorithm
Cut a list into blocks about as long as its square root so every operation touches only a few blocks. Mo's algorithm uses a similar idea for questions you know ahead of time: it reorders them so that the "window" you are looking at only moves a little between questions.
[Notes](Algorithms/notes/sqrt_decomposition.md) · [Code](Algorithms/code/sqrt_decomposition.cpp)

## Sweep Line
Sort the start and end points of intervals (meetings, segments, time ranges) and walk along them once while keeping count. It merges overlapping intervals, finds the busiest moment, measures total covered length, or finds the fewest points that touch every interval.
[Notes](Algorithms/notes/sweep_line.md) · [Code](Algorithms/code/sweep_line.cpp)

---

# Utilities (`Utilities/`)

Everyday tools that are not tied to one algorithm: a starting template, faster input, random test makers, small helpers and a way to find bugs automatically. Start here if you are new, because these help with every problem. Overview, contest-day checklist and common bugs: [Utilities/README.md](Utilities/README.md).

## Contest Template
A ready-to-copy starting file with short names for common types, handy shortcuts, and a debug printer (`dbg`) that only runs on your computer and disappears on the judge. Copy it at the start of every problem.
[Notes](Utilities/notes/template.md) · [Code](Utilities/code/template.cpp)

## Fast I/O
Reads and writes numbers using big buffers so programs with millions of inputs do not run out of time. Most of the time plain `cin` is enough, so reach for this only when input size is a problem.
[Notes](Utilities/notes/fast_io.md) · [Code](Utilities/code/fast_io.cpp)

## Random Utilities
Makes random numbers, lists, strings, trees and graphs for testing your solutions, and provides a hash function for `unordered_map` that cannot be broken by tricky judge tests.
[Notes](Utilities/notes/random_utils.md) · [Code](Utilities/code/random_utils.cpp)

## Binary Search & Ternary Search
Binary search finds a boundary by repeatedly cutting the search range in half, like guessing a number from "higher or lower" hints. It works on sorted lists and also for "find the smallest value that works" problems. Ternary search finds the lowest point of a valley-shaped function.
[Notes](Utilities/notes/binary_search.md) · [Code](Utilities/code/binary_search.cpp)

## Array Utilities
Frequently used list tricks: prefix sums (instant range sums), squeezing big values into small ranks, finding the next bigger element, sliding-window maximum, longest increasing subsequence, counting inversions and the maximum subarray sum.
[Notes](Utilities/notes/array_utils.md) · [Code](Utilities/code/array_utils.cpp)

## Bit Tricks
Computers store numbers as 0s and 1s, and these helpers work on those bits directly: count set bits, loop over every subset of a small set, sum over subsets (SOS DP), and an XOR basis for maximum-XOR problems.
[Notes](Utilities/notes/bit_tricks.md) · [Code](Utilities/code/bit_tricks.cpp)

## String Utilities
Small helpers for text: split a line into pieces, join, trim spaces, change case, compress runs of repeated letters, convert numbers between bases, and check palindromes or subsequences.
[Notes](Utilities/notes/string_utils.md) · [Code](Utilities/code/string_utils.cpp)

## Policy-Based Data Structures (pb_ds)
A special GCC feature: a set that can answer "what is the k-th smallest element?" and "how many elements are smaller than x?" while you insert and remove items, plus a faster hash table.
[Notes](Utilities/notes/pbds.md) · [Code](Utilities/code/pbds.cpp)

## Stress Testing
A script that hunts for your bug automatically: it creates many small random inputs, runs your fast solution and a slow but obviously correct one, and stops at the first input where they disagree. Includes a working example.
[Notes](Utilities/notes/stress.md) · [Script](Utilities/code/stress.sh) · [Generator](Utilities/code/gen.cpp) · [Solution](Utilities/code/sol.cpp) · [Brute force](Utilities/code/brute.cpp)

## Workflow (Compiling & Debugging)
How to compile for the judge versus for debugging, which warning flags catch real bugs, how to use CPH in VS Code, and a step-by-step routine for when your solution gets Wrong Answer or Time Limit Exceeded.
[Notes](Utilities/notes/workflow.md)
