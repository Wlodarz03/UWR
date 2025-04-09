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

(define (maximum xs)
  (define ind (- (length xs) 1))
  (if (null? xs)
      -inf.0
      (list-ref (insertion-sort xs) ind)))