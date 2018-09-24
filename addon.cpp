#include "file_icon.h"

NAN_METHOD(getIconForPath) {
    if (info.Length() < 5) {
        Nan::ThrowTypeError("Invalid number of arguments: expected 5 arguments");
        return;
    }

    if (!info[0]->IsString()) {
        Nan::ThrowTypeError("Invalid argument 'path': expected String");
        return;
    }

    if (!info[1]->IsNumber()) {
        Nan::ThrowTypeError("Invalid argument 'width': expected Number");
        return;
    }

    if (!info[2]->IsNumber()) {
        Nan::ThrowTypeError("Invalid argument 'height': expected Number");
        return;
    }

    if (!info[3]->IsNumber()) {
        Nan::ThrowTypeError("Invalid argument 'flags': expected Number");
        return;
    }

    if (!info[4]->IsFunction()) {
        Nan::ThrowTypeError("Invalid argument 'callback': expected Function");
        return;
    }

    v8::String::Utf8Value path{info[0]->ToString()};
    auto width = static_cast<uint32_t>(info[1]->Int32Value());
    auto height = static_cast<uint32_t>(info[2]->Int32Value());
    auto flags = static_cast<uint32_t>(info[3]->Int32Value());
    auto callback = new Nan::Callback(info[4].As<v8::Function>());

    Nan::AsyncQueueWorker(new FileIconAsyncWorker(*path, width, height, flags, callback));
}

NAN_MODULE_INIT(init) {
    NAN_EXPORT(target, getIconForPath);

    Nan::Set(
        target,
        Nan::New("ResizeToFit").ToLocalChecked(),
        Nan::New(static_cast<uint32_t>(SIIGBF_RESIZETOFIT))
    );

    Nan::Set(
        target,
        Nan::New("BiggerSizeOk").ToLocalChecked(),
        Nan::New(static_cast<uint32_t>(SIIGBF_BIGGERSIZEOK))
    );

    Nan::Set(
        target,
        Nan::New("MemoryOnly").ToLocalChecked(),
        Nan::New(static_cast<uint32_t>(SIIGBF_MEMORYONLY))
    );

    Nan::Set(
        target,
        Nan::New("IconOnly").ToLocalChecked(),
        Nan::New(static_cast<uint32_t>(SIIGBF_ICONONLY))
    );

    Nan::Set(
        target,
        Nan::New("ThumbnailOnly").ToLocalChecked(),
        Nan::New(static_cast<uint32_t>(SIIGBF_THUMBNAILONLY))
    );

    Nan::Set(
        target,
        Nan::New("InCacheOnly").ToLocalChecked(),
        Nan::New(static_cast<uint32_t>(SIIGBF_INCACHEONLY))
    );

    Nan::Set(
        target,
        Nan::New("CropToSquare").ToLocalChecked(),
        Nan::New(static_cast<uint32_t>(SIIGBF_CROPTOSQUARE))
    );

    Nan::Set(
        target,
        Nan::New("WideThumbnails").ToLocalChecked(),
        Nan::New(static_cast<uint32_t>(SIIGBF_WIDETHUMBNAILS))
    );

    Nan::Set(
        target,
        Nan::New("IconBackground").ToLocalChecked(),
        Nan::New(static_cast<uint32_t>(SIIGBF_ICONBACKGROUND))
    );

    Nan::Set(
        target,
        Nan::New("ScaleUp").ToLocalChecked(),
        Nan::New(static_cast<uint32_t>(SIIGBF_SCALEUP))
    );
}

NODE_MODULE(file_icon, init);
