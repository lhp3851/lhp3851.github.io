---
title: Float
date: 2022-04-09 10:38:45
tags: Float
---


## 1. 浮动布局

浮动布局常见的两种情况：圣杯布局与双飞翼布局。

### 1.1 圣杯布局

```html
<div class="container">
  <div class="main">main</div>
  <div class="left">left</div>
  <div class="right">right</div>
</div>
````

```css
.container {
  padding-left: 200px;  /* 预留左侧空间，为.left宽度*/
  padding-right: 300px; /* 预留左侧空间，为.right宽度*/
}
.main {
  float: left;
  width: 100%;
  height: 300px;
  background: #67c23a;
}
.left {
  float: left;
  margin-left: -100%;   /* 移动到左侧，100%是一个父元素宽度，这里也就是.container的宽度 */
  position: relative;   /* 因为.container设置了padding*/
  right: 200px;         /* 所以需要再向左移动自身宽度,left: -200px;也是可以的 */
  width: 200px;
  height: 300px;
  background: #e6a23c;
}
.right {
  float: left;
  margin-right: -300px; /* 移动到右侧，自身宽度*/
  width: 300px;
  height: 300px;
  background: #f56c6c;
}
```

### 1.2 双飞翼布局

```html
<div class="main-wrap">
    <div class="main">main</div>
</div>
<div class="left">left</div>
<div class="right">right</div>
```

```css
.main-wrap {
  float: left;
  width: 100%;
}
.main {
  margin-left: 200px;   /* 预留左侧空间，为.left宽度*/
  margin-right: 300px;  /* 预留左侧空间，为.right宽度*/
  height: 300px;
  background: #67c23a;
}
.left {
  float: left;
  margin-left: -100%;   /* 移动到左侧，100%是一个父元素宽度，这里也就是body的宽度*/
  width: 200px;
  height: 300px;
  background: #e6a23c;
}
.right {
  float: left;
  margin-left: -300px;  /* 移动到右侧，自身宽度*/
  width: 300px;
  height: 300px;
  background: #f56c6c;
}
```

## 2. 盒子坍塌[^CSS盒子塌陷]

盒子坍塌一般都是块元素引起的问题，主要有两类。

* 高度塌陷
* margin 的使用造成

### 2.1 塌陷原因

首先，盒子高度塌陷的大前提是，元素高度由以下两个条件决定：

* 当前元素设置了 height 属性，则元素的高度由 height 决定；
* 如果当前元素没有设置 height ，则元素高度由内部没有脱离文档流的元素的高度之和决定。

由此，可以推出出现盒子高度塌陷的必要条件是：

1. 当前父元素没有设置相应的 height ；
2. 且内部子元素脱离了文档流，导致内部没有元素可以撑起当前父元素

* 2.1 内部子元素使用了浮动导致内部元素脱离了文档流，且脱离文档流的元素无法撑起当前父元素。
* 2.2 内部子元素使用了绝对定位或者固定定位脱离文档流。

### 2.2 margin 塌陷原因

主要是由于 margin 纵向重叠的特性导致：

* 父子盒子元素 margin-top / margin-bottom 重叠（塌陷）。
* 兄弟盒子元素塌陷：盒子的 margin-top 与另一个盒子的 margin-bottom 重叠。

### 2.3  BFC（Block Formatting Context）块级格式环境

BFC是一个CSS的隐含属性，可以为一个元素开启BFC，开启BFC后该元素会变成一个独立的布局区域。元素开启BFC后有以下特点：1、开启BFC的元素不会被浮动元素所覆盖。2、开启BFC元素子元素和父元素外边距不会重叠。3、开启BFC的元素可以包含浮动的子元素。

#### 2.3.1 开启 BFC

开启BFC的方式有四种：

1. 设置元素的浮动。
2. 将元素设置为行内块元素。
3. 将元素的overfloat设置为一个非visible的值（常用方式为元素设置overflow：hidden使其开启BFC）。
4. 使用clear。

### 2.4 解决盒子坍塌[^float高度塌陷]

1. 给每个盒子设定固定的height，直到合适为止，这样的好处是简单方便，兼容性好，适合只改动少量内容不涉及盒子排布的版面。缺点是非自适应，浏览器的窗口大小直接影响用户体验。
2. 给外部的父盒子也添加浮动，让其也脱离标准文档流，这种方法方便，但是对页面的布局不是很友好，不易维护。
3. 触发父元素的 BFC ，例如：给父盒子添加 overflow 属性。但是 overflow:auto; 有可能出现滚动条，影响美观。 overflow:hidden; 可能会带来内容不可见的问题。详见 BFC 部分的总结。
4. 将外层盒子设置为非块结构，设置为inline-block。缺点是有可能影响到文档其他元素的布局。
5. 利用 clear 属性闭合浮动

```html
<!-- 1.清除浮动 -->
   <style>
         .container {
           border: 4px solid brown;
         }
         .wrap {
           border: 2px solid blueviolet;
         }
         .main {
           float: left;
           width: 100px;
           height: 100px;
           background-color: aqua;
         }
         .footer {
           clear: both;
         }
   </style>
   <body>
       <div class="container">
         <div class="wrap">
           <div class="main">main</div>
         </div>
         <div class="footer">footer</div>
       </div>
   </body>

   <!-- 2.闭合浮动 -->
   <style>
         .container {
           border: 4px solid brown;
         }
         .wrap {
           border: 2px solid blueviolet;
         }
         .main {
           float: left;
           width: 100px;
           height: 100px;
           background-color: aqua;
         }
         .clearfix:after {
           content: "."; /*尽量不要为空，一般写一个点，为空可能会造成空隙*/
           height: 0; /*盒子高度为0，看不见*/
           display: block; /*插入伪元素是行内元素，要转化为块级元素*/
           visibility: hidden; /*content有内容，将元素隐藏*/
           clear: both; /* 清除浮动 */
         }
   
         .clearfix {
           *zoom: 1; /*  *只有IE6,7识别，开启hasLayout，用于兼容IE6,7 */
         }
   </style>
   <body>
       <div class="container">
         <div class="wrap clearfix">
           <div class="main">main</div>
         </div>
         <div class="footer">footer</div>
       </div>
   </body>
   
   <!-- 清除浮动只能对当前使用clear:both的元素起作用，而闭合浮动则是消除/闭合浮动元素的影响 -->
```

闭合浮动也可以

```css
.clearfix:before, .clearfix:after {
  content: "";
  display: table;
}
.clearfix:after {
  clear: both;
}
.clearfix {
  *zoom: 1;
}   
```

[^CSS盒子塌陷]:[CSS基础：float应用 / 盒子塌陷](https://zhuanlan.zhihu.com/p/379341482)

[^float高度塌陷]:[float高度塌陷问题原理、优缺点、建议、以及解决的办法](https://blog.csdn.net/mrwu_beita/article/details/109919890)
