Research paper: [Introduction to the Burrows-Wheeler Transform and FM Index](https://www.cs.jhu.edu/%7Elangmea/resources/bwt_fm.pdf)

## 1 Burrows-Wheeler Transform (BWT)

Imagine a string T.  
Transform T into another string using a function BWT(T).  
Assume that T ends in $ (for simplicity sake). $ is smaller then any other character in T.  
Construct a **Burrows-Wheeler Matrix (BWM)**, then sort the rows in ascending order.  
The last column, when read from top to bottom is the new string **BWT(T)**.  

Example: string T is ABAABA$  
Step 1: rotate the previous string until $ is at the end of the string.  

| A | B | A | A | B | A | $ |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| $ | A | B | A | A | B | A |
| A | $ | A | B | A | A | B |
| B | A | $ | A | B | A | A |
| A | B | A | $ | A | B | A |
| A | A | B | A | $ | A | B |
| B | A | A | B | A | $ | A |
| A | B | A | A | B | A | $ |

Step 2: sort the rows in ascending order  

| A | B | A | A | B | A | $ |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| $ | A | B | A | A | B | A |
| A | $ | A | B | A | A | B |
| A | A | B | A | $ | A | B |
| A | B | A | $ | A | B | A |
| A | B | A | A | B | A | $ |
| B | A | $ | A | B | A | A |
| B | A | A | B | A | $ | A |

The result is the Burrows-Wheeler Matrix (BWM).
The new string BWT(T) are the characters in the last column.  

String T = ABAABA$  
BWT(T) = ABBA$AA  

### 1.1 BWT and the suffix array

A **suffix array** is an array of integers which tell the starting position of a suffix.  

Example: string T is ABAABA$

Step 1: create all suffixes  

| A | B | A | A | B | A | $ | suffixes |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:--------:|
| A | B | A | A | B | A | $ | s0 |
| - | B | A | A | B | A | $ | s1 |
| - | - | A | A | B | A | $ | s2 |
| - | - | - | A | B | A | $ | s3 |
| - | - | - | - | B | A | $ | s4 |
| - | - | - | - | - | A | $ | s5 |
| - | - | - | - | - | - | $ | s6 |


Step 2: sort the suffixes in ascending order  

| A | B | A | A | B | A | $ | suffixes |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:--------:|
| - | - | - | - | - | - | $ | s6 |
| - | - | - | - | - | A | $ | s5 |
| - | - | A | A | B | A | $ | s2 |
| - | - | - | A | B | A | $ | s3 |
| A | B | A | A | B | A | $ | s0 |
| - | - | - | - | B | A | $ | s4 |
| - | B | A | A | B | A | $ | s1 |

String T = ABAABA$  
The suffix array SA(T) = [6,5,2,3,0,4,1].  

To construct a suffix array of string T, SA(T), sort T's suffixes.  
To construct a BW Matrix of string T, rotate T.  
These two problems are connected.  

You can define BWT(T) using a suffix array SA(T).  
BWT[i] is a character in BWT(T).  
SA[i] is a suffix in SA(T).  

**If SA[i] > 0: BWT[i] = T[SA[i] - 1]  
If SA[i] == 0: $**  

Example: T = ABAABA$, SA(T) = [6,5,2,3,0,4,1], BWT(T) = ABBA$AA 

| - | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| T | A | B | A | A | B | A | $ |
| SA | 6 | 5 | 2 | 3 | 0 | 4 | 1 |
| BWT | A | B | B | A | $ | A | A |

i = 1  
SA[1] = 5
T[5 - 1] = T[4] = B  
T[4] = BWT[1] = B  

i = 4
SA[4] = 0  
because SA[4] = 0 -> $  
BWT[4] = $  

### 1.2 Burrows-Wheeler Transform in compression

TODO  

### 1.3 Reversing the Burrows-Wheeler Transform with the LF Mapping

BWT is reversible, however, it's not obvious how.  
Rewrite BW Matrix so that every character is given a rank depending on occurrence in string T.  
Ranking characters in string T is called **T-ranking**.  
First occurrence is 0, second is 1, ...  

If T = ABAABA$, then BWM(T) is:  

| A0 | B0 | A1 | A2 | B1 | A3 | $ |
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
|  $ | A0 | B0 | A1 | A2 | B1 | A3 |
| A3 |  $ | A0 | B0 | A1 | A2 | B1 |
| A1 | A2 | B1 | A3 |  $ | A0 | B0 |
| A2 | B1 | A3 |  $ | A0 | B0 | A1 |
| A0 | B0 | A1 | A2 | B1 | A3 |  $ |
| B1 | A3 |  $ | A0 | B0 | A1 | A2 |
| B0 | A1 | A2 | B1 | A3 |  $ | A0 |

Strangely, the rank order of each character in each column is the same.  
First column rank order -> A3, A1, A2, A0 and B1, B0  
Second column rank order -> A3, A1, A2, A0 and B1, B0  
Last column rank order -> A3, A1, A2, A0 and B1, B0  

Instead of giving every character a rank depending on occurrence in string T, do it for BWT(T).  
Ranking characters in string BWT(T) is called **B-ranking**.  

BWT(T) = ABBA$AA  
B-ranking is A0, B0, B1, A1, $, A2, A3.  

Ranks can be represented in the following manner:  

F is the first column of BWM(T).  
L is the last column of BWM(T).  
Rank is the B-ranking.  

| row | F | L | Rank |
|:---:|:-:|:-:|:----:|
|  1  | $ | A |   0  |
|  2  | A | B |   0  |
|  3  | A | B |   1  |
|  4  | A | A |   1  |
|  5  | A | $ |   0  |
|  6  | B | A |   2  |
|  7  | B | A |   3  |

The table above can be used to recover string T from BWT(T).  
The recovery process goes as follows:  
Start -> look at the first row in column F; it says $; look at the first row in column L; it says A; we can conclude that A if left of $  
Step -> look at the first row in column Rank; it says 0; we can conclude that the rank of A in column L is 0; we have found A0  
Step -> find A0 in column F; A0 can be found in row 2; we look at the second row in column L; it says B; we look at the second row in column Rank; it says 0; we have found B0 that is left of A0  
Step -> find B0 in column F; B0 can be found in row 6; we look at the sixth row in column L; it says A; we look at the sixth row in column Rank; it says 2; we have found A2 that is left of B0  
Step -> and so the cycle continues until $.  

## 2 FM Index

Because of **LF mapping**, BWT(T) is reversible.  
Using the same property, an index can be constructed.  

### 2.1 Searching

The BWM(T) if T = ABAABA$ is:  

| F | - | - | - | - | - | L | rank |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:----:|
| $ | A | B | A | A | B | A |  0   |
| A | $ | A | B | A | A | B |  0   |
| A | A | B | A | $ | A | B |  1   |
| A | B | A | $ | A | B | A |  1   |
| A | B | A | A | B | A | $ |  0   |
| B | A | $ | A | B | A | A |  2   |
| B | A | A | B | A | $ | A |  3   |

We want to find occurrences of substring P = ABA.  
Because BWM(T) is sorted, all rows with P as a prefix will be consecutive.  

First, we find the shortest suffix of P, A.  
Because we already have F, the first column, this is easy.  

| F | - | - | - | - | - | L | rank |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:----:|
| A | $ | A | B | A | A | B |  0   |
| A | A | B | A | $ | A | B |  1   |
| A | B | A | $ | A | B | A |  1   |
| A | B | A | A | B | A | $ |  0   |

Next, we find the second shortest suffix of P, BA.  
We can find the rows where B is before A by looking at the column L.  

| F | - | - | - | - | - | L | rank |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:----:|
| A | $ | A | B | A | A | B |  0   |
| A | A | B | A | $ | A | B |  1   |

Columns L and rank point to rows which begin with BA. These are rows 5 and 6.  

| F | - | - | - | - | - | L | rank |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:----:|
| B | A | $ | A | B | A | A |  2   |
| B | A | A | B | A | $ | A |  3   |

Next, we find the third shortest suffix of P, ABA.  
We find the rows where A is before B by looking at the column L. These are rows 3 and 4.  

| F | - | - | - | - | - | L | rank |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:----:|
| A | B | A | $ | A | B | A |  1   |
| A | B | A | A | B | A | $ |  0   |

We are done, as there are no more P suffixes.  

This process is called **backwards matching**.  
Apply LF matching to find a range of rows prefixed by P until we either run out of suffixes or the range become empty.  
The number of occurrences is equal to the size of range. In our case, two.  
