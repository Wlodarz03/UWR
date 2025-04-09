// Warm up

type HelloWorld = string

// Easy
//Pick
type MyPick<T, K extends keyof T> = {[key in K]: T[key]}

//Readonly
type MyReadonly<T> = {readonly [key in keyof T]: T[key] }

//TypleObject
type TupleToObject<T extends readonly PropertyKey[]> = {[K in T[number]]: K };

//First of Array
type First<T extends any[]> = T extends [] ? never : T[0];

//Lenght of Tuple
type Length<T extends readonly any[]> = T['length']; 

//Exclude
type MyExclude<T, U> = T extends U ? never : T;

//Awaited
type MyAwaited<T extends PromiseLike<any>> = T extends PromiseLike<infer U> ? U extends PromiseLike<any> ? MyAwaited<U> : U : never

//If
type If<C extends boolean, T, F> = C extends true ? T : F;

//Concat
type Concat<T extends readonly unknown[], U extends readonly unknown[]> = [...T, ...U];

//Includes

// type Includes<T extends readonly unknown[], U> =
//      T extends [infer Head, ...infer Tail] 
//     ? Equal<Head, U> extends true 
//         ? true
//         : Includes<Tail,U>
//      : false;

//Push
type Push<T extends unknown[], U> = [...T, U];
//type Push<T extends any[], U> = [...T, U];

//Unshift
type Unshift<T extends unknown[], U> = [U, ...T];
//type Unshift<T extends any[], U> = [U, ...T];

//Parameters
type MyParameters<T extends (...args: any[]) => any> = T extends (...any: infer S) => any ? S : any 
