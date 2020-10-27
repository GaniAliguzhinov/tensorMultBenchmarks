# tensorMultBenchmarks

https://bitbucket.org/blaze-lib/blaze/wiki/Blazemark

https://github.com/blitzpp/blitz

https://github.com/springer13/tcl
https://github.com/bennylp/awesome-cpp-ml

https://www.gnu.org/software/gcc/testing/testing-blitz.html

https://github.com/MaxKotlan/Cuda-Matrix-Multiplication-Benchmark

https://hduongtrong.github.io/2016/03/07/Matrix-Multiplication-Benchmark/
https://dzhelil.info/2019/07/17/cbench.html
# Heh

Intermediate functional language.

Arrays as mappings from indices to values.
Set of indices bound by shape.
Hyper-rectangular index spaces, so
Shape of any array can be described by a tuple of
natural numbers, with each el-t beign extent of corresp. axis.

$m$ rows and $n$ cols: tuple $\langle m, n \rangle$

Arrays constructed as a sequence of expressions in square brackets:
`[1, 2, 3, 4]` or `[[1,2], [3,4]]`.

Array selection: dot symbol - infix binary op betw array to select from 
and a valid index into that array:

```
[1,2,3,4].[0] = 1

[[1,2],[3,4]].[1,1] = 4

[[1,2],[3,4]].[1] = ?

```

Array shape by primitive `shape` operation: `|a|`
Lambda denoted with `l`

```
|[1,2]| = [2]

|[[]]| = [1,0]

|true| = []

|42| = []

|lx.x| = []

```

`reduce` combinator takes three args: binary function, 
neutral element, and the array to reduce.

Assuming row-major order:

```
reduce (+) 0 [[1,2], [3,4]] = ((((0+1)+2)+3)+4)
```

`imap` restricts the domain of an index-value-mapping f-n `f` to shape `s`.

```
imap s {_(iv):1
imap [5] {_(iv):1
```

Maps every index to constant 1, where indices are in `[5]`, i.e.: `{[0], [1], [2], [3], [4]}`.

We specify index mappings via partitions, using:

```
imap [5] {[0] <= iv < [3]: iv.[0] + 10,
          [3] <= iv < [5]: iv.[0] + 20
```

This breaks index space into partitions: `{[0], [1], [2]}`
and `{[3], [4]}`.
`iv` variable binds to each value within index-space, overall expression
evaluates to `[10, 11, 12, 23, 24]`.

When mapping evaluates to non-scalar, we use `imap s|s2 {_(iv): [1, 2]`
where `s2` has to be `[2]`, and `s` can be 3, for example, resulting in
`[[1,2],[1,2],[1,2]]` of shape `[3,2]`.

Example increment:

```
letrec inc = la.imap |a| {_(iv): a.iv + 1
```
# Experiments

```
letrec matplus = la.lb.
    imap |a| {_(iv): a.iv + b.iv

letrec matmul1 = la.lb.
    imap |a| {_(iv):
        letrec i = iv.[0] in
        letrec j = iv.[1] in
        letrec n = |a|.[0] in
        reduce (lx.ly.x+y) 0
            imap [n] {_(jv):
                letrec k = jv.[0] in
                    a.[i, k] * b.[k,j]

letrec sum = la.lb.ln.li.lj.lk.lres.
    if k = n then res
    else sum a b n i j (k+1)
            (res + a.[i,k] * b.[k,j]) in

letrec matmul2 = la.lb.
    imap |a| {_(iv): letrec i = iv.[0] in
                     letrec j = iv.[1] in
                     letrec n = |a|.[0] in
                     sum a b n i j 0 0
```
