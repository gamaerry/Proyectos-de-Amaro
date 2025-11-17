import puppeteer from 'puppeteer';

const browser = await puppeteer.launch({headless: false});
const page = await browser.newPage();
await page.goto('https://sim.morelia.tecnm.mx/');
await page.setViewport();
await page.locator('#user').fill('matricula');
await page.locator('#pass').fill('contrasena');
await new Promise(r => setTimeout(r, 1000));
await page.locator('button.inline-block').click();
await new Promise(r => setTimeout(r, 1000));
await page.goto('https://sim.morelia.tecnm.mx/encuestas/evaluacion-docente');

// Encuentra todos los selects cuyos id empiezan con "ratings."
const selects = await page.$$(`[id^="ratings."]`);

// Función para esperar ENTER
const waitForEnter = () =>
  new Promise(resolve => {
    process.stdin.resume();
    process.stdin.once("data", () => resolve());
  });

// Bucle infinito controlado por ENTER
while (true) {
  console.log("\n👉 Presiona ENTER para ejecutar la selección...");
  await waitForEnter();
  console.log("Seleccionando value=\"1\" en todos los selects...");
  const selects = await page.$$('[id^="ratings."]');
  for (const select of selects) {
    await select.select("1");
  }
  console.log("✔️ Selección completada.\n");
}
