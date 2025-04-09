#lang racket

(define (minimum xs) ;znajduje minimum
  (define (m? xs it a)
    (if (< it 0)
        a
        (if (< (list-ref xs it) a)
               (m? xs (- it 1) (list-ref xs it))
               (m? xs (- it 1) a))))
  (m? xs (- (length xs) 1) (list-ref xs (- (length xs) 1))))

(define (ind-min xs) ; index minimum
  (define (i xs it)
    (if (= (list-ref xs it) (minimum xs))
        it
        (i xs (- it 1))))
  (if (< (- (length xs) 1) 0)
      0
      (i xs (- (length xs) 1))))

(define (select xs) ; minimum na poczatek, reszta bez zmian w ogonie
  (define minin (ind-min xs))
  (define min (minimum xs))
  (define (it n xs ys)
    (if (= n minin)
        (cons min (append (reverse ys) (cdr xs)))
        (it (+ n 1) (cdr xs) (cons (car xs) ys))))
  (if (= (length xs) 0)
      '()
     (it 0 xs null)))

(define (select-sort xs) ;sortowanie
  (define (ss xs ys)
    (if (equal? xs null)
        (reverse ys)
        (ss (cdr (select xs)) (cons (car (select xs)) ys))))
  (ss xs null))