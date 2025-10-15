#pragma once
#include <Arduino.h>

const char MAIN_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="vi">
<head>
<meta charset="UTF-8">
<title>Tủ Thuốc Dashboard</title>
<style>
  body {
    margin:0;
    padding:0;
    font-family:"Segoe UI",sans-serif;
    background:#f5f6fa;
    display:flex;
    flex-direction:column;
    align-items:center;
    justify-content:flex-start;
    min-height:100vh;
  }
  h1 { margin:20px 0 10px 0; font-size:36px; color:#2f3640; }
  .status {
    font-size:22px; margin-bottom:20px; padding:10px 20px;
    border-radius:8px; background:#dcdde1; color:#2f3640;
    min-width:200px; text-align:center;
  }
  .row {
    display:flex; justify-content:center; gap:20px; width:90%; flex-wrap:wrap;
  }
  .card {
    background:#ffffff; flex:0 0 300px; padding:20px; border-radius:12px;
    box-shadow:0 4px 10px rgba(0,0,0,0.1);
  }
  .card h3 { margin-top:0; color:#273c75; }
  .card input, .card select {
    width:100%; padding:8px; font-size:16px; margin:8px 0;
    border-radius:6px; border:1px solid #dcdde1;
  }
  .card button {
    padding:10px 20px; font-size:16px; margin-top:10px;
    background:#44bd32; color:white; border:none; border-radius:6px;
    cursor:pointer;
  }
  .card button:hover { background:#4cd137; }
  #saved { margin-top:15px; font-size:18px; color:#0097e6; text-align:center; }
</style>
<script>
  function updateTime(){
    fetch('/time')
      .then(r => r.json())
      .then(data => {
        document.getElementById('time').innerText = data.time;
        document.getElementById('morning_display').innerText =
          "Sáng: " + data.morning + " (Ngăn " + data.drawer_morning + ")";
        document.getElementById('noon_display').innerText =
          "Trưa: " + data.noon + " (Ngăn " + data.drawer_noon + ")";
        document.getElementById('evening_display').innerText =
          "Tối: " + data.evening + " (Ngăn " + data.drawer_evening + ")";
        document.getElementById('drug_status').innerText = "Trạng thái: " + data.status;
        
        if (data.status.includes("Đến giờ")) {
          document.getElementById('drug_status').style.background = "#44bd32";
          document.getElementById('drug_status').style.color = "white";
        } else {
          document.getElementById('drug_status').style.background = "#dcdde1";
          document.getElementById('drug_status').style.color = "#2f3640";
        }
      });
  }
  setInterval(updateTime, 1000);

  function saveRealTime(){
    let real_time = document.getElementById("real_time").value;
    fetch(`/saveReal?real=${real_time}`)
    .then(r=>r.text()).then(msg=>{
      document.getElementById("saved").innerText = msg;
    });
  }

  // Lưu giờ hẹn từng buổi
  function saveMorning(){
    let t = document.getElementById("morning").value;
    let d = document.getElementById("drawer_select_morning").value;
    fetch(`/saveMorning?morning=${t}&drawer=${d}`)
    .then(r=>r.text()).then(msg=>{
      document.getElementById("saved").innerText = msg;
    });
  }

  function saveNoon(){
    let t = document.getElementById("noon").value;
    let d = document.getElementById("drawer_select_noon").value;
    fetch(`/saveNoon?noon=${t}&drawer=${d}`)
    .then(r=>r.text()).then(msg=>{
      document.getElementById("saved").innerText = msg;
    });
  }

  function saveEvening(){
    let t = document.getElementById("evening").value;
    let d = document.getElementById("drawer_select_evening").value;
    fetch(`/saveEvening?evening=${t}&drawer=${d}`)
    .then(r=>r.text()).then(msg=>{
      document.getElementById("saved").innerText = msg;
    });
  }
</script>
</head>
<body>
  <h1 id="time">--:--:--</h1>
  <div class="status" id="drug_status">Trạng thái: Chưa uống</div>

  <div class="row">
    <div class="card" style="text-align:center;">
      <h3>Giờ hẹn hiện tại</h3>
      <div id="morning_display">Sáng: --:--</div>
      <div id="noon_display">Trưa: --:--</div>
      <div id="evening_display">Tối: --:--</div>
    </div>

    <div class="card">
      <h3>Cài đặt giờ thực tế</h3>
      <input type="time" id="real_time">
      <button onclick="saveRealTime()">Lưu giờ thực tế</button>
    </div>

    <div class="card">
      <h3>Hẹn giờ uống thuốc</h3>
      <b>Sáng:</b><br>
      <input type="time" id="morning"><br>
      Ngăn:
      <select id="drawer_select_morning">
        <option value="1">Ngăn 1</option>
        <option value="2">Ngăn 2</option>
      </select><br>
      <button onclick="saveMorning()">Lưu giờ sáng</button><br><br>

      <b>Trưa:</b><br>
      <input type="time" id="noon"><br>
      Ngăn:
      <select id="drawer_select_noon">
        <option value="1">Ngăn 1</option>
        <option value="2">Ngăn 2</option>
      </select><br>
      <button onclick="saveNoon()">Lưu giờ trưa</button><br><br>

      <b>Tối:</b><br>
      <input type="time" id="evening"><br>
      Ngăn:
      <select id="drawer_select_evening">
        <option value="1">Ngăn 1</option>
        <option value="2">Ngăn 2</option>
      </select><br>
      <button onclick="saveEvening()">Lưu giờ tối</button>
    </div>
  </div>
  <div id="saved"></div>
</body>
</html>
)rawliteral";
