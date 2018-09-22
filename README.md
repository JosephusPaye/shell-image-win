# file-icon-win

Get the associated shell icon for a given path on Windows, as a PNG. Requires Vista or higher.

The shell icon is the icon or thumbnail that Windows Explorer would display for the item, as returned by [IShellItemImageFactory::GetImage](https://docs.microsoft.com/en-us/windows/desktop/api/shobjidl_core/nf-shobjidl_core-ishellitemimagefactory-getimage).

## Installation

```bash
npm install JosephusPaye/file-icon-win --save
```

## Usage

```js
const { writeFileSync } = require('fs');
const { getIconForPath, ICON_SIZE_LARGE } = require('file-icon-win');

getIconForPath('C:\\', ICON_SIZE_LARGE, (err, result) => {
    if (err) {
        console.error(err);
    }

    writeFileSync('icon.png', result);
});
```

## API

### Size constants

The correspondence between the size constants and the icon size actually obtainable on each platform is as follows:

| Constant                | Size    |
| ----------------------- | ------- |
| `ICON_SIZE_EXTRA_SMALL` |  16x16  |
| `ICON_SIZE_SMALL`       |  32x32  |
| `ICON_SIZE_MEDIUM`      |  64x64  |
| `ICON_SIZE_LARGE`       | 256x256 |
| `ICON_SIZE_EXTRA_LARGE` | 256x256 |

### getIconForPath(path, size, callback)

Gets the associated icon for the given file or folder path, and returns it as a buffer in PNG format.


## Credits

Most of the code here is adapted from [node-system-icon](https://github.com/mtojo/node-system-icon) by [@mtojo](https://github.com/mtojo).

It was simplified to remove macOS support and use [IShellItemImageFactory::GetImage](https://docs.microsoft.com/en-us/windows/desktop/api/shobjidl_core/nf-shobjidl_core-ishellitemimagefactory-getimage) instead of [SHGetImageList](https://docs.microsoft.com/en-us/windows/desktop/api/shellapi/nf-shellapi-shgetimagelist).

## Related

- [file-icon](https://github.com/sindresorhus/file-icon) (macOS only)
- [node-system-icon](https://github.com/mtojo/node-system-icon) (Windows and macOS)

## Licence

[MIT](LICENCE), © 2018 Josephus Paye II
