#lang racket

(define (empty-set)
  (lambda (x) #f))

(define (singleton a)
  (lambda (x) (equal? x a))) ; -> procedura ((singleton cos) cos)


(define (in a s)
  (s a)) 

(in 5 (singleton 5))
(in 3 (singleton 5))

(define (union s t)
  (lambda (x) (or (s x) (t x))))

((union (singleton 3) (singleton 5)) 5)
((union (singleton 3) (singleton 5)) 4)
((union (singleton 3) (singleton 5)) 3)

(define (intersect s t)
  (lambda (x) (and (s x) (t x))))

((intersect (singleton 3) (singleton 5)) 3)
((intersect (singleton 3) (singleton 5)) 5)
((intersect (singleton 3) (singleton 3)) 3)

((singleton -21) -21)
(define zbior (union (union (singleton 1) (singleton 2)) (singleton 3)))






