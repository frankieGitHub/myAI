test

# NNAPI 介绍
google在android8.1的源码中放入了NNAPI的框架代码，位置可以参考：
http://androidxref.com/8.1.0_r33/xref/frameworks/ml/nn/

android9.0源码又在NNAPI之上放置了tensorflow lite（以下简称tflite），对用户屏蔽了NNAPI。
用户可以看到tflite提供的JAVA API和C++ API。
整体软件框架如下：
![tflite + NNAPI + vendor accelerate](https://github.com/frankieGitHub/myAI/blob/master/srcImg/androidNNAPI.jpg)

而在NNAPI框架代码以下，如果有GPU/DSP则会使用，如果只有CPU则会fall back到CPU的实现。
通过HAL层的形式来加载各个vendor（高通或MTK）的具体实现。
具体位置：/system/lib64/vndk-28/android.hardware.neuralnetworks@1.0.so
或/system/lib64/android.hardware.neuralnetworks@1.0.so
没有看到这部分的具体代码:(

总体来看这个NNAPI的设计的好处：
主要有两个分层，在NNAPI以上有tflite或caffe2，在NNAPI以下把硬件加速的事情交给了vendor，各司其职。

# NNAPI的复用
看到这里，你会觉得这个NNAPI只能给tflite使用了？有人给了否定的答案。
网名：大缺弦，发布了个人作品：https://github.com/JDAI-CV/DNNLibrary
这个作品的就是把onnx格式的模型，通过他自己的脚本转化为自己的格式，然后跑到了NNAPI之上。

类似的描述连接：https://blog.csdn.net/zhaizu/article/details/79416625


这里可以看到，如果你的设备有GPU/DSP，那么NNAPI不错的选择（当然，你的选择还有高通SNPE或小米MACE）;
如果只有CPU，那么可以选择腾讯的NCNN库来部署模型。


