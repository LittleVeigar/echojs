// generator: traceur
// xfail: subclassing builtins is broken

// Array.from from kangax
class C extends Array {}
console.log(C.from({ length: 0 }) instanceof C);
