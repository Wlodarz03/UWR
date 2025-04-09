#lang racket

(require rackunit)

(define (suma a b c)
  (if (> a b) (if (> b c) (+ (* a a)(* b b))(+ (* a a)(* c c)))
      (if (> a c)  (+ (* a a) (* b b)) (+ (* b b)(* c c)))))

(check-equal? (suma 1 2 3) 13)
(check-equal? (suma 1 3 2) 13)
(check-equal? (suma 2 1 3) 13)
(check-equal? (suma 2 3 1) 13)
(check-equal? (suma 3 1 2) 13)
(check-equal? (suma 3 2 1) 13)
(check-true (number? (suma 3 2 1)))