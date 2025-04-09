#lang racket

(define-struct leaf () #:transparent)
(define-struct node (l elem r) #:transparent)


(define (bst? t)
  (define (bst-helper t min max)
    (cond
      [(leaf? t) #t]
      [(and (<= min (node-elem t)) (<= (node-elem t) max))
       (and (bst-helper (node-l t) min (node-elem t))
            (bst-helper (node-r t) (node-elem t) max))]
      [else #f]))
  (bst-helper t -inf.0 +inf.0))


(define (sum-paths t)
  (define (sum-paths-helper t sum-so-far)
    (cond
      [(leaf? t) (leaf)]
      [(node? t)
       (node (sum-paths-helper (node-l t) (+ sum-so-far (node-elem t)))
             (+ sum-so-far (node-elem t))
             (sum-paths-helper (node-r t) (+ sum-so-far (node-elem t))))]))
  (sum-paths-helper t 0))


( define t
   ( node
     ( node ( leaf ) 2 ( leaf ) )
     5
     ( node ( node ( leaf ) 6 ( leaf ) )
            8
            ( node ( leaf ) 9 ( leaf ) ) ) ) )

;(bst? t)
;(sum-paths t)
           