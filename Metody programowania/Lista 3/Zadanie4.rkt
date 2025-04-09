#lang racket

(define (square x)
  (* x x))

(define (inc x)
  (+ x 1))

(define (my-compose f g)
  (lambda (x) (f (g x))))

((my-compose square inc) 5)
; (my-compose square inc) -> procedura
; = (lambda (x) (square (inc x))) -> procedura
; ((lambda (x) (square (inc x))) 5)=
; = (square (inc 5)) =
; = (square 6) = 36

((my-compose inc square) 5)
; (my-compose inc square) -> procedura
; = (lambda (x) (inc (square x))) -> procedura
; ((lambda (x) (inc (square x)))5)=
; = (inc (square 5)) =
; = (inc 25) = 26
