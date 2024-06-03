const showWater = document.getElementById('total');
const readWater = document.getElementById('reading');
const water = 99;
readWater.textContent = `${water}%`
const Level = 100 - water
showWater.style.height = Level * 5 + "px"