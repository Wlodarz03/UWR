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

; structs

(struct sim ([time #:mutable] [actions #:mutable]))

(struct wire ([value #:mutable] [actions #:mutable] sim))

(define (cmp a b)
  (if (<= (car a) (car b))
      #t
      #f))

(define (make-sim)
  (sim 0 (make-heap cmp)))

(define (make-wire sim)
  (wire #f null sim))

; procedures

(define (call-actions xs)
  (if (null? xs)
      (void)
      (begin
        ((car xs))
        (call-actions (cdr xs)))))

(define (sim-wait! sim time)
  (if (and (not (equal? 0 (heap-count (sim-actions sim)))) (<= (car (heap-min (sim-actions sim))) (+ time (sim-time sim))))
      (let ([first-action (heap-min (sim-actions sim))])
        (begin
          (define tmp (- (+ time (sim-time sim)) (car first-action)))
          (heap-remove-min! (sim-actions sim))
          (set-sim-time! sim (car first-action))
          ((cdr first-action))
          (sim-wait! sim tmp)))
      (set-sim-time! sim (+ time (sim-time sim)))))

(define (wire-on-change! wire f)
  (begin
     (set-wire-actions! wire (append (wire-actions wire) (list f)))
     (f)))

(define (sim-add-action! sim time proc)
  (heap-add! (sim-actions sim) (cons (+ time (sim-time sim )) proc)))

(define (wire-set! wire value)
  (if (equal? value (wire-value wire))
      (void)
      (begin
        (set-wire-value! wire value)
        (call-actions (wire-actions wire)))))

; gates

(define (gate-not a b)
  (define (not-action)
    (sim-add-action! (wire-sim a) 1 (lambda () (wire-set! a (not (wire-value b)))) ))
  (wire-on-change! b not-action))

(define (gate-xor a b c)
  (define (xor-action)
    (sim-add-action! (wire-sim a) 2 (lambda () (wire-set! a (xor (wire-value b) (wire-value c)))) ))
  (wire-on-change! b xor-action)
  (wire-on-change! c xor-action))

(define (gate-or a b c)
  (define (or-action)
    (sim-add-action! (wire-sim a) 1 (lambda () (wire-set! a (or (wire-value b) (wire-value c)))) ))
  (wire-on-change! b or-action)
  (wire-on-change! c or-action))

(define (gate-and a b c)
  (define (and-action)
    (sim-add-action! (wire-sim a) 1 (lambda () (wire-set! a (and (wire-value b) (wire-value c)))) ))
  (wire-on-change! b and-action)
  (wire-on-change! c and-action))

(define (gate-nand a b c)
  (define (nand-action)
    (sim-add-action! (wire-sim a) 1 (lambda () (wire-set! a (not (and (wire-value b) (wire-value c))))) ))
  (wire-on-change! b nand-action)
  (wire-on-change! c nand-action))

(define (gate-nor a b c)
  (define (nor-action)
    (sim-add-action! (wire-sim a) 1 (lambda () (wire-set! a (not (or (wire-value b) (wire-value c))))) ))
  (wire-on-change! b nor-action)
  (wire-on-change! c nor-action))

; wires

(define (wire-not a)
  (define tmp (make-wire (wire-sim a)))
  (gate-not tmp a)
  tmp)

(define (wire-and a b)
  (define tmp (make-wire (wire-sim a)))
  (gate-and tmp a b)
  tmp)

(define (wire-or a b)
  (define tmp (make-wire (wire-sim a)))
  (gate-or tmp a b)
  tmp)

(define (wire-nand a b)
  (define tmp (make-wire (wire-sim a)))
  (gate-nand tmp a b)
  tmp)

(define (wire-nor a b)
  (define tmp (make-wire (wire-sim a)))
  (gate-nor tmp a b)
  tmp)

(define (wire-xor a b)
  (define tmp (make-wire (wire-sim a)))
  (gate-xor tmp a b)
  tmp)

; bus

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

(define (flip-flop out clk data)
  (define sim (wire-sim data))
  (define w1  (make-wire sim))
  (define w2  (make-wire sim))
  (define w3  (wire-nand (wire-and w1 clk) w2))
  (gate-nand w1 clk (wire-nand w2 w1))
  (gate-nand w2 w3 data)
  (gate-nand out w1 (wire-nand out w3)))

; tests

; boolean function
(define s1 (make-sim))

(define s1a (make-wire s1))
(wire-set! s1a #t)
(define s1b (make-wire s1))
(define s1c (make-wire s1))
(wire-set! s1c #t)
(define s1d (make-wire s1))
(define s1y (make-wire s1))
(define s1ny (wire-not s1y))
(define s1x (make-wire s1))
(define s1nx (wire-not s1x))

(define s1w0 (wire-and s1a s1nx))
(define s1w1 (wire-and s1w0 s1ny))
(define s1w2 (wire-and s1b s1nx))
(define s1w3 (wire-and s1w2 s1y))
(define s1w4 (wire-and s1c s1x))
(define s1w5 (wire-and s1w4 s1ny))
(define s1w6 (wire-and s1d s1x))
(define s1w7 (wire-and s1w6 s1y))
(define s1w8 (wire-or s1w1 s1w3))
(define s1w9 (wire-or s1w5 s1w7))

(define s1o (wire-or s1w8 s1w9))
(sim-wait! s1 100)
(check-equal? #t (wire-value s1o))
(wire-set! s1y #t)
(sim-wait! s1 100)
(check-equal? #f (wire-value s1o))
(wire-set! s1y #f)
(wire-set! s1x #t)
(sim-wait! s1 100)
(check-equal? #t (wire-value s1o))
(wire-set! s1y #t)
(wire-set! s1x #t)
(sim-wait! s1 100)
(check-equal? #f (wire-value s1o))

; two bit adder
(define s2 (make-sim))

(define s2a0 (make-wire s2))
(define s2a1 (make-wire s2))
(define s2b0 (make-wire s2))
(define s2b1 (make-wire s2))
(define s2o0 (make-wire s2))
(define s2o1 (make-wire s2))
(define s2c0 (make-wire s2))
(define s2c1 (make-wire s2))
(define s2f (make-wire s2))

(define (fulladder a b s c cin)
  (define l1 (wire-xor a b))
  (define l2 (wire-and a b))
  (define l3 (wire-and l1 cin))
  (gate-xor s l1 cin)
  (gate-or c l2 l3))

(fulladder s2a0 s2b0 s2o0 s2c0 s2f)
(fulladder s2a1 s2b1 s2o1 s2c1 s2c0)

(bus-set! (list s2a0 s2a1) 1)
(bus-set! (list s2b0 s2b1) 1)
(sim-wait! s2 20)
(check-equal? 2 (bus-value (list s2o0 s2o1)))
(bus-set! (list s2a0 s2a1) 0)
(bus-set! (list s2b0 s2b1) 0)
(sim-wait! s2 20)
(check-equal? 0 (bus-value (list s2o0 s2o1)))
(bus-set! (list s2a0 s2a1) 3)
(bus-set! (list s2b0 s2b1) 2)
(sim-wait! s2 20)
(check-equal? 1 (bus-value (list s2o0 s2o1)))
(bus-set! (list s2a0 s2a1) 1)
(bus-set! (list s2b0 s2b1) 2)
(sim-wait! s2 20)
(check-equal? 3 (bus-value (list s2o0 s2o1)))

; not clock + xor timing check
(define s3 (make-sim))
(define s3x (make-wire s3))
(define s3y (make-wire s3))
(define s3xor (wire-xor s3y s3x))

(gate-not s3x s3x)

(check-equal? (wire-value s3x) #f)
(wire-set! s3y #t)
(check-equal? (wire-value s3xor) #f)
(sim-wait! s3 1)
(check-equal? (wire-value s3x) #t)
(check-equal? (wire-value s3xor) #f)
(sim-wait! s3 1)
(check-equal? (wire-value s3x) #f)
(check-equal? (wire-value s3xor) #t)
(wire-set! s3y #f)
(sim-wait! s3 2)
(check-equal? (wire-value s3x) #f)
(check-equal? (wire-value s3xor) #f)
(sim-wait! s3 1)
(check-equal? (wire-value s3xor) #t)

; licznik binarny / test na flip flop, wzięty ze skosu
(define s4 (make-sim))

(define (make-counter n clk en)
  (if (= n 0)
      '()
      (let [(out (make-wire s4))]
        (flip-flop out clk (wire-xor en out))
        (cons out (make-counter (- n 1) clk (wire-and en out))))))

(define clk (make-wire s4))
(define en  (make-wire s4))
(define counter (make-counter 4 clk en))

(wire-set! en #t)

(define (tick)
  (wire-set! clk #t)
  (sim-wait! s4 20)
  (wire-set! clk #f)
  (sim-wait! s4 20)
  (bus-value counter))

(check-equal? (tick) 7)
(check-equal? (tick) 8)
(check-equal? (tick) 9)
(check-equal? (tick) 10)
(check-equal? (tick) 11)
(check-equal? (tick) 12)
(check-equal? (tick) 13)
(check-equal? (tick) 14)
(check-equal? (tick) 15)
(check-equal? (tick) 0)
(check-equal? (tick) 1)
(check-equal? (tick) 2)
(wire-set! en #f)
(sim-wait! s4 10)
(check-equal? (tick) 2)
(check-equal? (tick) 2)
