---
title: GuideLine
abbrlink: 1351
date: 2021-08-04 16:37:45
tags:
---

## 1. TypeScript 指南

JavaScript 的面向对象式编程语言

## 2. 基础类型

基础类型：string，boolean，number

数组，元组，枚举

Object，Any

void， Null， Undefined

Never

## 3. 变量声明

作用域规则

var，let，const

readonly

### 3.1 解构

数组解构，对象解构

属性重命名

默认值

函数声明中的结构：可选值，默认值，必须参数

展开(...):

1. 后面的覆盖前面的

2. 展开一个对象实例，会丢失其方法

## 4. 接口

可选属性：？

只读属性：readonly

### 4.1 额外的属性检查

对象字面量会被特殊对待而且会经过 `额外属性检查`，当将它们赋值给变量或作为参数传递的时候。 如果一个对象字面量存在任何“目标类型”不包含的属性时，你会得到一个错误。

索引签名/可索引的类型:

```typescript
interface SquareConfig {
    color?: string;
    width?: number;
    [propName: string]: any;
}
```

接口定义函数：

```typescript
interface SearchFunc {
  (source: string, subString: string): boolean;
}
```

### 4.2 类类型

接口描述了类的公共部分，而不是公共和私有两部分。

当一个类实现了一个接口时，只对其实例部分进行类型检查。constructor存在于类的静态部分，所以不在检查的范围内。

```typescript
interface ClockConstructor {
    new (hour: number, minute: number): ClockInterface;
}
interface ClockInterface {
    tick();
}

function createClock(ctor: ClockConstructor, hour: number, minute: number): ClockInterface {
    return new ctor(hour, minute);
}

class DigitalClock implements ClockInterface {
    constructor(h: number, m: number) { }
    tick() {
        console.log("beep beep");
    }
}
class AnalogClock implements ClockInterface {
    constructor(h: number, m: number) { }
    tick() {
        console.log("tick tock");
    }
}

let digital = createClock(DigitalClock, 12, 17);
let analog = createClock(AnalogClock, 7, 32);
```

### 4.3 接口继承

和类一样，接口也可以相互继承。

混合类型:

```typescript
interface Counter {
    (start: number): string;
    interval: number;
    reset(): void;
}

function getCounter(): Counter {
    let counter = <Counter>function (start: number) { };
    counter.interval = 123;
    counter.reset = function () { };
    return counter;
}

let c = getCounter();
c(10);
c.reset();
c.interval = 5.0;
```

接口继承类:

当接口继承了一个类类型时，它会继承类的成员但不包括其实现。 就好像接口声明了所有类中存在的成员，但并没有提供具体实现一样。 接口同样会继承到类的private和protected成员。 这意味着当你创建了一个接口继承了一个拥有私有或受保护的成员的类时，这个接口类型只能被这个类或其子类所实现（implement）。

## 5. 类

继承

公共，私有与受保护的修饰符

### 5.1 参数属性

```typescript
class Octopus {
    readonly numberOfLegs: number = 8;
    constructor(readonly name: string) {
    }
}
```

### 5.2 抽象类

```typescript
abstract class Department {

    constructor(public name: string) {
    }

    printName(): void {
        console.log('Department name: ' + this.name);
    }

    abstract printMeeting(): void; // 必须在派生类中实现
}

class AccountingDepartment extends Department {

    constructor() {
        super('Accounting and Auditing'); // 在派生类的构造函数中必须调用 super()
    }

    printMeeting(): void {
        console.log('The Accounting Department meets each Monday at 10am.');
    }

    generateReports(): void {
        console.log('Generating accounting reports...');
    }
}

let department: Department; // 允许创建一个对抽象类型的引用
department = new Department(); // 错误: 不能创建一个抽象类的实例
department = new AccountingDepartment(); // 允许对一个抽象子类进行实例化和赋值
department.printName();
department.printMeeting();
department.generateReports(); // 错误: 方法在声明的抽象类中不存在
```

### 5.3 构造函数

```typescript
class Greeter {
    greeting: string;
    constructor(message: string) {
        this.greeting = message;
    }
    greet() {
        return "Hello, " + this.greeting;
    }
}

let greeter: Greeter;
greeter = new Greeter("world");
console.log(greeter.greet());
```

转换为 JavaScript 后

```typescript
let Greeter = (function () {
    function Greeter(message) {
        this.greeting = message;
    }
    Greeter.prototype.greet = function () {
        return "Hello, " + this.greeting;
    };
    return Greeter;
})();

let greeter;
greeter = new Greeter("world");
console.log(greeter.greet());
```

改写一下这个例子，看看它们之间的区别:

```typescript
class Greeter {
    static standardGreeting = "Hello, there";
    greeting: string;
    greet() {
        if (this.greeting) {
            return "Hello, " + this.greeting;
        }
        else {
            return Greeter.standardGreeting;
        }
    }
}

let greeter1: Greeter;
greeter1 = new Greeter();
console.log(greeter1.greet());

let greeterMaker: typeof Greeter = Greeter;
greeterMaker.standardGreeting = "Hey there!";

let greeter2: Greeter = new greeterMaker();
console.log(greeter2.greet());
```

创建了一个叫做 greeterMaker的变量。 这个变量保存了这个类或者说保存了类构造函数。 然后我们使用 typeof Greeter，意思是取Greeter类的类型，而不是实例的类型。 或者更确切的说，"告诉我 Greeter标识符的类型"，也就是构造函数的类型。 这个类型包含了类的所有静态成员和构造函数。 之后，就和前面一样，我们在 greeterMaker上使用 new，创建 Greeter的实例。

## 6 函数

### 6.1 函数类型

```typescript
let myAdd: (x: number, y: number) => number =
    function(x: number, y: number): number { return x + y; };
```

可选参数和默认参数

剩余参数

### 6.2 `this`

```typescript
let deck = {
    suits: ["hearts", "spades", "clubs", "diamonds"],
    cards: Array(52),
    createCardPicker: function() {
        return function() {
            let pickedCard = Math.floor(Math.random() * 52);
            let pickedSuit = Math.floor(pickedCard / 13);

            return {suit: this.suits[pickedSuit], card: pickedCard % 13};
        }
    }
}

let cardPicker = deck.createCardPicker();
let pickedCard = cardPicker();

alert("card: " + pickedCard.card + " of " + pickedCard.suit);
```

this 为 window，在严格模式下为 undefined。

为了解决这个问题，我们可以在函数被返回时就绑好正确的this。 这样的话，无论之后怎么使用它，都会引用绑定的‘deck’对象。 我们需要改变函数表达式来使用ECMAScript 6箭头语法。 箭头函数能保存函数创建时的 this值，而不是调用时的值：

```typescript
let deck = {
    suits: ["hearts", "spades", "clubs", "diamonds"],
    cards: Array(52),
    createCardPicker: function() {
        // NOTE: the line below is now an arrow function, allowing us to capture 'this' right here
        return () => {
            let pickedCard = Math.floor(Math.random() * 52);
            let pickedSuit = Math.floor(pickedCard / 13);

            return {suit: this.suits[pickedSuit], card: pickedCard % 13};
        }
    }
}

let cardPicker = deck.createCardPicker();
let pickedCard = cardPicker();

alert("card: " + pickedCard.card + " of " + pickedCard.suit);
```

更好事情是，TypeScript会警告你犯了一个错误，如果你给编译器设置了--noImplicitThis标记。 它会指出 this.suits[pickedSuit]里的this的类型为any。

```typescript
interface Card {
    suit: string;
    card: number;
}
interface Deck {
    suits: string[];
    cards: number[];
    createCardPicker(this: Deck): () => Card;
}
let deck: Deck = {
    suits: ["hearts", "spades", "clubs", "diamonds"],
    cards: Array(52),
    createCardPicker: function(this: Deck) {
        return () => {
            let pickedCard = Math.floor(Math.random() * 52);
            let pickedSuit = Math.floor(pickedCard / 13);

            return {suit: this.suits[pickedSuit], card: pickedCard % 13};
        }
    }
}

let cardPicker = deck.createCardPicker();
let pickedCard = cardPicker();

alert("card: " + pickedCard.card + " of " + pickedCard.suit);
```

现在TypeScript知道createCardPicker期望在某个Deck对象上调用。 也就是说 this是Deck类型的，而非any，因此--noImplicitThis不会报错了。

## 7. 泛型

用带有调用签名的对象字面量来定义泛型函数：

```typescript
interface GenericIdentityFn {
    <T>(arg: T): T;
}

function identity<T>(arg: T): T {
    return arg;
}

let myIdentity: GenericIdentityFn = identity;
```

泛型接口：

```typescript
interface GenericIdentityFn {
    <T>(arg: T): T;
}

function identity<T>(arg: T): T {
    return arg;
}

let myIdentity: GenericIdentityFn = identity;
```

下面的写法与上面的等效

```typescript
interface GenericIdentityFn<T> {
    (arg: T): T;
}

function identity<T>(arg: T): T {
    return arg;
}

let myIdentity: GenericIdentityFn<number> = identity;
```

### 7.1 泛型类

```typescript
class GenericNumber<T> {
    zeroValue: T;
    add: (x: T, y: T) => T;
}

let myGenericNumber = new GenericNumber<number>();
myGenericNumber.zeroValue = 0;
myGenericNumber.add = function(x, y) { return x + y; };
```

### 7.2 泛型约束

```typescript
interface Lengthwise {
    length: number;
}

function loggingIdentity<T extends Lengthwise>(arg: T): T {
    console.log(arg.length);  // Now we know it has a .length property, so no more error
    return arg;
}
```

### 7.3 在泛型约束中使用类型参数

```typescript
function getProperty(obj: T, key: K) {
    return obj[key];
}

let x = { a: 1, b: 2, c: 3, d: 4 };

getProperty(x, "a"); // okay
getProperty(x, "m"); // error: Argument of type 'm' isn't assignable to 'a' | 'b' | 'c' | 'd'.
```

### 7.4 在泛型里使用类类型

在TypeScript使用泛型创建工厂函数时，需要引用构造函数的类类型。

```typescript
function create<T>(c: {new(): T; }): T {
    return new c();
}
```

原型属性推断并约束构造函数与类实例的关系:

```typescript
class BeeKeeper {
    hasMask: boolean;
}

class ZooKeeper {
    nametag: string;
}

class Animal {
    numLegs: number;
}

class Bee extends Animal {
    keeper: BeeKeeper;
}

class Lion extends Animal {
    keeper: ZooKeeper;
}

function createInstance<A extends Animal>(c: new () => A): A {
    return new c();
}

createInstance(Lion).keeper.nametag;  // typechecks!
createInstance(Bee).keeper.hasMask;   // typechecks!
```

## 8. 枚举

异构枚举

```typescript
enum BooleanLikeHeterogeneousEnum {
    No = 0,
    Yes = "YES",
}
```

联合枚举与枚举成员的类型

运行时的枚举

```typescript
enum E {
    X, Y, Z
}
```

```typescript
function f(obj: { X: number }) {
    return obj.X;
}

// Works, since 'E' has a property named 'X' which is a number.
f(E);
```

反向映射

```typescript
enum Enum {
    A
}
let a = Enum.A;
let nameOfA = Enum[a]; // "A"
```

外部枚举

```typescript
declare enum Enum {
    A = 1,
    B,
    C = 2
}
```

外部枚举和非外部枚举之间有一个重要的区别，在正常的枚举里，没有初始化方法的成员被当成常数成员。 对于非常数的外部枚举而言，没有初始化方法时被当做需要经过计算的。

## 9. 高级类型[^高级类型]

### 9.1 交叉类型

`Person & Serializable & Loggable`

```typescript
function extend<T, U>(first: T, second: U): T & U {
    let result = <T & U>{};
    for (let id in first) {
        (<any>result)[id] = (<any>first)[id];
    }
    for (let id in second) {
        if (!result.hasOwnProperty(id)) {
            (<any>result)[id] = (<any>second)[id];
        }
    }
    return result;
}

class Person {
    constructor(public name: string) { }
}
interface Loggable {
    log(): void;
}
class ConsoleLogger implements Loggable {
    log() {
        // ...
    }
}
var jim = extend(new Person("Jim"), new ConsoleLogger());
var n = jim.name;
jim.log();
```

### 9.2 联合类型（Union Types）

形式： `number | string | boolean`

```typescript
interface Bird {
    fly();
    layEggs();
}

interface Fish {
    swim();
    layEggs();
}

function getSmallPet(): Fish | Bird {
    // ...
}

let pet = getSmallPet();
pet.layEggs(); // okay
pet.swim();    // errors
```

### 9.3 类型保护与区分类型（Type Guards and Differentiating Types）

用户自定义类型保护：

```typescript
function isFish(pet: Fish | Bird): pet is Fish {
    return (<Fish>pet).swim !== undefined;
}
```

typeof类型保护：

```typescript
function isNumber(x: any): x is number {
    return typeof x === "number";
}

function isString(x: any): x is string {
    return typeof x === "string";
}

function padLeft(value: string, padding: string | number) {
    if (isNumber(padding)) {
        return Array(padding + 1).join(" ") + value;
    }
    if (isString(padding)) {
        return padding + value;
    }
    throw new Error(`Expected string or number, got '${padding}'.`);
}
```

instanceof类型保护：

```typescript
interface Padder {
    getPaddingString(): string
}

class SpaceRepeatingPadder implements Padder {
    constructor(private numSpaces: number) { }
    getPaddingString() {
        return Array(this.numSpaces + 1).join(" ");
    }
}

class StringPadder implements Padder {
    constructor(private value: string) { }
    getPaddingString() {
        return this.value;
    }
}

function getRandomPadder() {
    return Math.random() < 0.5 ?
        new SpaceRepeatingPadder(4) :
        new StringPadder("  ");
}

// 类型为SpaceRepeatingPadder | StringPadder
let padder: Padder = getRandomPadder();

if (padder instanceof SpaceRepeatingPadder) {
    padder; // 类型细化为'SpaceRepeatingPadder'
}
if (padder instanceof StringPadder) {
    padder; // 类型细化为'StringPadder'
}
```

### 9.4 可辨识联合（Discriminated Unions）

1. 具有普通的单例类型属性— 可辨识的特征。
2. 一个类型别名包含了那些类型的联合— 联合。
3. 此属性上的类型保护。

```typescript
interface Square {
    kind: "square"; // 可辨识的特征或 标签
    size: number;
}
interface Rectangle {
    kind: "rectangle"; // 可辨识的特征或 标签
    width: number;
    height: number;
}
interface Circle {
    kind: "circle"; // 可辨识的特征或 标签
    radius: number;
}

type Shape = Square | Rectangle | Circle; // 联合

function area(s: Shape) {
    switch (s.kind) {
        case "square": return s.size * s.size;
        case "rectangle": return s.height * s.width;
        case "circle": return Math.PI * s.radius ** 2;
    }
}
```

### 9.5 多态的 this类型

```typescript
class BasicCalculator {
    public constructor(protected value: number = 0) { }
    public currentValue(): number {
        return this.value;
    }
    public add(operand: number): this {
        this.value += operand;
        return this;
    }
    public multiply(operand: number): this {
        this.value *= operand;
        return this;
    }
    // ... other operations go here ...
}

let v = new BasicCalculator(2)
            .multiply(5)
            .add(1)
            .currentValue();


```

由于这个类使用了 this类型，你可以继承它，新的类可以直接使用之前的方法，不需要做任何的改变。

```typescript
class ScientificCalculator extends BasicCalculator {
    public constructor(value = 0) {
        super(value);
    }
    public sin() {
        this.value = Math.sin(this.value);
        return this;
    }
    // ... other operations go here ...
}

let v = new ScientificCalculator(2)
        .multiply(5)
        .sin()
        .add(1)
        .currentValue();
```

如果没有 this类型， ScientificCalculator就不能够在继承 BasicCalculator的同时还保持接口的连贯性。 multiply将会返回 BasicCalculator，它并没有 sin方法。 然而，使用 this类型， multiply会返回 this，在这里就是 ScientificCalculator。

### 9.6 索引类型（Index types）

```typescript
function pluck(o, names) {
    return names.map(n => o[n]);
}
```

下面是如何在TypeScript里使用此函数，通过 `索引类型查询`和 `索引访问`操作符：

```typescript
function pluck<T, K extends keyof T>(o: T, names: K[]): T[K][] {
  return names.map(n => o[n]);
}

interface Person {
    name: string;
    age: number;
}
let person: Person = {
    name: 'Jarid',
    age: 35
};
let strings: string[] = pluck(person, ['name']); // ok, string[]
```

编译器会检查 name是否真的是 Person的一个属性。 本例还引入了几个新的类型操作符。 首先是 keyof T， 索引类型查询操作符。 对于任何类型 T， keyof T的结果为 T上已知的公共属性名的联合。

```typescript
let personProps: keyof Person; // 'name' | 'age'
```

第二个操作符是 `T[K]`， 索引访问操作符。 在这里，类型语法反映了表达式语法。 这意味着 `person['name']`具有类型 `Person['name']` — 在我们的例子里则为 `string`类型。 然而，就像索引类型查询一样，你可以在普通的上下文里使用 `T[K]`，这正是它的强大所在。 你只要确保类型变量 K extends keyof T就可以了。

```typescript
function getProperty<T, K extends keyof T>(o: T, name: K): T[K] {
    return o[name]; // o[name] is of type T[K]
}
```

#### 9.6.1 索引类型和字符串索引签名

`keyof` 和 `T[K]`与字符串索引签名进行交互。 如果你有一个带有字符串索引签名的类型，那么 `keyof T`会是 `string`。 并且 `T[string]`为索引签名的类型：

```typescript
interface Map<T> {
    [key: string]: T;
}
let keys: keyof Map<number>; // string
let value: Map<number>['foo']; // number
```

### 9.7 映射类型

```typescript
type Readonly<T> = {
    readonly [P in keyof T]: T[P];
}
type Partial<T> = {
    [P in keyof T]?: T[P];
}
```

像下面这样使用：

```typescript
type PersonPartial = Partial<Person>;
type ReadonlyPerson = Readonly<Person>;
```

基于一些已存在的类型，且按照一定的方式转换字段。 这就是 keyof和索引访问类型要做的事情：

```typescript
type Nullable<T> = { [P in keyof T]: T[P] | null }
type Partial<T> = { [P in keyof T]?: T[P] }
```

在这些例子里，属性列表是 keyof T且结果类型是 T[P]的变体。 这是使用通用映射类型的一个好模版。 因为这类转换是 `同态的`，映射只作用于 `T`的属性而没有其它的。 编译器知道在添加任何新属性之前可以拷贝所有存在的属性修饰符。 例如，假设 `Person.name`是只读的，那么 `Partial<Person>.name`也将是只读的且为可选的。

下面是另一个例子， `T[P]`被包装在 `Proxy<T>`类里：

```typescript
type Proxy<T> = {
    get(): T;
    set(value: T): void;
}
type Proxify<T> = {
    [P in keyof T]: Proxy<T[P]>;
}
function proxify<T>(o: T): Proxify<T> {
   // ... wrap proxies ...
}
let proxyProps = proxify(props);
```

注意 `Readonly<T>`和 `Partial<T>`用处不小，因此它们与 `Pick`和 `Record`一同被包含进了TypeScript的标准库里：

```typescript
type Pick<T, K extends keyof T> = {
    [P in K]: T[P];
}
type Record<K extends string, T> = {
    [P in K]: T;
}
```

#### 9.7.1 由映射类型进行推断

现在你了解了如何包装一个类型的属性，那么接下来就是如何拆包。 其实这也非常容易：

```typescript
function unproxify<T>(t: Proxify<T>): T {
    let result = {} as T;
    for (const k in t) {
        result[k] = t[k].get();
    }
    return result;
}

let originalProps = unproxify(proxyProps);
```

**注意:** 这个拆包推断只适用于同态的映射类型。 如果映射类型不是同态的，那么需要给拆包函数一个明确的类型参数。

#### 9.7.2 预定义的有条件类型

`TypeScript 2.8`在`lib.d.ts`里增加了一些预定义的有条件类型：

* `Exclude<T, U>` -- 从T中剔除可以赋值给U的类型。
* `Extract<T, U>` -- 提取T中可以赋值给U的类型。
* `NonNullable<T>` -- 从T中剔除null和undefined。
* `ReturnType<T>` -- 获取函数返回值类型。
* `InstanceType<T>` -- 获取构造函数类型的实例类型。

```typescript
type T00 = Exclude<"a" | "b" | "c" | "d", "a" | "c" | "f">;  // "b" | "d"
type T01 = Extract<"a" | "b" | "c" | "d", "a" | "c" | "f">;  // "a" | "c"

type T02 = Exclude<string | number | (() => void), Function>;  // string | number
type T03 = Extract<string | number | (() => void), Function>;  // () => void

type T04 = NonNullable<string | number | undefined>;  // string | number
type T05 = NonNullable<(() => string) | string[] | null | undefined>;  // (() => string) | string[]

function f1(s: string) {
    return { a: 1, b: s };
}

class C {
    x = 0;
    y = 0;
}

type T10 = ReturnType<() => string>;  // string
type T11 = ReturnType<(s: string) => void>;  // void
type T12 = ReturnType<(<T>() => T)>;  // {}
type T13 = ReturnType<(<T extends U, U extends number[]>() => T)>;  // number[]
type T14 = ReturnType<typeof f1>;  // { a: number, b: string }
type T15 = ReturnType<any>;  // any
type T16 = ReturnType<never>;  // any
type T17 = ReturnType<string>;  // Error
type T18 = ReturnType<Function>;  // Error

type T20 = InstanceType<typeof C>;  // C
type T21 = InstanceType<any>;  // any
type T22 = InstanceType<never>;  // any
type T23 = InstanceType<string>;  // Error
type T24 = InstanceType<Function>;  // Error
```

**注意：** `Exclude`类型是建议的Diff类型的一种实现。我们使用`Exclude`这个名字是为了避免破坏已经定义了`Diff`的代码，并且我们感觉这个名字能更好地表达类型的语义。我们没有增加`Omit<T, K>`类型，因为它可以很容易的用`Pick<T, Exclude<keyof T, K>>`来表示。

[^高级类型]: [TypeScript 高级类型清单](https://chinese.freecodecamp.org/news/advanced-typescript-types-cheatsheet/)
