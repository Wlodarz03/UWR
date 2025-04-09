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
        [(neg? fi) (neg-nnf (to-nnf (neg-f fi)))]))

(define my-fi
  (disj (neg (conj (neg (var "p")) (var "q"))) (neg (var "r"))))

my-fi
""
(to-nnf my-fi)
               