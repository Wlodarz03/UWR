#lang racket

(define (helper xs) ;zwraca ostatni element
        (if (null? (mcdr xs))
            xs
            (helper (mcdr xs))))

(define (cycle! xs)
  (if (null? xs)
      null
      (set-mcdr! (helper xs) xs)))

(define l (mcons 1 (mcons 2 (mcons 3 null))))