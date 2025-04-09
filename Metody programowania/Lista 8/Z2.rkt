#lang racket

(define (mreverse! xs)
  (define (helper prev curr)
    (if (null? curr)
        prev
        (let [(next (mcdr curr))]
          (set-mcdr! curr prev)
          (helper curr next))))
  (helper null xs))

(define x (mcons 1 (mcons 2 (mcons 3 null))))