---
title: Zeta-Moebius Transform
documentation_of: //math/zeta_moebius_transform.hpp
---

## Description
Zeta-Moebius Transform provides fast convolution operations on sequences
indexed by integers. The divisor zeta transform, given a function $f$,
computes a function $g$ satisfying:

\[g(n) = \sum_{m | n} f(m)\]

The Möbius transform is the inverse of the zeta transform (given $g$, it
computes $f$). The multiple transform is defined similarly.

Using divisor FZT/FMT, LCM convolution can be computed efficiently:

\[c_k = \sum_{\mathrm{lcm}(i,j)=k} a_i b_j\]

Using multiple FZT/FMT, GCD convolution can be computed efficiently:

\[c_k = \sum_{\gcd(i,j)=k} a_i b_j\]

## Operations
- `multiple_fzt<T>(vector<T> &a)`
  + Fast zeta transform for multiple convolution
  + Transforms `a` in-place: `a[k] = sum_{k|d} a[d]`
  + Time complexity: $\mathcal O(n \log \log n)$ where $n$ is the array size
- `multiple_fmt<T>(vector<T> &a)`
  + Fast Moebius transform for multiple convolution (inverse of `multiple_fzt`)
  + Transforms `a` in-place
  + Time complexity: $\mathcal O(n \log \log n)$
- `divisor_fzt<T>(vector<T> &a)`
  + Fast zeta transform for divisor convolution
  + Transforms `a` in-place: `a[k] = sum_{d|k} a[d]`
  + Time complexity: $\mathcal O(n \log \log n)$
- `divisor_fmt<T>(vector<T> &a)`
  + Fast Moebius transform for divisor convolution (inverse of `divisor_fzt`)
  + Transforms `a` in-place
  + Time complexity: $\mathcal O(n \log \log n)$
- `gcd_convolution<T>(vector<T> a, vector<T> b)`
  + Computes GCD convolution: `c[k] = sum_{gcd(i,j)=k} a[i] * b[j]`
  + Returns the result vector
  + Time complexity: $\mathcal O(n \log \log n)$
- `lcm_convolution<T>(vector<T> a, vector<T> b)`
  + Computes LCM convolution: `c[k] = sum_{lcm(i,j)=k} a[i] * b[j]`
  + Returns the result vector
  + Time complexity: $\mathcal O(n \log \log n)$

## Note

The following table shows which transforms are used for different convolution
operations:

| Convolution | Transform | Inverse Transform |
|------------|-----------|-------------------|
| $\max$ | zeta transform (prefix sum, lower) | Möbius transform (prefix sum, lower) |
| $\min$ | zeta transform (prefix sum, upper) | Möbius transform (prefix sum, upper) |
| $\gcd$ | zeta transform (multiple) | Möbius transform (multiple) |
| $\mathrm{lcm}$ | zeta transform (divisor) | Möbius transform (divisor) |
| $\mathrm{bitwise\ and}$ | zeta transform (bit, upper) | Möbius transform (bit, upper) |
| $\mathrm{bitwise\ or}$ | zeta transform (bit, lower) | Möbius transform (bit, lower) |
| $\mathrm{bitwise\ xor}$ | Walsh-Hadamard transform | inverse Walsh-Hadamard transform |
| $+$ | Fourier transform, NTT | inverse Fourier transform, inverse NTT |

## References
- [sotanishy's implementation](https://sotanishy.github.io/cp-library-cpp/convolution/divisor_zeta_moebius_transform.hpp)
- [Understanding zeta/Möbius transforms - Qiita](https://qiita.com/convexineq/items/afc84f0c4c40c6d36d7d) (Japanese)
- [Fast divisor zeta transform O(N log(log(N))) - noshi91's memo](https://noshi91.github.io/algorithm-encyclopedia/dzeta-sieve.html) (Japanese)
