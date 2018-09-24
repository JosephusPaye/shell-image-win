#include "system_icon.hpp"

namespace Gdiplus {
    using std::max;
    using std::min;
}

#include <Gdiplus.h>

class ComInit {
    public:
        ComInit() {
            CoInitializeEx(0, COINIT_MULTITHREADED);
        }

        ~ComInit() {
            CoUninitialize();
        }

    private:
        ComInit(const ComInit&);
        ComInit& operator=(const ComInit&);
};

class GdiPlusInit {
    public:
        GdiPlusInit() {
            Gdiplus::GdiplusStartupInput startupInput;
            Gdiplus::GdiplusStartup(
                std::addressof(this->token),
                std::addressof(startupInput),
                nullptr
            );
        }

        ~GdiPlusInit() {
            Gdiplus::GdiplusShutdown(this->token);
        }

    private:
        GdiPlusInit(const GdiPlusInit&);
        GdiPlusInit& operator=(const GdiPlusInit&);
        ULONG_PTR token;
};

struct IStreamDeleter {
    void operator()(IStream* pStream) const {
        pStream->Release();
    }
};

std::wstring Utf8ToWide(const std::string& src) {
    const auto size = MultiByteToWideChar(CP_UTF8, 0u, src.data(), -1, nullptr, 0u);
    std::vector<wchar_t> dest(size, L'\0');

    if (
        MultiByteToWideChar(CP_UTF8, 0u, src.data(), -1, dest.data(), dest.size()) == 0
    ) {
        throw std::system_error{ static_cast<int>(GetLastError()), std::system_category() };
    }

    return std::wstring { dest.begin(), dest.end() };
}

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid) {
    UINT num = 0u;
    UINT size = 0u;

    Gdiplus::GetImageEncodersSize(std::addressof(num), std::addressof(size));

    if (size == 0u) {
        return -1;
    }

    std::unique_ptr<Gdiplus::ImageCodecInfo> pImageCodecInfo(
        static_cast<Gdiplus::ImageCodecInfo*>(static_cast<void*>(new BYTE[size]))
    );

    if (pImageCodecInfo == nullptr) {
        return -1;
    }

    GetImageEncoders(num, size, pImageCodecInfo.get());

    for (UINT i = 0u; i < num; i++) {
        if (std::wcscmp(pImageCodecInfo.get()[i].MimeType, format) == 0) {
            *pClsid = pImageCodecInfo.get()[i].Clsid;
            return i;
        }
    }

    return -1;
}

HBITMAP GetIconBitmapForPath(const std::string& name, uint32_t width, uint32_t height, uint32_t flags) {
    HBITMAP hbmp = NULL;
    PCWSTR errorMessage = NULL;

    IShellItemImageFactory *pImageFactory;
    HRESULT hr = SHCreateItemFromParsingName(Utf8ToWide(name).c_str(), NULL, IID_PPV_ARGS(&pImageFactory));

    if (SUCCEEDED(hr)) {
        SIZE size;
        size.cx = width;
        size.cy = height;

        hr = pImageFactory->GetImage(size, (SIIGBF) flags, &hbmp);

        if (FAILED(hr)) {
            errorMessage = L"IShellItemImageFactory::GetImage failed with error code %x";
        }

        pImageFactory->Release();
    } else {
        errorMessage = L"SHCreateItemFromParsingName failed with error %x";
    }

    // if (FAILED(hr)) {
    //     wprintf(errorMessage, hr);
    // }

    return hbmp;
}

std::unique_ptr<Gdiplus::Bitmap> CreateBitmapFromHBitmap(
    HBITMAP hBitmap,
    std::vector<std::int32_t>& buffer
) {
    BITMAP bm = { 0 };
    GetObject(hBitmap, sizeof(bm), std::addressof(bm));

    std::unique_ptr<Gdiplus::Bitmap> bitmap;

    if (bm.bmBitsPixel == 32) {
        auto hDC = GetDC(nullptr);

        BITMAPINFO bmi = { 0 };
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = bm.bmWidth;
        bmi.bmiHeader.biHeight = -bm.bmHeight;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;

        auto nBits = bm.bmWidth * bm.bmHeight;
        buffer.resize(nBits);

        GetDIBits(
            hDC, hBitmap, 0, bm.bmHeight,
            std::addressof(buffer[0]),
            std::addressof(bmi),
            DIB_RGB_COLORS
        );

        auto hasAlpha = false;

        for (std::int32_t i = 0; i < nBits; i++) {
            if ((buffer[i] & 0xFF000000) != 0) {
                hasAlpha = true;
                break;
            }
        }

        bitmap.reset(
            new Gdiplus::Bitmap(
                bm.bmWidth, bm.bmHeight, bm.bmWidth * sizeof(std::int32_t),
                PixelFormat32bppARGB,
                static_cast<BYTE*>(static_cast<void*>(std::addressof(buffer[0])))
            )
        );

        ReleaseDC(nullptr, hDC);
    } else {
        bitmap.reset(Gdiplus::Bitmap::FromHBITMAP(hBitmap, (HPALETTE) 0));
    }

    return bitmap;
}

std::vector<unsigned char> HBitmapToPNG(HBITMAP hBitmap) {
    GdiPlusInit init;

    std::vector<std::int32_t> buffer;
    auto bitmap = CreateBitmapFromHBitmap(hBitmap, buffer);

    CLSID encoder;
    if (GetEncoderClsid(L"image/png", std::addressof(encoder)) == -1) {
        return std::vector<unsigned char>{};
    }

    IStream* tmp;
    if (CreateStreamOnHGlobal(nullptr, TRUE, std::addressof(tmp)) != S_OK) {
        return std::vector<unsigned char>{};
    }

    std::unique_ptr<IStream, IStreamDeleter> pStream { tmp };

    if (bitmap->Save(pStream.get(), std::addressof(encoder), nullptr) != Gdiplus::Status::Ok) {
        return std::vector<unsigned char>{};
    }

    STATSTG stg = { 0 };
    LARGE_INTEGER offset = { 0 };

    if (pStream->Stat(std::addressof(stg), STATFLAG_NONAME) != S_OK || pStream->Seek(offset, STREAM_SEEK_SET, nullptr) != S_OK) {
        return std::vector<unsigned char>{};
    }

    std::vector<unsigned char> result(
        static_cast<std::size_t>(stg.cbSize.QuadPart)
    );

    ULONG ul;

    if (
        pStream->Read(
            std::addressof(result[0]),
            static_cast<ULONG>(stg.cbSize.QuadPart),
            std::addressof(ul)
        ) != S_OK
        || (stg.cbSize.QuadPart != ul)
    ) {
        return std::vector<unsigned char>{};
    }

    return result;
}

std::vector<unsigned char> GetIconForPath(const std::string& name, uint32_t width, uint32_t height, uint32_t flags) {
    ComInit init;

    HBITMAP hBitmap = GetIconBitmapForPath(name, width, height, flags);

    if (hBitmap == NULL) {
        return std::vector<unsigned char>{};
    }

    auto buffer = HBitmapToPNG(hBitmap);

    DeleteObject(hBitmap);

    return buffer;
}

void SystemIconAsyncWorker::Execute() {
    this->result = GetIconForPath(this->name, this->width, this->height, this->flags);
}
