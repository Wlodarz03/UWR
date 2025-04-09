#lang plait

(define-type Prop
  (var [v : String])
  (conj [l : Prop] [r : Prop])
  (disj [l : Prop] [r : Prop])
  (neg [f : Prop]))

(define my-prop
  (conj (var "p") (disj (var "p") (neg (var "r")))))


;pomocnicza funkcja union do zlepiania par zmiennych wolnych
(define (union a b)
  (cond
    ; jak a jest pusty zwracam b
    [(empty? a) b]
    ; jak jest w b nie dodaję do zbioru
    [(member (first a) b) (union (rest a) b)]
    ; jak nie ma go w b to tworzę z nim parę
    [else
     (cons (first a) (union (rest a) b))]))

(define (free-vars p)
  (cond
    ;jak będzie to zmienna
    [(var? p) (list (var-v p) )]
    ;koniunkcja
    [(conj? p) (union (free-vars (conj-l p)) (free-vars (conj-r p)))  ]
    ;alternatywa
    [(disj? p) (union (free-vars (disj-l p)) (free-vars (disj-r p)))  ]
    ;negacja
    [else (free-vars (neg-f p))]
    )
  )

(define test-formula (disj (conj (var "a") (var "c") ) (var "c") ) )
(free-vars test-formula)

(free-vars my-prop)