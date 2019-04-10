
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

  public boolean somesoftFaceAntiSpoofing(byte[] imageDate, int[] somesoftFaceBB)
      result = mtcnn.LivingBody(imageDate, somesoftFaceBB);


bool MTCNN::LivingBody(unsigned char *img_YUV, int *faceBB){
//    LOGD("somesoft native enter ");

    AS@#VL#%OF@!FS#@CR#@EEN previewFrame = {0};

    previewFrame.i3@@2He@@ight = 480;
    previewFrame.i@@32@@Wi@@dth = 640;

    previewFrame.pi@@32@@Pit@@ch[0] = previewFrame.i@@32@@Wi@@dth;
    previewFrame.pi@@32@@Pit@@ch[1] = previewFrame.i@@32@@Wi@@dth;

    previewFrame.u32PixelArrayFormat = AS@@VL@@_PA@@F_NV@@21;
    previewFrame.pp@@u8@@Pl@@ane[0] = img_YUV;
    previewFrame.pp@@u8@@Pl@@ane[1] = img_YUV + 640*480;

    AR@@C_FA@@S_Fa@@ceOu@@tput face@@Pa@@ram={0};    ///output from face detetor
    AR@@C_FA@@S_Fa@@ceIn@@put faceIn@@Pa@@ram ={0};  ///input to face an@@ti
    MR@@ES@@UL@@T nRet =AR@@C_FA@@S_De@@tec@@tFa@@ce(h@@Han@@dleL@@iven@@ess,&previewFrame,&face@@Pa@@ram);

    int biggestFaceID = 0;
    if(MOK!= nRet ||face@@Pa@@ram.i@@32@@Fac@@eNum@@ber ==0)
    {
//        LOGD("somesoft native face num %d ", face@@Pa@@ram.i@@32@@Fac@@eNum@@ber);
        if(nRet ==AR@@C_F@@AS@@_ME@@RR_MUL@@TI@@FA@@CE && face@@Pa@@ram.i@@32@@Fac@@eNum@@ber>1)
        {

            for(int i = 1; i < face@@Pa@@ram.i@@32@@Fac@@eNum@@ber; i++) {
                if((face@@Pa@@ram.st@@Fa@@ceRec@@tArr[i].bottom - face@@Pa@@ram.st@@Fa@@ceRec@@tArr[i].top) -
                        (face@@Pa@@ram.st@@Fa@@ceRec@@tArr[biggestFaceID].bottom - face@@Pa@@ram.st@@Fa@@ceRec@@tArr[biggestFaceID].top) > 0)
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

    faceIn@@Pa@@ram.i@@32@@Fac@@eNum@@ber = 1;
    faceIn@@Pa@@ram.i@@32F@@ace@@IDA@@rr[0] = 0;
    faceIn@@Pa@@ram.i3@@2Fac@@eOr@@ien@@tA@@rr[0] = face@@Pa@@ram.i3@@2Fac@@eOr@@ien@@tA@@rr[biggestFaceID];
    MM@@em@@Cpy(&faceIn@@Pa@@ram.st@@Fa@@ceRec@@tArr[0],&face@@Pa@@ram.st@@Fa@@ceRec@@tArr[biggestFaceID],sizeof(MRECT));

    ///the SDK may return the out of range value, if the face is on the margin.
    if(faceIn@@Pa@@ram.st@@Fa@@ceRec@@tArr[0].left < 0 || faceIn@@Pa@@ram.st@@Fa@@ceRec@@tArr[0].top < 0)
        return false;
    else if(faceIn@@Pa@@ram.st@@Fa@@ceRec@@tArr[0].right > previewFrame.i@@32@@Wi@@dth || faceIn@@Pa@@ram.st@@Fa@@ceRec@@tArr[0].bottom > previewFrame.i3@@2He@@ight)
        return false;

    faceBB[0] = faceIn@@Pa@@ram.i3@@2Fac@@eOr@@ien@@tA@@rr[0];
    faceBB[1] = faceIn@@Pa@@ram.st@@Fa@@ceRec@@tArr[0].left;
    faceBB[2] = faceIn@@Pa@@ram.st@@Fa@@ceRec@@tArr[0].right;
    faceBB[3] = faceIn@@Pa@@ram.st@@Fa@@ceRec@@tArr[0].top;
    faceBB[4] = faceIn@@Pa@@ram.st@@Fa@@ceRec@@tArr[0].bottom;

    if(faceBB[1] < 0 || faceBB[3] < 0) return false;
    else if(faceBB[2] > 640 || faceBB[4] > 480) return false;

    AR@@C_F@@AS_@@An@@tis@@poo@@fRe@@sult ani@@tis@@po@@ofResult={0};
    nRet =AR@@C_F@@AS_Pro@@ces@@sFa@@ceA@@nti@@Spo@@@of@@ing(h@@Han@@dleL@@iven@@ess,&previewFrame,&faceIn@@Pa@@ram,&ani@@tis@@po@@ofResult);
    if(nRet !=MOK ||ani@@tis@@po@@ofResult.i@@32@@Fac@@eNum@@ber ==0)
    {
        LOGD("somesoft native face an@@ti spo@@of fail!!!");
        return false;
    }

    for(int i=0;i<ani@@tis@@po@@ofResult.i@@32@@Fac@@eNum@@ber;i++)
    {
        if(ani@@tis@@po@@ofResult.i32@@An@@tispo@@ofR@@esu@@ltArr[i] == AR@@C_F@@AS_S@@TATE@@_NO@@TA@@LI@@VE)
        {
//            LOGD("somesoft native face not ali@@ve!!!");

        }else if(ani@@tis@@po@@ofResult.i32@@An@@tispo@@ofR@@esu@@ltArr[i] == AR@@C_FA@@S_S@@TAT@@E_AL@@IV@@E)
        {
//            LOGD("somesoft native face ali@@ve!!!");
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
