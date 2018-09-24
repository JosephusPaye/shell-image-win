# shell-image-win

Get the associated shell image for a given path on Windows, as a PNG buffer.

The shell image is the icon or thumbnail that Windows Explorer would display for the item, as extracted by [IShellItemImageFactory::GetImage](https://docs.microsoft.com/en-us/windows/desktop/api/shobjidl_core/nf-shobjidl_core-ishellitemimagefactory-getimage).

Requires Windows Vista or higher.

## Installation

```bash
npm install JosephusPaye/shell-image-win --save
```

## Usage

```js
const { writeFileSync } = require('fs');
const { getImageForPath, flags } = require('shell-image-win');

getImageForPath('C:\\', 256, 256, flags.ResizeToFit | flags.IconBackground, (err, imageBuffer) => {
    if (err) {
        console.error(err);
        return;
    }

    writeFileSync('image.png', imageBuffer);
});
```

## API

### `getImageForPath(path, options, callback)`

Get the associated shell image for a given path.

#### `path`: String

An absolute file system path or special `shell:` path. See [here](https://www.howtogeek.com/257715/how-to-open-hidden-system-folders-with-windos-shell-command/) for a list of special shell paths.

#### `options`: Object

Configuration options.

#### `options.width`: Number

The width of the image. Default is `256`.

#### `options.height`: Number

The height of the image. Default is `256`.

#### `options.flags`: Number

One or more of the following flags. Combine more than one flag with `|`, the [bitwise OR operator](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/Bitwise_Operators#Bitwise_OR).

- [`ResizeToFit`](https://docs.microsoft.com/en-us/windows/desktop/api/shobjidl_core/nf-shobjidl_core-ishellitemimagefactory-getimage#siigbf_resizetofit-0x00000000)
- [`BiggerSizeOk`](https://docs.microsoft.com/en-us/windows/desktop/api/shobjidl_core/nf-shobjidl_core-ishellitemimagefactory-getimage#siigbf_biggersizeok-0x00000001)
- [`MemoryOnly`](https://docs.microsoft.com/en-us/windows/desktop/api/shobjidl_core/nf-shobjidl_core-ishellitemimagefactory-getimage#siigbf_memoryonly-0x00000002)
- [`IconOnly`](https://docs.microsoft.com/en-us/windows/desktop/api/shobjidl_core/nf-shobjidl_core-ishellitemimagefactory-getimage#siigbf_icononly-0x00000004)
- [`ThumbnailOnly`](https://docs.microsoft.com/en-us/windows/desktop/api/shobjidl_core/nf-shobjidl_core-ishellitemimagefactory-getimage#siigbf_thumbnailonly-0x00000008)
- [`InCacheOnly`](https://docs.microsoft.com/en-us/windows/desktop/api/shobjidl_core/nf-shobjidl_core-ishellitemimagefactory-getimage#siigbf_incacheonly-0x00000010)
- [`CropToSquare`](https://docs.microsoft.com/en-us/windows/desktop/api/shobjidl_core/nf-shobjidl_core-ishellitemimagefactory-getimage#siigbf_croptosquare-0x00000020)
- [`WideThumbnails`](https://docs.microsoft.com/en-us/windows/desktop/api/shobjidl_core/nf-shobjidl_core-ishellitemimagefactory-getimage#siigbf_widethumbnails-0x00000040)
- [`IconBackground`](https://docs.microsoft.com/en-us/windows/desktop/api/shobjidl_core/nf-shobjidl_core-ishellitemimagefactory-getimage#siigbf_iconbackground-0x00000080)
- [`ScaleUp`](https://docs.microsoft.com/en-us/windows/desktop/api/shobjidl_core/nf-shobjidl_core-ishellitemimagefactory-getimage#siigbf_scaleup-0x00000100)

The flag constants are available on the module at `.flags`.

#### `callback(error, imageBuffer)`: Function

The function to call when the image is retrieved. `callback` is called with the following arguments:

- `error`: an error message if the function failed, `null` otherwise
- `imageBuffer`: a PNG buffer of the image retrieved

## Credits

A lot of the code here was adapted from [node-system-icon](https://github.com/mtojo/node-system-icon) by [@mtojo](https://github.com/mtojo).

## Related

- [file-icon](https://github.com/sindresorhus/file-icon) (macOS only)
- [node-system-icon](https://github.com/mtojo/node-system-icon) (Windows and macOS)

## Licence

[MIT](LICENCE), © 2018 Josephus Paye II
