
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
