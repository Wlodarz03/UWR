#lang plait

(module+ test
  (print-only-errors #t))

;; abstract syntax -------------------------------

(define-type Op
  (add)
  (sub)
  (mul)
  (leq))

(define-type Def
  (defD [fun : (Listof Func)] [e : Exp]))

(define-type Func
  (funF [name : Symbol] [args : (Listof Symbol)] [body : Exp]))

(define-type Exp
  (numE [n : Number])
  (varE [x : Symbol])
  (opE [e1 : Exp] [o : Op] [e2 : Exp])
  (ifE [e0 : Exp] [e1 : Exp] [e2 : Exp])
  (letE [x : Symbol] [e1 : Exp] [e2 : Exp])
  (appE [name : Symbol] [args : (Listof Exp)]))

;; parser --------------------------------


(define (parse-exp [s : S-Exp]) : Exp
  (cond
    [(s-exp-match? `NUMBER s)
     (numE (s-exp->number s))]
    [(s-exp-match? `SYMBOL s)
     (varE (s-exp->symbol s))]
    [(s-exp-match? `{ANY SYMBOL ANY} s)
     (opE (parse-exp (first (s-exp->list s)))
          (parse-op (s-exp->symbol (second (s-exp->list s))))
          (parse-exp (third (s-exp->list s))))]
    [(s-exp-match? `{ifz ANY then ANY else ANY} s)
     (ifE (parse-exp (second (s-exp->list s)))
          (parse-exp (fourth (s-exp->list s)))
          (parse-exp (last (s-exp->list s))))]
    [(s-exp-match? `{let SYMBOL be ANY in ANY} s)
     (letE (s-exp->symbol (second (s-exp->list s)))
           (parse-exp (fourth (s-exp->list s)))
           (parse-exp (last (s-exp->list s))))]
    [(s-exp-match? `{SYMBOL (ANY ...)} s)
     (appE (s-exp->symbol (first (s-exp->list s)))
           (parse-app (s-exp->list s)))]
    [else (error 'parse "invalid input")]))

(define (parse-func [f : S-Exp]) : Func
  (cond
    [(s-exp-match? `{fun SYMBOL (SYMBOL ...) = ANY} f)
     (funF (s-exp->symbol (second (s-exp->list f)))
           (map s-exp->symbol (s-exp->list(third (s-exp->list f))))
           (parse-exp (last (s-exp->list f))))]
    [else (error 'parse "invalid input")]))

(define (parse-def [d : S-Exp]) : Def
  (cond
    [(s-exp-match? `{define {ANY ...} for ANY} d)
     (defD (map parse-func (s-exp->list (second (s-exp->list d))))
       (parse-exp (last (s-exp->list d))))]
    [else (error 'parse "invalid input")]))
           
(define (parse-op [op : Symbol]) : Op
  (cond
    [(eq? op '+) (add)]
    [(eq? op '-) (sub)]
    [(eq? op '*) (mul)]
    [(eq? op '<=) (leq)]
    [else (error 'parse "unknown operator")]))

(define (last list)
  (first (reverse list)))

(define (parse-app [args : (Listof S-Exp)]) : (Listof Exp)
  (map parse-exp (s-exp->list (second args))))

;; typy ---------------------------

(define-type-alias Value Number)

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

(define-type Bindingf
  (bind2 [name : Symbol]
         [val : ((Listof Symbol) * Exp)]))

(define-type-alias Env2 (Listof Bindingf))

(define (lookup-env2 [env2 : Env2] [name : Symbol])
  (type-case (Listof Bindingf) env2
    [empty (error 'lookup "unbound variable")]
    [(cons b rst-env) (cond
                        [(eq? name (bind2-name b))
                         (bind2-val b)]
                        [else (lookup-env2 rst-env name)])]))

;;funkcje pomocnicze do evala ----------------------------

(define (op->proc [o : Op]) 
  (type-case Op o
    [(add) +]
    [(sub) -]
    [(mul) *]
    [(leq) (lambda (e1 e2) (if (<= e1 e2) 0 42))]))

(define (member? x l) ;funkcja pomocnicza czy x nalezy do l
  (if (empty? l)
      #f
      (if (equal? (first l) x)
          #t
          (member? x (rest l)))))

(define (member2? x l) ;do sprawdzania czy nazwa funkcji juz wystapila
  (if (empty? l)
      #f
      (if (equal? (bind2-name (first l)) x)
          #t
          (member2? x (rest l)))))

(define (helper list env) ;eval-func na calej liscie (do funkcji w define)
  (if (empty? list)
      env
      (helper (rest list) (eval-func (first list) env))))

(define (extend-more env l1 l2) ;rozszerzanie env o Bind (zmienna z funkcji , argument) 
  (if (= (length l1)(length l2))
      (if (empty? l1)
          env
          (extend-more (extend-env env (first l1) (first l2)) (rest l1) (rest l2)))
      (error 'app "zla ilosc argumentow")))

(define (helper2 list env env2) ;eval-exp na calej liscie (do argumentow)
  (if (empty? list)
      empty
      (cons (eval-exp (first list) env env2) (helper2 (rest list) env env2))))

;; eval --------------------------------

(define (eval-func [f : Func] [env2 : Env2]) ;eval funkcji tylko rozszerza env2
  (type-case Func f
    [(funF name args body)
     (if (member2? name env2)
         (error 'funkcja "byla juz")
         (cons (bind2 name (pair args body)) env2))]))

(define (eval-def [d : Def] [env : Env] [env2 : Env2])
  (type-case Def d
    [(defD fun e)
     (eval-exp e env (helper fun env2))]))
      
(define (eval-exp [e : Exp] [env : Env] [env2 : Env2]) : Value
  (type-case Exp e
    [(numE n) n]
    [(varE x) (lookup-env x env)]
    [(opE e1 o e2)
     ((op->proc o) (eval-exp e1 env env2) (eval-exp e2 env env2))]
    [(ifE e0 e1 e2)
     (if (= (eval-exp e0 env env2) 0)
         (eval-exp e1 env env2)
         (eval-exp e2 env env2))]
    [(letE x e1 e2)
     (eval-exp e2 (extend-env env x (eval-exp e1 env env2)) env2)]
    [(appE name args)
     (eval-exp (snd (lookup-env2 env2 name)) (extend-more mt-env (fst (lookup-env2 env2 name)) (helper2 args env env2)) env2)]))

;; run ----------------------
    
(define (run [e : S-Exp]) : Value
  (eval-def (parse-def e) empty empty))

;; testy -------------------

(module+ test
  (test (run `{define
                 {[ fun fact ( n ) = { ifz n then 1 else { n * { fact ({ n - 1}) }}}]}
                 for
                 { fact (5) }}) 120)
  (test (run `{ define
                  {[ fun even ( n ) = { ifz n then 0 else { odd ({ n - 1}) }}]
                   [ fun odd ( n ) = { ifz n then 42 else { even ({ n - 1}) }}]}
                  for
                  { even (1024) }}) 0)
  (test (run `{ define
                 {[ fun gcd ( m n ) = { ifz n
                                            then m
                                            else { ifz { m <= n }
                                                       then { gcd ( m { n - m }) }
                                                       else { gcd ({ m - n } n ) }}}]}
                 for
                 { gcd (81 63) }}) 9))