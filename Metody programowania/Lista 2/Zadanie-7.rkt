#lang racket


(define (suffixes xs)
  (if (null? xs)
      (list '())
      (cons xs (suffixes (cdr xs)))))

; (suffixes '(1 2 3 4) ->
; (cons '(1 2 3 4) (suffixes '(2 3 4))) ->
; (cons '(1 2 3 4) (cons '(2 3 4) (suffixes '(3 4)))) ->
; (cons '(1 2 3 4) (cons '(2 3 4) (cons '(3 4) (suffixes '(4))))) ->
; (cons '(1 2 3 4) (cons '(2 3 4) (cons '(3 4) (cons '(4) (suffixes '()))))) ->
; (cons '(1 2 3 4) (cons '(2 3 4) (cons '(3 4) (cons '(4) (list '()))))) ->
; (cons '(1 2 3 4) (cons '(2 3 4) (cons '(3 4) '((4) ())))) ->
; (cons '(1 2 3 4) (cons '(2 3 4) '((3 4) (4) ()))) ->
; (cons '(1 2 3 4) '((2 3 4) (3 4) (4) ()) ->
; '((1 2 3 4) (2 3 4) (3 4) (4) ())
