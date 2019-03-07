# 1. Vector的使用
## 初始化一个vector变量
vector<int> intV1(10); //定义10个int型的vector
intV1.size(); //获取这个vector的size
intV1.empty(); //vector判空
intV1.push_back(100); //向vector的尾部添加一个100的元素
intV1.clear(); //情况vector

可以参考：https://blog.csdn.net/longshengguoji/article/details/8507394


# virtual关键字使用
运行时多态:  
父类和子类都使用相同参数、相同返回值，相同函数名，在runtim时根据实际的对象，调用相应的函数  
运行时重载：  
父类和子类有相同函数名，单至少参数或返回值不同  

```
class A {
public:
    virtual int func(int i, int o);
};

class B : public A
{
public:
    int func(int i, int o);
};

A* a = new A();
a->func();

B* b = new B();
b->func();
```

要使用多态，需要使用virtual关键字，问题来啦：
如果不使用virtual会报错吗？  
不会，但是调用的是父类的成员函数  
