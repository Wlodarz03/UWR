#lang plait

;; abstract syntax -------------------------------

(define-type Op
  (add)
  (sub)
  (mul)
  (div))

(define-type Exp
  (numE [n : Number])
  (opE [op : Op] [args : (Listof Exp)]))

;; parse ----------------------------------------

(define (parse [s : S-Exp]) : Exp
  (cond
    [(s-exp-match? `NUMBER s)
     (numE (s-exp->number s))]
    [(s-exp-match? `{SYMBOL ANY ...} s)
     (opE (parse-op (s-exp->symbol (first (s-exp->list s))))
          (map parse (rest (s-exp->list s))))]
    [else (error 'parse "invalid input")]))

(define (parse-op [op : Symbol]) : Op
  (cond
    [(eq? op '+) (add)]
    [(eq? op '-) (sub)]
    [(eq? op '*) (mul)]
    [(eq? op '/) (div)]
    [else (error 'parse "unknown operator")]))

;; eval --------------------------------------

(define-type-alias Value Number)

(define (op->proc [op : Op]) : (Value Value -> Value)
  (type-case Op op
    [(add) +]
    [(sub) -]
    [(mul) *]
    [(div) /]))

(define (op-init [op : Op])
  (type-case Op op
    [(add) 0]
    [(sub) 0]
    [(mul) 1]
    [(div) 1]))

#;(define (helper xs acc f fi) 
    (if (empty? xs)
        acc
        (if (and (= fi (first xs)) (not (= fi +inf.0)))
            (helper (rest xs) (f (first xs) acc) f +inf.0)
            (helper (rest xs) (f acc (first xs)) f fi))))

(define (helper xs acc f size)
  (if (empty? xs)
      acc
      (if (= size (length xs))
          (helper (rest xs) (f (first xs) acc) f (+ size 1))
          (helper (rest xs) (f acc (first xs)) f (+ size 1)))))
            
(define (my-foldl f x xs)
  (helper xs x f (length xs)))

(define (eval [e : Exp]) : Value
  (type-case Exp e
    [(numE n) n]
    [(opE o args)
     (if (empty? args)
         0
         (my-foldl (op->proc o) (op-init o) (map eval args)))]))

(define (run [e : S-Exp]) : Value
  (eval (parse e)))

(module+ test
  (test (run `(+ 1 2 3)) 6)
  (test (run `(- 1 2 3 4)) -8)
  (test (run `(- 1 2 3 4 (+ 3 4 5))) -20)
  (test (run `(+ (- 1 2))) -1)
  (test (run `(+)) 0)
  (test (run `(/ 1 2 3)) 1/6)
  (test (run `(* 2)) 2))
