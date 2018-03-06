#include <node_api.h>
#include <stdio.h>
#include <stdint.h>

#include <al.h>
#include <alc.h>

#define NAPI_DEFINE_CONSTANT(target, constant)                           \
  do {                                                                   \
    napi_value v = NULL;                                                 \
    napi_create_int32(env, constant, &v);                                \
    napi_set_named_property(env, target, #constant, v);                  \
  }                                                                      \
  while (0)


#define NAPI_SET_METHOD(target, name, callback)                         \
  do {                                                                  \
    napi_value fn = NULL;                                               \
    napi_create_function(env, NULL, 0, callback, NULL, &fn);            \
    napi_set_named_property(env, target, name, fn);                     \
  }                                                                     \
  while (0)


#define NUM_BUFFERS 4
#define SLEEP_BUFFERING 10
static ALuint alSampleSet[NUM_BUFFERS];

napi_value alcOpenDevice_Callback(napi_env env, napi_callback_info info) {

  ALCdevice* device = alcOpenDevice(NULL);

  napi_value ret;
  napi_create_int64(env, (int64_t) device, &ret);
  return ret;
}

napi_value alGetError_Callback(napi_env env, napi_callback_info info) {

  int err = alGetError();

  napi_value ret;
  napi_create_int32(env, (int32_t) err, &ret);
  return ret;
}

napi_value alcCreateContext_Callback(napi_env env, napi_callback_info info) {

  napi_status status;
  size_t argc = 1;
  napi_value argv[1];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int64_t arg0;
  status = napi_get_value_int64(env, argv[0], &arg0);

  ALCcontext* context = alcCreateContext((ALCdevice*) arg0, NULL);

  napi_value ret;
  napi_create_int64(env, (int64_t) context, &ret);
  return ret;
}

napi_value alcMakeContextCurrent_Callback(napi_env env, napi_callback_info info) {

  napi_status status;
  size_t argc = 1;
  napi_value argv[1];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int64_t arg0;
  status = napi_get_value_int64(env, argv[0], &arg0);

  alcMakeContextCurrent((ALCcontext*)arg0);

  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value alGenSources_Callback(napi_env env, napi_callback_info info) {

  napi_status status;
  size_t argc = 1;
  napi_value argv[1];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int arg0;
  status = napi_get_value_int32(env, argv[0], &arg0);


  unsigned int alSource; // buffer source
  alGenSources(arg0, &alSource);

  napi_value ret;
  napi_create_int32(env, (int32_t) alSource, &ret);
  return ret;
}

napi_value alGenBuffers_Callback(napi_env env, napi_callback_info info) {

  alGenBuffers(4, alSampleSet);

  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}


napi_value alListener3f_Callback(napi_env env, napi_callback_info info) {

  napi_status status;
  size_t argc = 4;
  napi_value argv[4];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int arg0;
  status = napi_get_value_int32(env, argv[0], &arg0);
  double arg1, arg2, arg3;
  status = napi_get_value_double(env, argv[1], &arg1);
  status = napi_get_value_double(env, argv[2], &arg2);
  status = napi_get_value_double(env, argv[3], &arg3);

  alListener3f(arg0, arg1, arg2, arg3);

  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value alSourcePlay_Callback(napi_env env, napi_callback_info info) {

  napi_status status;
  size_t argc = 1;
  napi_value argv[1];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int arg0;
  status = napi_get_value_int32(env, argv[0], &arg0);

  alSourcePlay(arg0);
  
  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value alSourceStop_Callback(napi_env env, napi_callback_info info) {

  napi_status status;
  size_t argc = 1;
  napi_value argv[1];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int arg0;
  status = napi_get_value_int32(env, argv[0], &arg0);

  alSourceStop(arg0);
  
  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value alSourcei_Callback(napi_env env, napi_callback_info info) {

  napi_status status;
  size_t argc = 3;
  napi_value argv[3];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int arg0, arg1, arg2;
  status = napi_get_value_int32(env, argv[0], &arg0);
  status = napi_get_value_int32(env, argv[1], &arg1);
  status = napi_get_value_int32(env, argv[2], &arg2);

  alSourcei(arg0, arg1, arg2);
  
  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value alGetSourcei_Callback(napi_env env, napi_callback_info info) {

  napi_status status;
  size_t argc = 2;
  napi_value argv[2];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int arg0, arg1;
  status = napi_get_value_int32(env, argv[0], &arg0);
  status = napi_get_value_int32(env, argv[1], &arg1);

  int val;
  alGetSourcei(arg0, arg1, &val);
  
  napi_value ret;
  napi_create_int32(env, (int32_t) val, &ret);
  return ret;
}

napi_value alBufferData_Callback(napi_env env, napi_callback_info info) {

  napi_status status;
  size_t argc = 4;
  napi_value argv[4];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int arg0, arg1, arg3;
  status = napi_get_value_int32(env, argv[0], &arg0);
  status = napi_get_value_int32(env, argv[1], &arg1);
  status = napi_get_value_int32(env, argv[3], &arg3);

  uint8_t* data;
  size_t len;
  napi_get_buffer_info(env, argv[2], (void**) &data, &len);

  alBufferData(alSampleSet[arg0], arg1, data, len, arg3);
  
  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value alSourceQueueBuffers_Callback(napi_env env, napi_callback_info info) {

  napi_status status;
  size_t argc = 3;
  napi_value argv[3];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int arg0, arg1, arg2;
  status = napi_get_value_int32(env, argv[0], &arg0);
  status = napi_get_value_int32(env, argv[1], &arg1);
  status = napi_get_value_int32(env, argv[2], &arg2);

  ALuint buffer = 0;
  alSourceQueueBuffers(arg0, arg1, &buffer);
  
  napi_value ret;
  napi_create_int32(env, (int32_t) buffer, &ret);
  return ret;
}

napi_value alSourceQueueBuffersAll_Callback(napi_env env, napi_callback_info info) {

  napi_status status;
  size_t argc = 1;
  napi_value argv[1];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int arg0;
  status = napi_get_value_int32(env, argv[0], &arg0);
 
  alSourceQueueBuffers(arg0, 4, alSampleSet);
  
  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}


napi_value alSourceUnqueueBuffers_Callback(napi_env env, napi_callback_info info) {

  napi_status status;
  size_t argc = 2;
  napi_value argv[2];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int arg0, arg1;
  status = napi_get_value_int32(env, argv[0], &arg0);
  status = napi_get_value_int32(env, argv[1], &arg1);
 
  ALuint buffer = 0;
  alSourceUnqueueBuffers(arg0, arg1, &buffer);
  
  napi_value ret;
  napi_create_int32(env, (int32_t) buffer, &ret);
  return ret;
}


napi_value alFillData_Callback(napi_env env, napi_callback_info info) {

  napi_status status;
  size_t argc = 3;
  napi_value argv[3];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int arg0, arg2;
  status = napi_get_value_int32(env, argv[0], &arg0);
  status = napi_get_value_int32(env, argv[2], &arg2);
  uint8_t* data;
  size_t len;
  napi_get_buffer_info(env, argv[1], (void**) &data, &len);
 
  ALuint buffer = 0;
  alSourceUnqueueBuffers(arg0, 1, &buffer);
  alBufferData(buffer, AL_FORMAT_STEREO16, data, len, arg2);
  alSourceQueueBuffers(arg0, 1, &buffer);
  
  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value alDeleteSources_Callback(napi_env env, napi_callback_info info) {

  napi_status status;
  size_t argc = 2;
  napi_value argv[2];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int arg0, arg1;
  status = napi_get_value_int32(env, argv[0], &arg0);
  status = napi_get_value_int32(env, argv[1], &arg1);
  
  alDeleteSources(arg0, &arg1);
  
  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value alDeleteBuffers_Callback(napi_env env, napi_callback_info info) {

  napi_status status;
  size_t argc = 2;
  napi_value argv[2];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int arg0, arg1;
  status = napi_get_value_int32(env, argv[0], &arg0);
  status = napi_get_value_int32(env, argv[1], &arg1);
  
  alDeleteBuffers(arg0, (const ALuint *)&alSampleSet);
  
  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value alcDestroyContext_Callback(napi_env env, napi_callback_info info) {

  napi_status status;
  size_t argc = 1;
  napi_value argv[1];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int64_t arg0;
  status = napi_get_value_int64(env, argv[0], &arg0);
  
  alcDestroyContext((ALCcontext*) arg0);
  
  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}

napi_value alcCloseDevice_Callback(napi_env env, napi_callback_info info) {

  napi_status status;
  size_t argc = 1;
  napi_value argv[1];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  int64_t arg0;
  status = napi_get_value_int64(env, argv[0], &arg0);
  
  alcCloseDevice((ALCdevice*) arg0);
  
  napi_value ret;
  napi_get_undefined(env, &ret);
  return ret;
}


/////

napi_value Init(napi_env env, napi_value exports) {
  napi_status status;

  NAPI_DEFINE_CONSTANT(exports, AL_LOOPING);
  NAPI_DEFINE_CONSTANT(exports, AL_PLAYING);
  NAPI_DEFINE_CONSTANT(exports, AL_BUFFER);

  NAPI_DEFINE_CONSTANT(exports, AL_NO_ERROR);
  NAPI_DEFINE_CONSTANT(exports, AL_FALSE);

  NAPI_DEFINE_CONSTANT(exports, AL_FORMAT_MONO8);
  NAPI_DEFINE_CONSTANT(exports, AL_FORMAT_MONO16);
  NAPI_DEFINE_CONSTANT(exports, AL_FORMAT_STEREO8);
  NAPI_DEFINE_CONSTANT(exports, AL_FORMAT_STEREO16);
  NAPI_DEFINE_CONSTANT(exports, AL_SOURCE_STATE);
  NAPI_DEFINE_CONSTANT(exports, AL_BUFFERS_PROCESSED);
  NAPI_DEFINE_CONSTANT(exports, AL_BUFFERS_QUEUED);
  

  NAPI_SET_METHOD(exports, "alcOpenDevice", alcOpenDevice_Callback);
  NAPI_SET_METHOD(exports, "alGetError", alGetError_Callback);
  NAPI_SET_METHOD(exports, "alcCreateContext", alcCreateContext_Callback);
  NAPI_SET_METHOD(exports, "alcMakeContextCurrent", alcMakeContextCurrent_Callback);
  NAPI_SET_METHOD(exports, "alGenSources", alGenSources_Callback);
  NAPI_SET_METHOD(exports, "alGenBuffers", alGenBuffers_Callback);
  NAPI_SET_METHOD(exports, "alSourcePlay", alSourcePlay_Callback);
  NAPI_SET_METHOD(exports, "alSourceStop", alSourceStop_Callback);
  NAPI_SET_METHOD(exports, "alSourcei", alSourcei_Callback);
  NAPI_SET_METHOD(exports, "alListener3f", alListener3f_Callback);
  NAPI_SET_METHOD(exports, "alGetSourcei", alGetSourcei_Callback);
  NAPI_SET_METHOD(exports, "alBufferData", alBufferData_Callback);
  NAPI_SET_METHOD(exports, "alSourceQueueBuffers", alSourceQueueBuffers_Callback);
  NAPI_SET_METHOD(exports, "alSourceQueueBuffersAll", alSourceQueueBuffersAll_Callback);
  NAPI_SET_METHOD(exports, "alSourceUnqueueBuffers", alSourceUnqueueBuffers_Callback);
  NAPI_SET_METHOD(exports, "alDeleteSources", alDeleteSources_Callback);
  NAPI_SET_METHOD(exports, "alDeleteBuffers", alDeleteBuffers_Callback);
  NAPI_SET_METHOD(exports, "alcDestroyContext", alcDestroyContext_Callback);
  NAPI_SET_METHOD(exports, "alcCloseDevice", alcCloseDevice_Callback);
  NAPI_SET_METHOD(exports, "alFillData", alFillData_Callback);

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)