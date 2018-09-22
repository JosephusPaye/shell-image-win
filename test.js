const {writeFileSync} = require('fs');

const {
  getIconForPath,
  ICON_SIZE_MEDIUM,
  ICON_SIZE_LARGE,
} = require('./index');

getIconForPath("C:\\code\\Postman.lnk", ICON_SIZE_LARGE, (err, result) => {
  if (err) {
    console.error(err);
  } else {
    writeFileSync("icon.png", result);
  }
});
