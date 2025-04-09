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


;Niech P będzie własnością dla (NNF 'v), taką, że:
;(i) zachodzi P(nnf-lit),
;(ii) jeżeli zachodzi P(l) i P(r) to zachodzi P(nnf-conj l r) oraz P(nnf-disj l r)

;P(fi) := (neg-nnf (neg-nnf fi)) ≡ fi

;Podstawa indukcji:
; P(nnf-lit) = (neg-nnf (neg-nnf (nnf-lit fi))) ≡ (nnf-lit fi)
; z dzialania programu (neg-nnf (neg-nnf (nnf-lit fi))) ≡
;(neg-nnf (nnf-lit? (nnf-lit fi)))≡(z def neg-nnf)≡
;(neg-nnf (nnf-lit (not (nnf-lit-polarity fi)) (nnf-lit-var fi))) ≡ (tak jak poprzednio)
;(nnf-lit (not (not (nnf-lit-polarity fi))) (nnf-lit-var fi)) ≡
;(nnf-lit (nnf-lit-polarity fi) (nnf-lit-var fi)) ≡ (nnf-lit fi)

;Krok indukcyjny:
; Załóżmy że zachodzi P(l) i P(r) czyli (neg-nnf (neg-nnf l)) ≡ l i (neg-nnf (neg-nnf r)) ≡ r
; Pokazmy że zachodzi P(nnf-conj l r) oraz P(nnf-disj l r)

; Dla conj
; cel: (neg-nnf (neg-nnf (nnf-conj l r))) ≡ (nnf-conj l r)
; (neg-nnf (neg-nnf (nnf-conj l r))) ≡ (z definicji neg-nnf) ≡
; (neg-nnf (nnf-disj (neg-nnf l) (neg-nnf r))) ≡ (ponownie z definicji neg-nnf) ≡
; (nnf-conj (neg-nnf (neg-nnf l)) (neg-nnf (neg-nnf r))) ≡ (z z.i) ≡
; (nnf-conj l r)
; Zatem zachodzi P(nnf-conj l r)

; Dla disj
; cel: (neg-nnf (neg-nnf (nnf-disj l r))) ≡ (nnf-disj l r)
; (neg-nnf (neg-nnf (nnf-disj l r)))≡ (z definicji neg-nnf) ≡
; (neg-nnf (nnf-conj (neg-nnf l) (neg-nnf r))) ≡ (ponownie z definicji neg-nnf) ≡
; (nnf-disj (neg-nnf (neg-nnf l)) (neg-nnf (neg-nnf r)))) ≡ (z z.i) ≡
; (nnf-disj l r)
; Zatem zachodzi P(nnf-disj l r)

; Czyli dla dowolnej formuły fi zachodzi P(fi)