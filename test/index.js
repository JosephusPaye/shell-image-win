const fs = require('fs');
const path = require('path');
const { test } = require('tape-modern');

const shellImageWin = require('../index');

const { getImageForPath, flags } = shellImageWin;

test('it extracts the image for a special shell path', async t => {
    const expectedImageBuffer = fs.readFileSync(path.join(__dirname, 'control-panel.png'));
    const imageBuffer = await getImageForPath('shell:ControlPanelFolder', {
        width: 256,
        height: 256,
        flags: flags.BiggerSizeOk,
    });

    t.ok(expectedImageBuffer.equals(imageBuffer), 'extracted image matches expected image');
});

test('it extracts the default OS file icon for files without an icon', async t => {
    const expectedImageBuffer = fs.readFileSync(path.join(__dirname, 'default.png'));
    const imageBuffer = await getImageForPath(path.resolve(__dirname, 'file-a'), {
        width: 256,
        height: 256,
        flags: flags.BiggerSizeOk,
    });

    t.ok(expectedImageBuffer.equals(imageBuffer), 'extracted image matches expected image');
});
