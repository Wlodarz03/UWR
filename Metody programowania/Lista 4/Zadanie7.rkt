#lang racket

(define empty-queue (cons '() '()))

(define (empty? q)
  (null? (car q)))

(define (push-back x q)
  (if (empty? q)
      (cons '() (list x))
       (cons (car q) (cons x (cdr q)))))

(define (front q)
  (car (car q)))

(define (pop q)
  (cond
    [(and (null? (car q)) (null? (cdr q)))
     empty-queue]
    [(and (null? (cdr(car q))) (not (null? (cdr q))))
      (cons (reverse (cdr q)) '())]
    [else
      (cons (cdr (car q)) (cdr q))]))

(define q1 (cons '(1 2 3 4) '(6 5)))