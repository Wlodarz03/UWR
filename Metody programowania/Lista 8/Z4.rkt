#lang plait

(define-type Op
  (op-add) (op-mul) (op-sub) (op-div))

(define (parse-Op s)
  (let ([sym (s-exp->symbol s)])
  (cond
    [(equal? sym '+) (op-add)]
    [(equal? sym '-) (op-sub)]
    [(equal? sym '*) (op-mul)]
    [(equal? sym '/) (op-div)])))

(define (exp-eval s)
  (cond [(s-exp-number? s) (s-exp->number s)]
        [(s-exp-list? s)
         (let [(xs (s-exp->list s))]
           (let [(op (parse-Op (first xs)))]
             (cond [(equal? op (op-add)) (+ (exp-eval (second xs))(exp-eval (third xs)))]
                   [(equal? op (op-sub)) (- (exp-eval (second xs))(exp-eval (third xs)))]
                   [(equal? op (op-mul)) (* (exp-eval (second xs))(exp-eval (third xs)))]
                   [(equal? op (op-div)) (/ (exp-eval (second xs))(exp-eval (third xs)))])))]))

(define e `(+ 2 (- 5 2)))