#lang plait

( define-type ( NNF 'v )
( nnf-lit [ polarity : Boolean ] [ var : 'v ])
( nnf-conj [ l : ( NNF 'v ) ] [ r : ( NNF 'v ) ])
( nnf-disj [ l : ( NNF 'v ) ] [ r : ( NNF 'v ) ]) )

(define (neg-nnf fi)
  (cond [(nnf-lit? fi)
         (nnf-lit (not (nnf-lit-polarity fi)) (nnf-lit-var fi))]
        [(nnf-conj? fi)
         (nnf-disj (neg-nnf (nnf-conj-l fi)) (neg-nnf (nnf-conj-r fi)))]
        [(nnf-disj? fi)
         (nnf-conj (neg-nnf (nnf-disj-l fi)) (neg-nnf (nnf-disj-r fi)))]))

(define (eval-nnf wart fi)
  (cond [(nnf-lit? fi)
         (equal? (nnf-lit-polarity fi)(wart (nnf-lit-var fi)))]
        [(nnf-conj? fi)
         (and (eval-nnf wart (nnf-conj-l fi)) (eval-nnf wart (nnf-conj-r fi)))]
        [(nnf-disj? fi)
         (or (eval-nnf wart (nnf-disj-l fi)) (eval-nnf wart (nnf-disj-r fi)))]))

(define (my-wart v)
  (cond [(equal? v "p")
         #t]
        [(equal? v "q")
         #f]
        [else #t]))

(define my-nnf
  (nnf-conj (nnf-lit #t "p") (nnf-disj (nnf-lit #t "p") (nnf-lit #f "q"))))

(eval-nnf my-wart my-nnf)

;Niech P będzie własnością dla (NNF 'v), taką, że:
;(i) zachodzi P(nnf-lit),
;(ii) jeżeli zachodzi P(l) i P(r) to zachodzi P(nnf-conj l r) oraz P(nnf-disj l r)

;P(fi) := (eval-nnf wart (neg-nnf fi)) ≡ (not (eval-nnf wart fi))

;Podstawa indukcji:
;P(nnf-lit)
;(eval-nnf wart (neg-nnf (nnf-lit))) ≡ (z def neg-nnf) ≡
;(eval-nnf wart (nnf-lit (not (nnf-lit-polarity fi)) (nnf-lit-var fi)) ≡ (z def eval-nnf)≡
;(equal? (not (nnf-lit-polarity fi)) (wart (nnf-lit-var fi))≡ (not przed nawias) ≡
;(not (equal? (nnf-lit-polarity fi)(wart (nnf-lit-var fi))) ≡ (z def eval-nnf) ≡
;(not (eval-nnf wart (nnf-lit fi)))
;Zatem zachodzi P(nnf-lit)

;Krok indukcyjny:
;Załóżmy że zachodzi P(l) P(r) czyli (eval-nnf wart (neg-nnf l)) ≡ (not (eval-nnf wart l))
;oraz (eval-nnf wart (neg-nnf r)) ≡ (not (eval-nnf wart r))
;Pokazmy ze zachodzi P(nnf-conj l r) oraz P(nnf-disj l r)

;Dla conj
;cel: (eval-nnf wart (neg-nnf (nnf-conj l r))) ≡ (not (eval-nnf wart (nnf-conj l r)))

;(eval-nnf wart (neg-nnf (nnf-conj l r)))≡ (z def neg-nnf)≡
;(eval-nnf wart (nnf-disj (neg-nnf l) (neg-nnf r)) ≡ (z def eval-nnf)≡
;(or (eval-nnf wart (neg-nnf l)) (eval-nnf wart (neg-nnf r)))≡(z z.i)≡
;(or (not (eval-nnf wart l)) (not (eval-nnf wart r)))≡(z De Morgana) (~pv~q)≡~(p^q))≡
;(not (and (eval-nnf wart l)(eval-nnf wart r)))≡(z def eval-nnf)≡
;(not (eval-nnf wart (nnf-conj l r)))
;Zatem zachodzi P(nnf-conj l r)

;Dla disj
;cel :(eval-nnf wart (neg-nnf (nnf-disj l r))) ≡ (not (eval-nnf wart (nnf-disj l r)))

;(eval-nnf wart (neg-nnf (nnf-disj l r)))≡(z def neg-nnf)≡
;(eval-nnf wart (nnf-conj (neg-nnf l) (neg-nnf r))≡(z def eval-nnf)≡
;(and (eval-nnf wart (neg-nnf l)) (eval-nnf wart (neg-nnf r)))≡(z z.i)≡
;(and (not (eval-nnf wart l))(not (eval-nnf wart r)))≡(z De Morgana) (~p^~q)≡~(p v q))
;(not (or (eval-nnf wart l)(eval-nnf wart r)))≡(z def eval-nnf)≡
;(not (eval-nnf wart (nnf-disj l r)))
;Zatem zachodzi P(nnf-disj l r)

;czyli dla dowolnej formuły fi zachodzi P(fi)










