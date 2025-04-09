#lang racket

;(parametric->/c [a b] (-> a b a))
;(a b -> a) pierwsze a i b - negatywne, drugie a - pozytywne

(define/contract (f1 a b)
  (parametric->/c [a b] (-> a b a))
  a)

;(parametric->/c [a b c] (-> (-> a b c) (-> a b) a c))
;((a b ->c) (a->b) a -> c) pierwsze a,pierwsze b,drugie a i drugie c - pozytywne reszta -negatywne

(define/contract (f2 f g x)
  (parametric->/c [a b c] (-> (-> a b c) (-> a b) a c))
  (f (g x) x))

;(parametric->/c [a b c] (-> (-> b c) (-> a b) (-> a c)))
;((b->c)(a->b)->(a->c) pierwsze b,pierwsze a i drugie c - pozytywne; reszta -negatywne

(define/contract (f3 f g)
  (parametric->/c [a b c] (-> (-> b c) (-> a b) (-> a c)))
  (lambda (x) (f (g x))))

;(parametric->/c [a] (-> (-> (-> a a) a) a))
;(((a->a)->a)->a) drugie a i ostatnie a - pozytywne , pierwsze i trzecie a -negatywne 

(define/contract (f4 f)
  (parametric->/c [a] (-> (-> (-> a a) a) a))
  (f (lambda (x)(f (lambda (x) x)))))