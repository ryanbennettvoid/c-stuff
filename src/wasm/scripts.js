
var filename = 'func.wasm';
var funcId = 'fib'; // from intermediate .wat file

var jsFib = function( n ) {
  if ( n == 0 ) return 0;
  if ( n == 1 ) return 1;
  return jsFib( n -1 ) + jsFib( n - 2 );
};

fetch( filename )
  .then( function( res ) {
    return res.arrayBuffer();
  }  )
  .then( function( bits ) {
    return WebAssembly.compile( bits );
  } )
  .then( function( module ) {
    return new WebAssembly.Instance( module );
  } )
  .then( function( instance ) {

    var cFunc = instance.exports[ funcId ];
    var jsFunc = jsFib;
    var n = 42;

    // run fibonacci sequence in C
    var t1 = Date.now();
    cFunc( n );
    var t2 = Date.now();
    var cDur = (t2-t1)/1000;
    console.log( 'C func done in ' + cDur + 's' );

    // // run fibonacci sequence in JS
    var t3 = Date.now();
    jsFunc( n );
    var t4 = Date.now();
    var jsDur = (t4-t3)/1000;
    console.log( 'JS func done in ' + jsDur + 's' );

    var ratio = jsDur/cDur;
    console.log( 'the C version is ' + ratio.toFixed(3) + 'x faster' );

  } )
  .catch( function( err ) {
    console.error( 'could not load wasm file: ', err );
  } )
  ;