import sys

def B(i,j):
    return 'B_%d_%d' % (i,j)

def domains(Bs):
    return [ q + ' in 0..1' for q in Bs ]

def get_row(i, C):
    return [B(i,j) for j in range(C)] 
            
def get_column(j, R):
    return [B(i,j) for i in range(R)]

def triplets(R, C):
    cons = []
    # poziomo
    for i in range(R):
        for j in range(1, C-1):
            cons.append('tuples_in([[%s, %s, %s]], [[1, 1, 1], [0, 1, 1], [0, 0, 1], [0, 0, 0], [1, 0, 0], [1, 1, 0], [1, 0, 1]])' % (B(i, j-1), B(i, j), B(i, j+1)))

    # pionowo
    for j in range(C):
        for i in range(1, R-1):
            cons.append('tuples_in([[%s, %s, %s]], [[1, 1, 1], [0, 1, 1], [0, 0, 1], [0, 0, 0], [1, 0, 0], [1, 1, 0], [1, 0, 1]])' % (B(i-1, j), B(i, j), B(i+1, j)))
    
    return cons

def squares(R, C):
    cons = []
    for i in range(R-1):
        for j in range(C-1):
            cons.append('tuples_in([[%s, %s, %s, %s]], [[1, 1, 1, 1], [0, 0, 0, 0],' 
            '[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1],' 
            '[1, 1, 0, 0], [1, 0, 1, 0], [0, 1, 0, 1], [0, 0, 1, 1]])' % (B(i, j), B(i, j+1), B(i+1, j), B(i+1, j+1)))

    return cons

def rowSums(R, C, rows):
    cons = []
    for i in range(R):
        cons.append('sum([%s], #=, %d)' % (', '.join(get_row(i, C)), rows[i]))

    return cons

def colSums(R, C, cols):
    cons = []
    for j in range(C):
        cons.append('sum([%s], #=, %d)' % (', '.join(get_column(j, R)), cols[j]))

    return cons

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
    
def storms(R, C, fills, rows, cols):
    variables = [ B(i,j) for i in range(R) for j in range(C)]

    print (':- use_module(library(clpfd)).')
    print ('solve([' + ', '.join(variables) + ']) :- ')
  
    cs = domains(variables) + triplets(R, C) + squares(R, C) + rowSums(R, C, rows) + colSums(R, C, cols)
    for i,j,val in fills:
        cs.append( '%s #= %d' % (B(i,j), val) )

    print_constraints(cs, 4, 120),
    print ()
    print ('    labeling([ff], [' +  ', '.join(variables) + ']).' )
    print ()
    print (':- solve(X), write(X), nl.')  

if __name__ == '__main__':
  inputFile = open('zad_input.txt', 'r')

  rows = list(map(int, inputFile.readline().strip().split()))
  R = len(rows)

  cols = list(map(int, inputFile.readline().strip().split()))
  C = len(cols)  

  fills = []
  for line in inputFile:
    fills.append(list(map(int, line.strip().split())))

  with open('zad_output.txt', 'w') as sys.stdout:
    storms(R, C, fills, rows, cols)          