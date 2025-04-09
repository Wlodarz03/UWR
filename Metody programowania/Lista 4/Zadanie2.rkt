#lang racket

(define-struct leaf () #:transparent)
(define-struct node (l elem r) #:transparent)

(define (fold-tree f x tree)
  (cond [(leaf? tree) x]
        [(node? tree)
         (f (fold-tree f x (node-l tree))
            (node-elem tree)
            (fold-tree f x (node-r tree)))]))

(define (tree-sum tree)
  (fold-tree + 0 tree))

(define (tree-flip tree)
  (fold-tree (lambda (l elem r) (node r elem l)) (leaf) tree))

(define (tree-height tree)
  (fold-tree (lambda (l elem r)
              (+ 1 (max l r)))
            0
            tree))

(define (tree-span t)
  (cons
   (fold-tree (lambda (l elem r) (if (leaf? l) elem l)) (leaf) t)
  (fold-tree (lambda (l elem r) (if (leaf? r) elem r)) (leaf) t)))

(define (flatten t)
  (fold-tree (lambda (l elem r) (append l (list elem) r)) '() t))
            

( define t
   ( node
     ( node ( leaf ) 2 ( leaf ) )
     5
     ( node ( node ( leaf ) 6 ( leaf ) )
            8
            ( node ( leaf ) 9 ( leaf ) ) ) ) )

(define t2
  (node (leaf)
        5
        (node (leaf) 6 (leaf))))

(define h
  (node
   (node
    (node
     (node (leaf) 11 (leaf))
      3
      (leaf))
     8
     (leaf))
   5
   (node
    (leaf)
    9
    (node (leaf) 6 (leaf)))))
