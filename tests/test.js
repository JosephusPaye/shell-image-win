const fs = require('fs');
const path = require('path');
const { test } = require('uvu');
const assert = require('uvu/assert');

const { getImageForPath, flags } = require('..');

test('it extracts the image for a special shell path', async () => {
    const expectedImageBuffer = fs.readFileSync(path.join(__dirname, 'control-panel.png'));
    const imageBuffer = await getImageForPath('shell:ControlPanelFolder', {
        width: 256,
        height: 256,
        flags: flags.BiggerSizeOk,
    });

    assert.ok(expectedImageBuffer.equals(imageBuffer), 'extracted image matches expected image');
});

test('it extracts the default OS file icon for files without an icon', async () => {
    const expectedImageBuffer = fs.readFileSync(path.join(__dirname, 'default.png'));
    const imageBuffer = await getImageForPath(path.resolve(__dirname, 'sample-file'), {
        width: 256,
        height: 256,
        flags: flags.BiggerSizeOk,
    });

    assert.ok(expectedImageBuffer.equals(imageBuffer), 'extracted image matches expected image');
});

test.run();
