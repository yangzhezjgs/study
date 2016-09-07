# Python
-------

## 闭包
在一个内部函数中使用了外部函数（非全局作用域）的变量时，内部函数就是一个**闭包**，而使用的外部变量称为**自由变量**。换句话说，闭包就是一种保存了执行时的外部环境上下文的函数，它携带着外部函数的作用域的副本，也就是作用域绑定。

最简单的例子：
```Python
In [1]: def counter(start_at=0):
   ...:     count = [start_at]
   ...:     def incr():
   ...:         count[0] += 1
   ...:         return count[0]
   ...:     return incr
   
In [6]: count = counter()

In [7]: count()
Out[7]: 1

In [8]: count()
Out[8]: 2
```
在Python2中要将整型包裹成为列表，否则会出现`UnboundLocalError: local variable referenced before assignment`，在Python3中可以使用`nonlocal`关键字。

![LEGB](https://pic3.zhimg.com/7f8c20dcd6ae5a99a4d01b6c3a525142_r.jpg)      

Python遇到变量会按照LEGB的顺序寻找，并且在哪里创建变量就在哪个作用域绑定。用整型的话就会创建一个整型对象，然后绑定到局部变量上，不会向外部作用域寻找，就会出现先引用后定义导致的`UnboundLocalError`错误。使用列表，不是创建了一个变量，而是引用了外部的列表并修改列表内的引用。

**闭包还有几个注意点**：

* 在同一个函数内定义的多个内嵌函数**共享同一个闭包**。多次调用外部函数创建的闭包是相互独立的，各有一个外部函数环境的副本。

* 自由变量是在内部函数被调用时在闭包中寻找的，而不是绑定值，换句话说也就是**延迟绑定**:
> Late binding in closures: the values of variables used in closures are looked up at the time the inner function is called.


```Python
In [9]: def test():
   ...:     return [lambda x: x + i for i in range(3)]
   ...: 
   
# 共享闭包，延迟绑定，当调用func时，i在test内已经是2，所以结果相同
In [10]: for func in test():
   ....:     print func(0), func.func_closure
   ....:     
2 (<cell at 0x7f27acabdde0: int object at 0x254d140>,)
2 (<cell at 0x7f27acabdde0: int object at 0x254d140>,)
2 (<cell at 0x7f27acabdde0: int object at 0x254d140>,)

# 使用yield，延迟计算i
In [12]: def test2():
   ....:     for i in range(3):
   ....:         yield lambda x: x + i
   ....:         
   
# 要注意每个函数只能立即调用，因为共享闭包，所以后续yield将i改变也会影响到之前生成的函数
In [14]: for i, func in enumerate(test2()):
   ....:     if i == 0:
   ....:         saved = func
   ....:     print func(0), func.func_closure
   ....:     
0 (<cell at 0x7f27aca96de0: int object at 0x254d170>,)
1 (<cell at 0x7f27aca96de0: int object at 0x254d158>,)
2 (<cell at 0x7f27aca96de0: int object at 0x254d140>,)

# 共享闭包，后续的改变影响到了之前返回的函数
In [15]: print saved(0), saved.func_closure
2 (<cell at 0x7f27aca96de0: int object at 0x254d140>,)
```

解决闭包变化影响的一种方法是使用函数的默认参数，就有些类似偏函数partial了，但是这种方法缺少了闭包的强大功能，后续它是不可变的：
```Python
In [16]: def test3():
   ....:     return [lambda x, i=i: x + i for i in range(3)]
   ....: 

In [17]: for func in test3():
   ....:     print func(0)
   ....:     
0
1
2
# 无闭包
In [18]: func.func_closure

```
默认参数是函数自身的变量，也就没有引用外部的自由变量，当然就没有了闭包。默认参数对象在函数定义的时候被创建，之后的函数调用若未传入该参数，就将该对象绑定到变量上，这也会带来一点小陷阱：
```Python
In [19]: def append(l=[]):
   ....:     l.append(1)
   ....:     return l
   ....: 

In [20]: append()
Out[20]: [1]

# 因为列表是可变对象，调用append修改了对象的内容，值得一提的是列表的+=操作被实现为extend方法，也就是在对象内直接修改
In [21]: append()
Out[21]: [1, 1]
```
或许有人会问整型为什么可以，因为整型、字符串、元组是**不可变类型**。修改变量时，是创建了一个新的对象绑定到变量上，取代了旧对象，而默认参数一直指向原有的对象，没有发生变化。
