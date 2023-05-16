; *********************************************
; *  314 Principles of Programming Languages  *
; *  Spring 2023                              *
; *  Student Version                          *
; *********************************************

;; contains "ctv", "A", and "reduce" definitions
(load "include.ss")

;; contains simple dictionary definition
(load "dictionary.ss")

;; -----------------------------------------------------
;; HELPER FUNCTIONS

;; *** CODE FOR ANY HELPER FUNCTION GOES HERE ***
(define key-helper
  (lambda (l num)
    (if (null? l)
        num
        (key-helper (cdr l) (+ ( * 29 num) (ctv (car l))))
    )
  )
)

(define check-hash
  (lambda (vector w)
    (define answer (reduce
                     (lambda (x y)
                       (if
                        (or (eq? x y) (or (eq? x #t) (eq? y #t)))
                        #t
                        y))
                     vector (car w)))
    ;(display reduced)
    (if (boolean? answer)
         #t
         #f
         )))
    
    ;(if (null? w)
    ;    #t
    ;     (exists? (car w) vector)


(define hash
  (lambda (hashfunctionlist dict)
    (cond ((null? hashfunctionlist)
           '())
          (else
           (append (map (car hashfunctionlist) dict)
                   (hash (cdr hashfunctionlist) dict)
)))))
;;  (define hash-1 (gen-hash-division-method 70111))
;;  (define hash-2 (gen-hash-division-method 89997))
;;  (define hash-3 (gen-hash-multiplication-method 7221))
;;  (define hash-4 (gen-hash-multiplication-method 900))

;;  (define hashfl-1 (list hash-1 hash-2 hash-3 hash-4))
;;  (define checker-1 (gen-checker hashfl-1 dictionary))
;;  (checker-1 '(a r g g g g)) ==> #f

;; -----------------------------------------------------
;; KEY FUNCTION

(define key
    (lambda (w)
       (key-helper (reverse w) 5077)
      ;(key-helper (cdr l) (+ ( * 29 num) (ctv (car l))))
      
  ))
;(key '(t r e e f r o g))
;(key '(a p p l e))
;(key '(i n q u i r y))
;(key '(d i p l o m a t i c))
;(key '(a u t o n o m y))
;(key '(m i c r o p h o n e))



;; -----------------------------------------------------
;; EXAMPLE KEY VALUES
;;   (key '(h e l l o))       = 104146015601
;;   (key '(m a y))           = 123844020
;;   (key '(t r e e f r o g)) = 2539881083658035

;; -----------------------------------------------------
;; HASH FUNCTION GENERATORS
;; value of parameter "size" should be a prime number
;; range of values: 0..size-1
(define gen-hash-division-method
  (lambda (size)
      (lambda (k) (modulo (key k) size))
))

; -TEST- ((gen-hash-division-method 11) 100)

;; Note: hash functions may return integer values in "real"
;;       format, e.g., 17.0 for 17

(define gen-hash-multiplication-method
  (lambda (size) ;; range of values: 0..size-1
     (lambda (k)
       (let ((x (key k)))
       (floor (* size (- (* x A) (floor (* x A)))))
         ))
))


;; -----------------------------------------------------
;; EXAMPLE HASH FUNCTIONS AND HASH FUNCTION LISTS

;(define hash-1 (gen-hash-division-method 70111))
;(define hash-2 (gen-hash-division-method 16057))
;(define hash-3 (gen-hash-multiplication-method 7221))
;(define hash-4 (gen-hash-multiplication-method 911))

;(define hashfl-1 (list hash-1 hash-2 hash-3 hash-4))
;(define hashfl-2 (list hash-1 hash-3))
;(define hashfl-3 (list hash-2 hash-3))

;; -----------------------------------------------------
;; EXAMPLE HASH VALUES
;;   to test your hash function implementation
;;
;;  (hash-1 '(h e l l o))       ==> 51317
;;  (hash-1 '(m a y))           ==> 27994
;;  (hash-1 '(t r e e f r o g)) ==> 33645
;;
;;  (hash-2 '(h e l l o))       ==> 47249
;;  (hash-2 '(m a y))           ==> 8148
;;  (hash-2 '(t r e e f r o g)) ==> 53006
;;
;;  (hash-3 '(h e l l o))       ==> 711.0
;;  (hash-3 '(m a y))           ==> 4747.0
;;  (hash-3 '(t r e e f r o g)) ==> 5418.0
;;
;;  (hash-4 '(h e l l o))       ==> 88.0
;;  (hash-4 '(m a y))           ==> 591.0
;;  (hash-4 '(t r e e f r o g)) ==> 675.0


;; -----------------------------------------------------
;; SPELL CHECKER GENERATOR

(define gen-checker
  (lambda (hashfunctionlist dict)
    (let ((vector (hash hashfunctionlist dict)))
      ;(display vector)
      (lambda (w)
        (check-hash vector (hash hashfunctionlist (list w)))))))


;; -----------------------------------------------------
;; EXAMPLE SPELL CHECKERS


;(define checker-1 (gen-checker hashfl-1 dictionary))
;(define checker-2 (gen-checker hashfl-2 dictionary))
;(define checker-3 (gen-checker hashfl-3 dictionary))

;(checker-1 '(s t u p e n d o u s l y))
;(checker-2 '(h e l l o))
;(checker-2 '(a r g g g g))
;(checker-2 '(c r e a m))
;(checker-3 '(e x k k k z z z z z z s s s))


;; EXAMPLE APPLICATIONS OF A SPELL CHECKER
;;
;;  (checker-1 '(a r g g g g)) ==> #f
;;  (checker-2 '(h e l l o)) ==> #t
;;  (checker-2 '(a r g g g g)) ==> #f

(define hash-1 (gen-hash-division-method 70111))
(define hash-2 (gen-hash-division-method 89997))
(define hash-3 (gen-hash-multiplication-method 7221))
(define hash-4 (gen-hash-multiplication-method 900))
(define hashfl-1 (list hash-1))
(define checker-1 (gen-checker hashfl-1 dictionary))

(define (firsts number lst)
  (if (equal? 0 number)
      '()
      (cons (car lst)
            (firsts (- number 1) (cdr lst)))))

(map checker-1 (firsts 10000 dictionary)) 