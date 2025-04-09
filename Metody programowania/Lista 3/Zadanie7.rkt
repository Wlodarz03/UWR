#lang racket

( define ( foldr-reverse xs )
   ( foldr ( lambda ( y ys ) ( append ys ( list y ) ) ) null xs ) )

( foldr-reverse ( build-list 10000 identity ) )

; foldr-reverse uzywa appenda -> czyli doklejania nowej listy na koniec starej
; kiedy dodajemy wiec nowy elemnt musimy przejsc wszystkie pozostale wczesniej
; najpierw mamy 10000 - > 10000 9999 -> 10000 9999 9998 -> ...
; nieuzytkami beda wiec wszystkie podlisty ktore nie daja jeszcze koncowego wyniku
; czyli wszystkie consy poza ostatnim
; otrzymamy ciag ayrtmetyczny wiec consow bedzie n * (n+1) / 2