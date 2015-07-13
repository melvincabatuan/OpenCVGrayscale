#include "io_github_melvincabatuan_opencvgrayscale_MainActivity.h"

#include <android/bitmap.h>
#include <stdlib.h>

#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

 

/*
 * Class:     io_github_melvincabatuan_opencvgrayscale_MainActivity
 * Method:    process
 * Signature: (Landroid/graphics/Bitmap;[B)V
 */
JNIEXPORT void JNICALL Java_io_github_melvincabatuan_opencvgrayscale_MainActivity_process
  (JNIEnv * pEnv, jobject pClass, jobject pTarget, jbyteArray pSource){

   AndroidBitmapInfo bitmapInfo;
   uint32_t* bitmapContent;

   if(AndroidBitmap_getInfo(pEnv, pTarget, &bitmapInfo) < 0) abort();
   if(bitmapInfo.format != ANDROID_BITMAP_FORMAT_RGBA_8888) abort();
   if(AndroidBitmap_lockPixels(pEnv, pTarget, (void**)&bitmapContent) < 0) abort();

   /// Access source array data... OK
   jbyte* source = (jbyte*)pEnv->GetPrimitiveArrayCritical(pSource, 0);
   if (source == NULL) abort();

   ///  YUV420sp source --->  cv::Mat
    Mat srcGray(bitmapInfo.height, bitmapInfo.width, CV_8UC1, (unsigned char *)source);
  
   ///  BGRA --->  cv::Mat
    Mat mbgra(bitmapInfo.height, bitmapInfo.width, CV_8UC4, (unsigned char *)bitmapContent);

/***************************************************************************************************/

    /// YUV420spNV21 gray ---> BGRA
    cvtColor(srcGray, mbgra, CV_GRAY2BGRA);

/***************************************************************************************************/

    /// Release Java byte buffer and unlock backing bitmap
    pEnv-> ReleasePrimitiveArrayCritical(pSource,source,0);
   if (AndroidBitmap_unlockPixels(pEnv, pTarget) < 0) abort();
}
