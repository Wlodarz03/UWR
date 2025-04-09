#lang racket
(define (my-foldl f x xs)
  (define (it xs acc)
    (if (null? xs)
        acc
        (it (cdr xs) (f (car xs) acc))))
  (it xs x))

(define (product1 list)
  (if (null? list)
      0
      (my-foldl * 1 list)))

(define (product list)
  (if (null? list)
      0
      (foldl * 1 list)))