const { writeFileSync } = require('fs');
const fileIconWin = require('./index');

console.log(fileIconWin);

fileIconWin.getIconForPath('shell:Profile', 512, 512, fileIconWin.flags.IconBackground, (err, result) => {
    if (err) {
        console.error(err);
        return;
    }

    writeFileSync('icon.png', result);
});
