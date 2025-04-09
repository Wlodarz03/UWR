#lang racket

;(let ([x 3])
  ;(+ x y))
; x - zwiazane , y - wolne

;(let ([x 1]
      ;[y (+ x 2)])
  ;(+ x y))
; x - zwiazane przez [x 1] , y - zwiazane przez [y (+ x 2)] -> inny x!=1 wolny x , + -> zmienna wolna (moze byc tez mnozeniem)

;(let ([x 1])
  ;(let ([y (+ x 2)])
    ;(* x y)))
; x - zwiazane z [x 1] i [y (+ x 2)] , y - zwiazane [y (+ x 2)] ; +,* - wolne

;(define (f x y)
  ;(* x y z))
; x,y -zwiazane, z - wolne ; * - wolne ; f - wiazace 

;(define (f x)
  ;(define (g y z)
    ;(* x y z))
  ;(f x x x))
; x,y,z - zwiazane ; f,g - wiazace ; * - wolne
;let w lecie == let*

;do komentowaniu paru linijek #| zamykamy |#