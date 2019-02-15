# 自己搭建的3层全连接网络
用于识别MNST手写数据集，没有使用CNN
问题来源：https://www.zhihu.com/question/264693783

首先安装caffe，进入example目录，这个目录有几个caffe例子。
创建两个文件，
1、3FC.prototxt

name: "my3FC"

layer {
    name: "mnist"
    type: "Data"
    transform_param {
        scale: 0.00390625
    }
    data_param {
        source: "mnist_train_lmdb"
        backend: LMDB
        batch_size: 64
    }
    top: "data"
    top: "label"
}

layer {
    name: "fc1"
    type: "InnerProduct"
    bottom: "data"
    top: "fc1"
    inner_product_param {
        num_output: 4096
    }
}

layer {
    name: "fc2"
    type: "InnerProduct"
    bottom: "fc1"
    top: "fc2"
    inner_product_param {
        num_output: 2048
    }
}

layer {
    name: "fc3"
    type: "InnerProduct"
    bottom: "fc2"
    top: "fc3"
    inner_product_param {
        num_output: 10
    }
}

layer {
    name: "accuracy"
    type: "Accuracy"
    bottom: "fc3"
    bottom: "label"
    top: "accuracy"
}
layer {
    name: "loss"
    type: "SoftmaxWithLoss"
    bottom: "fc3"
    bottom: "label"
    top: "loss"
}


2、创建solver文件，如my3FC_solver.prototxt，定义训练参数
net: "examples/mnist/3FC.prototxt"
test_iter: 100
test_interval: 500
base_lr: 0.01
momentum: 0.9
weight_decay: 0.0005
lr_policy: "inv"
gamma: 0.0001
power: 0.75
display: 100
max_iter: 10000
snapshot: 5000
snapshot_prefix: "examples/mnist/myLetnet"
solver_mode: GPU

3、在命令行启动训练：
#!/usr/bin/env sh
set -e

./build/tools/caffe train --solver=examples/mnist/my3FC_solver.prototxt $@


