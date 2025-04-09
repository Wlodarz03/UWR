#lang plait

( define-type ( Formula 'v )
( var [ var : 'v ])
( neg [ f : ( Formula 'v ) ])
( conj [ l : ( Formula 'v ) ] [ r : ( Formula 'v ) ])
( disj [ l : ( Formula 'v ) ] [ r : ( Formula 'v ) ]) )

( define-type ( NNF 'v )
( nnf-lit [ polarity : Boolean ] [ var : 'v ])
( nnf-conj [ l : ( NNF 'v ) ] [ r : ( NNF 'v ) ])
( nnf-disj [ l : ( NNF 'v ) ] [ r : ( NNF 'v ) ]) )

(define (eval-nnf wart fi)
  (cond [(nnf-lit? fi)
         (equal? (nnf-lit-polarity fi)(wart (nnf-lit-var fi)))]
        [(nnf-conj? fi)
         (and (eval-nnf wart (nnf-conj-l fi)) (eval-nnf wart (nnf-conj-r fi)))]
        [(nnf-disj? fi)
         (or (eval-nnf wart (nnf-disj-l fi)) (eval-nnf wart (nnf-disj-r fi)))]))

(define (neg-nnf fi)
  (cond [(nnf-lit? fi)
         (nnf-lit (not (nnf-lit-polarity fi)) (nnf-lit-var fi))]
        [(nnf-conj? fi)
         (nnf-disj (neg-nnf (nnf-conj-l fi)) (neg-nnf (nnf-conj-r fi)))]
        [(nnf-disj? fi)
         (nnf-conj (neg-nnf (nnf-disj-l fi)) (neg-nnf (nnf-disj-r fi)))]))

(define (to-nnf fi)
  (cond [(var? fi)
         (nnf-lit #t (var-var fi))]
        [(conj? fi)
         (nnf-conj (to-nnf (conj-l fi)) (to-nnf (conj-r fi)))]
        [(disj? fi)
         (nnf-disj (to-nnf (disj-l fi)) (to-nnf (disj-r fi)))]
        [(neg? fi)
         (neg-nnf (to-nnf (neg-f fi)))]))

(define test (neg (neg (var "p"))))
(to-nnf test)


(define (eval-formula wart fi)
  (cond [(var? fi)
         (wart (var-var fi))]
        [(conj? fi)
         (and (eval-formula wart (conj-l fi))
              (eval-formula wart (conj-r fi)))]
        [(disj? fi)
         (or (eval-formula wart (disj-l fi))
             (eval-formula wart (disj-r fi)))]
        [(neg? fi)
         (not (eval-formula wart (neg-f fi)))]))

(define (my-wart v)
  (cond [(equal? v "p")
         #t]
        [(equal? v "q")
         #f]
        [else #f]))

(define my-fi
  (disj (neg (conj  (var "p") (neg (var "q")))) (neg (var "r"))))

my-fi
""
(to-nnf my-fi)
  
(eval-formula my-wart my-fi)
(eval-nnf my-wart (to-nnf my-fi))


;Niech P będzie własnością dla (Formula 'v), taką, że:
;(i) zachodzi P(var)
;(ii) jesli zachodzi P(l) i P(r) zachodzi takze P(conj l r) a takze P(disj l r)
;(iii) jesli zachodzi P(f) zachodzi takze P(neg f)


;P(fi) := (eval-nnf wart (to-nnf fi)) ≡ (eval-formula wart fi)

;Podstawa indukcji:
;P(var) = (eval-nnf wart (to-nnf var)) ≡ (eval-formula wart var)
;(eval-nnf wart (to-nnf var)) ≡ (z def to-nnf)≡
;(eval-nnf wart (nnf-lit #t (var-var fi)))≡(z definicji eval-nnf)≡
;(equal? (nnf-lit-polarity var)(wart (nnf-lit-var var)))≡((nnf-lit-polarity var)=#t)≡
;(wart (nnf-lit-var var))≡ (wart var) ≡ (z def eval-formula)≡
;(eval-formula wart var)
;Zatem zachodzi P(var)

;Krok indukcyjny
;Zalozmy ze zachodzi P(l),P(r) i P(f)
;Pokazmy ze zachodzi P(conj l r), P(disj l r) i P(neg f)

;Dla conj
;cel: (eval-nnf wart (to-nnf (conj l r))) ≡ (eval-formula wart (conj l r))

;(eval-nnf wart (to-nnf (conj l r))) ≡ (z def to-nnf)≡
;(eval-nnf wart (nnf-conj (to-nnf l) (to-nnf r)))≡(z def eval-nnf)≡
;(and (eval-nnf wart (to-nnf l)) (eval-nnf wart (to-nnf r)))≡(z z.i)≡
;(and (eval-formula wart l) (eval-formula wart r))≡(z def eval-formula)≡
;(eval-formula wart (conj l r))
;Zatem zachodzi P((conj l r))

;Dla disj
;cel: (eval-nnf wart (to-nnf (disj l r))) ≡ (eval-formula wart (disj l r))

;(eval-nnf wart (to-nnf (disj l r)))≡(z def to-nnf)≡
;(eval-nnf wart (nnf-disj (to-nnf l) (to-nnf r)))≡(z def eval-nnf)≡
;(or (eval-nnf wart (to-nnf l)) (eval-nnf wart (to-nnf r)))≡(z z.i)≡
;(or (eval-formula wart l) (eval-formula wart r))≡(z def eval-formula)≡
;(eval-formula wart (disj l r))
;Zatem zachodzi P((disj l r))

;Dla neg
;cel:(eval-nnf wart (to-nnf (neg f))) ≡ (eval-formula wart (neg f))

;(eval-nnf wart (to-nnf (neg f)))≡(z def to-nnf)≡
;(eval-nnf (neg-nnf (to-nnf (neg f))))≡(3 przypadki)≡

;1 przypadek (to-nnf (neg f))) = nnf-lit
;≡(z def neg-nnf)≡
;(eval-nnf (nnf-lit #f f));≡(z def eval-nnf)≡
; (equal? #f (wart f))≡(not (wart f))≡(z def eval-formula)≡
;(eval-formula wart f)
;Zatem zachodzi P((neg f)) dla (to-nnf (neg f))) = nnf-lit

;2 przypadek (to-nnf (neg f))) = nnf-disj
;(eval-nnf (neg-nnf (to-nnf (neg f))))≡(z def neg-nnf)≡
;(eval-nnf (nnf-conj (neg-nnf l) (neg-nnf r)))≡(z def eval-nnf)≡
;(and (eval-nnf wart (neg-nnf l)) (eval-nnf wart (neg-nnf l)))≡(z z.i)≡
;(and (eval-formula wart (neg l)) (eval-formula (neg r))≡ (z De Morgana)≡
;(not (eval formula (disj l r)))≡(z def eval-formula)≡
;(eval-formula (neg (disj l r)))≡(z tego przypadku (disj l r)=f)≡
;(eval-formula (neg f))
;Zatem zachodzi P((neg f)) dla (to-nnf (neg f))) = nnf-disj

;3 przypadek P((neg f)) dla (to-nnf (neg f))) = nnf-conj
;(eval-nnf (neg-nnf (to-nnf (neg f))))≡(z def neg-nnf)≡
;(eval-nnf (nnf-disj (neg-nnf l) (neg-nnf r))≡(z def eval-nnf)≡
;(or (eval-nnf wart (neg-nnf l)) (eval-nnf wart (neg-nnf r)))≡(z z.i)≡
;(or (eval-formula wart (neg l)) (eval-formula wart (neg r)))≡ (z De Morgana)≡
;(not (eval-formula wart (conj l r)))≡(z def eval-formula)≡
;(eval-formula wart (neg (conj l r)))≡(z tego przypadku (conj l r) = f)≡
;(eval-formula wart (neg f))
;Zatem zachodzi P((neg f)) dla (to-nnf (neg f)) = nnf-conj

;Zatem zachodzi P((neg f)) (dla wszystkich przypadkow f), P((conj l r)) i P((disj l r))
;Czyli dla dowolnej formuły fi zachodzi P(fi)

