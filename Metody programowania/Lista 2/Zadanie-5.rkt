#lang racket

(require rackunit)

(define (elem x xs)
  (define len (- (length xs) 1))
  (define (e? x xs len)
    (if (equal? (list-ref xs len) x)
        #t
        (if (>= (- len 1) 0)
            (e? x xs (- len 1))
            #f)))
  (e? x xs len))
