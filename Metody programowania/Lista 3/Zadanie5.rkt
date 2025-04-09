#lang racket

(define (negatives n)
  (build-list n (lambda (x) (- (- 1 2) x))))

(negatives 6)

(define (reciprocals n)
  (build-list n (lambda (x) (/ 1 (+ x 1)))))

(reciprocals 6)

(define (evens n)
  (build-list n (lambda (x) (* (+ x 1) 2))))

(evens 6)

(define (identityM n)
  (build-list n (lambda (x) (build-list n (lambda (y) (if (= x y) 1 0))))))

(identityM 3)
