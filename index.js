const addon = require('bindings')('addon');

function getImageForPath(path, options = {}, callback) {
    options.width = options.width || 256;
    options.height = options.height || 256;
    options.flags = options.flags || addon.flags.BiggerSizeOk;

    if (callback === undefined) {
        return new Promise((resolve, reject) => {
            addon.getImageForPath(path, options.width, options.height, options.flags, (err, imageBuffer) => {
                if (err) {
                    reject(err);
                    return;
                }

                resolve(imageBuffer);
            });
        });
    } else {
        addon.getImageForPath(path, options.width, options.height, options.flags, callback);
    }
}

module.exports = {
    getImageForPath,
    flags: {
        ResizeToFit: addon.ResizeToFit,
        BiggerSizeOk: addon.BiggerSizeOk,
        MemoryOnly: addon.MemoryOnly,
        IconOnly: addon.IconOnly,
        ThumbnailOnly: addon.ThumbnailOnly,
        InCacheOnly: addon.InCacheOnly,
        CropToSquare: addon.CropToSquare,
        WideThumbnails: addon.WideThumbnails,
        IconBackground: addon.IconBackground,
        ScaleUp: addon.ScaleUp,
    },
    path: addon.path,
};
