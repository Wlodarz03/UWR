#lang racket

(define (fib n)
  (cond ([= n 0] 0)
        ([= n 1] 1)
        [else (+ (fib (- n 1)) (fib (- n 2)))]))

(define (fib-iter n)
  (define (it n f1 f2)
    (if (= n 0)
        f2
        (it (- n 1) (+ f1 f2) f1)))
    (it n 1 0))



;(fib 5)->(cond ...)
;->(fib 4) + (fib 3)
;->(fib 3) + (fib 2) + (fib 2) + (fib 1)
;->(fib 2) + (fib 1) + (fib 1) + (fib 0) + (fib 1) + (fib 0) + (fib 1)
;->(fib 1) + (fib 0) + (fib 1) + (fib 1) + (fib 0) + (fib 1) + (fib 0) + (fib 1) = 5
; duzo wywolan

;(fib-iter 5) 
;-> (it 5 1 0)
;-> (it 4 1 1)
;-> (it 3 2 1)
;-> (it 2 3 2)
;-> (it 1 5 3)
;-> (it 0 8 5) = 5

;(fib-iter n) bedzie szybszy od (fib n), przy wiekszych n czas obliczeń iteracyjnie rośnie liniowo
; a przy rekurencji im wieksze n tym wiecej wywolan rekurencyjnych i czas gorszy