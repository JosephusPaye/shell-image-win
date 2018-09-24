#include <nan.h>
#include <string>
#include <windows.h>
#include <shobjidl.h>
#include <cstddef>
#include <cwchar>
#include <memory>
#include <algorithm>

enum class IconSize {
    ExtraSmall,
    Small,
    Medium,
    Large,
    ExtraLarge
};

class SystemIconAsyncWorker : public Nan::AsyncWorker {
    public:
        SystemIconAsyncWorker(const char* name, int width, int height, uint32_t flags, Nan::Callback* callback):
            Nan::AsyncWorker{callback}, name{ name }, width{ width }, height{ height }, flags{ flags } {}
        void Execute() override;

    protected:
        void HandleOKCallback() override {
            if (!this->result.empty()) {
                v8::Local<v8::Value> argv[] = {
                    Nan::Null(),
                    Nan::CopyBuffer(
                        static_cast<char*>(static_cast<void*>(this->result.data())),
                        this->result.size()
                    ).ToLocalChecked(),
                };

                callback->Call(2, argv);
            } else {
                v8::Local<v8::Value> argv[] = {Nan::Error("Failed to load icon")};
                callback->Call(1, argv);
            }
        }

    private:
        std::string name;
        int width;
        int height;
        uint32_t flags;
        std::vector<unsigned char> result;
};
