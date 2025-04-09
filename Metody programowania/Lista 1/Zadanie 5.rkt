#lang racket

(define (a-plus-abs-b a b)
  ((if (> b 0) + -) a b))

;a-plus-abs-b a b to suma a oraz wartości bezwzględnej b