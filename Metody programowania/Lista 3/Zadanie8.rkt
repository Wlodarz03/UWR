#lang racket

(define (list->llist xs)
  (lambda (ys) (foldr cons ys xs)))

(define (llist->list f)
  (f '()))

(define llist-null
  (lambda (xs) xs))

(define (llist-singleton xs)
  (list->llist (list xs)))

(define (list-append f g)
  (lambda (x) (f(g x))))