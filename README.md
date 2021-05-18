# Ray Tracing in One Weekend




![](https://cdn.jsdelivr.net/gh/Yousazoe/picgo-repo/img/zfk3Q1tuLECywHO.jpg)






### 引言

[《Ray Tracing In One Weekend》](https://raytracing.github.io/books/RayTracingInOneWeekend.html)（《一周末搞定光线追踪》）， 由Peter Shirley（就是那本图形学虎书的作者）所编写的的软渲光追三部曲第一本, 是一本非常好的入门级书籍, 篇幅不多, 一共只有54页, 适合新手学习。





> 原文源自[Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
>
> 本文转载自[ray tracing in one weekend 中文翻译](https://matrix4f.com/Graphic/ray-tracing-in-one-weekend/)的翻译,如果您愿意帮助译者改进这个翻译, 请直接**发送邮件**到[zgxmy@126.com](mailto:zgxmy@126.com), 万分感激



### 概述

> I’ve taught many graphics classes over the years. Often I do them in ray tracing, because you are forced to write all the code, but you can still get cool images with no API. I decided to adapt my course notes into a how-to, to get you to a cool program as quickly as possible. It will not be a full-featured ray tracer, but it does have the indirect lighting which has made ray tracing a staple in movies. Follow these steps, and the architecture of the ray tracer you produce will be good for extending to a more extensive ray tracer if you get excited and want to pursue that.

这些年来我开过不少图形学的课。我常常把光线追踪作为课堂上的教学内容。因为对于光线追踪来说, 在不使用任何API的情况下, 你不得不被迫手撸全部的代码, 但你仍然能渲染出炫酷的图片。我决定将我的课堂笔记改写成本教程, 让你能尽可能快的实现一个炫酷的光线追踪器（ray tracer）。这并不是一个功能完备的光线追踪器。但是它却拥用让光线追踪在电影行业成为主流的非直接光照（indirect lighting）。跟随本教程循序渐进, 你的光线追踪器的代码构筑将会变得易于拓展。如果之后你对这方面燃起了兴趣, 你可以将它拓展成一个更加完备的光线追踪器。



> When somebody says “ray tracing” it could mean many things. What I am going to describe is technically a path tracer, and a fairly general one. While the code will be pretty simple (let the computer do the work!) I think you’ll be very happy with the images you can make.

当大家提起”光线追踪”, 可能指的是很多不同的东西。我对这个词的描述是, 光线追踪在技术上就是一个路径追踪器, 事实上大部分情况下这个词都是这个意思。光线追踪器的代码也是十分的简单（让电脑帮我们算去吧!）。当你看到你渲染的图片时, 你一定会感到高兴的。



> I’ll take you through writing a ray tracer in the order I do it, along with some debugging tips. By the end, you will have a ray tracer that produces some great images. You should be able to do this in a weekend. If you take longer, don’t worry about it. I use C++ as the driving language, but you don’t need to. However, I suggest you do, because it’s fast, portable, and most production movie and video game renderers are written in C++. Note that I avoid most “modern features” of C++, but inheritance and operator overloading are too useful for ray tracers to pass on. I do not provide the code online, but the code is real and I show all of it except for a few straightforward operators in the `vec3` class. I am a big believer in typing in code to learn it, but when code is available I use it, so I only practice what I preach when the code is not available. So don’t ask!



接下来我会带你一步步的实现这个光线追踪, 并加入一些我的debug建议。最后你会得到一个能渲染出漂亮图片的光线追踪器。你认为你应该能在一个周末的时间内搞定。如果你花的时间比这长, 别担心, 也没太大问题。我使用C++作为本光线追踪器的实现语言。你其实不必, 但我还是推荐你用C++, 因为C++快速, 平台移植性好, 并且大部分的工业级电影和游戏渲染器都是使用C++编写的。注意这里我避免了大部分C++的新特性。但是继承和重载运算符我们保留, 对光线追踪器来说这个太有用了。网上的那些代码不是我提供的, 但是这些代码是真的可以跑的。除了`vec3`类中的一些简单的操作, 我将所有的代码都公开了。我是”学习编程要亲自动手敲代码”派。但是如果有一份代码摆在我面前, 我可以直接用, 我还是会用的。所以我只在没代码用的时候, 我才奉行我刚刚说的话。好啦, 别提这个了!



> I have left that last part in because it is funny what a 180 I have done. Several readers ended up with subtle errors that were helped when we compared code. So please do type in the code, but if you want to look at mine it is at:
>
> https://github.com/RayTracing/raytracing.github.io/



我没把上面一段删了, 因为我的态度180°大转变太好玩了。读者们帮我修复了一些次要的编译错误, 所以还是请你亲手来敲一下代码吧!但是你如果你想看看我的代码:

https://github.com/RayTracing/raytracing.github.io/



> I assume a little bit of familiarity with vectors (like dot product and vector addition). If you don’t know that, do a little review. If you need that review, or to learn it for the first time, check out Marschner’s and my graphics text, Foley, Van Dam, *et al.*, or McGuire’s graphics codex.



我假定你有一定的向量知识(比如说点乘和叉乘)。如果你记不太清楚, 回顾一下就行。如果你需要回顾, 或者你是第一次听说这个东西, 你可以看我或者Marschner的图像教材, Foley, Van Dam等也行。或者McGuire的codex。



> If you run into trouble, or do something cool you’d like to show somebody, send me some email at [ptrshrl@gmail.com.](mailto:ptrshrl@gmail.com.)
>
> I’ll be maintaining a site related to the book including further reading and links to resources at a blog https://in1weekend.blogspot.com/ related to this book.
>
> Thanks to everyone who lent a hand on this project. You can find them in the [acknowledgments](https://raytracing.github.io/books/RayTracingInOneWeekend.html#acknowledgments) section at the end of this book.
>
> Let’s get on with it!

如果你遇到的麻烦, 或者你弄出了很cooool的东西想要分享给大家看, 请给我发邮件。我的邮箱是[ptrshrl@gmail.com](mailto:ptrshrl@gmail.com)[点我发邮件](mailto:ptrshrl@gmail.com)

我会维护一个有关本书的博客网站, 网站里有一些拓展阅读和一些链接资源。网址是[https://in1weekend.blogspot.com](https://in1weekend.blogspot.com/)

好了不多BB, 让我们开始吧!





### 输出图像

#### PPM图像格式

> Whenever you start a renderer, you need a way to see an image. The most straightforward way is to write it to a file. The catch is, there are so many formats. Many of those are complex. I always start with a plain text ppm file. Here’s a nice description from Wikipedia:

当你开始写渲染器的时候, 你首先得能有办法看到你渲染的图像。最直接了当的方法就行把图像信息写入文件。问题是, 有那么多图片格式, 而且许多格式都挺复杂的。在开始部分, 我常常使用最简单的ppm文件，这里引用Wikipedia上面的简明介绍:

![](https://cdn.jsdelivr.net/gh/Yousazoe/picgo-repo/img/fig-1.01-ppm.jpg)

> Let’s make some C++ code to output such a thing:

我们来写一下输出这种图片格式的C++代码:



```c++
#include <iostream>

int main() {

    // Image

    const int image_width = 256;
    const int image_height = 256;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            auto r = double(i) / (image_width-1);
            auto g = double(j) / (image_height-1);
            auto b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
}
```





> There are some things to note in that code:
>
> 1. The pixels are written out in rows with pixels left to right.
> 2. The rows are written out from top to bottom.
> 3. By convention, each of the red/green/blue components range from 0.0 to 1.0. We will relax that later when we internally use high dynamic range, but before output we will tone map to the zero to one range, so this code won’t change.
> 4. Red goes from fully off (black) to fully on (bright red) from left to right, and green goes from black at the bottom to fully on at the top. Red and green together make yellow so we should expect the upper right corner to be yellow.

代码里有一些我们要注意的事情:

1. 对于像素来说, 每一行是从左往右写入的。

2. 行从上开始往下写入的。

3. 通常我们把RGB通道的值限定在0.0到1.0。我们之后计算颜色值的时候将使用一个动态的范围, 这个范围并不是0到1。但是在使用这段代码输出图像之前, 我们将把颜色映射到0到1。所以这部分输出图像代码不会改变。

4. 下方的红色从左到右由黑边红, 左侧的绿色从上到下由黑到绿。红+绿变黄, 所以我们的右上角应该是黄的。



下面是我个人的总结，这里有几个之前不是很清楚的点：

+ `auto`关键字就是变量的自动类型推断，可以在声明变量的时候根据变量初始值的类型自动为此变量选择匹配的类型，类似的关键字还有`decltype`

+ `static_cast`相当于传统的C语言里的强制转换，该运算符把`expression`转换为`new_type`类型，用来强迫隐式转换，例如`non-const`对象转为`const`对象，编译时检查，用于非多态的转换，可以转换指针及其他，但没有运行时类型检查来保证转换的安全性。它主要有如下几种用法：

  1. 用于类层次结构中基类（父类）和派生类（子类）之间指针或引用的转换

     **进行上行转换（把派生类的指针或引用转换成基类表示）是安全的**

     **进行下行转换（把基类指针或引用转换成派生类表示）时，由于没有动态类型检查，所以是不安全的**

  2. 用于基本数据类型之间的转换，如把`int`转换成`char`，把`int`转换成`enum`。这种转换的安全性也要开发人员来保证

  3. 把空指针转换成目标类型的空指针

  4. 把任何类型的表达式转换成`void`类型

  注意：`static_cast`不能转换掉`expression`的`const`、`volatile`、或者`__unaligned`属性

+ 这里行列的变化令人费解，第一层循环负责`image_height`也就是行的话显然是自顶向上的写入，而文中却说"The rows are written out from top to bottom."，让我感到困惑，可能是为了特定的色彩而故意为之吧



![](https://cdn.jsdelivr.net/gh/Yousazoe/picgo-repo/img/image-20210327092205919.png)





#### 创建图像文件

> Because the file is written to the program output, you'll need to redirect it to an image file. Typically this is done from the command-line by using the `>` redirection operator, like so:

现在我们要把cout的输出流写入文件中。幸好我们有命令行操作符`>`来定向输出流。在windows操作系统中差不多这样的:

```bash
build\Release\inOneWeekend.exe > image.ppm
```



> This is how things would look on Windows. On Mac or Linux, it would look like this:

在Mac或者Linux操作系统中, 大概是这个样子的:

```bash
build/inOneWeekend > image.ppm
```



这里我尝试直接按照上面的代码运行，结果并没有找到`build`指令。所以我按照linux平台的编译cpp程序的方式，得到了ppm格式的图像：

```shell
 g++ -o OneWeekend main.cpp
 ./OneWeekend > image.ppm
```



> Opening the output file (in `ToyViewer` on my Mac, but try it in your favorite viewer and Google “ppm viewer” if your viewer doesn’t support it) shows this result:

打开我们输出的文件（我是Mac系统, 我是用ToyViewer打开的, 你可以用你喜欢的任意看图软件来打开。如果你默认的看图软件比如windows下的图片不支持ppm格式, 只要Google一下”ppm viewer”装个新的就行。)打开后的结果如下:

![](https://cdn.jsdelivr.net/gh/Yousazoe/picgo-repo/img/img-1.01-first-ppm-image.png)



> Hooray! This is the graphics “hello world”. If your image doesn’t look like that, open the output file in a text editor and see what it looks like. It should start something like this:

好耶!这便是图形学中的”hello world”了。如果你的图像看上去不是这样的, 用文本编辑器打开你的输出文件, 看看里面内容是啥样的。不出意外的话, 正确格式应该是这样的:

```
P3
256 256
255
0 255 63
1 255 63
2 255 63
3 255 63
4 255 63
5 255 63
6 255 63
7 255 63
8 255 63
9 255 63
...
```



> If it doesn’t, then you probably just have some newlines or something similar that is confusing the image reader.
>
> If you want to produce more image types than PPM, I am a fan of `stb_image.h`, a header-only image library available on GitHub at https://github.com/nothings/stb.

如果不是这样的, 你可能当中多了些空行或者类似的什么东西, 因此你的看图软件识别不出来。

如果你想生成别的图像格式来代替基础的PPM, 我强烈安利[`stb_image.h`](https://github.com/nothings/stb/blob/master/stb_image.h), 你可以免费在[github](https://github.com/nothings/stb/blob/master/stb_image.h)上获取。



这里我自作聪明将`main.cpp`中的输出进行了更改，在后面造成了很大的错误：

```c++
//std::cout << "\nimage width: " << image_width << "    image height: " << image_height << "\n255\n";
std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

```



如果不按这种格式生成的`.ppm`打开会出现格式错误，需要格外注意。



#### 加入一个进度条

> Before we continue, let's add a progress indicator to our output. This is a handy way to track the progress of a long render, and also to possibly identify a run that's stalled out due to an infinite loop or other problem.

在我们往下走之前, 我们先来加个输出的进度提示。对于查看一次长时间渲染的进度来说, 这不失为一种简便的做法。也可以通过这个进度来判断程序是否卡住或者进入一个死循环。

> Our program outputs the image to the standard output stream (`std::cout`), so leave that alone and instead write to the error output stream (`std::cerr`):

我们的程序将图片信息写入标准输出流（`std::cout`）, 所以我们不能用这个流输出进度。我们换用错误输出流（`std::cerr`）来输出进度:

```diff
    for (int j = image_height-1; j >= 0; --j) {
+       std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto r = double(i) / (image_width-1);
            auto g = double(j) / (image_height-1);
            auto b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

+  	std::cerr << "\nDone.\n";
```





### vec3向量类

> Almost all graphics programs have some class(es) for storing geometric vectors and colors. In many systems these vectors are 4D (3D plus a homogeneous coordinate for geometry, and RGB plus an alpha transparency channel for colors). For our purposes, three coordinates suffices. We’ll use the same class `vec3` for colors, locations, directions, offsets, whatever. Some people don’t like this because it doesn’t prevent you from doing something silly, like adding a color to a location. They have a good point, but we’re going to always take the “less code” route when not obviously wrong. In spite of this, we do declare two aliases for `vec3`: `point3` and `color`. Since these two types are just aliases for `vec3`, you won't get warnings if you pass a `color` to a function expecting a `point3`, for example. We use them only to clarify intent and use.

几乎所有的图形程序都使用类似的类来储存几何向量和颜色。在许多程序中这些向量是四维的(对于位置或者几何向量来说是三维的齐次拓展, 对于颜色来说是RGB加透明通道)。对我们现在这个程序来说, 三维就足够了。我们用一个`vec3`类来储存所有的颜色, 位置, 方向, 位置偏移, 或者别的什么东西。一些人可能不太喜欢这样做, 因为全都用一个类, 没有限制, 写代码的时候难免会犯二, 比如你把颜色和位置加在一起。他们的想法挺好的, 但是我们想在避免明显错误的同时让代码量尽量的精简。所以这里就先一个类吧。【译注: 之后有添加新的color类】



#### 变量和函数

> Here’s the top part of my `vec3` class:

下面是我的`vec3`的头文件:

```c++
#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {
    public:
        vec3() : e{0,0,0} {}
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        vec3& operator+=(const vec3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        vec3& operator*=(const double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3& operator/=(const double t) {
            return *this *= 1/t;
        }

        double length() const {
            return sqrt(length_squared());
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

    public:
        double e[3];
};

// Type aliases for vec3
using point3 = vec3;   // 3D point
using color = vec3;    // RGB color

#endif
```



> We use `double` here, but some ray tracers use `float`. Either one is fine — follow your own tastes.

我们使用双精度浮点`double`, 但是有些光线追踪器使用单精度浮点`float`。这里其实都行, 你喜欢哪个就用那个。



#### vec3实用函数

> The second part of the header file contains vector utility functions:

头文件的第二部分包括一些向量操作工具函数:

```c++
// vec3 Utility Functions

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}
```





### 光线, 简单摄像机, 以及背景



> The one thing that all ray tracers have is a ray class and a computation of what color is seen along a ray. Let’s think of a ray as a function **P**(𝑡)=**A**+𝑡**b**. Here **P** is a 3D position along a line in 3D. **A** is the ray origin and **b** is the ray direction. The ray parameter 𝑡t is a real number (`double` in the code). Plug in a different 𝑡t and **P**(𝑡) moves the point along the ray. Add in negative 𝑡t values and you can go anywhere on the 3D line. For positive 𝑡t, you get only the parts in front of **A**, and this is what is often called a half-line or ray.



所有的光线追踪器都有个一个ray类, 我们假定光线的公式为**P**(𝑡)=**A**+𝑡**b**。这里的**P**是三维射线上的一个点。**A**是射线的原点, **b**是射线的方向。类中的变量**𝑡**是一个实数(代码中为`double`类型)。**P**(**𝑡**)接受任意的𝑡做为变量, 返回射线上的对应点。如果允许**𝑡**取负值你可以得到整条直线。对于一个正数**𝑡**, 你只能得到原点前部分**A**, 这常常被称为半条直线, 或者说射线。



![](https://cdn.jsdelivr.net/gh/Yousazoe/picgo-repo/img/fig-1.02-lerp.jpg)



> The function **P**(𝑡) in more verbose code form I call `ray::at(t)`:

我在代码中使用复杂命名, 将函数**P**(𝑡)扩写为`ray::at(t)`：

```c++
#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    public:
        ray() {}
        ray(const vec3& origin, const vec3& direction)
            : orig(origin), dir(direction)
        {}

        vec3 origin() const    { return orig; }
        vec3 direction() const { return dir; }

        vec3 at(double t) const {
            return orig + t*dir;
        }

    public:
        vec3 orig;
        vec3 dir;
};

#endif
```





> Now we are ready to turn the corner and make a ray tracer. At the core, the ray tracer sends rays through pixels and computes the color seen in the direction of those rays. The involved steps are (1) calculate the ray from the eye to the pixel, (2) determine which objects the ray intersects, and (3) compute a color for that intersection point. When first developing a ray tracer, I always do a simple camera for getting the code up and running. I also make a simple `ray_color(ray)` function that returns the color of the background (a simple gradient).



现在我们再拐回来做我们的光线追踪器。光线追踪器的核心是从像素发射射线, 并计算这些射线得到的颜色。这包括如下的步骤: (1)将射线从视点转化为像素坐标 (2)计算光线是否与场景中的物体相交 (3)如果有, 计算交点的颜色。在做光线追踪器的初期, 我会先弄个简单摄像机让代码能跑起来。我也会编写一个简单的`color(ray)`函数来返回背景颜色值(一个简单的渐变色)。



> I’ve often gotten into trouble using square images for debugging because I transpose 𝑥x and 𝑦y too often, so I’ll use a non-square image. For now we'll use a 16:9 aspect ratio, since that's so common.



在使用正方形的图像Debug时我时常会遇到问题, 因为我老是把x和y弄反。所以我坚持使用16:9这样长宽不等的图像。



> In addition to setting up the pixel dimensions for the rendered image, we also need to set up a virtual viewport through which to pass our scene rays. For the standard square pixel spacing, the viewport's aspect ratio should be the same as our rendered image. We'll just pick a viewport two units in height. We'll also set the distance between the projection plane and the projection point to be one unit. This is referred to as the “focal length”, not to be confused with “focus distance”, which we'll present later.



> I’ll put the “eye” (or camera center if you think of a camera) at (0,0,0)(0,0,0). I will have the y-axis go up, and the x-axis to the right. In order to respect the convention of a right handed coordinate system, into the screen is the negative z-axis. I will traverse the screen from the upper left hand corner, and use two offset vectors along the screen sides to move the ray endpoint across the screen. Note that I do not make the ray direction a unit length vector because I think not doing that makes for simpler and slightly faster code.



我会把视点(或者说摄像机, 如果你认为它是个摄像机的话)放在(0,0,0)(0,0,0)。这里y轴向上, x轴向右, 为了准守使用左手系的规范, 摄像机看向的方向为z轴的负方向。我会把发出射线的原点从图像的左下角开始沿着xy方向做增量直至遍历全图。注意我这里并没有将射线的向量设置为单位向量, 因为我认为这样代码会更加简单快捷。

![](https://tva1.sinaimg.cn/large/008i3skNgy1gqb0up1aq5j30ww0by752.jpg)





> Below in code, the ray `r` goes to approximately the pixel centers (I won’t worry about exactness for now because we’ll add antialiasing later):



下面是代码, 射线r现在只是近似的从各个像素的中心射出(现在不必担心精度问题, 因为我们一会儿就会加入抗锯齿):

```diff
#include "vec3.h"

#include <iostream>

int main() {
    const int image_width = 200;
    const int image_height = 100;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
+            vec3 color(double(i)/image_width, double(j)/image_height, 0.2);
+            color.write_color(std::cout);
        }
    }

    std::cerr << "\nDone.\n";
}
```



> The `ray_color(ray)` function linearly blends white and blue depending on the height of the 𝑦 coordinate *after* scaling the ray direction to unit length (so $−1.0<𝑦<1.0$). Because we're looking at the 𝑦 height after normalizing the vector, you'll notice a horizontal gradient to the color in addition to the vertical gradient.
>
> 
>
> I then did a standard graphics trick of scaling that to $0.0≤𝑡≤1.0$. When $𝑡=1.0$ I want blue. When $𝑡=0.0$ I want white. In between, I want a blend. This forms a “linear blend”, or “linear interpolation”, or “lerp” for short, between two things. A lerp is always of the form



`ray_color(ray)`函数根据y值将蓝白做了个线性差值的混合, 我们这里把射线做了个单位化, 以保证y的取值范围($−1.0<y<1.0$)。因为我们使用y轴做渐变, 所以你可以看到这个蓝白渐变也是竖直的。

我接下来使用了一个标准的小技巧将y的范围从$−1.0≤y≤1.0$映射到了$0≤y≤1.0$。这样$t=1.0$时就是蓝色, 而$t=0.0$时就是白色。在蓝白之间我想要一个混合效果(blend)。现在我们采用的是线性混合(linear blend)或者说线性插值(liner interpolation)。或者简称其为lerp。一个lerp一般来说会是下面的形式:
$$
blendedValue=(1−t)⋅startValue+t⋅endValue
$$


> with 𝑡 going from zero to one. In our case this produces:

当$t$从0到1, 我们会渲染出这样的图像:

![](https://tva1.sinaimg.cn/large/008i3skNgy1gqb0ywiam4j30b40690sm.jpg)



### 加入球体

> Let’s add a single object to our ray tracer. People often use spheres in ray tracers because calculating whether a ray hits a sphere is pretty straightforward.

让我们为我们的光线追踪器加入一个物体吧!人们通常使用的球体, 因为计算射线是否与球体相交是十分简洁明了的。



> Recall that the equation for a sphere centered at the origin of radius 𝑅R is $x^2+y^2+z^2=R^2$. Put another way, if a given point $(𝑥,𝑦,𝑧)$ is on the sphere, then $x^2+y^2+z^2=R^2$. If the given point (𝑥,𝑦,𝑧)(x,y,z) is *inside* the sphere, then $x^2+y^2+z^2<R^2$, and if a given point$ (𝑥,𝑦,𝑧)$ is *outside* the sphere, then $x^2+y^2+z^2>R^2$.
>
> It gets uglier if the sphere center is at (𝐶𝑥,𝐶𝑦,𝐶𝑧):

回想一下我们中学时期学过的球体表面方程, 对于一个半径为r的球体来说, 有方程$x^2+y^2+z^2=R^2$, 其中$(x,y,z)$是球面上的点。如果我们想要表示点$(x,y,z)$在球体的内部, 那便有方程$x^2+y^2+z^2<R^2$, 类似的, 如果要表示球体外部的点, 则有$x^2+y^2+z^2>R^2$。

如果球体的球心在$(c_x,c_y,c_z)$, 那么这个式子就会变得丑陋一些:
$$
(x−c_x)2+(y−c_y)^2+(z−c_z)^2=R^2
$$


在图形学中, 你总希望你方程里面所有东西都是用向量表达的, 这样我们就能用`vec3`这个类来存储所有的这些xyz相关的东西了。你也许会意识到, 对于到球面上的点$P=(x,y,z)$到球心$c=(c_x,c_y,c_z)$的距离可以使用向量表示为$(p−c)$, 于是就有
$$
(p−c)⋅(p−c)=(x−c_x)2+(y−c_y)2+(z−c_z)2
$$


> So the equation of the sphere in vector form is:

于是我们就能得到球面方程的向量形式:
$$
(p−c)⋅(p−c)=R^2
$$


> We can read this as “any point **𝐏** that satisfies this equation is on the sphere”. We want to know if our ray $P(t)=A+tb$ ever hits the sphere anywhere. If it does hit the sphere, there is some 𝑡t for which $P(t) $satisfies the sphere equation. So we are looking for any 𝑡t where this is true:

我们可以将其解读为”满足方程上述方程的任意一点$p$一定位于球面上”。我们还要知道射线$p(t)=a+t \vec b$是否与球体相交。如果说它相交了, 那么肯定有一个$t$使直线上的点$p(t)$满足球面方程。所以我们先来计算满足条件的任意$t$值:
$$
(p(t)−c)⋅(p(t)−c)=R^2
$$


> or expanding the full form of the ray $P(t)$:

或者将$p(t)$展开为射线方程:
$$
(a+t \vec b−c)⋅(a+t \vec b−c)=R^2
$$


> The rules of vector algebra are all that we would want here. If we expand that equation and move all the terms to the left hand side we get:

好啦, 我们需要的代数部分就到这里。现在我们来展开表达式并移项, 得:
$$
t^2 \vec b⋅\vec b+2t \vec b⋅\vec{(a−c)}+ \vec{(a−c)}⋅\vec {(a−c)}−R^2=0
$$


> The vectors and 𝑟r in that equation are all constant and known. The unknown is 𝑡, and the equation is a quadratic, like you probably saw in your high school math class. You can solve for 𝑡t and there is a square root part that is either positive (meaning two real solutions), negative (meaning no real solutions), or zero (meaning one real solution). In graphics, the algebra almost always relates very directly to the geometry. What we have is:

方程中的向量和半径R都是已知的常量, 唯一的未知数就是t, 并且这个等式是关于t的一个一元二次方程, 就像你在高中数学课上【？？？】学到的那样。你可以用求根公式来判别交点个数, 为正则2个交点, 为负则1个交点, 为0则没有交点。在图形学中, 代数与几何往往密切相关, 你看图:



![](https://tva1.sinaimg.cn/large/008i3skNgy1gqb12l4m1vj30ig0cb3yw.jpg)



> If we take that math and hard-code it into our program, we can test it by coloring red any pixel that hits a small sphere we place at −1 on the z-axis:

如果我们使用代码来求解, 并使用红色来表示射线击中我们放在$(0,0,-1)$的小球:

```diff
bool hit_sphere(const vec3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant > 0);
}

+vec3 ray_color(const ray& r) {
+    if (hit_sphere(vec3(0,0,-1), 0.5, r))
+        return vec3(1, 0, 0);
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}
```



我们会得到:

![](https://tva1.sinaimg.cn/large/008i3skNgy1gqb1d0g7fuj30b40690sm.jpg)

现在我们啥都缺: 例如光照, 反射, 加入更多的物体, 但是我们离成功又近了一步!现在你要注意我们其实求的是直线与球相交的解, $t<0$的那些情况也计算进去了, 而我们只想要直线中一段射线的解。如果你将你的球心设置在$(0,0,1)$你会得到完全相同的结果。这不是一个特性(feature)!【吐槽: 直接说it’s a bug嘛】我们会在接下来的章节修复这个bug。



### 面法线与复数物体

> First, let’s get ourselves a surface normal so we can shade. This is a vector that is perpendicular to the surface at the point of intersection. There are two design decisions to make for normals. The first is whether these normals are unit length. That is convenient for shading so I will say yes, but I won’t enforce that in the code. This could allow subtle bugs, so be aware this is personal preference as are most design decisions like that. For a sphere, the outward normal is in the direction of the hit point minus the center:



为了来给球体着色, 首先我们来定义一下面法线。面法线应该是一种垂直于交点所在平面的三维向量。关于面法线我们存在两个设计抉择。首先是是否将其设计为单位向量, 这样对于着色器来说, 所以我会说”yes!”但是我并没有在代码里这么做, 这部分差异可能会导致一些潜在的bug。所以记住, 这个是个人喜好, 大多数的人喜好使用单位法线。对于球体来说, 朝外的法线是直线与球的交点减去球心:

![](https://cdn.jsdelivr.net/gh/Yousazoe/picgo-repo/img/fig-1.05-sphere-normal.jpg)



> On the earth, this implies that the vector from the earth’s center to you points straight up. Let’s throw that into the code now, and shade it. We don’t have any lights or anything yet, so let’s just visualize the normals with a color map. A common trick used for visualizing normals (because it’s easy and somewhat intuitive to assume **𝐧** is a unit length vector — so each component is between −1 and 1) is to map each component to the interval from 0 to 1, and then map x/y/z to r/g/b. For the normal, we need the hit point, not just whether we hit or not. We only have one sphere in the scene, and it's directly in front of the camera, so we won't worry about negative values of 𝑡t yet. We'll just assume the closest hit point (smallest 𝑡t). These changes in the code let us compute and visualize **𝐧**:



说到底, 其实就是从球心到交点再向外延伸的那个方向。让我们把这部分转变成代码并开始着色。我们暂时还没有光源这样的东西, 所以让我们直接将法线值作为颜色输出吧。对于法线可视化来说, 我们常常将xyz分量的值先映射到0到1的范围(假定`vecN`是一个单位向量, 它的取值范围是-1到1的),再把它赋值给rgb。对于法线来说, 光能判断射线是否与球体相交是不够的, 我们还需求出交点的坐标。在有两个交点的情况下, 我们选取最近的交点smallest(t)。计算与可视化球的法向量的代码如下:

```diff
+double hit_sphere(const vec3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
+    if (discriminant < 0) {
+        return -1.0;
+    } else {
+        return (-b - sqrt(discriminant) ) / (2.0*a);
+    }
}

vec3 ray_color(const ray& r) {
+    auto t = hit_sphere(vec3(0,0,-1), 0.5, r);
+    if (t > 0.0) {
+        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
+        return 0.5*vec3(N.x()+1, N.y()+1, N.z()+1);
+    }
    vec3 unit_direction = unit_vector(r.direction());
+    t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}
```



这会得到下面的结果:

![](https://cdn.jsdelivr.net/gh/Yousazoe/picgo-repo/img/img-1.04-normals-sphere.png)



还有一种基于计算过程对代码的简化，我也写出来供参考，但这个简化效率提升不多，所以代码保留之前好理解的。

> Let’s revisit the ray-sphere equation:


我们再来回顾上面的直线方程:

```c++
vec3 oc = r.origin() - center;
auto a = dot(r.direction(), r.direction());
auto b = 2.0 * dot(oc, r.direction());
auto c = dot(oc, oc) - radius*radius;
auto discriminant = b*b - 4*a*c;
```



> First, recall that a vector dotted with itself is equal to the squared length of that vector.
>
> Second, notice how the equation for `b` has a factor of two in it. Consider what happens to the quadratic equation if 𝑏=2ℎ:

首先, 回想一下一个向量与自己的点积就是它的长度的平方(都是$x^2+y^2+z^2$)

其次, 注意其实我们的`b`有一个系数2, 我们设`b=2h`, 有:

$\frac{-b +/- \sqrt{b^2-4ac}}{2a} = \frac{-2h +/- \sqrt{(2h)^2-4ac}}{2a} = \frac{-h +/- \sqrt{h^2-ac}}{a}$



> Using these observations, we can now simplify the sphere-intersection code to this:

所以射线与球体求交的代码其实可以简化成下面这样:

```diff
vec3 oc = r.origin() - center;
-auto a = dot(r.direction(), r.direction());
-auto b = 2.0 * dot(oc, r.direction());
-auto c = dot(oc, oc) - radius*radius;
-auto discriminant = b*b - 4*a*c;
+auto a = r.direction().length_squared();
+auto half_b = dot(oc, r.direction());
+auto c = oc.length_squared() - radius*radius;
+auto discriminant = half_b*half_b - a*c;

if (discriminant < 0) {
    return -1.0;
} else {
-   return (-b - sqrt(discriminant) ) / (2.0*a);
+   return (-half_b - sqrt(discriminant) ) / a;
}
```



> Now, how about several spheres? While it is tempting to have an array of spheres, a very clean solution is the make an “abstract class” for anything a ray might hit, and make both a sphere and a list of spheres just something you can hit. What that class should be called is something of a quandary — calling it an “object” would be good if not for “object oriented” programming. “Surface” is often used, with the weakness being maybe we will want volumes. “hittable” emphasizes the member function that unites them. I don’t love any of these, but I will go with “hittable”.

好啦, 那么怎么在场景中渲染不止一个球呢? 很直接的我们想到使用一个sphere数组, 这里有个很简洁的好方法: 使用一个抽象类, 任何可能与光线求交的东西实现时都继承这个类, 并且让球以及球列表也都继承这个类。我们该给这个类起个什么样的名字呢? 叫它`object`好像不错但现在我们使用面向对象编程(oop)。`suface`是时常被翻牌, 但是如果我们想要体积体(volumes)的话就不太适合了。`hittable`又过于强调了自己的成员函数`hit`。所以我哪个都不喜欢, 但是总得给它个名字的嘛, 那我就叫它`hittable`。



> This `hittable` abstract class will have a hit function that takes in a ray. Most ray tracers have found it convenient to add a valid interval for hits 𝑡𝑚𝑖𝑛tmin to 𝑡𝑚𝑎𝑥tmax, so the hit only “counts” if $𝑡_{𝑚𝑖𝑛}<𝑡<𝑡_{𝑚𝑎𝑥}$. For the initial rays this is positive 𝑡t, but as we will see, it can help some details in the code to have an interval $𝑡_{𝑚𝑖𝑛}$ to $𝑡_{𝑚𝑎𝑥}$. One design question is whether to do things like compute the normal if we hit something. We might end up hitting something closer as we do our search, and we will only need the normal of the closest thing. I will go with the simple solution and compute a bundle of stuff I will store in some structure. Here’s the abstract class:

`hittable`类理应有个接受射线为参数的函数, 许多光线追踪器为了便利, 加入了一个区间$t_{min}<t<t_{max}$来判断相交是否有效。对于一开始的光线来说, 这个t值总是正的, 但加入这部分对代码实现的一些细节有着不错的帮助。现在有个设计上的问题:我们是否在每次计算求交的时候都要去计算法相?但其实我们只需要计算离射线原点最近的那个交点的法相就行了, 后面的东西会被遮挡。接下来我会给出我的代码, 并将一些计算的结果存在一个结构体里, 来看, 这就是那个抽象类:

```c++
#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct hit_record {
    vec3 p;
    vec3 normal;
    double t;
};

class hittable {
    public:
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif
```



> And here’s the sphere:

```c++
#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere: public hittable {
    public:
        sphere() {}
        sphere(vec3 cen, double r) : center(cen), radius(r) {};

        virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const;

    public:
        vec3 center;
        double radius;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = half_b*half_b - a*c;

    if (discriminant > 0) {
        auto root = sqrt(discriminant);
        auto temp = (-half_b - root)/a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        temp = (-half_b + root) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }
    return false;
}


#endif
```



> The second design decision for normals is whether they should always point out. At present, the normal found will always be in the direction of the center to the intersection point (the normal points out). If the ray intersects the sphere from the outside, the normal points against the ray. If the ray intersects the sphere from the inside, the normal (which always points out) points with the ray. Alternatively, we can have the normal always point against the ray. If the ray is outside the sphere, the normal will point outward, but if the ray is inside the sphere, the normal will point inward.



好了, 让我们来谈谈第二个关于面法相设计上的问题吧， 那就是面法相的朝向问题。对于现在来说, 如果光线从球体外部击中球体, 那么法相也是朝外的, 与射线的方向相反(不是数学意义上的严格相反, 只是大致逆着)。如果光线从内部射向球面时, 此时的面法相依然朝外, 与射线方向相同。相对的, 我们也可以总是让法相向量与射线方向相反, 即射线从外部射向球面, 法向量朝外, 射线从内部射向球面, 法向量向着球心。

![](https://cdn.jsdelivr.net/gh/Yousazoe/picgo-repo/img/fig-1.06-normal-sides.jpg)



> We need to choose one of these possibilities because we will eventually want to determine which side of the surface that the ray is coming from. This is important for objects that are rendered differently on each side, like the text on a two-sided sheet of paper, or for objects that have an inside and an outside, like glass balls.

在我们着色前, 我们需要仔细考虑一下采用上面哪种方式, 这对于双面材质来说至关重要。例如一张双面打印的A4纸, 或者玻璃球这样的同时具有内表面和外表面的物体。



> If we decide to have the normals always point out, then we will need to determine which side the ray is on when we color it. We can figure this out by comparing the ray with the normal. If the ray and the normal face in the same direction, the ray is inside the object, if the ray and the normal face in the opposite direction, then the ray is outside the object. This can be determined by taking the dot product of the two vectors, where if their dot is positive, the ray is inside the sphere.

如果我们决定让法相永远朝外, 那在我们就得在射入的时候判断是从表面的哪一侧射入的, 我们可以简单的将光线与法相做点乘来判断。如果法相与光线方向相同, 那就是从内部击中内表面, 如果相反则是从外部击中外表面。【译注: $dot(a,b)=cosθ|a||b|$】

```c++
if (dot(ray_direction, outward_normal) > 0.0) {
    // ray is inside the sphere
    ...
} else {
    // ray is outside the sphere
    ...
}
```



> If we decide to have the normals always point against the ray, we won't be able to use the dot product to determine which side of the surface the ray is on. Instead, we would need to store that information:

如果我们永远让法相与入射方向相反, 我们就不用去用点乘来判断射入面是内侧还是外侧了, 但相对的, 我们需要用一个变量储存摄入面的信息:



```c++
bool front_face;
if (dot(ray_direction, outward_normal) > 0.0) {
    // ray is inside the sphere
    normal = -outward_normal;
    front_face = false;
}
else {
    // ray is outside the sphere
    normal = outward_normal;
    front_face = true;
}
```



> We can set things up so that normals always point “outward” from the surface, or always point against the incident ray. This decision is determined by whether you want to determine the side of the surface at the time of geometry intersection or at the time of coloring. In this book we have more material types than we have geometry types, so we'll go for less work and put the determination at geometry time. This is simply a matter of preference, and you'll see both implementations in the literature.
>
> We add the `front_face` bool to the `hit_record` struct. We'll also add a function to solve this calculation for us.

其实采取哪种策略, 关键在于你想把这部分放在着色阶段还是几何求交的阶段。【译注:反正都要算的, v2.0的时候是在着色阶段判别的, v3.0把它放在了求交阶段】。在本书中我们我们的材质类型会比我们的几何图元类型多, 所以为了有更少的代码量, 我们会在几何部分先判别射入面是内侧还是外侧。这当然也是一种个人喜好。

我们在结构体`hit_record`中加入`front_face`变量, 我们接下来还会弄一些动态模糊相关的事情(Book2 chapter1),所以我还会加入一个时间变量:

```diff
ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct hit_record {
    vec3 p;
    vec3 normal;
+    double t;
+    bool front_face;

+    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class hittable {
    public:
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};
#endif
```



> And then we add the surface side determination to the class:

接下来我们在求交时加入射入面的判别:

```diff
bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = half_b*half_b - a*c;

    if (discriminant > 0) {
        auto root = sqrt(discriminant);
        auto temp = (-half_b - root)/a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
+            vec3 outward_normal = (rec.p - center) / radius;
+            rec.set_face_normal(r, outward_normal);
            return true;
        }
        temp = (-half_b + root) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
+            vec3 outward_normal = (rec.p - center) / radius;
+            rec.set_face_normal(r, outward_normal);
            return true;
        }
    }
    return false;
}
```



我们加入存放物体的列表：

```c++
#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list: public hittable {
    public:
        hittable_list() {}
        hittable_list(shared_ptr<hittable> object) { add(object); }

        void clear() { objects.clear(); }
        void add(shared_ptr<hittable> object) { objects.push_back(object); }

        virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const;

    public:
        std::vector<shared_ptr<hittable>> objects;
};

bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

#endif
```







#### 一些C++的新特性

> The `hittable_list` class code uses two C++ features that may trip you up if you're not normally a C++ programmer: `vector` and `shared_ptr`.

`hittable_list`类使用了两种C++的特性:`vector`和`shared_ptr`, 如果你并不熟悉C++, 你可能会感到有些困惑。



##### shared_ptr

> `shared_ptr<type>` is a pointer to some allocated type, with reference-counting semantics. Every time you assign its value to another shared pointer (usually with a simple assignment), the reference count is incremented. As shared pointers go out of scope (like at the end of a block or function), the reference count is decremented. Once the count goes to zero, the object is deleted.

`shared_ptr<type>`是指向一些已分配内存的类型的指针。每当你将它的值赋值给另一个智能指针时, 物体的引用计数器就会+1。当智能指针离开它所在的生存范围(例如代码块或者函数外), 物体的引用计数器就会-1。一旦引用计数器为0, 即没有任何智能指针指向该物体时, 该物体就会被销毁。



> Typically, a shared pointer is first initialized with a newly-allocated object, something like this:

一般来说, 智能指针首先由一个刚刚新分配好内存的物体来初始化:

```c++
shared_ptr<double> double_ptr = make_shared<double>(0.37);
shared_ptr<vec3>   vec3_ptr   = make_shared<vec3>(1.414214, 2.718281, 1.618034);
shared_ptr<sphere> sphere_ptr = make_shared<sphere>(vec3(0,0,0), 1.0);
```



> `make_shared<thing>(thing_constructor_params ...)` allocates a new instance of type `thing`, using the constructor parameters. It returns a `shared_ptr<thing>`.
>
> Since the type can be automatically deduced by the return type of `make_shared<type>(...)`, the above lines can be more simply expressed using C++'s `auto` type specifier:

`make_shared<thing>(thing_constructor_params ...)`为指定的类型分配一段内存, 使用你指定的构造函数与参数来创建这个类, 并返回一个智能指针`shared_ptr<thing>`

使用C++的`auto`类型关键字, 可以自动推断`make_shared<type>`返回的智能指针类型, 于是我们可以把上面的代码简化为:

```c++
auto double_ptr = make_shared<double>(0.37);
auto vec3_ptr   = make_shared<vec3>(1.414214, 2.718281, 1.618034);
auto sphere_ptr = make_shared<sphere>(vec3(0,0,0), 1.0);
```



> We'll use shared pointers in our code, because it allows multiple geometries to share a common instance (for example, a bunch of spheres that all use the same texture map material), and because it makes memory management automatic and easier to reason about.
>
> `std::shared_ptr` is included with the `<memory>` header.



我们在代码中使用智能指针的目的是为了能让多个几何图元共享一个实例(举个栗子, 一堆不同球体使用同一个纹理材质), 并且这样内存管理比起普通的指针更加的简单方便。

`std::shared_ptr`在头文件`<memory>`中:

```c++
#include <memory>
```





##### vector

> The second C++ feature you may be unfamiliar with is `std::vector`. This is a generic array-like collection of an arbitrary type. Above, we use a collection of pointers to `hittable`. `std::vector` automatically grows as more values are added: `objects.push_back(object)` adds a value to the end of the `std::vector` member variable `objects`.

第二个你可能不太熟悉的C++特性是`std::vector`。这是一个类似数组的结构类型, 可以存储任意指定的类型。在上面的代码中, 我们将hittable类型的智能指针存入`vector`中, 随着`objects.push_back(object)`的调用, `object`被存入`vector`的末尾, 同时`vector`的储存空间会自动增加。



> `std::vector` is included with the `<vector>` header.

`std::vector`在头文件`<vector>`中

```c++
#include <vector>
```



> Finally, the `using` statements in [listing 20](https://raytracing.github.io/books/RayTracingInOneWeekend.html#listing_hittable-list-initial) tell the compiler that we'll be getting `shared_ptr` and `make_shared` from the `std` library, so we don't need to prefex these with `std::` every time we reference them.

最后, 位于`hittable_list.h`文件开头部分的`using`语句告诉编译器, `shared_ptr`与`make_shared`是来自`std`库的。这样我们在使用它们之前就不用每次都加上前缀`std::`。





#### 常用的常数与工具函数

我们需要在头文件中定义一些常用的常数。目前为止我们只需要定义无穷。但是我们先把pi在这里定义好, 之后要用的。对于pi来说并没有什么跨平台的标准定义【译注: 这就是为什么不使用之前版本中`M_PI`宏定义的原因】, 所以我们自己来定义一下。我们在`rtweekend.h`中给出了一些未来常用的常数和函数:

```c++
#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>


// Usings

using std::shared_ptr;
using std::make_shared;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180;
}

inline double ffmin(double a, double b) { return a <= b ? a : b; }
inline double ffmax(double a, double b) { return a >= b ? a : b; }

// Common Headers

#include "ray.h"
#include "vec3.h"

#endif
```



以及这是更新后的main函数:

```diff
#include "rtweekend.h"
#include "hittable_list.h"
#include "sphere.h"
#include <iostream>

vec3 ray_color(const ray& r, const hittable& world) {
+    hit_record rec;
+    if (world.hit(r, 0, infinity, rec)) {
+        return 0.5 * (rec.normal + vec3(1,1,1));
+    }    

     vec3 unit_direction = unit_vector(r.direction());
+    auto t = 0.5*(unit_direction.y() + 1.0);    
     return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main() {    
    const int image_width = 200;    
    const int image_height = 100;    

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";    
    vec3 lower_left_corner(-2.0, -1.0, -1.0);    
    vec3 horizontal(4.0, 0.0, 0.0);    
    vec3 vertical(0.0, 2.0, 0.0);    
    vec3 origin(0.0, 0.0, 0.0);
+    hittable_list world;
+    world.add(make_shared<sphere>(vec3(0,0,-1), 0.5));
+    world.add(make_shared<sphere>(vec3(0,-100.5,-1), 100));    
    
    for (int j = image_height-1; j >= 0; --j) {        
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;        
        for (int i = 0; i < image_width; ++i) {            
            auto u = double(i) / image_width;            
            auto v = double(j) / image_height;            
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
+           vec3 color = ray_color(r, world);            
            color.write_color(std::cout);        
        }    
    }    
    std::cerr << "\nDone.\n";
}
```



这样我们就会得到一张使用法向作为球体颜色值的图片。当你想查看模型的特征细节与瑕疵时, 输出面法向作为颜色值不失为一种很好的方法。