#lang racket

(define-struct leaf () #:transparent)
(define-struct node (l elem r) #:transparent)

(define (leftmost-elem t)
  (cond [(leaf? t) (leaf)]
        [(leaf? (node-l t)) (node-elem t)]
        [else (leftmost-elem (node-l t))]))

(define (delete-bst x t)
  (cond [(leaf? t) (leaf)]
        [(= x (node-elem t))
         (cond [(leaf? (node-l t)) (node-r t)]
               [(leaf? (node-r t)) (node-l t)]
               [else (node (node-l t)
                           (leftmost-elem (node-r t))
                           (delete-bst (leftmost-elem (node-r t)) (node-r t)))])]
        [(< x (node-elem t))
         (node (delete-bst x (node-l t))
               (node-elem t)
               (node-r t))]
        [else
         (node (node-l t)
               (node-elem t)
               (delete-bst x (node-r t)))]))

( define t
   ( node
     ( node ( leaf ) 2 ( leaf ) )
     5
     ( node ( node ( leaf ) 6 ( leaf ) )
            8
            ( node ( leaf ) 9 ( leaf ) ) ) ) )

               