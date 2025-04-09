#lang plait

;cel istnieje lista zs (append xs ys) = zs dla dowolnych xs ys

; 1 przypadek
; xs = empty
; ys = empty
; Z 1 lematu udowodnionego na wykładzie (append empty ys) = ys
;zatem (append xs ys) = (append empty empty) = empty
;czyli isnieje zs=empty

; 2 przypadek
; xs = empty
; ys dowolny
; Z 1 lematu (append empty ys) = ys
; zatem (append xs ys) = (append empty ys) = ys
; czyli istnieje takie zs = ys

; 3 przypadek
; xs dowolny
; ys = empty
; z 2 lematu udowodnionego na wykładzie (append xs empty) = xs
; zatem (append xs ys) = (append xs empty) = xs
; czyli istnieje takie zs = xs

; 4 przypadek
; xs dowolny
; ys dowolny

; Niech P bedzie wlasnoscia list, taka ,ze:
; (i) P(empty)
; (ii) dla dowolnego elementu x oraz listy xs jesli P(xs) to P((cons x xs))
; wowczas dla dowolnej listy zachodzi P(xs)

;Wlasnosc P(xs) := (append xs ys) = zs

; Podstawa indukcji:
; P(empty) zachodzi z 1 lematu

; Krok indukcyjny:
; Zalozmy P(xs) czyli istnieje takie zs ze (append xs ys) = zs
; Pokazmy ze (append (cons x xs) ys) = (cons x zs)
; (append (cons x xs) ys) =(z def. append) = (cons x (append xs ys)) = (z z.i) = (cons x zs)

