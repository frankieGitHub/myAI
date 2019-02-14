test

# NNAPI 介绍
google在android8.1的源码中放入了NNAPI的框架代码，位置可以参考：http://androidxref.com/8.1.0_r33/xref/frameworks/ml/nn/
android9.0源码又在NNAPI之上放置了tensorflow lite（以下简称tflite），对用户屏蔽了NNAPI。
用户可以看到tflite提供的JAVA API和C++ API。
整体软件框架如下：

![tflite + NNAPI + vendor accelerate](https://github.com/frankieGitHub/myAI/srcImg/AndroidNNAPI.png)
