const fs = require('fs').promises;
const path = 'z4.txt';

fs.readFile(path, 'utf8')
  .then((data) => {
    console.log('data:', data);
  })
  .catch((err) => {
    console.error('error:', err);
  });