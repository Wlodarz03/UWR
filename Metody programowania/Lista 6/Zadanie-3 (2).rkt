#lang plait

( define-type ( NNF 'v )
( nnf-lit [ polarity : Boolean ] [ var : 'v ])
( nnf-conj [ l : ( NNF 'v ) ] [ r : ( NNF 'v ) ])
( nnf-disj [ l : ( NNF 'v ) ] [ r : ( NNF 'v ) ]))

;Niech P będzie własnością dla (NNF 'v), taką, że:
;(i) zachodzi P(nnf-lit)
;(ii) jeżeli zachodzi P(l) i P(r) to zachodzi P(nnf-conj l r) oraz P(nnf-disj l r)
