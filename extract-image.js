const fs = require('fs');
const path = require('path');
const shellImageWin = require('./index');

const { getImageForPath } = shellImageWin;
const arg = process.argv[2];

if (arg) {
    getImageForPath(arg, { width: 512, height: 512 }, (err, imageBuffer) => {
        if (err) {
            console.error(err);
            return;
        }

        fs.writeFileSync('image.png', imageBuffer);

        console.log(`Image extracted to ${path.join(__dirname, 'image.png')}\n`);
    });
} else {
    console.log('Usage: npm run extract <path>\n<path> should be an absolute Windows-style path');
}
