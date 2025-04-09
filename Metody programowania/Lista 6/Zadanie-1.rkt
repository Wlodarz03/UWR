#lang plait

(define (my-map f xs)
  (if (empty? xs)
      xs
      (cons (f (first xs)) (my-map f (rest xs)))))

;(my-map f (my-map g xs)) ≡ (my-map (lambda (x) (f (g x))) xs)

;Niech P będzie własnością list, taką, że:
;(i) P(empty),
;(ii) dla dowolnego elementu x oraz listy xs, jeśli P(xs) to P((cons x xs)).
;Wówczas dla dowolnej listy xs zachodzi P(xs).

;P(xs) := (my-map f (my-map g xs)) ≡ (my-map (lambda (x) (f (g x))) empty)

;Podstawa indukcji
; P(empty) := (my-map f(my-map g empty)) ≡ (my-map (lambda (x) (f (g x)) empty)
; Lewa - (my-map f (if (empty? empty) empty (...))) ≡ (my-map f empty) ≡ empty
; Prawa - (my-map (lambda (x) (f (g x)) empty) ≡ (if (empty? empty) empty (...)) ≡ empty
; Lewa ≡ Prawa
; Zatem zachodzi P(empty)

;Krok indukcyjny
;Załóżmy że zachodzi P(xs) czyli (my-map f (my-map g xs)) ≡ (my-map (lambda (x) (f (g x)))xs)
;Pokażmy że zachodzi P((cons x xs))
;(my-map f (my-map g (cons x xs))) ≡ (my-map (lambda (x) (f (g x)))(cons x xs))

; Lewa - (my-map f (my-map g (cons x xs))) ≡
; (my-map f (cons (g x) (my-map g xs))) ≡
; (cons (f (g x)) (my-map f (my-map g xs))

;Prawa - (my-map (lambda (x) (f (g x)))(cons x xs)) ≡
;(cons (f (g x)) (my-map (lambda (x) (f (g x))) xs))

;Skoro dla list po lewej i po prawej bez pierwszych elementow zachodzi P(xs)
; to po dolaczeniu do kazdej z nich tego samego elementu dalej L≡P
;czyli zachodzi P((cons x xs))
