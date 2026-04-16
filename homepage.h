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
  padding: 14px;
}

/* ── Stat cards grid ── */
.stat-grid {
  display: grid;
  grid-template-columns: 1fr 1fr;
  gap: 10px;
  margin-bottom: 10px;
}

.stat-card {
  border: 1px solid var(--line);
  border-radius: 10px;
  padding: 16px 12px 14px;
  background: rgba(255,255,255,.03);
  display: flex;
  flex-direction: column;
  align-items: center;
  text-align: center;
}

.stat-label {
  font-size: 13px;
  color: var(--muted);
  font-weight: 600;
  text-transform: uppercase;
  letter-spacing: .06em;
  margin-bottom: 8px;
}

.stat-value {
  font-size: 42px;
  font-weight: 700;
  font-variant-numeric: tabular-nums;
  line-height: 1;
  margin-bottom: 4px;
}

.stat-unit {
  font-size: 15px;
  color: var(--muted);
}

/* ── Air quality block ── */
.aq-section {
  border: 1px solid var(--line);
  border-radius: 10px;
  padding: 14px 16px 16px;
  background: rgba(255,255,255,.03);
}

.aq-top {
  display: flex;
  align-items: center;
  justify-content: space-between;
  margin-bottom: 6px;
}

.aq-label-text {
  font-size: 13px;
  color: var(--muted);
  font-weight: 600;
  text-transform: uppercase;
  letter-spacing: .06em;
}

.aq-badge {
  padding: 3px 11px;
  border-radius: 20px;
  font-size: 13px;
  font-weight: 600;
}

.aq-badge.aq-good      { background: rgba(34,197,94,.18);  color: var(--good); }
.aq-badge.aq-moderate  { background: rgba(245,158,11,.18); color: var(--moderate); }
.aq-badge.aq-poor      { background: rgba(251,146,60,.18); color: var(--poor); }
.aq-badge.aq-dangerous { background: rgba(239,68,68,.18);  color: var(--danger); }

.aq-reading {
  font-size: 42px;
  font-weight: 700;
  font-variant-numeric: tabular-nums;
  line-height: 1;
  margin-bottom: 12px;
}

.aq-bar-h {
  width: 100%;
  height: 10px;
  background: rgba(255,255,255,.08);
  border-radius: 5px;
  overflow: hidden;
}

.aq-fill-h {
  height: 100%;
  border-radius: 5px;
}

.aq-fill-h.aq-good      { background: var(--good); }
.aq-fill-h.aq-moderate  { background: var(--moderate); }
.aq-fill-h.aq-poor      { background: var(--poor); }
.aq-fill-h.aq-dangerous { background: var(--danger); }

/* ── Note ── */
.note {
  margin-top: 10px;
  padding: 8px 10px;
  font-size: 15px;
  color: var(--muted);
  border: 1px dashed var(--line);
  border-radius: 8px;
}
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
)=====");

String homePagePart2 = F(R"=====(
        <div class="note">
          Air quality thresholds (MQ135 ADC):
          Good &le;1000 &nbsp;&middot;&nbsp; Moderate 1001&ndash;1600 &nbsp;&middot;&nbsp; Poor 1601&ndash;2400 &nbsp;&middot;&nbsp; Dangerous &gt;2400
        </div>
      </div>
    </section>
  </div>
</body>
</html>
)=====");
