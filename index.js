const addon = require('bindings')('addon');

module.exports = {
    getIconForPath: addon.getIconForPath,
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
