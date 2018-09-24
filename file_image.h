#include <nan.h>
#include <string>
#include <windows.h>
#include <shobjidl.h>
#include <cstddef>
#include <cwchar>
#include <memory>
#include <algorithm>

class FileImageAsyncWorker : public Nan::AsyncWorker {
    public:
        FileImageAsyncWorker(const char* name, uint32_t width, uint32_t height, uint32_t flags, Nan::Callback* callback)
            : Nan::AsyncWorker{callback}, name{ name }, width{ width }, height{ height }, flags{ flags }
        {
            // Empty constructor
        }

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
                v8::Local<v8::Value> argv[] = { Nan::Error("Failed to load image") };
                callback->Call(1, argv);
            }
        }

    private:
        std::string name;
        uint32_t width;
        uint32_t height;
        uint32_t flags;
        std::vector<unsigned char> result;
};
