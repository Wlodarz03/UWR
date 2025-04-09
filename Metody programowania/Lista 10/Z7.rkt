#lang plait

;(define-syntax do
 ; (syntax-rules ()
  ;  [(do () a)
   ;  a]
    ;[(do ([x1 a1] [x2 a2] ...) a)
    ; (bind a1 (λ (x1) (do ([x2 a2] ...) a)))]))


(define-syntax my-and
  (syntax-rules ()
    [(my-and) #t] ;jeżeli doszlismy do konca i brak jest jakiegokolwiek argumentu, zwracam #t
    [(my-and x1 x2 ...)
     (if x1
         (my-and x2 ...) ;jak choć jeden się okaże fałszem, to otrzymam #f
         #f)]))

(define-syntax my-or
  (syntax-rules ()
    [(my-or) #f] ;jeżeli doszlismy do konca i brak jest jakiegokolwiek argumentu, zwracam #f
    [(my-or x1 x2 ...)
       (if x1
           #t ;jak choć jeden się okaże prawda, to otrzymam #t
           (my-or x2 ...))]))

(my-and (= 2 2) (> 3 2) (< 4 5)) ; Zwróci #t
(my-or (= 2 2) (> 3 2) (< 4 5)) ; Zwróci #t
(my-and (= 2 2) (< 3 2) (> 4 5)) ; Zwróci #f
(my-or (= 2 2) (< 3 2) (> 4 5)) ; Zwróci #t

(define-syntax my-let
  (syntax-rules ()
    [(my-let () a) a]
    [(my-let ([x1 a1] [x2 a2] ...) body)
     ((lambda (x1 x2 ...) body) a1 a2 ...)]))

(define-syntax my-let*
  (syntax-rules ()
    [(my-let* () a) a]
    [(my-let* ([x1 a1] [x2 a2] ...) body)
     ((lambda (x1) (my-let* ([x2 a2] ...) body)) a1)]))

(my-let ((x 2)
          (y 3))
  (+ x y)) ; Zwróci 5

(my-let* ((x 1)
          (y (+ x 2))
          (z (+ y 1)))
  (+ x z)) ; zwraca 1 + 2 + 1 + 1 = 5

(my-let ((x 2) (y 3))
          (my-and (= x 2) (= y 3)))