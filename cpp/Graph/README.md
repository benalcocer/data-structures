# Introduction
The vertex.h file is an implementation of an adjacency list. This Computer Science assignment that follows is written in main.cpp that accomplishes the ICPC style problem written by my professor Jimi Andro-Vasko. It showcases a case where an adjacency list can be used. Another example is in my "icpc" repository for Savage Pokemon. Check it out here: https://github.com/benalcocer/icpc/

# Description CS302 Assignment 8, by Jimi Andro-Vasko
 
Morty!!! I finally did it! I discovered a way to time travel, and no Morty, I’m not using that DeLorean or whatever was used in that time traveling movie...time machine right? That’s what it’s called? Time machine? The one where they go to the future or to the past orRick I don’t think that’s the right mov there’s not time for that Morty! We need to go now! I found a way to use my portal device to go through wormholes that takes us to the same universe but in a different point in time, we just have to keep taking the same set of wormholes to go back in the past! And yes we are doing this instead of inter-dimensional cable...
A wormhole is a subspace tunnel through space and time connecting two star systems. Wormholes have a few peculiar properties:
* Wormholes are one − way only
* The time it takes to travel through a wormhole is negligible
* A wormhole has two end points, each situated in a star system
* A star system may have more than one wormhole end point within its boundaries
* For some unknown reason, starting from our solar system, it is always possible to end up in any star system by following a sequence of wormholes (maybe Earth is the center of the universe)
* Between any pair of star systems, there is at most one wormhole in either direction
* There are no wormholes with both end points in the same star system

All wormholes have a constant time difference between their end points. For example, a specific wormhole may cause the person traveling through it to end up 15 years in the future. Another wormhole may cause the person to end up 42 years in the past.

A brilliant physicist, living on earth, wants to use wormholes to study the Big Bang. Since warp drive has not been invented yet, it is not possible for Rick and Morty to travel from one star system to another one directly. This can be done using wormholes, of course
 
The scientist wants to reach a cycle of wormholes somewhere in the universe that causes him to end up in the past. By traveling along this cycle a lot of times, the scientist is able to go back as far in time as necessary to reach the beginning of the universe and see the Big Bang with his own eyes. Write a program to find out whether such a cycle exists.

# Input
The input file starts with a line containing the number of cases c to be analyzed. Each case starts with a line with two numbers n and m. These indicate the number of star systems (1 ≤ n ≤ 1000) and the number of wormholes (0 ≤ m ≤ 2000). The star systems are numbered from 0 (our solar system) through n − 1. For each wormhole a line containing three integer numbers x, y and t is given. These numbers indicate that this wormhole allows someone to travel from the star system numbered x to the star system numbered y, thereby ending ending up t (−1000 ≤ t ≤ 1000) years in the future.

# Output
The output consists of c lines, one line for each case, containing the word ”possible” if it is indeed possible to go back in time indefinitely, or ”not possible” if this is not possible with the given set of star systems and wormholes.
 
# Example Output
$  cat  portal . txt 2

3  3

0  1  1000

1  2  15

2  1   -42


4  4

0  1  10

1  2  20

2  3  30

3  0   -60


**$ g++ main . cpp**

Time to load data into the portal device: portal.txt 

Possible

Not   Possible
