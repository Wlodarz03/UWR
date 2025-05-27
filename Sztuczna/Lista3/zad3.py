import sys

def V(i,j):
    return 'V%d_%d' % (i,j)
    
def domains(Vs):
    return [ q + ' in 1..9' for q in Vs ]
    
def all_different(Qs):
    return 'all_distinct([' + ', '.join(Qs) + '])'
    
def get_column(j):
    return [V(i,j) for i in range(9)] 
            
def get_raw(i):
    return [V(i,j) for j in range(9)] 
                        
def horizontal():   
    return [ all_different(get_raw(i)) for i in range(9)]

def vertical():
    return [all_different(get_column(j)) for j in range(9)]

def square(i, j): # kwadrat 3x3 który ma lewy górny róg w i, j
    vals = []
    for x in range(i, i + 3):
        for y in range(j, j + 3):
            vals.append(V(x, y))
    return vals

def squares():
    return [all_different(square(i, j)) for i in range(0, 7, 3) for j in range(0, 7, 3)]

def print_constraints(Cs, indent, d):
    position = indent
    print (indent * ' ', end='')
    for c in Cs:
        print (c + ',', end=' ')
        position += len(c)
        if position > d:
            position = indent
            print ()
            print (indent * ' ', end='')

      
def sudoku(assigments):
    variables = [ V(i,j) for i in range(9) for j in range(9)]
    
    print (':- use_module(library(clpfd)).')
    print ('solve([' + ', '.join(variables) + ']) :- ')
    
    
    cs = domains(variables) + vertical() + horizontal() + squares() #TODO: too weak contraints, add something!
    for i,j,val in assigments:
        cs.append( '%s #= %d' % (V(i,j), val) )
    
    print_constraints(cs, 4, 70),
    print ()
    print ('    labeling([ff], [' +  ', '.join(variables) + ']).' )
    print ()
    print (':- solve(X), write(X), nl.')       

if __name__ == "__main__":
    raw = 0
    triples = []
    inputFile = open('zad_input.txt', 'r')
    with open('zad_output.txt', 'w') as sys.stdout:
    
        for x in inputFile.readlines():
            x = x.strip()
            if len(x) == 9:
                for i in range(9):
                    if x[i] != '.':
                        triples.append( (raw,i,int(x[i])) ) 
                raw += 1
        sudoku(triples)
    
    inputFile.close()
    
"""
89.356.1.
3...1.49.
....2985.
9.7.6432.
.........
.6389.1.4
.3298....
.78.4....
.5.637.48

8,9,4,3,5,6,7,1,2
3,2,5,7,1,8,4,9,6
7,1,6,4,2,9,8,5,3
9,8,7,1,6,4,3,2,5
2,4,1,5,7,3,6,8,9
5,6,3,8,9,2,1,7,4
4,3,2,9,8,1,5,6,7
6,7,8,2,4,5,9,3,1
1,5,9,6,3,7,2,4,8

53..7....
6..195...
.98....6.
8...6...3
4..8.3..1
7...2...6
.6....28.
...419..5
....8..79

3.......1
4..386...
.....1.4.
6.924..3.
..3......
......719
........6
2.7...3..
"""    
