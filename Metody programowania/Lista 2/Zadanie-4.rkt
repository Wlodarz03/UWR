#lang racket

(define-struct matrix (a b c d)) ; a-b 1 wiersz c-d 2 wiersz

(define (matrix-mult m n)
  (make-matrix (+ (* (matrix-a m) (matrix-a n)) (* (matrix-b m) (matrix-c n)))
               (+ (* (matrix-a m) (matrix-b n)) (* (matrix-b m) (matrix-d n)))
               (+ (* (matrix-c m) (matrix-a n)) (* (matrix-d m) (matrix-c n)))
               (+ (* (matrix-c m) (matrix-b n)) (* (matrix-d m) (matrix-d n)))))

(define matrix-id (make-matrix 1 0 0 1))

(define (matrix-expt-fast m k)
  (cond ([= k 0] matrix-id)
        ([even? k] (matrix-expt-fast (matrix-mult m m) (/ k 2)))
        [else (matrix-mult m (matrix-expt-fast m (- k 1)))]))

(define (fib-fast k)
  (define m (make-matrix 1 1 1 0))
  (define n (matrix-expt-fast m k))
  (matrix-b n))

; np. k=8
; dla fib-fast matrix-expt-fast wywola sie 3 razy (wywolania T(n) = logn)
; a dla fib-matrix matrix-expt wywola sie 8 razy (wywolania T(n) = n)
; zatem fib-fast bedzie szybszy od fib-matrix
;time-apply do czasu