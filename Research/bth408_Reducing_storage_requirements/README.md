Research paper: [Reducing storage requirements for biological sequence comparison](https://academic.oup.com/bioinformatics/article/20/18/3363/202143)

## 1 Intro

Task: find similar substrings in strings T1 and T2.  
Choose a short substrings called **seed**.  
For each seed common to both T1 and T2, align T1 and T2 so that the seeds align. After aligning, check if the seed match extends beyond the seed.  
Si are seeds representing a Ti string.  
**k-mers** are contiguous k-letter substrings.  


Example: 2310343 has the following 3-mers: 231, 310, 103, 034 and 343.

| Subsequence | 2 | 3 | 1 | 0 | 3 | 4 | 3 |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| - | 2 | 3 | 1 | - | - | - | - |
| - | - | 3 | 1 | 0 | - | - | - |
| - | - | - | 1 | 0 | 3 | - | - |
| - | - | - | - | 0 | 3 | 4 | - |
| - | - | - | - | - | 3 | 4 | 3 |

By sorting seeds, similar seeds end up next to each other. This means you can easily apply the **extend algorithm** to find longer matches.  
**Collection criterion** is the ability to recognise matches as soon as the dataset is sorted.  

**k-mer triple** is (s, i, p) where:  
s is a k-mer string (seed),  
i is a Ti string identifier,  
p is the position of seed s in string Ti.  

## 2 Minimizers

Choose a representative k-mer from adjacent k-mers such that strings Ti and Tj choose the same representative if they share a long enough subsequence.  
**Minimizers** are a special set of k-mers. Minimizers are the substring representatives and therefor, the seeds.  

Minimizers have the following property:  
Property 1: if two strings Ti and Tj have a significant exact match, then AT LEAST ONE of the minimizers chosen from Ti will also be chosen from Tj.  

### 2.1 Interior minimizers

You must choose a k-mer ordering such as numerical/lexicographic ordering.  

**Window size** w is the number of consecutive k-mers.  
w k-mers cover a string of w + k - 1 characters.  
Find a minimizer by examining w and select the smallest k-mer (based on chosen ordering).  
In case of a tie, each of the smallest k-mers is a minimizers.  

A k-mer triple (s, i, p) is a (w, k) minimizer for Ti.  
A better formalised Property 1 is:  
Property 1': if two strings Ti and Tj have a substring of length w + k - 1 in common, then they have a (w, k) minimizer in common.  

Example: (w=5, k=3, l=7)  
w is the number of k-mers,  
k is k-mer length,  
l is string length calculated as l=w+k-1.  

034 is the minimizer as it is the smallest k-mer when substring k-mers are sorted numerically.

| Position | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| Subsequence | 2 | 3 | 1 | 0 | 3 | 4 | 3 |
| - | 2 | 3 | 1 | - | - | - | - |
| - | - | 3 | 1 | 0 | - | - | - |
| - | - | - | 1 | 0 | 3 | - | - |
| - | - | - | - | 0 | 3 | 4 | - |
| - | - | - | - | - | 3 | 4 | 3 |

Note: Ti has a lot of characters (this example show only a small substring; Ti may have more then a million characters), so you will need to apply the above method many times.  
After choosing a k-mer length k and window size w, apply it to the first substring of Ti.  
The first substring of Ti starts at position 0.  
From the resulting k-mers choose the smallest k-mer to become the minimizers.  
Apply the same method to the second substring of Ti which starts at position 1...  
Apply the method over and over again until you have reached the end of Ti.  

A gap between minimizers can be at most w - k. If you don't want any gaps, set w <= k.  

### 2.2 End minimizers

The gap mentioned is between minimizers, not between a minimizer and the end or beginning of the string.  

You can then add a (u, k) **end minimizer**.  
An end minimizer is a minimizer chosen from a window u and anchored to the end of the string.  
k-end-minimizers are all minimizers for u from i up to v.  

End minimizers have the following property:  
Property 2: if ends of two strings have an exact overlap of at least k characters and at most k + v - 1, then they share at least one k end minimizer.  

### 2.3 Mixed strategy

Combine both (w, k) minimizers and (u, k) end minimizers for best results.  

### 2.4 Ordering

To make sure you sample as few k-mers as possible and therefor save as such storage as possible, make sure you choose a good ordering.  

C and G nucleobases occure less frequently then A and T nucleobases.  
Because we want to find rare k-mers we should assign the following numbers to each nucleobase: 0,1,2,3 are C,A,T,G respectively.  

There are many different ways of ordering k-mers.  
