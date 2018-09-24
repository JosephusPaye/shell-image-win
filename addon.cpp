#include "system_icon.hpp"
#include <nan.h>

NAN_METHOD(getIconForPath) {
    if (info.Length() < 2) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }

    if (!info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowTypeError("Wrong arguments");
        return;
    }

    v8::String::Utf8Value path{info[0]->ToString()};
    // auto size = static_cast<IconSize>(info[1]->Int32Value());
    auto callback = new Nan::Callback(info[1].As<v8::Function>());

    Nan::AsyncQueueWorker(new SystemIconAsyncWorker(*path, callback));
}

NAN_MODULE_INIT(init) {
    NAN_EXPORT(target, getIconForPath);

    // Nan::Set(
    //     target,
    //     Nan::New("ICON_SIZE_EXTRA_SMALL").ToLocalChecked(),
    //     Nan::New(static_cast<int>(IconSize::ExtraSmall))
    // );

    // Nan::Set(
    //     target,
    //     Nan::New("ICON_SIZE_SMALL").ToLocalChecked(),
    //     Nan::New(static_cast<int>(IconSize::Small))
    // );

    // Nan::Set(
    //     target,
    //     Nan::New("ICON_SIZE_MEDIUM").ToLocalChecked(),
    //     Nan::New(static_cast<int>(IconSize::Medium))
    // );

    // Nan::Set(
    //     target,
    //     Nan::New("ICON_SIZE_LARGE").ToLocalChecked(),
    //     Nan::New(static_cast<int>(IconSize::Large))
    // );

    // Nan::Set(
    //     target,
    //     Nan::New("ICON_SIZE_EXTRA_LARGE").ToLocalChecked(),
    //     Nan::New(static_cast<int>(IconSize::ExtraLarge))
    // );
}

NODE_MODULE(system_icon, init);
