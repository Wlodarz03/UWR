#lang racket

(define-struct leaf () #:transparent)
(define-struct node (l elem r) #:transparent)

(define (fold-tree f x tree)
  (cond [(leaf? tree) x]
        [(node? tree)
         (f (fold-tree f x (node-l tree))
            (node-elem tree)
            (fold-tree f x (node-r tree)))]))

( define t
   ( node
     ( node ( leaf ) 2 ( leaf ) )
     5
     ( node ( node ( leaf ) 6 ( leaf ) )
            8
            ( node ( leaf ) 9 ( leaf ) ) ) ) )

(define (flatten t)
  (fold-tree (lambda (l elem r) (append l (list elem) r)) '() t))

( define (list->left-tree xs )
   ( foldl ( lambda ( x t ) ( node t x ( leaf ) ) ) ( leaf ) xs ) )

( define test-tree ( list->left-tree ( build-list 20000 identity ) ) )

(define (flat-append t xs)
  (cond [(leaf? t) xs]
        [(node? t)
         (flat-append (node-l t)
                      (cons (node-elem t) (flat-append (node-r t) xs)))]))

(define (flatten2 t)
  (flat-append t '()))


;(equal? (flatten t) (flatten2 t))
    