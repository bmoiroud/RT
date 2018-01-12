// Copyright 2009-2015 Intel Corporation.
//
// The source code, information and material ("Material") contained herein is 
// owned by Intel Corporation or its suppliers or licensors, and title to such 
// Material remains with Intel Corporation or its suppliers or licensors. 
// The Material contains proprietary information of Intel or its suppliers and 
// licensors. The Material is protected by worldwide copyright laws and treaty 
// provisions. No part of the Material may be used, copied, reproduced, modified, 
// published, uploaded, posted, transmitted, distributed or disclosed in any way 
// without Intel's prior express written permission. No license under any patent, 
// copyright or other intellectual property rights in the Material is granted to 
// or conferred upon you, either expressly, by implication, inducement, estoppel 
// or otherwise. Any license under such intellectual property rights must be 
// express and approved by Intel in writing.
//
// *OpenCL(TM) - OpenCL and the OpenCL logo are trademarks of Apple Inc. used by 
// permission by Khronos.
//
// *Third Party trademarks are the property of their respective owners.
//
// Intel and the Intel logo are trademarks of Intel Corporation in the U.S. and/or 
// other countries.
//
// Unless otherwise agreed by Intel in writing, you may not remove or alter this 
// notice or any other notice embedded in Materials by Intel or Intel's suppliers 
// or licensors in any way.




#include "CL/cl.h"
#include "basic.hpp"


#pragma once


#define OCL_ABORT_ON_ERR(x)\
{\
    cl_int __err = x;\
    if( __err != CL_SUCCESS )\
{\
    printf("OCL: ERROR: %s\n\
AT: %s(%i)\n\
IN: %s\n\n",opencl_error_to_str(__err),__FILE__,__LINE__,__FUNCTION__);\
    abort();\
}\
}

#define OCL_RETURN_ON_ERR(x)\
{\
    cl_int __err = x;\
    if( __err != CL_SUCCESS )\
{\
    printf("OCL: ERROR: %s\n\
AT: %s(%i)\n\
IN: %s\n\n",opencl_error_to_str(__err),__FILE__,__LINE__,__FUNCTION__);\
    return __err;\
}\
}

union cl_types
{
    cl_mem mem_ptr;
    cl_sampler sampler_val;

    cl_char c_val;
    cl_char2 c2_val;
    cl_char3 c3_val;
    cl_char4 c4_val;
    cl_char8 c8_val;
    cl_char16 c16_val;
    cl_uchar uc_val;
    cl_uchar2 uc2_val;
    cl_uchar3 uc3_val;
    cl_uchar4 uc4_val;
    cl_uchar8 uc8_val;
    cl_uchar16 uc16_val;
    cl_short s_val;
    cl_short2 s2_val;
    cl_short3 s3_val;
    cl_short4 s4_val;
    cl_short8 s8_val;
    cl_short16 s16_val;
    cl_ushort us_val;
    cl_ushort2 us2_val;
    cl_ushort3 us3_val;
    cl_ushort4 us4_val;
    cl_ushort8 us8_val;
    cl_ushort16 us16_val;
    cl_int i_val;
    cl_int2 i2_val;
    cl_int3 i3_val;
    cl_int4 i4_val;
    cl_int8 i8_val;
    cl_int16 i16_val;
    cl_uint ui_val;
    cl_uint2 ui2_val;
    cl_uint3 ui3_val;
    cl_uint4 ui4_val;
    cl_uint8 ui8_val;
    cl_uint16 ui16_val;
    cl_long l_val;
    cl_long2 l2_val;
    cl_long3 l3_val;
    cl_long4 l4_val;
    cl_long8 l8_val;
    cl_long16 l16_val;
    cl_ulong ul_val;
    cl_ulong2 ul2_val;
    cl_ulong3 ul3_val;
    cl_ulong4 ul4_val;
    cl_ulong8 ul8_val;
    cl_ulong16 ul16_val;
    cl_half h_val;
    cl_float f_val;
    cl_float2 f2_val;
    cl_float4 f3_val;
    cl_float4 f4_val;
    cl_float8 f8_val;
    cl_float16 f16_val;
    cl_double d_val;
    cl_double2 d2_val;
    cl_double3 d3_val;
    cl_double4 d4_val;
    cl_double8 d8_val;
    cl_double16 d16_val;
};


void rand_clfloatn(void* out, size_t type_size, float max);
void line_clfloatn(void* out, float frand, size_t type_size);

cl_mem createRandomFloatVecBuffer(    cl_context* context,
                                  cl_mem_flags flags,
                                  size_t atomic_size,
                                  cl_uint num,
                                  cl_int *errcode_ret,
                                  float randmax = 1.0f);


cl_int fillRandomFloatVecBuffer(    cl_command_queue* cmdqueue,
                                cl_mem* buffer,
                                size_t atomic_size,
                                cl_uint num,
                                cl_event *ev = NULL,
                                float randmax = 1.0f );


#ifdef __linux__
char *ReadSources(const char *fileName);
#else
char *ReadSources(const wchar_t *fileName);
#endif

cl_platform_id GetIntelOCLPlatform();

void BuildFailLog( cl_program program, cl_device_id device_id );

//Bitmap file headers and utilities
#pragma pack (push)
#pragma pack(1)
typedef struct  {
        unsigned short    bfType;
        unsigned int   bfSize;
        unsigned short    bfReserved1;
        unsigned short    bfReserved2;
        unsigned int   bfOffBits;
} BITMAPFILEHEADER_OWN;


typedef struct  {
        unsigned int      biSize;
        int       biWidth;
        int       biHeight;
        unsigned short       biPlanes;
        unsigned short       biBitCount;
        unsigned int      biCompression;
        unsigned int      biSizeImage;
        int       biXPelsPerMeter;
        int       biYPelsPerMeter;
        unsigned int      biClrUsed;
        unsigned int      biClrImportant;
}  BITMAPINFOHEADER_OWN;
#pragma pack(pop)

bool SaveImageAsBMP ( unsigned int* ptr, int width, int height, const char* fileName);
bool SaveImageAsBMP_32FC4(cl_float* p_buf, cl_float scale, cl_uint array_width, cl_uint array_height, const char* p_file_name);
bool SaveImageAsBMP_32FC4_Pitch(cl_float* p_buf, cl_float scale, cl_uint array_width, cl_uint array_height, const char* p_file_name, cl_uint array_pitch, bool convert_RGB_to_sRGB);


