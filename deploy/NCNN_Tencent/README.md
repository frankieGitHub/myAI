


## 代码结构走读

### 使用
使用上比较简单，实例化一个Net，根据这个Net 来create 一个extrator。
紧接着给这个extrator input，然后执行extrator，具体如下：
```
ncnn::Net net;
net.load_param("alexnet.param");
net.load_model("alexnet.bin");
///还有其他两种初始化Net的方法，可以见连接

ncnn::Mat in;// input blob as above
ncnn::Mat out;
ncnn::Extractor ex = net.create_extractor();
ex.set_light_mode(true);
ex.input("data", in);
ex.extract("prob", out);
```
参考：https://github.com/Tencent/ncnn/wiki/ncnn-%E7%BB%84%E4%BB%B6%E4%BD%BF%E7%94%A8%E6%8C%87%E5%8C%97-alexnet


### JAVA APP里传递模型最好是bin传递到JNI，这样才方便OTA升级
```
    private boolean initMobileNetSSD() throws IOException {
        byte[] param = null;
        byte[] bin = null;
        {
            //用io流读取二进制文件，最后存入到byte[]数组中
            InputStream assetsInputStream = mActivity.getAssets().open("mobilenetSSD_baidu40000addFruit.param.bin");// param：  网络结构文件
            int available = assetsInputStream.available();
            param = new byte[available];
            int byteCode = assetsInputStream.read(param);
            assetsInputStream.close();
        }
        {
            //用io流读取二进制文件，最后存入到byte上，转换为int型
            InputStream assetsInputStream = mActivity.getAssets().open("mobilenetSSD_baidu40000addFruit.bin");//bin：   model文件
            int available = assetsInputStream.available();
            bin = new byte[available];
            int byteCode = assetsInputStream.read(bin);
            assetsInputStream.close();
        }

//        Log.i(TAG, "frankie caffe start init bd48000...");

        boolean load_result = mCaffeDetectModel.SSDInit(param, bin);// 再将文件传入java的NDK接口(c++ 代码中的init接口 )
//        Log.i(TAG, "frankie caffe init " + load_result);
        return load_result;
    }

///JNI实现在libAIObjDetCaffe_so里面
```

### extract的调用过程
其中，关键的函数ex.extract的调用过程如下：  
int Extractor::extract(const char* blob_name, Mat& feat)  
    |---net->forward_layer  
            |---if (blob_mats[bottom_blob_index].dims == 0) ///还没有forward的计算，每个blob的dim都应该是0，递归的推图的依据  
            |---forward_layer(blobs[bottom_blob_index].producer, blob_mats, opt);   ///在这里有一个递归调用，往前推到data input  
            |---。。。->递归到data input层  
            |---。。。。。。。。->递归到data input层  
            |---。。。。。。。。。。。。。。->递归到data input层  
            |---。。。。。。。。。。。。。。。。。。->递归到data input层  
            |---。。。。。。。。。。。。。。。。。。。。。。->递归到data input层  
            |---。。。。。。。。。。。。。。。。。。。。。。。。。->递归到data input层  
            |---。。。。。。。。。。。。。。。。。。。。。。。。。。<-逐层调用改层的forward  
            |---。。。。。。。。。。。。。。。。。。。。。。<-逐层调用改层的forward  
            |---。。。。。。。。。。。。。。。。。。<-逐层调用改层的forward  
            |---。。。。。。。。。。。。。。<-  
            |---。。。。。。。。<-  
            |---。。。<-  
            |---layer->forward_inplace(bottom_top_blob, opt);  
这个目录下的net_layer_forward.cpp模拟了ncnn的这个计算过程。

### gpu分支
使用vulkan版本（NCNN废弃opecl分支）  
https://github.com/Tencent/ncnn/wiki/vulkan-notes  

https://github.com/Tencent/ncnn/compare/opencl  
可以看看opencl分支的修改内容  

ncnn的Android要使用vulkan编译环境为：  
ndk-r18b, sdk : android-24  


