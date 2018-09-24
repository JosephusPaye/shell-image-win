#include "system_icon.hpp"

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
    auto width = static_cast<int>(info[1]->Int32Value());
    auto height = static_cast<int>(info[2]->Int32Value());
    auto flags = static_cast<uint32_t>(info[3]->Int32Value());
    auto callback = new Nan::Callback(info[4].As<v8::Function>());

    Nan::AsyncQueueWorker(new SystemIconAsyncWorker(*path, width, height, flags, callback));
}

NAN_MODULE_INIT(init) {
    NAN_EXPORT(target, getIconForPath);

    Nan::Set(
        target,
        Nan::New("RESIZETOFIT").ToLocalChecked(),
        Nan::New(static_cast<int>(SIIGBF_RESIZETOFIT))
    );

    Nan::Set(
        target,
        Nan::New("BIGGERSIZEOK").ToLocalChecked(),
        Nan::New(static_cast<int>(SIIGBF_BIGGERSIZEOK))
    );

    Nan::Set(
        target,
        Nan::New("MEMORYONLY").ToLocalChecked(),
        Nan::New(static_cast<int>(SIIGBF_MEMORYONLY))
    );

    Nan::Set(
        target,
        Nan::New("ICONONLY").ToLocalChecked(),
        Nan::New(static_cast<int>(SIIGBF_ICONONLY))
    );

    Nan::Set(
        target,
        Nan::New("THUMBNAILONLY").ToLocalChecked(),
        Nan::New(static_cast<int>(SIIGBF_THUMBNAILONLY))
    );

    Nan::Set(
        target,
        Nan::New("INCACHEONLY").ToLocalChecked(),
        Nan::New(static_cast<int>(SIIGBF_INCACHEONLY))
    );

    Nan::Set(
        target,
        Nan::New("CROPTOSQUARE").ToLocalChecked(),
        Nan::New(static_cast<int>(SIIGBF_CROPTOSQUARE))
    );

    Nan::Set(
        target,
        Nan::New("WIDETHUMBNAILS").ToLocalChecked(),
        Nan::New(static_cast<int>(SIIGBF_WIDETHUMBNAILS))
    );

    Nan::Set(
        target,
        Nan::New("ICONBACKGROUND").ToLocalChecked(),
        Nan::New(static_cast<int>(SIIGBF_ICONBACKGROUND))
    );

    Nan::Set(
        target,
        Nan::New("SCALEUP").ToLocalChecked(),
        Nan::New(static_cast<int>(SIIGBF_SCALEUP))
    );
}

NODE_MODULE(system_icon, init);
