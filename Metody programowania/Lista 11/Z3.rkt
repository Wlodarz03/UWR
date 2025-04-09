#lang plait


;; abstract syntax -------------------------------

(define-type Op
  (add) (sub) (mul) (div) (eql) (leq))

(define-type Exp
  (numE [n : Number])
  (opE [op : Op] [l : Exp] [r : Exp])
  (ifE [b : Exp] [l : Exp] [r : Exp])
  (varE [x : Symbol])
  (letE [bindings : (Listof (Symbol * Exp))] [body : Exp])
  (let*E [bindings : (Listof (Symbol * Exp))] [body : Exp]))
  ;(letE [x : Symbol] [e1 : Exp] [e2 : Exp]))

;; parse ----------------------------------------

(define (parse [s : S-Exp]) : Exp
  (cond
    [(s-exp-match? `NUMBER s)
     (numE (s-exp->number s))]
    [(s-exp-match? `{SYMBOL ANY ANY} s)
     (opE (parse-op (s-exp->symbol (first (s-exp->list s))))
          (parse (second (s-exp->list s)))
          (parse (third (s-exp->list s))))]
    [(s-exp-match? `{if ANY ANY ANY} s)
     (ifE (parse (second (s-exp->list s)))
          (parse (third (s-exp->list s)))
          (parse (fourth (s-exp->list s))))]
    [(s-exp-match? `SYMBOL s)
     (varE (s-exp->symbol s))]
    [(s-exp-match? `{let {SYMBOL ANY} ... ANY} s)
     (parse-bindings (butlastfirst (s-exp->list s)) (last (s-exp->list s)))]
    [(s-exp-match? `{let* {SYMBOL ANY} ... ANY} s)
     (parse-bindings2 (butlastfirst (s-exp->list s)) (last (s-exp->list s)))]
    #;[(s-exp-match? `{let SYMBOL ANY ANY} s)
     (letE (s-exp->symbol (second (s-exp->list s)))
           (parse (third (s-exp->list s)))
           (parse (fourth (s-exp->list s))))]
    [else (error 'parse "invalid input")]))

(define (butlastfirst list)
  (reverse (rest (reverse (rest list)))))

(define (last list)
  (first (reverse list)))

(define (parse-binding [binding : S-Exp]) : (Symbol * Exp)
  (pair (s-exp->symbol (first (s-exp->list binding)))
        (parse (second (s-exp->list binding)))))

(define (parse-bindings [bindings : (Listof S-Exp)] [body : S-Exp]) : Exp
  (letE (map parse-binding bindings)
        (parse body)))

(define (parse-bindings2 [bindings : (Listof S-Exp)] [body : S-Exp]) : Exp
  (let*E (map parse-binding bindings)
        (parse body)))


(define (parse-op [op : Symbol]) : Op
  (cond
    [(eq? op '+) (add)]
    [(eq? op '-) (sub)]
    [(eq? op '*) (mul)]
    [(eq? op '/) (div)]
    [(eq? op '=) (eql)]
    [(eq? op '<=) (leq)]
    [else (error 'parse "unknown operator")]))

;; eval --------------------------------------

;; values

(define-type Value
  (numV [n : Number])
  (boolV [b : Boolean]))

;; primitive operations

(define (op-num-num->proc [f : (Number Number -> Number)]) : (Value Value -> Value)
  (λ (v1 v2)
    (type-case Value v1
      [(numV n1)
       (type-case Value v2
         [(numV n2)
          (numV (f n1 n2))]
         [else
          (error 'eval "type error")])]
      [else
       (error 'eval "type error")])))

(define (op-num-bool->proc [f : (Number Number -> Boolean)]) : (Value Value -> Value)
  (λ (v1 v2)
    (type-case Value v1
      [(numV n1)
       (type-case Value v2
         [(numV n2)
          (boolV (f n1 n2))]
         [else
          (error 'eval "type error")])]
      [else
       (error 'eval "type error")])))

(define (op->proc [op : Op]) : (Value Value -> Value)
  (type-case Op op
    [(add) (op-num-num->proc +)]
    [(sub) (op-num-num->proc -)]
    [(mul) (op-num-num->proc *)]
    [(div) (op-num-num->proc /)]
    [(eql) (op-num-bool->proc =)]
    [(leq) (op-num-bool->proc <=)]))

;; environments

(define-type Binding
  (bind [name : Symbol]
        [val : Value]))

(define-type-alias Env (Listof Binding))

(define mt-env empty)
(define (extend-env [env : Env] [x : Symbol] [v : Value]) : Env
  (cons (bind x v) env))
(define (lookup-env [n : Symbol] [env : Env]) : Value
  (type-case (Listof Binding) env
    [empty (error 'lookup "unbound variable")]
    [(cons b rst-env) (cond
                        [(eq? n (bind-name b))
                         (bind-val b)]
                        [else (lookup-env n rst-env)])]))

(define (extend-more env bindings)
  (if (empty? bindings)
      env
      (extend-more (extend-env env (fst (first bindings))
                                (eval (snd (first bindings)) mt-env))
                    (rest bindings))))

(define (extend-more2 env bindings)
  (if (empty? bindings)
      env
      (extend-more2 (extend-env env (fst (first bindings))
                               (eval (snd (first bindings)) env))
                   (rest bindings))))

;; evaluation function

(define (eval [e : Exp] [env : Env]) : Value
  (type-case Exp e
    [(numE n) (numV n)]
    [(opE o l r) ((op->proc o) (eval l env) (eval r env))]
    [(ifE b l r)
     (type-case Value (eval b env)
       [(boolV v)
        (if v (eval l env) (eval r env))]
       [else
        (error 'eval "type error")])]
    [(varE x)
     (lookup-env x env)]
    [(letE bindings body)
     (eval body (extend-more env bindings))]
    [(let*E bindings body)
     (eval body (extend-more2 env bindings))]))
    #;[(letE x e1 e2)
     (let ([v1 (eval e1 env)])
       (eval e2 (extend-env env x v1)))]

(define (run [e : S-Exp]) : Value
  (eval (parse e) mt-env))

(module+ test
  (test (run `{let {x 2} {y 3} {+ x y}}) (numV 5))
  (test (run `{let* {x 2} {y {+ 1 x}} {+ x y}}) (numV 5))
  (test (run `{let {x 2} {y {+ 1 x}} {+ x y}}) (numV 5)))