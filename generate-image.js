const fs = require('fs');
const path = require('path');
const shellImageWin = require('./index');

console.log(shellImageWin);
const { getImageForPath, flags } = shellImageWin;

getImageForPath(__dirname, { width: 256, height: 256, flags: flags.IconBackground }, (err, imageBuffer) => {
    if (err) {
        console.error(err);
        return;
    }

    fs.writeFileSync('image.png', imageBuffer);
});
