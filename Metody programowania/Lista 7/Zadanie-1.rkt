#lang plait

(define-type (23drzewa 'v)
  (leaf [var1 : 'v])
  (node1 [var1 : 'v][l : (23drzewa 'v)][r : (23drzewa 'v)])
  (node2 [var1 : 'v][var2 : 'v][l : (23drzewa 'v)][mid : (23drzewa 'v)][r : (23drzewa 'v)]))

(define (23tree? tree min max)
  (cond [(leaf? tree)
         (and (< min (leaf-var1 tree))(> max (leaf-var1 tree)))]
        [(node1? tree)
         (if (and (< min (node1-var1 tree))(> max (node1-var1 tree)))
             (and (23tree? (node1-l tree) min (node1-var1 tree))
                  (23tree? (node1-r tree) (node1-var1 tree) max))
             #f)]
        [(node2? tree)
         (if (and (< (node2-var1 tree)(node2-var2 tree))
                  (and
                   (and (< min (node2-var1 tree))(> max (node2-var1 tree)))
                   (and (< min (node2-var2 tree))(> max (node2-var2 tree)))))
             (and (23tree? (node2-l tree) min (node2-var1 tree))
                  (23tree? (node2-r tree) (node2-var2 tree) max)
                  (23tree? (node2-mid tree) (node2-var1 tree)(node2-var2 tree)))
             #f)]))

(define (all tree)
  (cond
    [(leaf? tree) (list 0)]
    [(node1? tree)
     (append (map add1 (all (node1-l tree)))
             (map add1 (all (node1-r tree))))] 
    [(node2? tree)
     (append
      (append (map add1 (all (node2-l tree)))
             (map add1 (all (node2-mid tree))))
             (map add1 (all (node2-r tree))))]))

(define (helper paths)
  (cond [(empty? (rest paths)) #t]
        [(= (first paths)(first (rest paths)))
         (helper (rest paths))]
        [else #f]))

(define (same? tree)
  (helper (all tree)))

(define (is23tree? tree)
  (and (same? tree)(23tree? tree -inf.0 +inf.0)))

(define my23tree
  (node1 6 (node2 2 4 (leaf 1)(leaf 3)(leaf 5))
         (node2 9 11 (leaf 7)(leaf 10)(leaf 12))))

(define my23tree2
  (node1 6 (node2 2 4 (leaf 1)(leaf 3)(leaf 5))
         (node2 9 11 (leaf 7)(leaf 10)(node1 13 (leaf 12) (leaf 14)))))
      