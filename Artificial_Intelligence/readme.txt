Leonardo Freiherr von Lerchenfeld
Matrikelnr.: 03637585
MATLAB 2016b - ladders.m

---

At the initialization, my algorithm divides the wordlist into groups corresponding to the amount of letters. Furthermore, it calculates how many letters are different from the startword to the goalword (="stepsize"). 

Then it calls the function search providing the possible candidates (at the beginning this is only the startword). It counts the number of letters of the candidate and looks in the list of words that have 1 letter more or less. A word is accepted as a next candidate, iff

- it has not been used already,
- only 1 letter is different from the next candidate to the current candidate,
- the difference between the next candidate to the goalword is smaller/equal to the stepsize+1

If the next candidate fulfills all criteria, then it`s path and its stepsize are saved. 

This iteration continues until the goalword is found.


