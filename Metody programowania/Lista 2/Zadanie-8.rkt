#lang racket

(define (insert n xs)
  (if (null? xs)
      (list n)
      (if (< n (car xs))
          (cons n xs)
          (cons (car xs) (insert n (cdr xs))))))

(define (insertion-sort xs)
  (define (it xs ys)
    (if (null? xs)
        ys
        (it (cdr xs) (insert (car xs) ys))))
  (it xs null))

(define (sorted? xs)
  (equal? xs (insertion-sort xs)))
