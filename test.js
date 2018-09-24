const { writeFileSync } = require('fs');
const shellImageWin = require('./index');

console.log(shellImageWin);
const { getImageForPath, flags } = shellImageWin;

getImageForPath('shell:Fonts', { width: 512, height: 512, flags: flags.IconBackground }, (err, imageBuffer) => {
    if (err) {
        console.error(err);
        return;
    }

    writeFileSync('image.png', imageBuffer);
});
