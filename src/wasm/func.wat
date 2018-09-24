(module
 (table 0 anyfunc)
 (memory $0 1)
 (export "memory" (memory $0))
 (export "_Z6squarei" (func $_Z6squarei))
 (func $_Z6squarei (; 0 ;) (param $0 i32) (result i32)
  (i32.mul
   (get_local $0)
   (get_local $0)
  )
 )
)
