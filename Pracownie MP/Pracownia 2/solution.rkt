#lang racket
(require data/heap)
(require rackunit)
(provide sim? wire?
         (contract-out
          [make-sim        (-> sim?)]
          [sim-wait!       (-> sim? positive? void?)]
          [sim-time        (-> sim? real?)]
          [sim-add-action! (-> sim? positive? (-> any/c) void?)]

          [make-wire       (-> sim? wire?)]
          [wire-on-change! (-> wire? (-> any/c) void?)]
          [wire-value      (-> wire? boolean?)]
          [wire-set!       (-> wire? boolean? void?)]

          [bus-value (-> (listof wire?) natural?)]
          [bus-set!  (-> (listof wire?) natural? void?)]

          [gate-not  (-> wire? wire? void?)]
          [gate-and  (-> wire? wire? wire? void?)]
          [gate-nand (-> wire? wire? wire? void?)]
          [gate-or   (-> wire? wire? wire? void?)]
          [gate-nor  (-> wire? wire? wire? void?)]
          [gate-xor  (-> wire? wire? wire? void?)]

          [wire-not  (-> wire? wire?)]
          [wire-and  (-> wire? wire? wire?)]
          [wire-nand (-> wire? wire? wire?)]
          [wire-or   (-> wire? wire? wire?)]
          [wire-nor  (-> wire? wire? wire?)]
          [wire-xor  (-> wire? wire? wire?)]

          [flip-flop (-> wire? wire? wire? void?)]))

;; strukty

(struct sim ([time #:mutable] [actions #:mutable]))

(struct wire ([value #:mutable] [actions #:mutable] sim))

;; funkcje dla sim

(define (make-sim)
  (sim 0 (make-heap (lambda (a b) (<= (car a) (car b))))))

(define (sim-wait! sim t)
  (if (and (not (equal? 0 (heap-count (sim-actions sim))))
           (<= (car (heap-min (sim-actions sim))) (+ (sim-time sim) t)))
      (let ([fst (heap-min (sim-actions sim))])
        (begin
          (define temp (- (+ (sim-time sim) t) (car fst)))
          (heap-remove-min! (sim-actions sim))
          (set-sim-time! sim (car fst))
          ((cdr fst))
          (sim-wait! sim temp)))
      (set-sim-time! sim (+ (sim-time sim) t))))

(define (sim-add-action! sim t f)
  (heap-add! (sim-actions sim) (cons (+ t (sim-time sim)) f)))

;; funkcje dla wire

(define (make-wire sim)
  (wire #f null sim))

(define (wire-on-change! wire f)
  (begin 
    (set-wire-actions! wire (append (wire-actions wire) (list f)))
    (f)))
  
(define (call-all-actions ac)
  (if (null? ac)
      (void)
      (begin
        ((car ac))
        (call-all-actions (cdr ac)))))

(define (wire-set! wire b)
  (if (equal? b (wire-value wire))
      (void)
      (begin
        (set-wire-value! wire b)
        (call-all-actions (wire-actions wire)))))

;; magistrale z szablonu

(define (bus-set! wires value)
  (match wires
    ['() (void)]
    [(cons w wires)
     (begin
       (wire-set! w (= (modulo value 2) 1))
       (bus-set! wires (quotient value 2)))]))

(define (bus-value ws)
  (foldr (lambda (w value) (+ (if (wire-value w) 1 0) (* 2 value)))
         0
         ws))

;; bramki logiczne

(define (gate-not o i)
  (define (proc-not)
    (sim-add-action! (wire-sim o) 1 (lambda () (wire-set! o (not (wire-value i))))))
  (wire-on-change! i proc-not))

(define (gate-and o i1 i2)
  (define (proc-and)
    (sim-add-action! (wire-sim o) 1 (lambda () (wire-set! o (and (wire-value i1)(wire-value i2))))))
  (wire-on-change! i1 proc-and)
  (wire-on-change! i2 proc-and))

(define (gate-nand o i1 i2)
  (define (proc-nand)
    (sim-add-action! (wire-sim o) 1 (lambda () (wire-set! o (not (and (wire-value i1)(wire-value i2)))))))
  (wire-on-change! i1 proc-nand)
  (wire-on-change! i2 proc-nand))

(define (gate-or o i1 i2)
  (define (proc-or)
    (sim-add-action! (wire-sim o) 1 (lambda () (wire-set! o (or (wire-value i1)(wire-value i2))))))
  (wire-on-change! i1 proc-or)
  (wire-on-change! i2 proc-or))

(define (gate-nor o i1 i2)
  (define (proc-nor)
    (sim-add-action! (wire-sim o) 1 (lambda () (wire-set! o (not (or (wire-value i1)(wire-value i2))))))) 
  (wire-on-change! i1 proc-nor)
  (wire-on-change! i2 proc-nor))

(define (gate-xor o i1 i2)
  (define (proc-xor)
    (sim-add-action! (wire-sim o) 2 (lambda () (wire-set! o (xor (wire-value i1)(wire-value i2))))))
  (wire-on-change! i1 proc-xor)
  (wire-on-change! i2 proc-xor))


;; wire-gates

(define (wire-not i)
  (let ([o (make-wire (wire-sim i))])
    (gate-not o i)
    o))

(define (wire-and i1 i2)
  (let ([o (make-wire (wire-sim i1))])
    (gate-and o i1 i2)
    o))

(define (wire-nand i1 i2)
  (let ([o (make-wire (wire-sim i1))])
    (gate-nand o i1 i2)
    o))

(define (wire-or i1 i2)
  (let ([o (make-wire (wire-sim i1))])
    (gate-or o i1 i2)
    o))

(define (wire-nor i1 i2)
  (let ([o (make-wire (wire-sim i1))])
    (gate-nor o i1 i2)
    o))

(define (wire-xor i1 i2)
  (let ([o (make-wire (wire-sim i1))])
    (gate-xor o i1 i2)
    o))

(define (flip-flop out clk data)
  (define sim (wire-sim data))
  (define w1  (make-wire sim))
  (define w2  (make-wire sim))
  (define w3  (wire-nand (wire-and w1 clk) w2))
  (gate-nand w1 clk (wire-nand w2 w1))
  (gate-nand w2 w3 data)
  (gate-nand out w1 (wire-nand out w3)))

(define s1 (make-sim))

(define (make-counter n clk en)
  (if (= n 0)
      '()
      (let [(out (make-wire s1))]
        (flip-flop out clk (wire-xor en out))
        (cons out (make-counter (- n 1) clk (wire-and en out))))))

(define clk (make-wire s1))
(define en  (make-wire s1))
(define counter (make-counter 4 clk en))

(wire-set! en #t)

(define (tick)
  (wire-set! clk #t)
  (sim-wait! s1 20)
  (wire-set! clk #f)
  (sim-wait! s1 20)
  (bus-value counter))


;testy
(define s2 (make-sim))
(define w1 (make-wire s2))
(define w2 (make-wire s2))
(wire-set! w2 #t)

(define w3 (wire-or w1 w2)) ;(or #f #t) => #t
(define w4 (wire-and w3 w2)) ;(and #t #t) => #t
(define w5 (wire-xor w4 w2)) ;(xor #t #t) => #f
(define w6 (wire-nor w5 w1)) ;(nor #f #f) => #t
(define w7a (wire-nand w6 w2)) ;(nand #t #t) => #f
(define w7b (wire-nand w6 w1)) ;(nand #t #f) => #t
(sim-wait! s2 100)
(check-equal? (wire-value w7a) #f)
(check-equal? (wire-value w7b) #t)

