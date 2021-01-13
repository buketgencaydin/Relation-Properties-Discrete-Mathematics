# Relation-Properties-Discrete-Maths

--------------------------
-> Compile the source file: 

	$ g++ -o relations relations.cpp -std=gnu++11
-> Run

	$ ./relations 	
	
--------------------------

An algorithm to determine if a given relation R is reflexive, symmetric, anti-symmetric, and transitive.

-> Read the relations in the text file "input.txt".

-> Let R be a relation on a set A. Each relation R is represented with 3 lines in
the file:

1. The first line says how many relations in R.

2. The second line gives the elements of the set A.

3. The following lines gives each relation in R.


-> output.txt:

1. Start a new line with "n" which indicates a new relation.

2. The set of R

3. Reflexive: Yes or No, explain the reason if No (e.g. "(a, a) is not found").

4. Symmetric: Yes or No, explain the reason if No (e.g. "(b, a) is not found whereas (a, b) is found.")

5. Antisymmetric: Yes or No, explain the reason if No (e.g. "(b, a) and (a, b) are found.")

6. Transitive: Yes or No, explain the reason if No (e.g. "(a, c) is not found whereas (a, b) and (b, c)
are found.")
