
var filename = 'func.wasm';
var funcId = '_Z6squarei'; // from intermediate .wat file

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
    var fn = instance.exports[ funcId ];
    var result = fn( 7 );
    console.log( 'result from func: ', result );
  } )
  .catch( function( err ) {
    console.error( 'could not load wasm file: ', err );
  } )
  ;