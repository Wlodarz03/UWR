#lang racket

(define (fold-right f acc xs) ;bledna
  (if (null? xs)
      acc
      (f (car xs) (fold-right f (car xs) (cdr xs)))))

(define (my-foldr f x xs) ;dobra
  (if (empty? xs)
      x
      (f (car xs) (my-foldr f x (cdr xs)))))

(fold-right + 0 '(1 2 3))
(my-foldr + 0 '(1 2 3))

;(parametric->/c [ a b ] (-> (-> a b b) b ( listof a ) b))
;(parametric->/c [ a ] (-> (-> a a a) a ( listof a ) a))