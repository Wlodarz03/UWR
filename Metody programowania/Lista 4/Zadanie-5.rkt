#lang racket

(define-struct leaf () #:transparent)
(define-struct node (l elem r) #:transparent)

(define (fold-tree f x tree)
  (cond [(leaf? tree) x]
        [(node? tree)
         (f (fold-tree f x (node-l tree))
            (node-elem tree)
            (fold-tree f x (node-r tree)))]))

(define (flatten t)
  (fold-tree (lambda (l elem r) (append l (list elem) r)) '() t))

(define (insert-bst x t)
  (cond [(leaf? t) (node (leaf) x (leaf))]
        [(node? t)
         (cond [(< x (node-elem t))
                (node (insert-bst x (node-l t))
                      (node-elem t)
                      (node-r t))]
               [else (node (node-l t)
                           (node-elem t)
                           (insert-bst x (node-r t)))])]))

(define (treesort xs)
  (define (pom xs t) ; funkcja bierze po kolei elementy z listy i robi insert-bst
    (if (empty? xs) (flatten t)
        (pom (cdr xs) (insert-bst (car xs) t))))
    (pom xs (leaf)))


( define t
   ( node
     ( node ( leaf ) 2 ( leaf ) )
     5
     ( node ( node ( leaf ) 6 ( leaf ) )
            8
            ( node ( leaf ) 9 ( leaf ) ) ) ) )