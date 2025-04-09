#lang plait

;1.
( define (apply f x ) ( f x ) )
;funkcja apply przyjmuje funkcje f i x i zwraca f(x)
;funkcja f przyjmuje x (typu 'a) i zwraca typ ('b) czyli f ma typ ('a->'b)
;zatem funkcja apply ma typ (('a->'b)'a -> 'b), bo f(x) ma typ 'b

;2.
( define ( compose f g ) ( lambda ( x ) ( f ( g x ) ) ) )
;funkcja compose przyjmuje dwie funkcje jako argumenty i zwraca procedure
;ktora przyjmuje x (typ 'c) i zwraca f(g(x))
;funkcja g przyjmuje typ 'c (bo x) i zwraca typ 'a
;funkcja f przyjmuje typ 'a i zwraca typ 'b
;zatem (f(g(x)) to typ 'b
;czyli funkcja compose ma typ (('a->'b)('c->'a)->('c->'b))

;3.
( define (flip f ) ( lambda ( x y ) ( f y x ) ) )
;flip przyjmuje funkcje f i zwraca funkcje
;funkcja f przyjmuje dwa argumenty y (typ 'a) x (typ 'b) i zwraca f(x,y) (typ 'c)
;zwraca procedure ktora przyjmuje x y i zwraca f(x,y)
;zatem flip ma typ (('a 'b -> 'c)->('b 'a->'c))

;4
( define ( curry f ) ( lambda ( x ) ( lambda ( y ) ( f x y ) ) ) )
;curry przyjmuje funkcje f ktora zwraca funkcje ktora zwraca funkcje
;f ma typ ('a 'b -> 'c),lambda_y ma typ ('b -> 'c) przyjmuje y(typ 'b) zwraca f(x,y) (typ 'c)
;lambda_x ma typ ('a -> ('b -> 'c))
;zatem curry ma typ (('a 'b -> 'c) -> ('a -> ('b -> 'c)))

