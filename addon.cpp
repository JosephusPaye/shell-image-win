#include "get_shell_image.h"
#include <napi.h>

// The async worker that calls the GetImageForPath() to get the image
class GetShellImageWorker : public Napi::AsyncWorker {
private:
  std::string filePath;
  uint32_t width;
  uint32_t height;
  uint32_t flags;
  std::vector<unsigned char> result;

public:
  // The constructor: sets the callback and arguments for GetImageForPath()
  GetShellImageWorker(Napi::Function &callback, std::string filePath,
                      uint32_t width, uint32_t height, uint32_t flags)
      : Napi::AsyncWorker{callback}, filePath{filePath}, width{width},
        height{height}, flags{flags} {}

  // Empty destructor
  ~GetShellImageWorker() {}

  // Execute the async task: get the image for the given path and set the result
  void Execute() override {
    this->result =
        GetImageForPath(this->filePath, this->width, this->height, this->flags);
  }

  // OK callback, called when Execute() is ran successfully.
  // This checks the result and calls the user's JS callback with the image
  // buffer or an error.
  void OnOK() override {
    Napi::HandleScope scope(Env());

    // Check that the extracted image buffer is not empty
    if (!this->result.empty()) {
      // The first argument to the callback is null (for no error)
      // The second argument to the callback is the image buffer
      Callback().Call(
          {Env().Null(),
           Napi::Buffer<char>::Copy(
               Env(),
               static_cast<char *>(static_cast<void *>(this->result.data())),
               this->result.size())});
    } else {
      // Call the callback with one argument: the error
      Callback().Call({Napi::String::New(Env(), "Failed to load image")});
    }
  }
};

// This method wraps the GetImageForPath() method for Node, via N-API, using an
// AsyncWorker
Napi::Value Method(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (info.Length() < 5) {
    Napi::TypeError::New(env,
                         "Invalid number of arguments: expected 5 arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsString()) {
    Napi::TypeError::New(env, "Invalid argument 'path': expected String")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "Invalid argument 'width': expected Number")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[2].IsNumber()) {
    Napi::TypeError::New(env, "Invalid argument 'height': expected Number")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[3].IsNumber()) {
    Napi::TypeError::New(env, "Invalid argument 'flags': expected Number")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[4].IsFunction()) {
    Napi::TypeError::New(env, "Invalid argument 'callback': expected Function")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  // Get the arguments
  std::string path = info[0].As<Napi::String>().Utf8Value();
  uint32_t width = info[1].As<Napi::Number>().Uint32Value();
  uint32_t height = info[2].As<Napi::Number>().Uint32Value();
  uint32_t flags = info[3].As<Napi::Number>().Uint32Value();
  Napi::Function callback = info[4].As<Napi::Function>();

  // Create the async worker and queue the task.
  // This will call Execute() on GetShellImageWorker when a thread is available
  // to run the task.
  GetShellImageWorker *worker =
      new GetShellImageWorker(callback, path, width, height, flags);
  worker->Queue();

  // Return undefined, the result is returned using the callback
  return info.Env().Undefined();
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  // Export the getImageForPath() method
  exports.Set(Napi::String::New(env, "getImageForPath"),
              Napi::Function::New(env, Method));

  // Export the ResizeToFit constant
  exports.Set(
      Napi::String::New(env, "ResizeToFit"),
      Napi::Number::New(env, static_cast<uint32_t>(SIIGBF_RESIZETOFIT)));

  // Export the BiggerSizeOk constant
  exports.Set(
      Napi::String::New(env, "BiggerSizeOk"),
      Napi::Number::New(env, static_cast<uint32_t>(SIIGBF_BIGGERSIZEOK)));

  // Export the MemoryOnly constant
  exports.Set(Napi::String::New(env, "MemoryOnly"),
              Napi::Number::New(env, static_cast<uint32_t>(SIIGBF_MEMORYONLY)));

  // Export the IconOnly constant
  exports.Set(Napi::String::New(env, "IconOnly"),
              Napi::Number::New(env, static_cast<uint32_t>(SIIGBF_ICONONLY)));

  // Export the ThumbnailOnly constant
  exports.Set(
      Napi::String::New(env, "ThumbnailOnly"),
      Napi::Number::New(env, static_cast<uint32_t>(SIIGBF_THUMBNAILONLY)));

  // Export the InCacheOnly constant
  exports.Set(
      Napi::String::New(env, "InCacheOnly"),
      Napi::Number::New(env, static_cast<uint32_t>(SIIGBF_INCACHEONLY)));

  // Export the CropToSquare constant
  exports.Set(
      // Export the CropToSquare constant
      Napi::String::New(env, "CropToSquare"),
      Napi::Number::New(env, static_cast<uint32_t>(SIIGBF_CROPTOSQUARE)));

  // Export the WideThumbnails constant
  exports.Set(
      Napi::String::New(env, "WideThumbnails"),
      Napi::Number::New(env, static_cast<uint32_t>(SIIGBF_WIDETHUMBNAILS)));

  // Export the IconBackground constant
  exports.Set(
      Napi::String::New(env, "IconBackground"),
      Napi::Number::New(env, static_cast<uint32_t>(SIIGBF_ICONBACKGROUND)));

  // Export the ScaleUp constant
  exports.Set(Napi::String::New(env, "ScaleUp"),
              Napi::Number::New(env, static_cast<uint32_t>(SIIGBF_SCALEUP)));

  return exports;
}

NODE_API_MODULE(addon, Init)
