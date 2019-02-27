
# Tengine
Tengine便是一款轻量级模块化高性能的神经网络推理引擎，专门针对Arm嵌入式设备优化。完美支持Arm平台，支持Arm Cortex CPU，Arm Mali GPU，Arm DLA，第三方DSP，堪称兼容“全能王”。

它是由OPEN AI LAB开发的开源。

开发者可以使用Tengine一网打尽主流框架模型和嵌入式操作系统，还能异构调度平台里的各类硬件，充分利用硬件算力。此外，Tengine还提供了常见AI应用算法，包括图像检测，人脸识别，语音识别等。不懂AI没关系，上手就能跑AI应用。Tengine同时还支持各类常见卷积神经网络，包括SqueezeNet，MobileNet，AlexNet，ResNet等，支持层融合、8位量化等优化策略。并且通过调用针对不同CPU微构架优化的HCL库，将Arm CPU的性能充分挖掘出来。

![tengine framwork](https://github.com/frankieGitHub/myAI/blob/master/srcImg/tengine.png)

发布tengine库时跟ncnn的比较，呵呵了
 
## Tengine的“发动机”——HCL计算库
 有人说NCNN是一个为手机端极致优化的高性能神经网络前向计算框架，从设计之初深刻考虑手机端的部署和使用。在过去，NCNN确实是这样的，只是那时候还没有Tengine。
  
现在，HCL计算库作为Tengine的插件，是性能最快的Arm CPU NN计算库，并且支持动态8位量化计算，精度几乎不变，相比于NCNN最快能带来2-3倍的性能提升，内存使用减少为三分之一。



## Tengine + HCL，不同人群的量身定制
Tengine作为AI应用框架，不仅对上层应用提供推理API接口，支持主流模型与格式，还在下层定义硬件接口，适配嵌入式平台各类计算模块，此外支持同时运行多个AI应用算法以及调用多个计算模块计算。因此，Tengine的面世对AI开源生态具有里程碑的意义。有了Tengine，应用和算法厂商可以摆脱复杂的嵌入式平台适配工作，配合HCL直接挖掘硬件的全部潜能；有了Tengine，芯片厂能够站在Arm 嵌入式AI生态的肩膀上，以最快的速度顺利将芯片推向市场，在边缘AI应用中部署。作为OPEN AI  LAB为边缘AI应用部署开发的两大利器，Tengine + HCL将助力嵌入式人工智能产业加速向前推进，为最终实现万物智能贡献力量。
参考连接：https://www.eefocus.com/mcu-dsp/421293
------

# AID.Face
在以上的基础上，open AI还推出了嵌入式前端人脸识别SDK - AID.Face
![人脸注册和识别流程](https://github.com/frankieGitHub/myAI/blob/master/srcImg/FaceReg.jpg)


在Tengin之上添加算法和流程的SDK如下：
![SDK](https://github.com/frankieGitHub/myAI/blob/master/srcImg/FaceSDK_Tengine.jpg)

参考连接：https://zhuanlan.zhihu.com/p/57744874


