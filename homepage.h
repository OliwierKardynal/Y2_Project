#pragma once

String homePagePart1 = F(R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<meta http-equiv="refresh" content="5">

<title>Smart Environmental Monitoring System</title>

<style>
:root {
  --bg: #0f172a;
  --panel: #111c34;
  --text: #e5e7eb;
  --muted: #9ca3af;
  --line: rgba(255,255,255,.10);
  --good: #22c55e;
  --moderate: #f59e0b;
  --poor: #fb923c;
  --danger: #ef4444;
}

* {
  box-sizing: border-box;
}

body {
  margin: 0;
  font-family: Arial, sans-serif;
  background: var(--bg);
  color: var(--text);
}

.wrap {
  max-width: 920px;
  margin: 0 auto;
  padding: 20px 14px 40px;
}

header {
  padding: 16px;
  border: 1px solid var(--line);
  border-radius: 12px;
  margin-bottom: 14px;
  background: rgba(255,255,255,.03);
}

h1 {
  margin: 0;
  font-size: 32px;
  font-weight: 600;
}

.sub {
  margin: 6px 0 0;
  font-size: 18px;
  color: var(--muted);
}

.card {
  border: 1px solid var(--line);
  border-radius: 12px;
  overflow: hidden;
  background: rgba(255,255,255,.03);
}

.card h2 {
  margin: 0;
  padding: 12px 14px;
  font-size: 20px;
  border-bottom: 1px solid var(--line);
  font-weight: 600;
  color: var(--muted);
}

.content {
  padding: 10px 14px 14px;
}

table {
  width: 100%;
  border-collapse: collapse;
  font-size: 20px;
}

th, td {
  padding: 10px 8px;
  border-bottom: 1px solid var(--line);
}

th {
  text-align: left;
  font-weight: 600;
  color: var(--muted);
  font-size: 18px;
}

td:nth-child(2) {
  text-align: right;
  font-variant-numeric: tabular-nums;
  font-weight: 600;
}

td:nth-child(3) {
  text-align: right;
  color: var(--muted);
  white-space: nowrap;
}

tr:last-child td {
  border-bottom: none;
}

.note {
  margin-top: 10px;
  padding: 8px 10px;
  font-size: 16px;
  color: var(--muted);
  border: 1px dashed var(--line);
  border-radius: 8px;
}

.aq-wrap {
  display: flex;
  align-items: center;
  justify-content: flex-end;
  gap: 10px;
}

.aq-num {
  min-width: 70px;
  text-align: right;
  font-weight: 700;
}

.aq-bar {
  width: 12px;
  height: 28px;
  border: 1px solid rgba(255,255,255,.25);
  background: rgba(255,255,255,.06);
  border-radius: 4px;
  overflow: hidden;
  position: relative;
}

.aq-fill {
  position: absolute;
  bottom: 0;
  left: 0;
  width: 100%;
}

.aq-good { background: var(--good); }
.aq-moderate { background: var(--moderate); }
.aq-poor { background: var(--poor); }
.aq-dangerous { background: var(--danger); }
</style>
</head>

<body>
  <div class="wrap">
    <header>
      <h1>Smart Environmental Monitoring System</h1>
      <p class="sub">Live temperature, humidity, pressure, altitude and air quality</p>
    </header>

    <section class="card">
      <h2>Sensor Data</h2>
      <div class="content">
        <table>
          <thead>
            <tr>
              <th>Sensor</th>
              <th>Value</th>
              <th>Unit / Status</th>
            </tr>
          </thead>
          <tbody>
)=====");

String homePagePart2 = F(R"=====(
          </tbody>
        </table>

        <div class="note">
          Air quality thresholds (MQ135 ADC):
          Good ≤1000 · Moderate 1001–1600 · Poor 1601–2400 · Dangerous &gt;2400
        </div>
      </div>
    </section>
  </div>
</body>
</html>
)=====");