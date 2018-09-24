const { writeFileSync } = require('fs');
const mod = require('./index');
// { getIconForPath, ICON_SIZE_LARGE }

console.log(mod);

mod.getIconForPath('C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Excel.lnk', 256, 256, mod.ICONBACKGROUND, (err, result) => {
    if (err) {
        console.error(err);
        return;
    }

    writeFileSync('icon.png', result);
});
