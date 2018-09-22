const { writeFileSync } = require('fs');
const mod = require('./index');
// { getIconForPath, ICON_SIZE_LARGE }

console.log(mod);

mod.getIconForPath('C:\\code\\ww.docx', mod.ICON_SIZE_LARGE, (err, result) => {
    if (err) {
        console.error(err);
        return;
    }

    writeFileSync('icon.png', result);
});
