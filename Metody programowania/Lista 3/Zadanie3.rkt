#lang racket

(( lambda ( x y ) (+ x (* x y ) ) ) 1 2)
; = (+ 1 (* 1 2)) = 3

;(( lambda ( x ) x ) ( lambda ( x ) x ) )
; = (lambda (( lambda ( x ) x )) ( lambda ( x ) x ))
; = (lambda (x) x) -> procedura ktora zwraca swoj argument
((( lambda ( x ) x ) ( lambda ( x ) x ) ) 2)

;(( lambda ( x ) ( x x ) ) ( lambda ( x ) x ) )
; = (lambda (( lambda ( x ) x )) (( lambda ( x ) x ) ( lambda ( x ) x ))
; ((lambda (x) x) (lambda (x) x)) = (lambda (x) x) - z poprzedniego podpunktu
; = (lambda ((lambda (x) x)) (lambda (x) x))
; = (lambda (x) x)

;(( lambda ( x ) ( x x ) ) ( lambda ( x ) ( x x ) ) )

; = (lambda (( lambda ( x ) ( x x ) )) (( lambda ( x ) ( x x ) ) ( lambda ( x ) ( x x ) ))
; = (lambda (( lambda ( x ) ( x x ) )) ((lambda (( lambda ( x ) ( x x ) )) (( lambda ( x ) ( x x ) ) ( lambda ( x ) ( x x ) ))
; i tak w nieskonczonosc bedzie roslo i nic nie wyjdzie