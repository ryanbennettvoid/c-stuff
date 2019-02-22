
const fs = require('fs');

const randomString = () => Math.random().toString(36).substring(7);
const randomNumber = () => Math.random() * 100;
const count = 1000;

let str = '';

for (let i = 0; i < count; i++) {
  const name = randomString();
  const x = randomNumber();
  const y = randomNumber();
  const z = randomNumber();
  const line = `${name},${x},${y},${z}`;
  str += line + '\n';
}

fs.writeFileSync('./data.txt', str);
