#lang racket

(require rackunit)

(provide (struct-out column-info)
         (struct-out table)
         (struct-out and-f)
         (struct-out or-f)
         (struct-out not-f)
         (struct-out eq-f)
         (struct-out eq2-f)
         (struct-out lt-f)
         table-insert
         table-project
         table-sort
         table-select
         table-rename
         table-cross-join
         table-natural-join)

(define-struct column-info (name type) #:transparent)

(define-struct table (schema rows) #:transparent)

(define cities
  (table
   (list (column-info 'city    'string)
         (column-info 'country 'string)
         (column-info 'area    'number)
         (column-info 'capital 'boolean))
   (list (list "Wrocław" "Poland"  293 #f)
         (list "Warsaw"  "Poland"  517 #t)
         (list "Poznań"  "Poland"  262 #f)
         (list "Berlin"  "Germany" 892 #t)
         (list "Munich"  "Germany" 310 #f)
         (list "Paris"   "France"  105 #t)
         (list "Rennes"  "France"   50 #f))))

(define countries
  (table
   (list (column-info 'country 'string)
         (column-info 'population 'number))
   (list (list "Poland" 38)
         (list "Germany" 83)
         (list "France" 67)
         (list "Spain" 47))))

(define (empty-table columns) (table columns '()))

;Pierwsza funkcja table-insert

;funkcja pomocnicza sprawdzajaca typ elementu w row
(define (get-type x)
  (cond [(string? x)
         'string]
        [(number? x)
         'number]
        [(symbol? x)
         'symbol]
        [(boolean? x)
         'boolean]
        [else 'unknown]))

;funkcja pomocnicza sprawdzajaca czy wszystkie elementy zgadzaja sie z typami w schemacie
(define (pom row tab)
  (if (null? row)
      #t
      (if (equal? (get-type (car row)) (column-info-type (car (table-schema tab))))
          (pom (cdr row) (table (cdr (table-schema tab)) (table-rows tab)))
          #f)))

(define (table-insert row tab)
  (if (equal? (length row) (length (table-schema tab)))
      (if (pom row tab)
          (table (table-schema tab)(append (list row)(table-rows tab)))
          (error "zly typ"))
     (error "zly typ")))


;Druga funkcja table-project

;czy nalezy element do listy
(define (member? el cols)
  (if (null? cols)
      #f
      (if (equal? (car cols) el)
          #t
          (member? el (cdr cols)))))

;funkcja pomocnicza ktora bedzie zwracala dobry schemat
(define (new-schema cols schem)
  (if (or (null? cols)(null? schem))
      null
      (if (member? (column-info-name (car schem)) cols)
          (cons (car schem) (new-schema cols (cdr schem)))
          (new-schema cols (cdr schem)))))
          
          
;funkcja zwracajaca element o indeksie kolumny (korzystam z funkcji napisanej do selecta)
(define (el-row name tab)
  (list-ref (car (table-rows tab)) (index name tab)))

;funkcja ktora tworzy wiersz z elementami odpowiednio z kolumn
(define (row-maker cols tab)
  (if (null? cols)
      null
      (cons (el-row (car cols) tab) (row-maker (cdr cols) tab))))

;funkcja ktora tworzy wszystkie wiersze z odpowiednimi elementami
(define (rows-maker cols tab)
  (if (null? cols)
      null
      (if (null? (table-rows tab))
          null
          (cons (row-maker cols tab) (rows-maker cols (table (table-schema tab)(cdr (table-rows tab))))))))

(define (empty-rows rows)
  (if (null? rows)
      null
      (cons '() (empty-rows (cdr rows)))))

;funkcja ktora laczy poprzednie i tworzy tabele (find3 schemat->cols)
(define (table-project cols tab)
  (if (null? cols)
      (table '() (empty-rows (table-rows tab)))
      (if (null? (table-rows tab))
          (table (new-schema cols (table-schema tab)) null)
          (table (new-schema cols (table-schema tab)) (rows-maker (find3 (new-schema cols (table-schema tab))) tab)))))


;Trzecia funkcja table-rename

(define (table-rename col ncol tab)
  (if (equal? tab (empty-table '()))
      tab
      (if (equal? col (column-info-name (car (table-schema tab))))
          (table (cons (column-info ncol (column-info-type (car (table-schema tab)))) (cdr (table-schema tab))) (table-rows tab))
          (if (null? (cdr (table-schema tab)))
              tab
              (table (cons (car (table-schema tab)) (table-schema (table-rename col ncol (table (cdr (table-schema tab)) (table-rows tab))))) (table-rows tab))))))

;Czwarta funkcja table-select

(define-struct and-f (l r)) ; koniunkcja formuł
(define-struct or-f (l r)) ; dysjunkcja formuł
(define-struct not-f (e)) ; negacja formuły
(define-struct eq-f (name val)) ; wartość kolumny name równa val
(define-struct eq2-f (name name2)) ; wartości kolumn name i name2 równe
(define-struct lt-f (name val)) ; wartość kolumny name mniejsza niż val

;funkcja pomocnicza do indeksu kolumny (do wierszy)
(define (index name tab)
  (if (equal? (column-info-name (car (table-schema tab))) name)
      0
      (if (null? (cdr (table-schema tab)))
          (error "nie ma takiej kolumny")
          (+ 1 (index name (table (cdr (table-schema tab)) (table-rows tab)))))))

;funkcja pomocnicza sprawdzajaca czy wiersz spelnia formule
(define (eval form row tab)
  (cond [(and-f? form) (and (eval (and-f-l form) row tab) (eval (and-f-r form) row tab))]
        [(or-f? form) (or (eval (or-f-l form) row tab) (eval (or-f-r form) row tab))]
        [(not-f? form) (not (eval (not-f-e form) row tab))]
        [(eq-f? form) (if (equal? (get-type (list-ref row (index (eq-f-name form) tab)))(get-type (eq-f-val form)))
                          (equal? (list-ref row (index (eq-f-name form) tab)) (eq-f-val form))
                          (error "zły typ"))]
        [(eq2-f? form) (if (equal? (get-type (list-ref row (index (eq2-f-name form) tab)))(get-type (list-ref row (index (eq2-f-name2 form) tab))))
                           (equal? (list-ref row (index (eq2-f-name form) tab)) (list-ref row (index (eq2-f-name2 form) tab)))
                           (error "zły typ"))]
        [(lt-f? form) (if (equal? (get-type (list-ref row (index (lt-f-name form) tab)))(get-type (lt-f-val form)))
                          (cond [(string? (lt-f-val form))
                                 (string<? (list-ref row (index (lt-f-name form) tab))(lt-f-val form))]
                                [(number? (lt-f-val form))
                                 (< (list-ref row (index (lt-f-name form) tab)) (lt-f-val form))]
                                [(symbol? (lt-f-val form))
                                 (string<? (symbol->string (list-ref row (index (lt-f-name form) tab)))(symbol->string (lt-f-val form)))]
                                [(boolean? (lt-f-val form))
                                 (cond [(and (equal? (list-ref row (index (lt-f-name form) tab)) #t)(equal? (lt-f-val form) #t)) #f]
                                       [(and (equal? (list-ref row (index (lt-f-name form) tab)) #t)(equal? (lt-f-val form) #f)) #t]
                                       [(and (equal? (list-ref row (index (lt-f-name form) tab)) #f)(equal? (lt-f-val form) #t)) #f]
                                       [(and (equal? (list-ref row (index (lt-f-name form) tab)) #f)(equal? (lt-f-val form) #f)) #f])])
                          (error "zły typ"))]
        [(boolean? form) form]
        [else (error "to nie jest formula")]))

;funkcja zwracajace wszystkie wiersze z tab-rows ktore spelniaja formule
(define (eval-cols form rows tab)
  (if (null? rows)
      null
      (if (eval form (car rows) tab)
          (cons (car rows) (eval-cols form (cdr rows) tab))
          (eval-cols form (cdr rows) tab))))

(define (table-select form tab)
  (table (table-schema tab) (eval-cols form (table-rows tab) tab)))

;Piata funkcja - table-sort

;druga wersja index
(define (index2 name tab)
  (if (equal? (column-info-name (car (table-schema tab))) name)
      0
      (if (null? (cdr (table-schema tab)))
          -inf.0
          (+ 1 (index2 name (table (cdr (table-schema tab)) (table-rows tab)))))))

;zmiana cols jak bedzie zły klucz
(define (cols-update cols tab)
  (if (null? cols)
      null
      (if (equal? (index2 (car cols) tab) -inf.0)
          (cols-update (cdr cols) tab)
          (cons (car cols) (cols-update (cdr cols) tab)))))

;funkcja pomocnicza do porownywania dwoch wierszy (get-type,index z poprzednich funkcji)
(define (compare row1 row2 cols tab)
  (define type (get-type (list-ref row1 (index (car cols) tab))))
  (cond [(equal? 'string type)
         (cond [(string<? (list-ref row1 (index (car cols) tab))(list-ref row2 (index (car cols) tab)))
                #t]
               [(string>? (list-ref row1 (index (car cols) tab)) (list-ref row2 (index (car cols) tab)))
                #f]
               [else
                (if (null? (cdr cols))
                    #f
                    (compare row1 row2 (cdr cols) tab))])]
        [(equal? 'number type)
         (cond [(< (list-ref row1 (index (car cols) tab)) (list-ref row2 (index (car cols) tab)))
                #t]
               [(> (list-ref row1 (index (car cols) tab)) (list-ref row2 (index (car cols) tab)))
                #f]
               [else
                (if (null? (cdr cols))
                    #f
                    (compare row1 row2 (cdr cols) tab))])]
        [(equal? 'symbol type)
         (cond [(string<? (symbol->string (list-ref row1 (index (car cols) tab))) (symbol->string (list-ref row2 (index (car cols) tab))))
                #t]
               [(string>? (symbol->string (list-ref row1 (index (car cols) tab))) (symbol->string (list-ref row2 (index (car cols) tab))))
                #f]
               [else
                (if (null? (cdr cols))
                    #f
                    (compare row1 row2 (cdr cols) tab))])]
        [(equal? 'boolean type) ; specyfikacja #t<#f 
         (cond [(and (equal? (list-ref row1 (index (car cols) tab)) #t) (equal? (list-ref row2 (index (car cols) tab)) #t))
                (if (null? (cdr cols))
                    #f
                    (compare row1 row2 (cdr cols) tab))]
               [(and (equal? (list-ref row1 (index (car cols) tab)) #t) (equal? (list-ref row2 (index (car cols) tab)) #f)) #t]
               [(and (equal? (list-ref row1 (index (car cols) tab)) #f) (equal? (list-ref row2 (index (car cols) tab)) #t)) #f]
               [(and (equal? (list-ref row1 (index (car cols) tab)) #f) (equal? (list-ref row2 (index (car cols) tab)) #f))
                (if (null? (cdr cols))
                    #f
                    (compare row1 row2 (cdr cols) tab))])]
        [else (error "zły typ")]))

;funkcja ktora insertuje mi odpowiednio wiersz
(define (insert row res cols tab)
  (if (null? res)
      (list row)
      (if (compare row (car res) cols tab)
          (cons row res)
          (cons (car res) (insert row (cdr res) cols tab)))))

;funkcja insert-sort 
(define (insert-sort rows cols tab)
  (define (insert-sort-helper rows ys cols tab)
    (if (null? rows)
        ys
        (insert-sort-helper (cdr rows) (insert (car rows) ys cols tab) cols tab)))
  (if (null? cols)
      null
      (insert-sort-helper rows null cols tab)))

;table-sort
(define (table-sort cols tab)
  (if (null? (cols-update cols tab))
      tab
      (table (table-schema tab)
             (insert-sort (table-rows tab) (cols-update cols tab) tab))))

;Szósta funkcja table-cross-join

;funkcja do łączenia schematow z dwoch tablic
(define (schema-join tab1 tab2)
  (append (table-schema tab1) (table-schema tab2)))

;funkcja do laczenia dwoch wierszy (1wszy z tab1 z 1wszym z tab2)
(define (rows-join-helper tab1 tab2)
  (if (null? (table-rows tab1))
      null
      (append (car (table-rows tab1)) (car (table-rows tab2)))))

;funkcja do tworzenia wszystkich kombinacji na pierwszym wierszu tab1 (1wszy wiersz z tab1 z wszystkimi z tab2)
(define (rows-join-helper2 tab1 tab2)
  (if (null? (table-rows tab2))
      null
      (cons (rows-join-helper tab1 tab2) (rows-join-helper2 tab1 (table (table-schema tab2) (cdr (table-rows tab2)))))))

;funkcja do tworzenia wszystkich kombinacji tab1 i tab2
(define (rows-join tab1 tab2)
  (if (null? (table-rows tab1))
      null
      (append (rows-join-helper2 tab1 tab2) (rows-join (table (table-schema tab1)(cdr(table-rows tab1))) tab2))))

;polaczenie wszystkich joinow na table
(define (table-cross-join tab1 tab2)
  (if (or (null? (table-rows tab1))(null? (table-rows tab2)))
      (empty-table (schema-join tab1 tab2))
      (table (schema-join tab1 tab2) (rows-join tab1 tab2))))

;Siódma funkcja table-natural-join

(define (find cols1 col)
  (if (null? cols1)
      #f
      (if (equal? (car cols1) col)
          #t
          (find (cdr cols1) col))))

(define (bfind cols1 cols2 ys)
  (if (null? cols2)
      ys
      (if (find cols1 (car cols2))
          (bfind cols1 (cdr cols2) (cons (column-info-name(car cols2)) ys))
          (bfind cols1 (cdr cols2) ys))))

(define (ads1 list)
  (if (null? list)
      null
      (cons (cons (car list)(string->symbol (string-append (symbol->string (car list)) "1"))) (ads1 (cdr list)))))

(define (find2 cols1 cols2)
  (if (null? cols2)
      cols1
      (if (find cols1 (car cols2))
          (find2 cols1 (cdr cols2))
          (find2 (append cols1 (list (car cols2))) (cdr cols2)))))

(define (find3 schema)
  (if (null? schema)
      null
      (cons (column-info-name (car schema)) (find3 (cdr schema)))))

(define (change tab2 list)
  (if (null? list)
      tab2
      (change (table (table-schema (table-rename (car (car list)) (cdr (car list)) tab2)) (table-rows tab2)) (cdr list))))

(define (make-form list)
  (if (null? list)
      #t
      (if (null? (cdr list))
          (eq2-f (car (car list))(cdr (car list)))
          (and-f (eq2-f (car (car list)) (cdr (car list))) (make-form (cdr list))))))

(define (select-time tab1 tab2)
  (define list (ads1 (bfind (table-schema tab1)(table-schema tab2)null)))
  (table-select (make-form list) (table-cross-join tab1 (change tab2 list))))

(define (table-natural-join tab1 tab2)
  (table-project (find3 (find2 (table-schema tab1)(table-schema tab2)))(select-time tab1 tab2)))

              
;TESTY
;do inserta
(check-equal?
 (table-rows (table-insert (list "Rzeszow" "Poland" 129 #f) cities))
 (list (list "Rzeszow" "Poland" 129 #f)
       (list "Wrocław" "Poland" 293 #f)
       (list "Warsaw" "Poland" 517 #t)
       (list "Poznań" "Poland" 262 #f)
       (list "Berlin" "Germany" 892 #t)
       (list "Munich" "Germany" 310 #f)
       (list "Paris" "France" 105 #t)
       (list "Rennes" "France" 50 #f)))

;do projecta
(check-equal?
 (table-project '(city country) cities)
 (table
  (list (column-info 'city 'string)
        (column-info 'country 'string))
  (list (list "Wrocław" "Poland")
        (list "Warsaw" "Poland")
        (list "Poznań" "Poland")
        (list "Berlin" "Germany")
        (list "Munich" "Germany")
        (list "Paris" "France")
        (list "Rennes" "France"))))

;do rename
(check-equal?
 (table-rename 'city 'name cities)
 (table
  (list (column-info 'name 'string)
        (column-info 'country 'string)
        (column-info 'area 'number)
        (column-info 'capital 'boolean))
  (list (list "Wrocław" "Poland" 293 #f)
        (list "Warsaw" "Poland" 517 #t)
        (list "Poznań" "Poland" 262 #f)
        (list "Berlin" "Germany" 892 #t)
        (list "Munich" "Germany" 310 #f)
        (list "Paris" "France" 105 #t)
        (list "Rennes" "France" 50 #f))))

;do selecta
(check-equal?
 (table-rows (table-select (and-f (eq-f 'capital #t)
                                  (not-f (lt-f 'area 300))) cities ))
 (list ( list "Warsaw" "Poland" 517 #t)
(list "Berlin" "Germany" 892 #t )))

;do sorta
(check-equal?
 (table-rows (table-sort '(country city) cities))
 (list (list "Paris" "France" 105 #t)
        (list "Rennes" "France" 50 #f)
        (list "Berlin" "Germany" 892 #t)
        (list "Munich" "Germany" 310 #f)
        (list "Poznań" "Poland" 262 #f)
        (list "Warsaw" "Poland" 517 #t)
        (list "Wrocław" "Poland" 293 #f)))

;do cross-joina
(check-equal?
  (table-cross-join cities (table-rename 'country 'country1 countries))
  (table
  (list (column-info 'city 'string)
        (column-info 'country 'string)
        (column-info 'area 'number)
        (column-info 'capital 'boolean)
        (column-info 'country1 'string)
        (column-info 'population 'number))
  (list (list "Wrocław" "Poland" 293 #f "Poland" 38)
        (list "Wrocław" "Poland" 293 #f "Germany" 83)
        (list "Wrocław" "Poland" 293 #f "France" 67)
        (list "Wrocław" "Poland" 293 #f "Spain" 47)
        (list "Warsaw" "Poland" 517 #t "Poland" 38)
        (list "Warsaw" "Poland" 517 #t "Germany" 83)
        (list "Warsaw" "Poland" 517 #t "France" 67)
        (list "Warsaw" "Poland" 517 #t "Spain" 47)
        (list "Poznań" "Poland" 262 #f "Poland" 38)
        (list "Poznań" "Poland" 262 #f "Germany" 83)
        (list "Poznań" "Poland" 262 #f "France" 67)
        (list "Poznań" "Poland" 262 #f "Spain" 47)
        (list "Berlin" "Germany" 892 #t "Poland" 38)
        (list "Berlin" "Germany" 892 #t "Germany" 83)
        (list "Berlin" "Germany" 892 #t "France" 67)
        (list "Berlin" "Germany" 892 #t "Spain" 47)
        (list "Munich" "Germany" 310 #f "Poland" 38)
        (list "Munich" "Germany" 310 #f "Germany" 83)
        (list "Munich" "Germany" 310 #f "France" 67)
        (list "Munich" "Germany" 310 #f "Spain" 47)
        (list "Paris" "France" 105 #t "Poland" 38)
        (list "Paris" "France" 105 #t "Germany" 83)
        (list "Paris" "France" 105 #t "France" 67)
        (list "Paris" "France" 105 #t "Spain" 47)
        (list "Rennes" "France" 50 #f "Poland" 38)
        (list "Rennes" "France" 50 #f "Germany" 83)
        (list "Rennes" "France" 50 #f "France" 67)
        (list "Rennes" "France" 50 #f "Spain" 47))))

;do natural-joina
(check-equal?
 (table-natural-join cities countries)
 (table-project '(city country area capital population)
                (table-select (eq2-f 'country 'country1)
                              (table-cross-join cities
                                               ( table-rename 'country 'country1 countries)))))
