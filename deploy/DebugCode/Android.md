
# Read img from /sdcard to do inference
```


    public static void saveBitmapForDebug(Bitmap bitmap,int index){
        String filename = "test" + "_" + index;
        String wholeFolderPath = fh.ImgSave_PATH + "test";
        new File(wholeFolderPath).mkdirs();
        Log.i(TAG, "bitmap.width = :" + bitmap.getWidth() + "filename = :" + filename);
        fh.saveBitmapToImage(wholeFolderPath + "/", bitmap, filename);
    }

    public static float[] inputBitmapDataforward(Bitmap mBitmap, int[] objNum) {
        if(bitMapIndex++ == 500) bitMapIndex = 0;
        objNum[0] = 0;
//        mBitmap = Bitmap.createScaledBitmap(mBitmap, 300, 300, false);

//        saveBitmapForDebug(mBitmap, bitMapIndex);
//
        String path=Environment.getExternalStorageDirectory()+"/test.jpg";
        String path2=Environment.getExternalStorageDirectory()+"/test2.jpg";
//        Bitmap mBitmap = null;
        File mFile=new File(path);
        File mFile2=new File(path2);

        if (mFile.exists() && mFile2.exists()) {

            if(bitMapIndex%2 == 0) {
                Log.i(TAG, "read test... ");
                mBitmap = BitmapFactory.decodeFile(path);

            }
            else {
                Log.i(TAG, "read test2... ");
                mBitmap = BitmapFactory.decodeFile(path2);
            }

            mBitmap = Bitmap.createScaledBitmap(mBitmap, 300, 300, false);
        }
//        else
//            return null;
//
//            mBitmap = Bitmap.createScaledBitmap(mBitmap, 300, 300, false);
            final FloatTensor tensor = mNeuralNetwork.createFloatTensor(
                    mNeuralNetwork.getInputTensorsShapes().get(mInputLayer));


```

# use arc face 
```
IsFaceAlive = mFaceIdApi.somesoftFaceAntiSpoofing(bytes, somesoftFaceBB);

  public boolean somesoftFaceAntiSpoofing(byte[] imageDate, int[] ArcsoftFaceBB)
      result = mtcnn.LivingBody(imageDate, ArcsoftFaceBB);


bool MTCNN::LivingBody(unsigned char *img_YUV, int *faceBB){
//    LOGD("somesoft native enter ");

    ASVLOFFSCREEN previewFrame = {0};

    previewFrame.i32Height = 480;
    previewFrame.i32Width = 640;

//    previewFrame.pi32Pitch[0] = IMAGE_ALIGN(previewFrame.i32Width, 128);
//    previewFrame.pi32Pitch[1] = IMAGE_ALIGN(previewFrame.i32Height, 32);
    previewFrame.pi32Pitch[0] = previewFrame.i32Width;
    previewFrame.pi32Pitch[1] = previewFrame.i32Width;

//    LOGD("somesoft native pi32Pitch new: %d ", previewFrame.pi32Pitch[0]);
//    previewFrame.pi32Pitch[0] = previewFrame.i32Width;
//    previewFrame.pi32Pitch[1] = previewFrame.i32Width;
//    previewFrame.u32PixelArrayFormat = ASVL_PAF_YUV;
    previewFrame.u32PixelArrayFormat = ASVL_PAF_NV21;
    previewFrame.ppu8Plane[0] = img_YUV;
    previewFrame.ppu8Plane[1] = img_YUV + 640*480;

    ARC_FAS_FaceOutput faceParam={0};    ///output from face detetor
    ARC_FAS_FaceInput faceInParam ={0};  ///input to face anti spoofing
    MRESULT nRet =ARC_FAS_DetectFace(hHandleLiveness,&previewFrame,&faceParam);

    int biggestFaceID = 0;
    if(MOK!= nRet ||faceParam.i32FaceNumber ==0)
    {
//        LOGD("somesoft native face num %d ", faceParam.i32FaceNumber);
        if(nRet ==ARC_FAS_MERR_MULTIFACE && faceParam.i32FaceNumber>1)
        {
            // here, set the first face to do anti-spoofing
            // user can choose the bigger face to do anti-spoofing
//            LOGD("somesoft native multi face...");
//            for(int j = 0; j < faceParam.i32FaceNumber; j++) {
//                LOGD("somesoft native get faceid %d ", faceParam.i32FaceIDArr[j]);
//
//            }

            for(int i = 1; i < faceParam.i32FaceNumber; i++) {
                if((faceParam.stFaceRectArr[i].bottom - faceParam.stFaceRectArr[i].top) -
                        (faceParam.stFaceRectArr[biggestFaceID].bottom - faceParam.stFaceRectArr[biggestFaceID].top) > 0)
                    biggestFaceID = i;
//                LOGD("somesoft native biggest face is ID %d ", biggestFaceID);
            }
        }
        else
        {
            LOGD("somesoft native  DetectFace fail or no faces can be detected!!!");
            return false;
        }
    }
    else
    {
//        LOGD("somesoft native Detect one face!!!");
    }

    faceInParam.i32FaceNumber = 1;
    faceInParam.i32FaceIDArr[0] = 0;
    faceInParam.i32FaceOrientArr[0] = faceParam.i32FaceOrientArr[biggestFaceID];
//    faceInParam.stFaceRectArr[0].top = faceParam.stFaceRectArr[biggestFaceID].top;
//    faceInParam.stFaceRectArr[0].left = faceParam.stFaceRectArr[biggestFaceID].left;
//    faceInParam.stFaceRectArr[0].bottom = faceParam.stFaceRectArr[biggestFaceID].bottom;
//    faceInParam.stFaceRectArr[0].right = faceParam.stFaceRectArr[biggestFaceID].right;
    MMemCpy(&faceInParam.stFaceRectArr[0],&faceParam.stFaceRectArr[biggestFaceID],sizeof(MRECT));

    ///the SDK may return the out of range value, if the face is on the margin.
    if(faceInParam.stFaceRectArr[0].left < 0 || faceInParam.stFaceRectArr[0].top < 0)
        return false;
    else if(faceInParam.stFaceRectArr[0].right > previewFrame.i32Width || faceInParam.stFaceRectArr[0].bottom > previewFrame.i32Height)
        return false;

    faceBB[0] = faceInParam.i32FaceOrientArr[0];
    faceBB[1] = faceInParam.stFaceRectArr[0].left;
    faceBB[2] = faceInParam.stFaceRectArr[0].right;
    faceBB[3] = faceInParam.stFaceRectArr[0].top;
    faceBB[4] = faceInParam.stFaceRectArr[0].bottom;

    if(faceBB[1] < 0 || faceBB[3] < 0) return false;
    else if(faceBB[2] > 640 || faceBB[4] > 480) return false;
//    LOGD("somesoft native choose face orien: %d", faceInParam.i32FaceOrientArr[0]);
//    LOGD("somesoft native choose face top: %d", faceInParam.stFaceRectArr[0].top);
//    LOGD("somesoft native choose face left: %d", faceInParam.stFaceRectArr[0].left);
//    LOGD("somesoft native choose face bottom: %d", faceInParam.stFaceRectArr[0].bottom);
//    LOGD("somesoft native choose face right: %d", faceInParam.stFaceRectArr[0].right);
//    LOGD("somesoft native face width: %d", faceInParam.stFaceRectArr[0].right - faceInParam.stFaceRectArr[0].left);
//    LOGD("somesoft native face heigh: %d", faceInParam.stFaceRectArr[0].bottom - faceInParam.stFaceRectArr[0].top);


    ARC_FAS_AntispoofResult antispoofResult={0};
    nRet =ARC_FAS_ProcessFaceAntiSpoofing(hHandleLiveness,&previewFrame,&faceInParam,&antispoofResult);
//    nRet =ARC_FAS_ProcessFaceAntiSpoofing(hHandleLiveness,&previewFrame,(ARC_FAS_FaceInput *)&faceParam,&antispoofResult);
    if(nRet !=MOK ||antispoofResult.i32FaceNumber ==0)
    {
        LOGD("somesoft native face anti spoof fail!!!");
        return false;
    }

    for(int i=0;i<antispoofResult.i32FaceNumber;i++)
    {
//        string filename = "";
        //char filename[40] = {0};
        if(antispoofResult.i32AntispoofResultArr[i] == ARC_FAS_STATE_NOTALIVE)
        {
//            LOGD("somesoft native face not alive!!!");

        }else if(antispoofResult.i32AntispoofResultArr[i] == ARC_FAS_STATE_ALIVE)
        {
//            LOGD("somesoft native face alive!!!");
            return true;
        }
        else
        {
            LOGD("somesoft native error!!!");
        }
    }

    return false;
}
         
```
