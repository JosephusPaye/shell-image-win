const { writeFileSync } = require('fs');
const mod = require('./index');
// { getIconForPath, ICON_SIZE_LARGE }

console.log(mod);

mod.getIconForPath('C:\\code\\ww.docx', 100, 100, (err, result) => {
    if (err) {
        console.error(err);
        return;
    }

    writeFileSync('icon.png', result);
});
