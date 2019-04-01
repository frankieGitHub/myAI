export ANDROID_NDK_ROOT=/home/coolpad/Android/NDK/android-ndk-r17
export SNPE_ROOT=/home/coolpad/AI/AI_framwork/snpe-1.23.1/snpe-1.23.1.245
export CAFFE_DIR=/home/coolpad/AI/CameraScene/caffe
export CAFFE_HOME=/home/coolpad/AI/CameraScene/caffe

source bin/dependencies.sh
source bin/check_python_depends.sh

source bin/envsetup.sh -c $CAFFE_DIR

#snpe-caffe-to-dlc --caffe_txt $SNPE_ROOT/models/mobilenetSSD/no_bn.prototxt --caffe_bin $SNPE_ROOT/models/mobilenetSSD/no_bn.caffemodel --dlc $SNPE_ROOT/models/mobilenetSSD/mobilenetSSD.dlc

#snpe-dlc-quantize --input_dlc $SNPE_ROOT/models/mobilenetSSD/mobilenetSSD.dlc --input_list /home/coolpad/AI/AI_framwork/snpe-1.24/snpe-1.24.0.256/models/mobilenetSSD/file_list.txt --output_dlc $SNPE_ROOT/models/mobilenetSSD/mobilenetSSD_quantized.dlc
